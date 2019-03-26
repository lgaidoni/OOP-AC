//Luca Gaidoni 9483450
//This program will implement an AC circuit 

//Here are the base includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <chrono>
#include <thread>

using namespace std;

//Here are the includes for header files created by me
#include "Options.h"
#include "CircuitNode.h"
#include "DrawEmpty.h"
#include "DrawCircuit.h"
#include "Resistor.h"
#include "CustomComponent.h"
#include "UserInputFunctions.h"
#include "ComponentLibraryCreator.h"

////////////////////////////////////////////////////////////
///To save time running the code multiple times, one can copy this into the console when asked to select an option and press enter, and it will generate a circuit
///This is the demo circuit used in the report
///1 1 y 4 120 5 60 6 1 470 y 2 4.7e-6 y 2 1.5e-6 y 3 650e-3 n 1 2 3 2 2 2 1 2 3 4 3 3 3 1
///////////////////////////////////////////////////////////

//Here is the main function
int main() {

	string windows7{ usingWindows7() };  //For determining if the user is on windows 7 or not
	if (windows7 == "Y" || windows7 == "y") {  //If the user is on windows 7, inform them of how to resize the window
		cout << endl << endl;
		cout << "                You are on Windows 7" << endl;
		cout << "        Please right click on the title bar" << endl;
		cout << "Click Propties->Layout and set window size to at least 150";
		cout << endl << endl << endl << endl;
		this_thread::sleep_for(chrono::seconds(10));  //Leave the message on screen for 10 seconds
	}
	else cout << endl << endl << "Please resize the window to at least 1200x700" << endl << endl;  //Otherwise, tell the user the reccommended window size
	//This is the only way to resize the window on windows 7 without using the <Windows.h> external library
	//as it is an external library, and it will prevent the program from working correctly on a mac/linux machine

	//This is the components library
	vector<circuitObject*> components;

	options options; //This is where the options are created

	bool programRuns{ true };

	//These are the default options
	///These can be changed here, but are also changeable from within the program
	options.setWillDrawCircuit(true);
	options.setComponentLibraryExists(true);
	options.setCircuitNotIdeal(false);
	options.setVoltage(240);
	options.setFrequency(50);

	cout << "//////////////////////////////////////////////////" << endl; //50 wide
	cout << "///                                            ///" << endl;
	cout << "///            AC CIRCUIT DESIGNER             ///" << endl;
	cout << "///          Luca Gaidoni -- 9483450           ///" << endl;
	cout << "///                                            ///" << endl;
	cout << "///         Third Year OOP C++ Project         ///" << endl;
	cout << "///                                            ///" << endl;
	cout << "//////////////////////////////////////////////////" << endl;
	cout << endl << endl;
	cout << "It is reccommended to make the console as large as" << endl;
	cout << "possible to ensure correct visual representation  " << endl;
	cout << endl << endl;
	options.getSettings();  //Display the current program settings
	cout << endl << endl;

	//Here the user will be asked what they would like to do
	cout << "           What would you like to do?" << endl << endl;
	cout << "      Open Options Menu -------- [1]" << endl;
	cout << "      Create a circuit --------- [2]" << endl << endl;

	int mainProgramOption{ mainProgramRequest() };  //Ask the user for their option

	if (mainProgramOption == 1) options.openOptionsMenu();  //If the user chose to open the options menu

	if (options.getComponentLibraryExists() == true) {  //If the user wanted to create a component library

		components = createComponentsLibrary(options);  //Create the components library
		///This is technically a shallow copy of all the objects within the components vector
		///This is desired in order to save memory

	}

	while (programRuns == true) {


		drawEmpty(options, components);  //Here the circuit is drawn (Just an empty box)

		using chrono::system_clock;  //Use the system clock

		auto preCircuitCreation = system_clock::now();  //Make a start time for circuit calculation time
		circuitNode newCircuit(40, 1, 40 / 2, options, components);  //Here the main circuit is created
		auto postCircuitCreation = system_clock::now();  //Make an end time for circuit calculation time

		chrono::duration<double> circuitCreationTime = postCircuitCreation - preCircuitCreation;  //How long it took to make the circuit

		system("CLS");  //Clear the screen

		//If the circuit is to be drawn, then draw it
		if (options.getWillDrawCircuit() == true) drawCircuit(&newCircuit, options, components);

		auto preVoltageAndCurrentCalculation = system_clock::now();  //Make a start time for the voltage calculation time

		complex<double> newCircuitImpedance(newCircuit.getImpedance());  //Get the impedance of the circuit
		complex<double> voltage(options.getVoltage(), 0);  //Create a complex voltage

		double absoluteImpedanceForCalculation{ abs(newCircuitImpedance) };  //Get the abs of the impedance
		double argumentImpedanceForCalculation{ arg(newCircuitImpedance) };  //Get the arg of the impedance

		double absoluteVoltageForCalculation{ abs(voltage) };  //Get the abs of the voltage
		double argumentVoltageForCalculation{ arg(voltage) };  //Get the arg of the voltage

		//Here V/Z = I is performed to be given to a complex current
		double currentAbsolute{ absoluteVoltageForCalculation / absoluteImpedanceForCalculation };
		double currentArgument{ argumentVoltageForCalculation - argumentImpedanceForCalculation };

		complex<double> current(polar(currentAbsolute, currentArgument));  //Here a complex current is created

		//The complex voltage and current is calculated for every component in the 
		cout << "Component Impedances, Voltages and Currents are listed in the order they were placed: " << endl;
		cout << "Parallel and Series subcircuits output their Voltages and currents in completion order: " << endl << endl;
		newCircuit.setVoltageAndCurrent(voltage, current);

		auto postVoltageAndCurrentCalculation = system_clock::now();  //Make an end time for the voltage calculation time

		chrono::duration<double> voltageAndCurrentCalculationTime = postVoltageAndCurrentCalculation - preVoltageAndCurrentCalculation;  //How long it took to calculate voltage

		//Here the impedance of the circuit is output for the user to see.
		cout << "Impedance of circuit:            Magnitude = " << abs(newCircuitImpedance) << " Ohms --- Phase = " << arg(newCircuitImpedance) * (180 / pi) << (char)248 << endl;
		cout << "Voltage across circuit:          Magnitude = " << abs(voltage) << " V --- Phase = " << arg(voltage) * (180 / pi) << (char)248 << endl;
		cout << "Current across circuit:          Magnitude = " << abs(current) << " A --- Phase = " << arg(current) * (180 / pi) << (char)248 << endl;
		cout << "Circuit created in:              " << circuitCreationTime.count() << "s" << endl;
		cout << "Voltage/Current calculated in:   " << voltageAndCurrentCalculationTime.count() << "s" << endl << endl;

		string saveComponentToLibrary{ saveToLibrary() };  //Ask if the user wants to save this circuit as a component

		if (saveComponentToLibrary == "Y" || saveComponentToLibrary == "y") {  //If yes

			int tempX{ 100 };  //Create a temp X
			int tempY{ 100 };  //Create a temp Y

			//If the component library exists, push the custom component into the circuit
			if (options.getComponentLibraryExists() == true) components.push_back(new customComponent(tempX, tempY, options, newCircuit.getImpedance()));
			//If the component library doesn't exist, set it to exist, then push the custom component into the circuit
			else {
				options.setComponentLibraryExists(true);
				components.push_back(new customComponent(tempX, tempY, options, newCircuit.getImpedance()));
			}

		}
		else { programRuns = false; }  //Otherwise, the loop will end

		newCircuit.~circuitNode();  //Here the circuit for this loop is destructed

	}

	for (auto current = components.begin(); current < components.end(); ++current) {  //For all the components in the library

		delete *current;  //Delete the components

	}

	components.clear();  //Clear the components vector

	return 0;
}