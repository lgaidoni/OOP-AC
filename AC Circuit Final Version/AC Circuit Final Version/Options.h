#pragma once
//Normal Includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

//Includes for user created headers
#include "UserInputFunctions.h"

//Using standard namespace
using namespace std;

class options {  //This is the options menu class

private:
	bool componentLibraryExists;  //Does the component library exist
	bool willDrawCircuit;  //Should the circuit be drawn
	bool circuitNotIdeal;  //Is the circuit ideal
	double voltage;  //What is the desired voltage
	double frequency;  //What is the desired frequency

public:
	options(); //Default constructor
	~options();  //Destructor

	//These functions set voltage, frequency, component library exists, draw circuit, and circuit ideality
	void setVoltage(const double forVoltage);
	void setFrequency(const double forFrequency);
	void setComponentLibraryExists(const bool input);
	void setWillDrawCircuit(const bool input);
	void setCircuitNotIdeal(const bool input);

	void openOptionsMenu();  //This function opens the options menu

	//These functions ask the user for voltage, frequency, component library exists, draw circuit, and circuit ideality
	void askVoltage();
	void askFrequency();
	void askComponentLibraryExists();
	void askWillDrawCircuit();
	void askCircuitNotIdeal();

	//These functions get the values for voltage, frequency, component library exists, draw circuit, and circuit ideality
	const double getVoltage();
	const double getFrequency();
	const bool getComponentLibraryExists();
	const bool getWillDrawCircuit();
	const bool getCircuitNotIdeal();

	const void getSettings();  //This function outputs the current settings

};