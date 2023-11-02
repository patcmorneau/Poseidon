#include <libgpsmm.h>
#include <gps.h>
#include <iostream>
using namespace std;


static void libgps_dump_state(struct gps_data_t *data){
	std::cout<<"ok4 \n";
	/*
    char ts_str[TIMESPEC_LEN];

    if (data->set & TIME_SET) {
        (void)fprintf(stdout, "TIME: %s\n",
                      timespec_str(&data->fix.time, ts_str, sizeof(ts_str)));
    }
	*/
	
	struct timespec * ts;
	ts = &data->fix.time;
	char buff[100];
    strftime(buff, sizeof buff, "%D %T", gmtime(&ts->tv_sec));
    printf("Current time: %s.%09ld UTC\n", buff, ts->tv_nsec);
//    printf("Raw timespec.time_t: %jd\n", (intmax_t)ts.tv_sec);
//    printf("Raw timespec.tv_nsec: %09ld\n", ts.tv_nsec);
}



int main(void)
{
    gpsmm gps_rec("localhost", "2947");

    if (gps_rec.stream(WATCH_ENABLE | WATCH_NEWSTYLE) == NULL) {
        cerr << "No GPSD running.\n";
        return 1;
    }

    for (;;) {
		struct gps_data_t* newdata;
		//std::cout<<"ok1\n";
		if (!gps_rec.waiting(50000000)){
			//std::cout<<"ok2\n";
			continue;
		}

		if ((newdata = gps_rec.read()) == NULL) {
			cerr << "Read error.\n";
			return 1;
		} else {
			std::cout<<"ok3\n";
			libgps_dump_state(newdata);
		}
    }
    return 0;
}
