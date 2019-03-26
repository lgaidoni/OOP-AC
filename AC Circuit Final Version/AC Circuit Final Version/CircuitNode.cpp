//Normal Includes
#include <iterator>
#include "CircuitNode.h"

int circuitNode::parallelNodeCount{ 0 };  //Initialise the parallel node count static
int circuitNode::seriesNodeCount{ 0 };  //Initialise the series node count static

//This is the parameterised constructor, taking X, Y, parallel width, the options menu, and the component library
circuitNode::circuitNode(const int forX, const int forY, const int nextParallelWidth, options &options, vector<circuitObject*> components) {

	x = forX;  //Sets the x coordinate
	y = forY;  //Sets the y coordinate

	parallelWidth = nextParallelWidth;  //Sets parallel width

	//cout << "Node Centre is (" << x << ", " << y << ")" << endl;

	int desiredNodeType{ circuitRequest() };  //Asks the user what kind of node they want

	if (desiredNodeType == 1) {  //If the node is a series node

		nodeTypeIdentifier = "series";  //Set the node type
		seriesNodeCount++;  //Increment the series node counter
		stringstream forNodeName;  //Stringstream for naming the node
		forNodeName << "Series Subcircuit " << seriesNodeCount;  //Name the node
		nodeName = forNodeName.str();  //Save the name of the node

		connectedNodes = nodeNumber();  //Set the number of connected nodes

		nodeWidth = 1;  //Set the node with to 1, because series

		for (int nodes{ 0 }; nodes < connectedNodes * 2; nodes += 2) {  //For all the connected nodes

			if (options.getWillDrawCircuit() == true) drawCircuit(this, options, components);  //Draw the current circuit
			circuitObjectPointerVector.push_back(new circuitNode(x, y + nodes + 1, parallelWidth, options, components));  //Create a new circuit node
			if (options.getWillDrawCircuit() == true) drawCircuit(this, options, components);  //Draw the circuit again

		}

	}
	else if (desiredNodeType == 2) {  //If the node is a parallel node

		nodeTypeIdentifier = "parallel";  //Set the node type
		parallelNodeCount++;  //Increment the parallel node counter
		stringstream forNodeName;  //Strincstream for naming the node
		forNodeName << "Parallel Subcircuit " << parallelNodeCount;  //Name the node
		nodeName = forNodeName.str();  //Save the name of the node

		connectedNodes = nodeNumber();  //Set the number of connected nodes
		while (connectedNodes <= 1) {  //Parallel nodes need at least two nodes
			cout << "Parallel nodes need at least two connected nodes" << endl;  //Tell the user this
			connectedNodes = nodeNumber();  //Ask again
		}
		nodeWidth = connectedNodes;  //Save the new node width

		int nodeAtLower{ forX - (parallelWidth) };  //X position of the leftmost node
		int nodeAtHigher{ forX + (parallelWidth) + 1};  //X position of the desired rightmost node

		for (int i{ nodeAtLower }; i <= nodeAtHigher; i++) {  //For every x between lowest and highest
			drawParallelLinkLocations.push_back(i);  //Create a parallel linker
		}

		int finalNodeAt;  //Int for the location of the final node

		//For all the positions of nodes, starting from the left and moving right according to a desired gap calculation (below here)
		for (int nodeAt{ forX - (parallelWidth) }; nodeAt <= (forX + (parallelWidth)); nodeAt += ((parallelWidth*2)) / (connectedNodes - 1)) {
			if (options.getWillDrawCircuit() == true) drawCircuit(this, options, components);  //Draw the circuit
			circuitObjectPointerVector.push_back(new circuitNode(nodeAt, y + 1, parallelWidth / 2, options, components));  //Add a new node connected to this one
			if (options.getWillDrawCircuit() == true) drawCircuit(this, options, components);  //Draw the circuit again
			finalNodeAt = nodeAt;  //Save the x location of the final node
		}

		int parallelLinkSubtractions{ nodeAtHigher - finalNodeAt - 1};  //Find the difference between the actual position of the right node, and the desired position of the right node
		for (int i{ 0 }; i < parallelLinkSubtractions; i++)  drawParallelLinkLocations.pop_back();  //For this difference, remove overshoot parallel linkers

	}
	else {  //Otherwise, it's a component

		nodeTypeIdentifier = "component";  //Set the node type

		connectedNodes = 1;  //Set the number of connected nodes (1, as component)

		if (options.getComponentLibraryExists() == false) {  //If there is no component library

			int desiredComponent{ componentRequest() };  //Ask what kind of component the user wants

			if (desiredComponent == 1) circuitObjectPointerVector.push_back(new resistor(x, y + 1, options));  //If resistor, add a resistor
			else if (desiredComponent == 2) circuitObjectPointerVector.push_back(new capacitor(x, y + 1, options));  //If capacitor, add a capacitor
			else if (desiredComponent == 3) circuitObjectPointerVector.push_back(new inductor(x, y + 1, options));  //If inductor, add an inductor

		}
		else if (options.getComponentLibraryExists() == true) {  //If there is a component library

			int desiredComponent;  //Which component would the user like
			cout << "Which component from the component library would you like to use: ";
			cin >> desiredComponent;  //Take a value for desired component
			while (cin.fail() || !(desiredComponent >= 1 && desiredComponent <= (int)components.size())) {  //If that's not a real component
				cout << "Which component from the component library would you like to use: ";  //Reinform the user of the desired input
				cin.clear();  //Clear the cin error
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
				cin >> desiredComponent;  //Accept user input once more
			}

			//For each component, create an empty one...
			if (components[desiredComponent - 1]->getAppearance() == "R") circuitObjectPointerVector.push_back(new resistor());
			if (components[desiredComponent - 1]->getAppearance() == "C") circuitObjectPointerVector.push_back(new capacitor());
			if (components[desiredComponent - 1]->getAppearance() == "L") circuitObjectPointerVector.push_back(new inductor());
			if (components[desiredComponent - 1]->getAppearance() == "X") circuitObjectPointerVector.push_back(new customComponent());

			//Then copy over the data from the one in the component library
			circuitObjectPointerVector[0]->setX(x);
			circuitObjectPointerVector[0]->setY(y+1);
			circuitObjectPointerVector[0]->setImpedance(components[desiredComponent - 1]->getImpedance());
			circuitObjectPointerVector[0]->setComponentName(components[desiredComponent - 1]->getComponentName());
			circuitObjectPointerVector[0]->setComponentResistance(components[desiredComponent - 1]->getComponentResistance());
			circuitObjectPointerVector[0]->setComponentCapacitance(components[desiredComponent - 1]->getComponentCapacitance());
			circuitObjectPointerVector[0]->setComponentInductance(components[desiredComponent - 1]->getComponentInductance());

		}

		cout << endl;

		return;  //If it's a component, don't set node impedance to component's impedance

	}

	impedance = this->getImpedance();  //Get the node's own impedance

}

