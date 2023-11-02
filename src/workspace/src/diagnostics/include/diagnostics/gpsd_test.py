import gps
import time
from datetime import datetime

# Connectez-vous à GPSD
session = gps.gps("localhost", "2947")
session.stream(gps.WATCH_ENABLE | gps.WATCH_NEWSTYLE)

try:
    while True:
        report = session.next()
        if report['class'] == 'TPV':
            if hasattr(report, 'time'):
                gps_time = report.time
                system_time = time.time()
                time_difference = gps_time - system_time
                gps_time_str = datetime.utcfromtimestamp(gps_time).strftime('%Y-%m-%d %H:%M:%S')
                system_time_str = datetime.utcfromtimestamp(system_time).strftime('%Y-%m-%d %H:%M:%S')
                print(f"GPS Time: {gps_time_str}")
                print(f"System Time: {system_time_str}")
                print(f"Time Difference (seconds): {time_difference}")
                break

except KeyboardInterrupt:
    session.close()

