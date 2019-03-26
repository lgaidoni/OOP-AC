#include "Capacitor.h"  //Need to get the capacitor class

int capacitor::capacitorCount{ 0 };  //Initialise the capacitor count static

capacitor::capacitor() {  //Default constructor
	capacitorCount++;  //Increment the capacitor count
	appearance = "C";  //Set the appearance of the empty capacitor to C
	double resistance{ 0 };  //Set its resistance to 0
	double reactance{ 0 };  //Set its reactance to 0
	complex<double> forImpedance(resistance, reactance);  //Create the impedance using resistance and reactance
	impedance = forImpedance;  //Set the impedance using forImpedance
}

//Parameterised Constructor, takes X position, Y position, and the options menu. Passes these into the circuitComponent constructor
capacitor::capacitor(const int forX, const int forY, options &options) : circuitComponent(forX, forY, options) {

	capacitorCount++;  //Increment the capacitor count
	stringstream forComponentName;  //Create a stringstream for the name of the component
	forComponentName << "C" << capacitorCount;  //Set the name of the component to be C + however many capacitors there are
	componentName = forComponentName.str();  //Set the name itself, taking from the stringstream
	appearance = "C";  //Set the apperance of the capacitor to C

	double capacitance;  //Create a capacitance varialbe to have data input into it
	double resistance{ 0 };  //Create a resistance variable for the purposes of creating the complex impedance
	componentResistance = resistance;  //Set the component resistance to be equal to the resistance

	cout << "Please enter the Capacitance of this component: ";	//Ask the user for the capacitance
	cin >> capacitance;  //Take a value of capacitance
	while (cin.fail() || !(capacitance >= 1e-12 && capacitance <= 10e-3)) {  //If the capacitance isn't within the bounds of accepted values
		cout << "Please enter the Capacitance of the component [1pF - 10mF]: ";  //Ask again
		cin.clear();  //Clear cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore previous inputs for cin
		cin >> capacitance;  //Take a value of capacitance again
	}
	componentCapacitance = capacitance;  //Set the component Capcitance to the input capacitance

	double reactance{ -1 / (capacitance * options.getFrequency() * 2 * pi) };  //Set the reactance equal to X = -1/wC

	if (options.getCircuitNotIdeal() == true) {  //If the circuit is not ideal
		double inductance;  //Stores the parasitic inductance of the capacitor
		cout << "Please enter the Parasitic Inductance of this component: ";  //Ask for it
		cin >> inductance;  //Take a value for parasitic inductance
		while (cin.fail() || !(inductance >= 1e-9 && inductance <= 1)) {  //While the input is not correct
			cout << "Please enter the Parasitic Inductance of this component [1nH - 1H]: ";  //Ask again
			cin.clear();  //Clear cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what's in cin
			cin >> inductance;  //Take a new value for inductance
		}
		componentInductance = inductance;  //Set the component Inductance to be the taken value
		reactance += inductance * options.getFrequency() * 2 * pi;  //Add the parasitic inductance to the reactance
		/// Z = i(-1/wC + wL)
	}

	complex<double> forImpedance(resistance, reactance);  //create a complex value for impedance
	impedance = forImpedance;  //Set the impedance of the component

}

capacitor::~capacitor() { capacitorCount--; }  //Destructor for the capacitor count, decrease capacitorCount by 1

void capacitor::setImpedance(const double forResistance, const double forReactance) {  //Function to set impedance
	complex<double> forImpedance(forResistance, forReactance);  //Take given resistance and reactance and create temp complex impedance
	impedance = forImpedance;  //Set impedance equal to temp value
}

void capacitor::setImpedance(const complex<double> forImpedance) {  //Function to set impedance if given a complex impedance
	impedance = forImpedance;  //Set impedance to given impedance
}

const double capacitor::getResistance() { return real(impedance); }  //Get real resistance
const double capacitor::getReactance() { return imag(impedance); }  //Get imaginary reactance
const complex<double> capacitor::getImpedance() { return impedance; }  //Get complex impedance