#include <libgpsmm.h>
#include <iostream>
using namespace std;

int main(void)
{
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

    if (gps_rec.stream(WATCH_ENABLE|WATCH_NEWSTYLE) == NULL) {
        cerr << "No GPSD running.\n";
        return 1;
    }

    for (;;) {
	struct gps_data_t* newdata;

	if (!gps_rec.waiting(50000000))
	  continue;

	if ((newdata = gps_rec.read()) == NULL) {
	    cerr << "Read error.\n";
	    return 1;
	} else {
	    //PROCESS(newdata);
	}
    }
    return 0;
}