circuitNode::~circuitNode() {  //Destructor

	if (nodeTypeIdentifier == "series") seriesNodeCount--;  //Decrease the number of series nodes if series
	if (nodeTypeIdentifier == "parallel") parallelNodeCount--;  //Decreate the number of parallel nodes if parallel

	//vector<circuitObject*>::iterator current;
	//Iterate over the circuit object pointer vector
	for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {
		delete circuitObjectPointerVector[i];  //Delete the circuit objects in the circuit object pointer vector
	}

	circuitObjectPointerVector.clear();  //Clear the circuitObjectPointerVector
	drawParallelLinkLocations.clear();  //Clear the parallelLinkLocations vector

}

const int circuitNode::getX() { return x; }  //Get the x value
const int circuitNode::getY() { return y; }  //Get the y value
void circuitNode::setX(int forX) {}  //Set the x value
void circuitNode::setY(int forY) {}  //Set the y value

const int circuitNode::getNodeWidth() {  //This is the function to get node width

	int toReturn{ 0 };  //Create a value to 

	if (nodeTypeIdentifier == "parallel") {  //If the node is parallel
		for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the elements in the circuit object pointer vector
			toReturn += circuitObjectPointerVector[i]->getNodeWidth();  //Add to the node width
		}
	}
	else toReturn = 1;  //Otherwise, return 1

	return toReturn;  //Return the toReturn value
}

const string circuitNode::getNodeType() { return nodeTypeIdentifier; }  //Get the node type

bool circuitNode::circuitObjectXYPositionCheck(const int xCheck, const int yCheck) {  //This is the function to check X and Y position for object existance

	for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the objects in the circuitObjectPointerVector

		if (circuitObjectPointerVector[i]->circuitObjectXYPositionCheck(xCheck, yCheck) == true) return true;  //Of xy position check on object returns true, return true

	}

	if (xCheck == x && yCheck == y) return true;  //Also return true of the node exists there

	return false;  //Otherwise return false

}

string circuitNode::circuitObjectXYTypeGet(const int xCheck, const int yCheck) {  //This is a function to get node type for drawing at X and Y position

	for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the objects in the corcuitObjectPointerVector

		if (circuitObjectPointerVector[i]->circuitObjectXYPositionCheck(xCheck, yCheck) == true) return circuitObjectPointerVector[i]->circuitObjectXYTypeGet(xCheck, yCheck);
		//If an object exists at that position, return its type

	}

	return "|";  //Otherwise return | (For node linking)

}

