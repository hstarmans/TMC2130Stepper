/**
 * @author: Hexastorm
 * @description: quick test to check communication with stepper driver for the firestarter board
 *           
*/
#include<iostream>

#include <TMC2130Stepper.h>
#include <generic-gpio.h>

// firestarter v0.2 z-direction
#define EN_PIN    (GPIO_2_BASE | 1)   // Z_ENABLE
#define DIR_PIN   (GPIO_0_BASE | 16)  // Z_DIR    8.17				  	
#define STEP_PIN  (GPIO_1_BASE | 14)  // Z_STEP   8.16
#define CS_PIN    (GPIO_0_BASE | 26)  // SPIO_CSZ 8.14

bool dir = true;

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
        return 1;
	}
	else{
		std::cout << "succesfull connected to board" << std::endl; 
		return 1;
	}
	// TODO: set current, move drive
}
