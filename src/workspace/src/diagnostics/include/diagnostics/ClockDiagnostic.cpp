#include <libgpsmm.h>
#include <gps.h>
#include <iostream>
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
			struct timespec ts;
			ts = gpsData->fix.time;
			//cout << "GPS Time: " << ts << std::endl;
			char buff[100];
			strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
			printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
		}


	}
	return 0;
}
