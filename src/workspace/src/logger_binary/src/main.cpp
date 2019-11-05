#ifndef MAIN_CPP
#define MAIN_CPP

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PointStamped.h"
#include "std_msgs/String.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../../utils/ReaderWriter.hpp"

Position pos;
Imu imu;
Sonar sonar;

Writer *writer;

std::string outputGnssFile;
std::string outputImuFile;
std::string outputSonarFile;
std::string outputFolder;
std::ofstream outputGnss;
std::ofstream outputImu;
std::ofstream outputSonar;
std::string sep = ";";

uint64_t buildTimeStamp(int sec, int nsec);

void gnssCallback(const geometry_msgs::PoseStamped& gnss)
{
  pos.timeStamp = buildTimeStamp(gnss.header.stamp.sec, gnss.header.stamp.nsec);
  pos.x = gnss.pose.position.x;
  pos.y = gnss.pose.position.y;
  pos.z = gnss.pose.position.z;

  writer->writeBinGnss(pos);
}

void imuCallback(const geometry_msgs::PoseStamped& imuMsgs)
{
  imu.timeStamp = buildTimeStamp(imuMsgs.header.stamp.sec, imuMsgs.header.stamp.nsec);
  imu.w = imuMsgs.pose.orientation.w;
  imu.x = imuMsgs.pose.orientation.x;
  imu.y = imuMsgs.pose.orientation.y;
  imu.z = imuMsgs.pose.orientation.z;

  writer->writeBinImu(imu);
}

void sonarCallback(const geometry_msgs::PointStamped& sonarMsgs)
{
  sonar.timeStamp = buildTimeStamp(sonarMsgs.header.stamp.sec, sonarMsgs.header.stamp.nsec);
  sonar.depth = sonarMsgs.point.z;

  writer->writeBinSonar(sonar);
}

uint64_t buildTimeStamp(int sec, int nsec){
  std::ostringstream os;
  os << sec;
  os << nsec;
  std::string ntime = os.str();

  uint64_t timestamp;
  std::istringstream iss(ntime.c_str());
  iss >> timestamp;

  return timestamp;
}

int main(int argc, char **argv)
{

//   std::cout << "\nlogger_binary, argc: " << argc << "\n" << std::endl;

//   for ( int count = 0; count < argc; count++)
//     std::cout << count << ", '" << argv[ count ] << "'" << std::endl;

//   std::cout << "\n" << std::endl;

  if(argc < 2){

    // std::cout << "\nif(argc < 2), argc: " << argc << std::endl;

    std::cout << "logger_binary, Missing output folder path" << std::endl;
    return 1;
  }

  std::string folderPath(argv[1]);
  outputFolder = folderPath;

  outputGnssFile = outputFolder + "/" + getStringDate() + "_gnss.bin";
  outputImuFile = outputFolder + + "/" + getStringDate() + "_imu.bin";
  outputSonarFile = outputFolder + "/" + getStringDate() + "_sonar.bin";

  writer = new Writer(outputGnssFile, outputImuFile, outputSonarFile, true);

  ros::init(argc, argv, "logger_binary");

  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("position", 1000, gnssCallback);
  ros::Subscriber sub2 = n.subscribe("pose", 1000, imuCallback);
  ros::Subscriber sub3 = n.subscribe("depth", 1000, sonarCallback);

  ros::spin();

  return 0;
}

#endif
