#pragma once

//Normal Includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <complex>

#include "Options.h"

using namespace std;

//This is the abstract class circuitObject
class circuitObject {

	//These are the public members of the class
public:
	virtual ~circuitObject() {}  //This is the virtual destructor

	virtual void setImpedance(const double forResistance, const double forReactance) = 0;  //This sets impedance when given separate R and X
	virtual void setImpedance(const complex<double> forImpedance) = 0;  //This sets impedance given complex impedance
	virtual const double getResistance() = 0;  //This gets the resistance
	virtual const double getReactance() = 0;  //This gets the reactance  
	virtual const complex<double> getImpedance() = 0;  //This gets the complex impedance

	virtual const int getX() = 0;  //This gets X
	virtual const int getY() = 0;  //This gets Y
	virtual void setX(int forX) = 0;  //This sets X given X
	virtual void setY(int forY) = 0;  //This sets Y given Y
	virtual const int getNodeWidth() = 0;  //This gets the node width 
	virtual const string getNodeType() = 0;  //This gets the node type
	virtual const string getAppearance() = 0;  //This gets the appearance

	virtual void setVoltageAndCurrent(complex<double> voltage, complex<double> current) = 0;  //This sets the voltage and current given a complex voltage and compelx current

	virtual bool circuitObjectXYPositionCheck(const int xCheck, const int yCheck) = 0;  //This checks existance of component at position x, y
	virtual string circuitObjectXYTypeGet(const int xCheck, const int yCheck) = 0;  //This checks which component exists at position x, y
	 
	virtual bool checkParallelLinkLocations(const int xCheck, const int yCheck) = 0;  //This looks for parallel linkers at position x, y

	virtual const void displayCircuitInformation(options options) = 0;  //This displays the cirucit information given options

	virtual void setComponentName(string input) = 0;  //Sets the name
	virtual void setComponentResistance(double input) = 0;  //Sets the resistance
	virtual void setComponentCapacitance(double input) = 0;  //Sets the capacitance
	virtual void setComponentInductance(double input) = 0;  //Sets the inductance
	virtual const string getComponentName() = 0;  //Gets the name
	virtual const double getComponentResistance() = 0;  //Gets the resistance
	virtual const double getComponentCapacitance() = 0;  //Gets the capacitance 
	virtual const double getComponentInductance() = 0;  //Gets the inductance

};