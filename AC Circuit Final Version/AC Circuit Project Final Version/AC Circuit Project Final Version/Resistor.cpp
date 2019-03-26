#include "Resistor.h"  //Need to get the resistor class

int resistor::resistorCount{ 0 };  //Initialise the resistor count static

resistor::resistor() {  //Default constructor
	resistorCount++;  //Increment the resistor count
	appearance = "R";  //Set the appearance of the empty resistor to R
	double resistance{ 0 };  //Set its resistance to 0
	double reactance{ 0 };  //Set its reactance to 0
	complex<double> forImpedance(resistance, reactance);  //Create the impedance using resistance and reactance
	impedance = forImpedance;  //Set the impedance using forImpedance
}

//Parameterised Constructor, takes X position, Y position, and the options menu. Passes these into the circuitComponent constructor
resistor::resistor(const int forX, const int forY, options &options) : circuitComponent(forX, forY, options) {

	resistorCount++;  //Increment the resistor count
	stringstream forComponentName;  //Strginstream for the name
	forComponentName << "R" << resistorCount;  //Name the component
	componentName = forComponentName.str();  //Save the name
	appearance = "R";  //Set the appearance

	double resistance;//Create a resistance varialbe to have data input into it
	double reactance{ 0 };//Create a reactance variable for the purposes of creating the complex impedance
	componentCapacitance = 0; //set capacitance to 0

	cout << "Please enter the Resistance of this component: ";	//Ask the user for the resistance
	cin >> resistance;  //Take a value
	while (cin.fail() || !(resistance > 0.01 && resistance < 1000)) {  //If out of bounds or failed
		cout << "Please enter the Resistance of the component [0.01 Ohms - 1000 Ohms]: ";
		cin.clear();  //Clear cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore previous inputs for cin
		cin >> resistance;  //Take a value again
	}
	componentResistance = resistance;  //Set the resistance

	if (options.getCircuitNotIdeal() == true) {  //If the circuit is not ideal
		double inductance;  //Stores the parasitic inductance 
		cout << "Please enter the Parasitic Inductance of this component: ";  //Ask for it
		cin >> inductance;  //Take a value
		while (cin.fail() || !(inductance > 1e-9 && inductance < 1)) {  //While the input is not correct
			cout << "Please enter the Parasitic Inductance of this component [1nH - 1H]: ";  //Ask again
			cin.clear();  //Clear cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what's in cin
			cin >> inductance;  //Take a new value
		}
		componentInductance = inductance;  //Set the component Inductance to be the taken value
		reactance = inductance * options.getFrequency() * 2 * pi;  //set the parasitic inductance for the reactance
	}

	complex<double> forImpedance(resistance, reactance);  //create a complex value for impedance
	impedance = forImpedance;  //Set the impedance of the component

}

resistor::~resistor() { resistorCount--; }  //Destructor, decrease resistorCount by 1

void resistor::setImpedance(const double forResistance, const double forReactance) {  //Function to set impedance
	complex<double> forImpedance(forResistance, forReactance);  //Take given resistance and reactance and create temp complex impedance
	impedance = forImpedance;  //Set impedance equal to temp value
}

void resistor::setImpedance(const complex<double> forImpedance) {  //Function to set impedance if given a complex impedance
	impedance = forImpedance;  //Set impedance to given impedance
}

const double resistor::getResistance() { return real(impedance); }  //Get real resistance
const double resistor::getReactance() { return imag(impedance); }  //Get imaginary reactance
const complex<double> resistor::getImpedance() { return impedance; }  //Get complex impedance