bool circuitNode::checkParallelLinkLocations(const int xCheck, const int yCheck) {  //This is a function to check existance of parallelLinkers

	for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the object in the circuitObjectPointerVector
		if (circuitObjectPointerVector[i]->checkParallelLinkLocations(xCheck, yCheck) == true) return true; // If they return this function as true, return true
	}

	for (int i{ 0 }; i < (int)drawParallelLinkLocations.size() - 1; i++) {  //For all the link locations in this node
		if (xCheck == drawParallelLinkLocations[i] && yCheck == y) return true;  //If one exists at that x and y, reuturn true
	}

	return false;  //Otherwise return false

}


void circuitNode::setImpedance(const double forResistance, const double forReactance) {}  //Do nothing, can't set impedance of node
void circuitNode::setImpedance(const complex<double> forImpedance) {}  //Do nothing, can't set impedance of node
const void circuitNode::displayCircuitInformation(options options) {}  //Do nothing, nothing to display for node
const string circuitNode::getAppearance() {   //Do nothing (but need to return something), node has no appearance
	string toReturn{ " " }; 
	return toReturn; 
}

const double circuitNode::getResistance() {  //Node has no resistance
	return 0;
}

const double circuitNode::getReactance() {  //Node has no reactance
	return 0;
}

const complex<double> circuitNode::getImpedance() { //Function to get the impedance

	if (nodeTypeIdentifier == "parallel") {  //If the node is parallel

		double flippedResistanceSum{ 0 };  //Resistance for the flipped impedance
		double flippedReactanceSum{ 0 };  //Reactance for the flipped impedance

		for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the objects in the node

			complex<double> tempForFlip(circuitObjectPointerVector[i]->getImpedance());  //Create a temporary complex number for the ith object in the node

			double absoluteForFlip{abs(tempForFlip)};  //Get the absolute of the temporary complex number
			double argumentForFlip{arg(tempForFlip)};  //Get the argument of the temporary complex number

			complex<double> toSum(polar(1 / absoluteForFlip, -1 * argumentForFlip));  //Create a new complex number and give it the inverted information

			flippedResistanceSum += real(toSum);  //Sum the inverted resistance
			flippedReactanceSum += imag(toSum);  //Sum the inverted reactance
		}

		complex<double> tempForReFlip(flippedResistanceSum, flippedReactanceSum);  //Create a new temp complex number to be re-inverted to get Ztot

		double absoluteForReFlip{ abs(tempForReFlip) };  //Absolute value to be re flipped
		double argumentForReFlip{ arg(tempForReFlip) };  //Argument value to be re flipped

		complex<double> toReturn(polar(1 / absoluteForReFlip, -1 * argumentForReFlip));  //Temp complex number using flipped polar form of data to be re-flipped

		return toReturn;  //Return the complex impedance of the parallel combination of every object in the node

	}
	else if (nodeTypeIdentifier == "series") {  //If the node is series

		double resistanceSum{ 0 };  //Resistance for sum
		double reactanceSum{ 0 };  //Reactance for sum

		for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the nodes in this node

			complex<double> temp(circuitObjectPointerVector[i]->getImpedance());  //Get their impedance

			resistanceSum += real(temp);  //Sum their resistances
			reactanceSum += imag(temp);  //Sum their reactances

		}

		complex<double> toReturn(resistanceSum, reactanceSum);  //Return the impedance sum

		return toReturn; //Return the impedance sum

	}
	else {  //Otherwise, the node will be a component

		complex<double> toReturn{ circuitObjectPointerVector[0]->getImpedance() };  //Value to return (gets resistance of the component)

		//cout << "Resistance of this node is " << toReturn << endl;  //Inform the user of its resistance

		return toReturn;  //Return the Impedance of the component

	}

}

