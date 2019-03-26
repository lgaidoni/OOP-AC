#include "Inductor.h"  //Need to get the inductor class

int inductor::inductorCount{ 0 };  //Initialise the inductor count static

inductor::inductor() {  //Default constructor
	inductorCount++;  //Increment the inductor count
	appearance = "L";  //Set the appearance of the empty inductor to L
	double resistance{ 0 };  //Set its resistance to 0
	double reactance{ 0 };  //Set its reactance to 0
	complex<double> forImpedance(resistance, reactance);  //Create the impedance using resistance and reactance
	impedance = forImpedance;  //Set the impedance using forImpedance
}

//Parameterised Constructor, takes X position, Y position, and the options menu. Passes these into the circuitComponent constructor
inductor::inductor(const int forX, const int forY, options &options) : circuitComponent(forX, forY, options) {

	inductorCount++;  //Increment the inductor count
	stringstream forComponentName;  //Strginstream for the name
	forComponentName << "L" << inductorCount;  //Name the component
	componentName = forComponentName.str();  //Save the name
	appearance = "L";  //Set the appearance

	double inductance;  //Create an inductance varialbe to have data input into it
	double resistance{ 0 };//Create a resistance variable for the purposes of creating the complex impedance
	componentResistance = resistance;  //Set resistance to 0

	cout << "Please enter the Inductance of this component: ";	//Ask the user for the inductance
	cin >> inductance;  //Take a value
	while (cin.fail() || !(inductance >= 1e-9 && inductance <= 1)) {  //If out of bounds or failed
		cout << "Please enter the Capacitance of the component [1nH - 1H]: ";
		cin.clear();  //Clear cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore previous inputs for cin
		cin >> inductance;  //Take a value again
	}
	componentInductance = inductance;  //Set the inductance

	double reactance{ inductance * options.getFrequency() * 2 * pi };  //Set the reactance

	if (options.getCircuitNotIdeal() == true) {  //If the circuit is not ideal
		double capacitance;  //Stores the parasitic capacitance
		cout << "Please enter the Parasitic Capacitance of this component: ";  //Ask for it
		cin >> capacitance;  //Take a value
		while (cin.fail() || !(capacitance >= 1e-12 && capacitance <= 10e-3)) {  //While the input is not correct
			cout << "Please enter the Parasitic Capacitance of this component [1pF - 10mF]: ";  //Ask again
			cin.clear();  //Clear cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what's in cin
			cin >> capacitance;  //Take a new value
		}
		componentCapacitance = capacitance;  //Set the component capacitance to be the taken value
		reactance *= (1 / (1 - (pow(options.getFrequency() * 2 * pi,2) * capacitance * inductance)));  //multiply in parasitic inductance to the reactance
	}

	complex<double> forImpedance(resistance, reactance);  //create a complex value for impedance
	impedance = forImpedance;  //Set the impedance of the component

}

inductor::~inductor() { inductorCount--; }  //Destructo, decrease inductorCount by 1

void inductor::setImpedance(const double forResistance, const double forReactance) {  //Function to set impedance
	complex<double> forImpedance(forResistance, forReactance);  //Take given resistance and reactance and create temp complex impedance
	impedance = forImpedance;  //Set impedance equal to temp value
}

void inductor::setImpedance(const complex<double> forImpedance) {  //Function to set impedance if given a complex impedance
	impedance = forImpedance;  //Set impedance to given impedance
}

const double inductor::getResistance() { return real(impedance); }  //Get real resistance
const double inductor::getReactance() { return imag(impedance); }  //Get imaginary reactance
const complex<double> inductor::getImpedance() { return impedance; }  //Get complex impedance