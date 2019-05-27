/**
 * @author: Hexastorm
 * @description: quick test to check communication with stepper driver for the firestarter board
 *           
*/
#include<iostream>

#include <TMC2130Stepper.h>
#include <generic-gpio.h>
#include <chrono>
#include <thread>

// firestarter v0.2 z-direction
#define EN_PIN    (GPIO_2_BASE | 1)   // Z_ENABLE 8.11
#define DIR_PIN   (GPIO_0_BASE | 16)  // Z_DIR    8.17				  	
#define STEP_PIN  (GPIO_1_BASE | 14)  // Z_STEP   8.16
#define CS_PIN    (GPIO_0_BASE | 26)  // SPIO_CSZ 8.14


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
            case 1: std::cout << "loose connection" << std::endl; break;
            case 2: std::cout << "Likely cause: no power " << std::endl; break;
        }
        std::cout << "Fix the problem and reset board." << std::endl;
	}
	else{
		std::cout << "succesfull connected to board" << std::endl; 
	}
	driver.rms_current(600);
	driver.stealthChop(1);
	// enable motor
	clr_gpio(EN_PIN);
	// set direction
	clr_gpio(DIR_PIN);
	// do 100 steps
    for(int step = 0 ; step < 100; step += 1){
		clr_gpio(STEP_PIN);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		set_gpio(STEP_PIN);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	// disable motor
	set_gpio(EN_PIN);
	return 0;
}
