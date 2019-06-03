/**
 * @author: Hexastorm
 * @description: quick test to check communication with stepper driver for the firestarter board v2
 *               board details can be found here https://github.com/hstarmans/firestarter
 *           
*/
#include<iostream>
#include <chrono>
#include <thread>

#include <TMC2130Stepper.h>
#include <generic-gpio.h>


#define Z_MOTOR_STEP (GPIO_1_BASE | 14)
#define Z_MOTOR_DIR (GPIO_0_BASE | 27)
#define Z_MOTOR_ENABLE (GPIO_2_BASE | 1)
#define Z_MOTOR_SELECT (GPIO_0_BASE | 26) // CSZ 8.14 0|26, CSX 0|5, CSY 0|13

TMC2130Stepper driver = TMC2130Stepper(Z_MOTOR_ENABLE, Z_MOTOR_DIR, Z_MOTOR_STEP, Z_MOTOR_SELECT);


using namespace std;

int main() {
	map_gpio();
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
	clr_gpio(Z_MOTOR_ENABLE);
	// set direction
	clr_gpio(Z_MOTOR_DIR);
	// infinitely move up an down with moves of 2 seconds
	bool dir = true;
    while(true){
		if(dir){
			std::cout << "Direction up" << std::endl;
			clr_gpio(Z_MOTOR_DIR);
		}
		else{
			std::cout << "Direction down" << std::endl;
			set_gpio(Z_MOTOR_DIR);
		}
		dir = !dir ;
		// do 2 seconds steps
		for(int step = 0; step < 10000; step += 1){
			clr_gpio(Z_MOTOR_STEP);
			std::this_thread::sleep_for(std::chrono::microseconds(10));
			set_gpio(Z_MOTOR_STEP);
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
    // TODO: program never reaches this part of code
	// disable motor
	set_gpio(Z_MOTOR_ENABLE);
	return 0;
}