void circuitNode::setVoltageAndCurrent(complex<double> voltage, complex<double> current) {  //Function to set the voltage and current of the nodes

	if (nodeTypeIdentifier == "parallel") {  //If the node is parallel

		for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the nodes connected to this node

			complex<double> impedanceForCalculation(circuitObjectPointerVector[i]->getImpedance());  //Get the impedance

			double absoluteImpedanceForCalculation{ abs(impedanceForCalculation) };  //Get the abs of impedance
			double argumentImpedanceForCalculation{ arg(impedanceForCalculation) };  //Get the arg of impedance

			double absoluteVoltageForCalculation{ abs(voltage) };  //Get the abs of voltage
			double argumentVoltageForCalculation{ arg(voltage) };  //Get the arg of voltage

			double currentAbsolute{ absoluteVoltageForCalculation / absoluteImpedanceForCalculation };  //  V/R = I
			double currentArgument{ argumentVoltageForCalculation - argumentImpedanceForCalculation };  //  Change in phase

			complex<double> forCurrent(polar(currentAbsolute, currentArgument));  //Current from calculations above

			circuitObjectPointerVector[i]->setVoltageAndCurrent(voltage, forCurrent);  //Set voltage and current of deeper components

			//Output of voltage and current data
			cout << "~~~~~~~~~~  " << circuitObjectPointerVector[i]->getComponentName() << "  ~~~~~~~~~~" << endl;
			cout << "Impedance: Magnitude = " << abs(impedanceForCalculation) << " Ohms ---  Phase = " << arg(impedanceForCalculation) * (180 / pi) << (char)248 << endl;
			cout << "Voltage:   Magnitude = " << abs(voltage) << " V ---  Phase = " << arg(voltage) * (180 / pi) << (char)248 << endl;
			cout << "Current:   Magnitude = " << abs(forCurrent) << " A --- Phase = " << arg(forCurrent) * (180 / pi) << (char)248 << endl << endl;

		}

	}
	else if (nodeTypeIdentifier == "series") {  //If the node is series	

		for (int i{ 0 }; i < (int)circuitObjectPointerVector.size(); i++) {  //For all the nodes connected to this node

			complex<double> impedanceForCalculation(circuitObjectPointerVector[i]->getImpedance());  //Get the impedance

			double absoluteImpedanceForCalculation{ abs(impedanceForCalculation) };  //Get the abs of impedance
			double argumentImpedanceForCalculation{ arg(impedanceForCalculation) };  //Get the arg of impedance

			double absoluteCurrentForCalculation{ abs(current) };  //Get the abs of voltage
			double argumentCurrentForCalculation{ arg(current) };  //Get the arg of voltage

			double voltageAbsolute{ absoluteCurrentForCalculation * absoluteImpedanceForCalculation };  //  V = IR
			double voltageArgument{ argumentCurrentForCalculation + argumentImpedanceForCalculation };  //  Change in phase

			complex<double> forVoltage(polar(voltageAbsolute, voltageArgument));  //Voltage from calculations above

			circuitObjectPointerVector[i]->setVoltageAndCurrent(forVoltage, current);  //Set voltage and current of deeper components

			//Output of bolrage and current data
			cout << "~~~~~~~~~~  " << circuitObjectPointerVector[i]->getComponentName() << "  ~~~~~~~~~~" << endl;
			cout << "Impedance: Magnitude = " << abs(impedanceForCalculation) << " Ohms --- Phase = " << arg(impedanceForCalculation) * (180 / pi) << (char)248 << endl;
			cout << "Voltage:   Magnitude = " << abs(forVoltage) << " V --- Phase = " << arg(forVoltage) * (180 / pi) << (char)248 << endl;
			cout << "Current:   Magnitude = " << abs(current) << " A --- Phase = " << arg(current) * (180 / pi) << (char)248 << endl << endl;
		}

	}
	else {  //Otherwise, the node will be a component

		circuitObjectPointerVector[0]->setVoltageAndCurrent(voltage, current);

	}

}

void circuitNode::setComponentName(string input) {}  //Set name does nothing
const string circuitNode::getComponentName() {  //Get Name gets the component name of node is a component
	if (nodeTypeIdentifier == "component") {
		return circuitObjectPointerVector[0]->getComponentName();
	}
	else return nodeName;
	string toReturn{ "" };
	return toReturn;
}

void circuitNode::setComponentResistance(double input) {}  //Set resistance does nothing
const double circuitNode::getComponentResistance() {  //Get resistance gets resistance if node is component
	if (nodeTypeIdentifier == "component") {
		return circuitObjectPointerVector[0]->getComponentResistance();
	}
	double toReturn{ 0 };
	return toReturn;
}

void circuitNode::setComponentCapacitance(double input) {}  //Set capacitance does nothing
const double circuitNode::getComponentCapacitance() {  //Get capacitance gets caparitance if node is component
	if (nodeTypeIdentifier == "component") {
		return circuitObjectPointerVector[0]->getComponentCapacitance();
	}
	double toReturn{ 0 };
	return toReturn;
}

void circuitNode::setComponentInductance(double input) {}  //Set Inductance does nothing
const double circuitNode::getComponentInductance() {  //Get inductance gets inductance if node is component
	if (nodeTypeIdentifier == "component") {
		return circuitObjectPointerVector[0]->getComponentInductance();
	}
	double toReturn{ 0 };
	return toReturn;
}