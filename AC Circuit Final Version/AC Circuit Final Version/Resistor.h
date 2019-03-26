#pragma once

//Normal Includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

//Includes for custom headers
#include "circuitComponent.h"  //Capacitor derived from component
#include "Options.h"  //Needs the options menu
#include "GlobalConstants.h"  //Needs to know pi

//Using the standard namespace
using namespace std;

class resistor : public circuitComponent {  //Resistor derived from component

//Private member data
private:
	static int resistorCount;

//Public members
public:
	resistor(const int forX, const int forY, options &options);  //Parameterised Constructor
	resistor();  //Default Constructor
	~resistor();  //Destructor
	void setImpedance(const double forResistance, const double forReactance);  //Function to set impedance given resistance and reactance
	void setImpedance(const complex<double> forImpedance);  //Function to set impedance given a complex impedance
	const double getResistance();  //Function to get the resistance
	const double getReactance();  //Function to get the reactance
	const complex<double> getImpedance();  //Function to get the impedance, returns a complex impedance
};