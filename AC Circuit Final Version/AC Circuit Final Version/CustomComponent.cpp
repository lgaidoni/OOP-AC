#include "CustomComponent.h"

int customComponent::customComponentCount{ 0 };  //Initialise the counter for custom components

customComponent::customComponent() {  //Default constructor
	customComponentCount++;  //Increment the custom count
	appearance = "X";  //Set the appearance of the custom component to X
	double resistance{ 0 };  //Set its resistance to 0
	double reactance{ 0 };  //Set its reactance to 0
	complex<double> forImpedance(resistance, reactance);  //Create the impedance using resistance and reactance
	impedance = forImpedance;  //Set the impedance using forImpedance
}

//Parameterised Constructor, takes X position, Y position, the options menu, and a complex impedance. Passes all but impeance into the circuitComponent constructor
customComponent::customComponent(const int forX, const int forY, options &options, complex<double> forImpedance) : circuitComponent(forX, forY, options) {

	customComponentCount++;  //Increment the custom count
	stringstream forComponentName; //Create a stringstream for the name of the component
	forComponentName << "X" << customComponentCount;  //Name the component
	componentName = forComponentName.str();  //Save the name of the component

	appearance = "X";  //Set the appearance of the component

	//Set all three parameters to 0, custom doesn't need them
	componentResistance = 0;
	componentInductance = 0;
	componentCapacitance = 0;

	//Set the impedance of the component directly
	impedance = forImpedance;

}

customComponent::~customComponent() { customComponentCount--; }  //Destructor for the custom component, decreases custom component count

void customComponent::setImpedance(const double forResistance, const double forReactance) {  //Function to set impedance
	complex<double> forImpedance(forResistance, forReactance);  //Take given resistance and reactance and create temp complex impedance
	impedance = forImpedance;  //Set impedance equal to temp value
}

void customComponent::setImpedance(const complex<double> forImpedance) {  //Function to set impedance if given a complex impedance
	impedance = forImpedance;  //Set impedance to given impedance
}

const double customComponent::getResistance() { return real(impedance); }  //Get real resistance
const double customComponent::getReactance() { return imag(impedance); }  //Get imaginary reactance
const complex<double> customComponent::getImpedance() { return impedance; }  //Get complex impedance