/**
 * Author Teemu Mäntykallio
 * Initializes the library and turns the motor in alternating directions.
*/
#include<iostream>
#define EN_PIN    38  // Nano v3:	16 Mega:	38	//enable (CFG6)
#define DIR_PIN   55  //			19			55	//direction
#define STEP_PIN  54  //			18			54	//step
#define CS_PIN    40  //			17			64	//chip select

bool dir = true;

#include <TMC2130Stepper.h>
TMC2130Stepper driver = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);


using namespace std;

int main() {
	cout << "sometext\n" << endl;
}
