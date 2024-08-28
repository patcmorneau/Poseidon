#include <iostream>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cstdint>

class HIH8130 {
public:
	HIH8130(const char* i2cDevice, uint8_t address) : deviceAddress(address) {
		if ((fileDescriptor = open(i2cDevice, O_RDWR)) < 0) {
			std::cerr << "Failed to open the I2C bus" << std::endl;
			exit(1);
		}

		if (ioctl(fileDescriptor, I2C_SLAVE, deviceAddress) < 0) {
			std::cerr << "Failed to connect to the sensor" << std::endl;
			exit(1);
		}
	}

	double get_humidity() {
		uint8_t data[4];

		if (write(fileDescriptor, &deviceAddress, 1) != 1) {
			std::cerr << "Failed to write to the sensor" << std::endl;
			exit(1);
		}

		usleep(100000);  // 100 ms

		if (read(fileDescriptor, data, 4) != 4) {
			std::cerr << "Failed to read from the sensor" << std::endl;
			exit(1);
		}

		uint16_t humidityRaw = ((data[0] & 0x3F) << 8) + data[1];
		return (humidityRaw / (double)((1 << 14) - 2)) * 100.0;
	}
	
	double get_temperature(){
		uint8_t data[4];

		if (write(fileDescriptor, &deviceAddress, 1) != 1) {
			std::cerr << "Failed to write to the sensor" << std::endl;
			exit(1);
		}

		usleep(100000);  // 100 ms

		if (read(fileDescriptor, data, 4) != 4) {
			std::cerr << "Failed to read from the sensor" << std::endl;
			exit(1);
		}
		
		uint16_t tempRaw = (data[2] << 6) + (data[3] >> 2);
		return ((tempRaw / (double)((1 << 14) - 2)) * 165.0) - 40.0;
		
	}

	~HIH8130() {
		close(fileDescriptor);
	}

private:
	int fileDescriptor;
	uint8_t deviceAddress;
};

