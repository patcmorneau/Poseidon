#include <libgpsmm.h>
//#include <gps.h>
#include <iostream>
#include <chrono>
using namespace std;


int main(void){
	gpsmm gps_rec("localhost", "2947");

	if (gps_rec.stream(WATCH_ENABLE | WATCH_NEWSTYLE) == NULL) {
		cerr << "No GPSD running.\n";
		return 1;
	}

	for (;;) {
		struct gps_data_t* gpsData = gps_rec.read();
		if (gpsData != nullptr) {
			if (gpsData->set & TIME_SET){
				cout<<"gps status :" << gpsData->status <<"\n"
				struct timespec ts = gpsData->fix.time;
				
				auto systemTime = std::chrono::system_clock::now();
				auto systemTimePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(systemTime);
				auto systemTimeMs = systemTimePoint.time_since_epoch().count();
				
				unsigned int timeDifferenceMs = std::abs(systemTimeMs-(ts.tv_sec * 1000 + ts.tv_nsec / 1000000));
				
				cout<<"time diff : " << timeDifferenceMs <<"\n";
			}
		}


	}
	return 0;
}
