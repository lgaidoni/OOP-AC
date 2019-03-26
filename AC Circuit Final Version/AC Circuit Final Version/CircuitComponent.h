#pragma once

//Normal Includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "CircuitObject.h"
#include "Options.h"
#include "GlobalConstants.h"

using namespace std;

class circuitComponent : public circuitObject {

	//Protected members
protected:

	//Here is the complex impedance
	complex<double> impedance;

	//Here are the actual parameters across the node
	complex<double> voltageAcrossComponent;  //Voltage can be complex
	complex<double> currentAcrossComponent;  //Current can be complex
	double componentResistance;  //Resistance of component
	double componentCapacitance;  //Capacitance of component
	double componentInductance;  //Inductance of component

	//x and y coordinates for the component
	int x;
	int y;

	//Visual Representation of the component
	string appearance;
	string componentName;

	//Public members
public:
	circuitComponent();  //Default constructor
	circuitComponent(const int forX, const int forY, options &options);  //Parameterised constructor
	virtual ~circuitComponent() {};  //Virtual destructor, overriden by each component
	const int getX();  //Get the X value
	void setX(int forX);  //Set the X value
	void setY(int forY);  //Set the Y value
	const int getY();  //Get the Y value
	const int getNodeWidth();  //Get the width of the node
	const double getResistance();  //Get the resistance of the component
	const double getCapacitance();  //Get the capacitance of the component
	const double getInductance();  //Get the inductance of the component
	const string getNodeType();  //Get the type of node this is (always returns component)
	const string getAppearance();  //Get the appearance of the component
	bool circuitObjectXYPositionCheck(const int xCheck, const int yCheck);  //Check whether a component exists at this X, Y value
	string circuitObjectXYTypeGet(const int xCheck, const int yCheck);  //Check what kind of component exists at this X, Y value
	bool checkParallelLinkLocations(const int xCheck, const int yCheck);  //Does a parallel link exist at this location
	const void displayCircuitInformation(options options);  //Display circuit information
	void setVoltageAndCurrent(complex<double> voltage, complex<double> current);  //Set the voltage and current across this node
	void setComponentName(string input);  //Set the name of this component
	const string getComponentName();  //Get the name of this component
	void setComponentResistance(double input);  //Set the resistance
	const double getComponentResistance();  //Get the resistance
	void setComponentCapacitance(double input);  //Set the capacitance
	const double getComponentCapacitance();  //Get the capacitance
	void setComponentInductance(double input);  //Set the inductance
	const double getComponentInductance();  //Get the inductance
};