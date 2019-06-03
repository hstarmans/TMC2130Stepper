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

// firestarter v0.2 z-direction
#define EN_PIN    (GPIO_2_BASE | 1)   // Z_ENABLE 8.11
#define DIR_PIN   (GPIO_0_BASE | 16)  // Z_DIR    8.17				  	
#define STEP_PIN  (GPIO_1_BASE | 14)  // Z_STEP   8.16
#define CS_PIN    (GPIO_0_BASE | 26)  // CSZ 8.14 0|26, CSX 0|5, CSY 0|13


TMC2130Stepper driver = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);


using namespace std;

int main() {
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
	clr_gpio(EN_PIN);
	// set direction
	clr_gpio(DIR_PIN);
	// infinitely move up an down with moves of 2 seconds
	bool dir = true;
    while(true){
		if(dir){
			clr_gpio(DIR_PIN);
		}
		else{
			set_gpio(DIR_PIN);
		}
		dir = !dir ;
		// do 2 seconds steps
		for(int step = 0; step < 10000; step += 1){
			clr_gpio(STEP_PIN);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			set_gpio(STEP_PIN);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
    // TODO: program never reaches this part of code
	// disable motor
	set_gpio(EN_PIN);
	return 0;
}
