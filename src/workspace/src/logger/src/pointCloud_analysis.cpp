#include <SbetProcessor.hpp>
#include <filesystem>
#include "../../../MBES-lib/src/Position.hpp"
#include "../../../MBES-lib/src/Attitude.hpp"
#include <iostream>
#include <fstream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/crop_box.h>
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
				std::cerr<<"Invalid point cloud file path." << std::endl;
			}
		}
		
		void readSbet(){
			readFile(this->sbetFilePath);
		}
		
		void read(){
			readPointCloud();
			readSbet();
			
			//std::cerr<<pointCloudXs.size() << " points read && " << sbetPositions.size() << " positions read" << std::endl;
		}
		
		void denoise(){
			/*
			pcl::CropBox<pcl::PointXYZ> box(true); //TODO set to false when dev is done
			
			int minIndex = 0;
			int maxIndex = 10;
			while(maxIndex < sbetPositions.size()-1){
				
				Position min = sbetPositions.at(minIndex);
				Position max = sbetPositions.at(maxIndex);
			
				//Eigen::Vector4f minBoxPoint();
				//Eigen::Vector4f maxBoxPoint;
				//box.setMin()
				
				
				minIndex += 10;
				maxIndex += 10;
				if(maxIndex > sbetPositions.size()-1){
					maxIndex = sbetPositions.size()-1;
				}
				if(minIndex >= sbetPositions.size()-1 || minIndex == maxIndex){
					break;
				}
			}
			*/
			
		}
		
		void done(){} // needed because of sbetprocessor base class
		
		void showPointCloud(){
			pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
		
			viewer.showCloud (this->cloud);
			
			while (!viewer.wasStopped ()){}
		}
		
	private:
		std::string sbetFilePath;
		std::string pointCloudFilePath;
		
		std::vector<Position> sbetPositions;
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
		//pca.showPointCloud();
		
	}
	
	
}
