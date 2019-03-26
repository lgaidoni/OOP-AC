#include "CircuitComponent.h"  //Needs to get the component class

circuitComponent::circuitComponent() {  //Default constructor, sets x and y to 0
	x = 0;
	y = 0;
}

//Parameterised constructor, takes X, Y and options menu
circuitComponent::circuitComponent(const int forX, const int forY, options &options) {
	x = forX;  //Set x
	y = forY;  //Set y
}

const int circuitComponent::getX() { return x; }  //Get the x value
void circuitComponent::setX(int forX) { x = forX; }  //Set the x value
const int circuitComponent::getY() { return y; }  //Get the y value
void circuitComponent::setY(int forY) { y = forY; }  //Set the y value
const int circuitComponent::getNodeWidth() { return 1; }  //Get the node width (1)
const string circuitComponent::getNodeType() { return "component"; }  //Get the node type (component)
const string circuitComponent::getAppearance() { return appearance; }  //Get the appearance
const double circuitComponent::getResistance() { return componentResistance; }  //Get the resistance
const double circuitComponent::getCapacitance() { return componentCapacitance; }  //Get the capacitance
const double circuitComponent::getInductance() { return componentInductance; }  //Get the inductance

//Function to check if the component exists at an x and y value
bool circuitComponent::circuitObjectXYPositionCheck(const int xCheck, const int yCheck) {
	if (xCheck == x && yCheck == y) return true;  //If the component exists there, return true
	else return false;  //Otherwise, return false
}

//Function to check what kind of component exists at an x and y value (only called once position is true, so no need for checks)
string circuitComponent::circuitObjectXYTypeGet(const int xCheck, const int yCheck) { return appearance; }

//Function to check whether a parallel link exists at an x and y value (always returns false)
bool circuitComponent::checkParallelLinkLocations(const int xCheck, const int yCheck) { return false; }

//Function to display the circuit information, takes the options menu
const void circuitComponent::displayCircuitInformation(options options) {

	if (appearance == "R") {  //If the component is a resistor
		cout << "[" << componentName << "] Resistor: R = " << componentResistance;
		if (options.getCircuitNotIdeal() == true) {  //If the component is non-ideal
			cout << "  L = " << componentInductance;
		}
	}
	if (appearance == "C") {  //If the component is a capacitor
		cout << "[" << componentName << "] Capacitor: C = " << componentCapacitance;
		if (options.getCircuitNotIdeal() == true) {  //If the component is non-ideal
			cout << "  L = " << componentInductance;
		}
	}
	if (appearance == "L") {  //If the component is an inductor
		cout << "[" << componentName << "] Inductor: L = " << componentInductance;
		if (options.getCircuitNotIdeal() == true) {  //If the component is non-ideal
			cout << "  C = " << componentCapacitance;
		}
	}
	if (appearance == "X") {  //If the component is custom
		cout << "[" << componentName << "] Custom: Z = " << impedance;
	}

}

//Function to set the voltage and current
void circuitComponent::setVoltageAndCurrent(complex<double> voltage, complex<double> current) {

	voltageAcrossComponent = voltage;  //Sets the voltage
	currentAcrossComponent = current;  //Sets the current

}

const string circuitComponent::getComponentName() { return componentName; }  //Gets the componetn name
void circuitComponent::setComponentName(string input) { componentName = input; }  //Sets the component name
const double circuitComponent::getComponentResistance() { return componentResistance; }  //Gets the resistance
void circuitComponent::setComponentResistance(double input) { componentResistance = input; }  //Sets the resistance
const double circuitComponent::getComponentCapacitance() { return componentCapacitance; }  //Gets the capacitance
void circuitComponent::setComponentCapacitance(double input) { componentCapacitance = input; }  //Sets the capacitance
const double circuitComponent::getComponentInductance() { return componentInductance; }  //Gets the inductance
void circuitComponent::setComponentInductance(double input) { componentInductance = input; }  //Sets the inductance