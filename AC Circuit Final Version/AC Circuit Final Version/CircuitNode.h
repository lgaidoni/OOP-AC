#pragma once

//Normal Includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "circuitObject.h"
#include "Options.h"
#include "DrawCircuit.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "CustomComponent.h"
#include "userInputFunctions.h"

using namespace std;

class circuitNode : public circuitObject {

//Private members
private:
	//Here is the complex impedance
	complex<double> impedance;

	//Here are the actual parameters across the node
	double voltageAcrossNode;
	double currentAcrossNode;
	double frequencyAcrossNode;

	//x and y coordinates for the component
	int x;
	int y;

	//What type of node this is
	string nodeTypeIdentifier;

	//Static counters for series and parallel
	static int parallelNodeCount;
	static int seriesNodeCount;

	//String for the name of the node
	string nodeName;

	//Node width
	int nodeWidth;

	//How many connected nodes are there to this one
	int connectedNodes;

	//How wide should the parallel width be
	int parallelWidth;

	//Here is the base class pointer that will hold what is stored in this node
	vector<circuitObject*> circuitObjectPointerVector;

	//Here is the vector that will store the x coordinates of the "_" for drawing circuits
	vector<int> drawParallelLinkLocations;

//Public members
public:
	//Parameterised constructor, takes X, Y, ParallelWidth, Options menu, and the component library
	circuitNode(const int forX, const int forY, const int nextParallelWidth, options &options, vector<circuitObject*> components);
	~circuitNode();  //Destructor

	const int getX();  //Gets X
	const int getY();  //Gets Y
	void setX(int forX);  //Sets X
	void setY(int forY);  //Sets Y
	const int getNodeWidth();  //Gets the node width
	const string getNodeType();  //Gets the node type
	const string getAppearance();  //Gets the appearance

	bool circuitObjectXYPositionCheck(const int xCheck, const int yCheck);  //Checks for deeper component X and Y positions
	string circuitObjectXYTypeGet(const int xCheck, const int yCheck);  //Checks for deeper component Types

	bool checkParallelLinkLocations(const int xCheck, const int yCheck);  //Checks for parallel link locations for this node

	const double getResistance();  //Gets the resistance
	const double getReactance();  //Gets the reactance
	const complex<double> getImpedance();  //Gets the impedance
	void setImpedance(const double forResistance, const double forReactance);  //Sets the impedance given separated R and X
	void setImpedance(const complex<double> forImpedance);  //Sets the impedance given complex impedance

	void setVoltageAndCurrent(complex<double> voltage, complex<double> current);  //Sets the voltage given complex voltage and complex current

	const void displayCircuitInformation(options options);  //Displays the circuit information (calls component version)

	void setComponentName(string input);  //Sets the name
	const string getComponentName();  //Gets the name

	void setComponentResistance(double input);  //Sets resistance
	const double getComponentResistance();  //Gets resitance

	void setComponentCapacitance(double input);  //Sets capacitance
	const double getComponentCapacitance();  //Gets capacitance

	void setComponentInductance(double input);  //Sets inductance
	const double getComponentInductance();  //Gets inductance

};