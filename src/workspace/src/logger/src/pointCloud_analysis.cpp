#include <SbetProcessor.hpp>
#include <filesystem>
#include "../../../MBES-lib/src/Position.hpp"
#include "../../../MBES-lib/src/math/CoordinateTransform.hpp"

#include <iostream>
#include <fstream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
//#include <pcl/filters/crop_box.h>
#include <pcl/visualization/cloud_viewer.h>



class PointCloudAnalyz0r : public SbetProcessor{
	
	public:
		PointCloudAnalyz0r(std::string sbetFilePath, std::string pointCloudFilePath): sbetFilePath(sbetFilePath), pointCloudFilePath(pointCloudFilePath){}
		
		~PointCloudAnalyz0r(){}
		
		
		void processEntry(SbetEntry * entry){
			
			Position position(static_cast<uint64_t>(entry->time * 1000000), entry->latitude, entry->longitude, entry->altitude);
			
			this->sbetPositions.push_back(position);
		}
		
		
		void readPointCloud(){
			
			this->cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr (new pcl::PointCloud<pcl::PointXYZ>);
		
			std::ifstream file(this->pointCloudFilePath);
				
			if (file.is_open()) {
				std::string line;
				unsigned long int lineCount = 0;
				
				while (std::getline(file, line)) {
					lineCount++;
					std::istringstream iss(line);
    				float x,y,z;
    				
    				if(!(iss >> x >> y >> z)){
    					std::cerr<<"Error while reading point cloud file at line: "<< lineCount << std::endl;
    				}
    				else{
    					this->cloud->push_back(pcl::PointXYZ(x, y, z) );
    				}		
				}//end while
				
				file.close();
				this->kdtree.setInputCloud (cloud);
			}
			else{
				std::cerr<<"Invalid path for point cloud file." << std::endl;
			}
		}
		
		
		void readSbet(){
			readFile(this->sbetFilePath);
		}
		
		
		void read(){
			readPointCloud();
			readSbet();
			
			Position firstPos = this->sbetPositions.at(0);	
			
			double firstLat = firstPos.getLatitude();
			double firstLon = firstPos.getLongitude();
			
			setEcef2EnuMatrix(firstLat, firstLon);
			
			setFirstPositionEcef(firstPos);
			
			//std::cout<< "first pos ecef: "<<   this->firstPositionECEF<<"\n";
		}
		
		
		void setFirstPositionEcef(Position & firstPosition){
			CoordinateTransform::getPositionECEF(this->firstPositionECEF, firstPosition);
		}
		
		
		Eigen::Vector3d computeUnitVector(Position & position1, Position & position2){
			
			Eigen::Vector3d positionLGF1;
			position2lgf(positionLGF1, position1);
			
			Eigen::Vector3d positionLGF2;
			position2lgf(positionLGF2, position2);
			
			//std::cout<< "pos1: \n"<<positionLGF1<<"\n\n";
			//std::cout<< "pos2: \n"<<positionLGF2<<"\n\n";
			
			Eigen::Vector3d vector = positionLGF2 - positionLGF1;
			
			Eigen::Vector3d unitVector = vector / vector.norm(); //TODO 
			
			std::cout<<"unit vector: \n" << unitVector <<"\n\n";
			
			return unitVector;
		}
		
		
		void denoise(){
			
			for(long unsigned int i = 0; i < this->sbetPositions.size(); i=i+100){
				Position pos1 = this->sbetPositions.at(i);
				Position pos2 = this->sbetPositions.at(i+100); //TODO make step a param
				
				Eigen::Vector3d unitVector = computeUnitVector(pos1, pos2); 
				
				break;
				
			}
		}
		
		
		void done(){} // needed because of sbetprocessor base class
		
		
		void showPointCloud(){
			pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
		
			viewer.showCloud (this->cloud);
			
			while (!viewer.wasStopped ()){}
		}
		
		
		void position2lgf(Eigen::Vector3d & positionLGF, Position & p){
			
			Eigen::Vector3d positionECEF;
			
			CoordinateTransform::getPositionECEF(positionECEF, p);
			
			positionLGF = this->ecef2enu * (positionECEF - this->firstPositionECEF);
			
		}
		
		
		void setEcef2EnuMatrix(double & firstLat, double & firstLon){
			this->ecef2enu << -sin(firstLon*D2R), cos(firstLon*D2R), 0,
					-sin(firstLat*D2R)*cos(firstLon*D2R), -sin(firstLat*D2R)*sin(firstLon*D2R), cos(firstLat*D2R),
					cos(firstLat*D2R)*cos(firstLon*D2R), cos(firstLat*D2R)*sin(firstLon*D2R), sin(firstLat*D2R);
			
			this->ecef2enu.transposeInPlace();
		}
		
	private:
		std::string sbetFilePath;
		std::string pointCloudFilePath;
		
		std::vector<Position> sbetPositions;
		
		Eigen::Matrix3d ecef2enu;
		Eigen::Vector3d firstPositionECEF;
		
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud; 
		pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
};


int main(int argc,char** argv){

	if(argc < 3){
		std::cerr<<"usage ./pca sbet pointcloud" <<std::endl;
	}
	else{
		std::string sbetFilePath = argv[1];
		std::string pointCloudFilePath = argv[2];
		
		PointCloudAnalyz0r pca(sbetFilePath, pointCloudFilePath);
		pca.read();
		
		pca.denoise();
		
		//pca.showPointCloud();
		
		
	}
	
	
}
