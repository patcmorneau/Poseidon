#ifndef IMUCALIBRATIONDIAGNOISTIC_H
#define IMUCALIBRATIONDIAGNOISTIC_H

#include "DiagnosticsTest.h"
#include "sensor_msgs/Imu.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "../../utils/QuaternionUtils.h"

class ImuCalibrationDiagnostic : public DiagnosticsTest{
	
public:
	ImuCalibrationDiagnostic(std::string name, int _messageFrequency): DiagnosticsTest(name), transformListener(buffer), messageFrequency(_messageFrequency){}
	~ImuCalibrationDiagnostic(){}

	void callback(const sensor_msgs::Imu& imu){
		messageCount++;
		
		double heading = 0;
		double pitch   = 0;
		double roll    = 0;
		
		geometry_msgs::TransformStamped imuBodyTransform = buffer.lookupTransform("base_link", "imu", ros::Time(0));
		QuaternionUtils::applyTransform(imuBodyTransform.transform.rotation, imu.orientation, heading, pitch, roll);
		
		if(std::abs(pitch) > 1.5 || std::abs(roll) > 1.5){
			calibrated = false;
			
			r =roll;
			p = pitch;
			h = heading;
			
		}
	}
	
	void do_test()override{
		try{
			//reinitialize test results
			calibrated = true;
			this->status = false;
			this->value = "";
			this->messageCount = 0;
			r = 0;
			p = 0;
			h = 0;
			
			subscriber = node.subscribe("imu/data", 10, &ImuCalibrationDiagnostic::callback, this);
			
			ros::Time startTime = ros::Time::now();
			double elapsedTime = 0.0;
			//loop while messageCount condition is not met or exit loop if timer has expired
			while (ros::ok()){
				
				ros::Time currentTime = ros::Time::now();
				elapsedTime = (currentTime - startTime).toSec();
			
				if (messageCount >= (messageFrequency * sleepDuration)){
					break;
				}
				
				if (elapsedTime >= sleepDuration){
					break;
				}
				ros::Duration(0.1).sleep();
			}
			
			this->value = (calibrated && messageCount>0) ? "Calibrated" : "Not calibrated. \nRoll: " + std::to_string(r) + "\nPitch: "+ std::to_string(p) + "\nHeading: "+ std::to_string(h);
			this->status = calibrated && (messageCount>0);
			subscriber.shutdown();
		}
		catch(const std::exception& ex){
			ROS_ERROR_STREAM(ex.what());
			this->status = false;
			this->value = ex.what();
			subscriber.shutdown();
		}
	}
	
private:
	ros::Subscriber subscriber;
	ros::NodeHandle node;
	double sleepDuration = 1.0;
	int messageCount = 0;
	int messageFrequency;
	bool calibrated = true;
	tf2_ros::Buffer buffer;
	tf2_ros::TransformListener transformListener;
	double r,p,h;

};
#endif
