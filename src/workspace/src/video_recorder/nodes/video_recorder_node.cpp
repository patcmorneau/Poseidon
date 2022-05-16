#include "video_recorder/video_recorder.h"
//#include "../../utils/timestamp.h"


int main(int argc, char **argv)
{
	if(argc < 2){

		std::cout << "video recorder, Missing output folder path" << std::endl;
		return 1;
	}

	try{
		ros::init(argc, argv, "video_recorder");

		ros::NodeHandle n;

		std::string outputFolder( argv[1] );

		VideoProcessor videoProcessor(outputFolder);
		
		ros::Subscriber sub1 = n.subscribe("fix", 1000, &VideoProcessor::gnssCallback,&videoProcessor);
		videoProcessor.run();
		ros::spin();
	}
	catch(std::exception & e){
		ROS_ERROR("%s",e.what());
	}

	return 0;
}
