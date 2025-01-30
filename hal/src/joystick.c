#include "hal/joystick.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define I2CDRV_LINUX_BUS "/dev/i2c-1"   // The I2C bus to communicate with the joystick.
#define I2C_DEVICE_ADDRESS 0x48         // The I2C address of the joystick device.

#define REG_CONFIGURATION 0x01          // Register address for configuration.
#define REG_DATA 0x00                   // Register address for data.

#define TLA2024_CHANNEL_CONF_X 0x83C2   // Configuration value for X-axis reading.
#define TLA2024_CHANNEL_CONF_Y 0x83D2   // Configuration value for Y-axis reading.

//Flag to track if joystick module has been initialized.
static bool is_initialized = false;

//Helper functions for I2C communication obtained from course I2C Guide.
static int init_i2c_bus(char *bus, int address);
static void write_i2c_reg16(int i2c_file_desc, uint8_t reg_addr, uint16_t value);
static uint16_t read_i2c_reg16(int i2c_file_desc, uint8_t reg_addr);

void joystick_init(Joystick *joystick) 
{
    assert(joystick != NULL);
    assert(!joystick->is_initialized);
    assert(!is_initialized);

    joystick->i2c_file_desc = init_i2c_bus(I2CDRV_LINUX_BUS, I2C_DEVICE_ADDRESS);
    if (joystick->i2c_file_desc < 0) {
        perror("Failed to initialize I2C");
        exit(EXIT_FAILURE);
    }
    
    joystick->is_initialized = true;
    is_initialized = true;
}

int joystick_read_input(Joystick *joystick, JoystickDirection dir) 
{
    assert(joystick != NULL);
    assert(joystick->is_initialized);
    assert(dir == JOYSTICK_X || dir == JOYSTICK_Y);
    assert(is_initialized);

    uint16_t config;
    if (dir == JOYSTICK_X) {
        config = TLA2024_CHANNEL_CONF_X;
    } else {
        config = TLA2024_CHANNEL_CONF_Y;
    }
    write_i2c_reg16(joystick->i2c_file_desc, REG_CONFIGURATION, config);

    // Read the raw value from the joystick, obtained from tla2024_demo.c
    uint16_t raw_read = read_i2c_reg16(joystick->i2c_file_desc, REG_DATA);
    uint16_t value = ((raw_read  & 0xFF) << 8) | ((raw_read  & 0xFF00) >> 8);
    value = value >> 4;

    // Scales value to [-100, 100] based on observed min and max values for usability.
    int min_x = 1, max_x = 1630;
    int min_y = 34, max_y = 1645;
    
    if (dir == JOYSTICK_X) {
        return ((value - min_x) * 200) / (max_x - min_x) - 100;
    } else {
        return ((value - min_y) * 200) / (max_y - min_y) - 100;
    }
}

void joystick_cleanup(Joystick *joystick) 
{
    assert(joystick != NULL);
    assert(joystick->is_initialized);
    assert(is_initialized);

    close(joystick->i2c_file_desc);
    joystick->is_initialized = false;
    is_initialized = false;
}

static int init_i2c_bus(char* bus, int address)
{
	int i2c_file_desc = open(bus, O_RDWR);
	if (i2c_file_desc == -1) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(EXIT_FAILURE);
	}

	if (ioctl(i2c_file_desc, I2C_SLAVE, address) == -1) {
		perror("Unable to set I2C device to slave address.");
		exit(EXIT_FAILURE);
	}
	return i2c_file_desc;
}

static void write_i2c_reg16(int i2c_file_desc, uint8_t reg_addr, uint16_t value)
{
	int tx_size = 1 + sizeof(value);
	uint8_t buff[tx_size];
	buff[0] = reg_addr;
	buff[1] = (value & 0xFF);
	buff[2] = (value & 0xFF00) >> 8;
	int bytes_written = write(i2c_file_desc, buff, tx_size);
	if (bytes_written != tx_size) {
		perror("Unable to write i2c register");
		exit(EXIT_FAILURE);
	}
}

static uint16_t read_i2c_reg16(int i2c_file_desc, uint8_t reg_addr)
{
	int bytes_written = write(i2c_file_desc, &reg_addr, sizeof(reg_addr));
	if (bytes_written != sizeof(reg_addr)) {
		perror("Unable to write i2c register.");
		exit(EXIT_FAILURE);
	}

	uint16_t value = 0;
	int bytes_read = read(i2c_file_desc, &value, sizeof(value));
	if (bytes_read != sizeof(value)) {
		perror("Unable to read i2c register");
		exit(EXIT_FAILURE);
	}
	return value;
}