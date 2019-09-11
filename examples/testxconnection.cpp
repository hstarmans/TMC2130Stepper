/**
 * @author: Hexastorm
 * @description: quick test to check communication with x stepper driver for the firestarter board v2
 *               board details can be found here https://github.com/hstarmans/firestarter
 *           
*/
#include<iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <TMC2130Stepper.h>
#include <generic-gpio.h>

#define X_MOTOR_STEP 0xFFFFFFFF          // Z_STEP 1|14 X_STEP PRU Y_STEP PRU 
#define X_MOTOR_DIR (GPIO_0_BASE | 7)    // Z_DIR  0|27  X_DIR 0|7 Y_DIR  1|15
#define STEPPER_ENABLE (GPIO_1_BASE | 28)
#define X_MOTOR_SELECT 0XFFFFFFFF        // CSZ 0|26, CSX select via SPI, CSY 0|30

TMC2130Stepper driver = TMC2130Stepper(STEPPER_ENABLE, X_MOTOR_DIR, X_MOTOR_STEP, X_MOTOR_SELECT);

using namespace std;

int main() {
	//NOTE: driver begin maps the pins
	driver.begin();
	uint8_t result = driver.test_connection();
	if (result) {
        std::cout << "failed!" << std::endl; 
		std::cout << "Likely cause: " << std::endl;
		// if power is inserted, still returns "no power", test seems incorrect
        switch(result) {
            case 1: std::cout << "Loose connection or no power." << std::endl; break;
            case 2: std::cout << "Communication seems to work but something is off." << std::endl; break;
        }
	}
	else{
		std::cout << "Succesfull connected to board." << std::endl; 
	}
	driver.rms_current(600);
	driver.microsteps(1);
	driver.toff(3);
	driver.stealthChop(1);
	// enable motor
	clr_gpio(STEPPER_ENABLE);
	// set direction
	clr_gpio(X_MOTOR_DIR);
	// y connection can only be moved via PRU
	// disable motor
	set_gpio(STEPPER_ENABLE);
	return 0;
}
