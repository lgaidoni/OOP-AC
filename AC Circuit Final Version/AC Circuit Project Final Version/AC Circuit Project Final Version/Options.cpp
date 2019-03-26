#include "Options.h"  //Need the options class

options::options() {} //This is the default constructor

options::~options() {}  //This is the destructor

//These functions set voltage, frequency, component library exists, draw circuit, and circuit ideality
void options::setVoltage(const double forVoltage) { voltage = forVoltage; }
void options::setFrequency(const double forFrequency) { frequency = forFrequency; }
void options::setComponentLibraryExists(const bool input) { componentLibraryExists = input; }
void options::setWillDrawCircuit(const bool input) { willDrawCircuit = input; }
void options::setCircuitNotIdeal(const bool input) { circuitNotIdeal = input; }

//These functions get the values for voltage, frequency, component library exists, draw circuit, and circuit ideality
const double options::getVoltage() { return voltage; }
const double options::getFrequency() { return frequency; }
const bool options::getComponentLibraryExists() { return componentLibraryExists; }
const bool options::getWillDrawCircuit() { return willDrawCircuit; }
const bool options::getCircuitNotIdeal() { return circuitNotIdeal; }

const void options::getSettings() {  //This function gets the current settings and outputs them
	cout << "           Current Program Settings" << endl;
	cout << "      Component Library Exists:     "; 
	if (componentLibraryExists == false) cout << "False";
	else cout << "True";
	cout << endl;
	cout << "      Circuit Will Be Drawn:        ";
	if (willDrawCircuit == false) cout << "False";
	else cout << "True";
	cout << endl;
	cout << "      Circuit Is Ideal:             ";
	if (circuitNotIdeal == false) cout << "True";
	else cout << "False";
	cout << endl;
	cout << "      Voltage across circuit:       " << voltage << " V" <<  endl;
	cout << "      Frequency across circuit:     " << frequency << " Hz" << endl;
}

void options::askVoltage() {  //This function asks for voltage

	cout << "Please enter the new voltage [1V - 50000V]: ";
	double forVoltage;
	cin >> forVoltage;  //Ask for voltage
	while (cin.fail() || forVoltage < 1 || forVoltage > 50000) {  //Whilst the user enters a value not in range

		cout << "Please enter the new voltage [1V - 50000V]: ";
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> forVoltage;  //Accept user input once more

	}

	this->setVoltage(forVoltage);  //Set the voltage for the options

}

void options::askFrequency() {  //This function asks for frequency

	cout << "Please enter the new frequency [1Hz- 15MHz]: ";
	double forFrequency;
	cin >> forFrequency;  //Ask for frequency
	while (cin.fail() || forFrequency < 1 || forFrequency > 15000000) {  //Whilst the user enters a value not in range

		cout << "Please enter the new frequency [1Hz - 15MHz]: ";
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> forFrequency;  //Accept user input once more

	}

	this->setFrequency(forFrequency);  //Set the frequency for the options

}

void options::askComponentLibraryExists() {  //Ask the user if the components library exists

	string libraryExists{ createLibrary() };  //Ask the user if the component library exists

	if (libraryExists == "Y" || libraryExists == "y") setComponentLibraryExists(true);  //If yes, set to true
	else if (libraryExists == "N" || libraryExists == "n") setComponentLibraryExists(false);  //If no, set to false

}

void options::askWillDrawCircuit() {  //Should the circuit be drawn?

	cout << "Would you like the circuit to be drawn? Y/N: ";

	string request{ "" };

	cin >> request;  //Ask the user

	while (cin.fail() || !(request == "Y" || request == "N" || request == "y" || request == "n")) {  //Whilst the user hasn't entered the correct input

		cout << "Would you like to create a component library? Y/N: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	if (request == "Y" || request == "y") setWillDrawCircuit(true);  //If yes, set true
	else if (request == "N" || request == "n") setWillDrawCircuit(false);  //If no, set false

}

void options::askCircuitNotIdeal() {  //This function will ask the user if the circuit is ideal

	cout << "Is the circuit ideal? Y/N: ";

	string request{ "" };

	cin >> request;  //Ask the user

	while (cin.fail() || !(request == "Y" || request == "N" || request == "y" || request == "n")) {  //Whilst the user hasn't entered the correct input

		cout << "Is the circuit ideal? Y/N: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	if (request == "Y" || request == "y") setCircuitNotIdeal(false);  //If the user says yes, the circuit is ideal, so set NotIdeal to false
	else if (request == "N" || request == "n") setCircuitNotIdeal(true);  //If the user says no, the circuit is not ideal, so set NotIdeal to true

}

void options::openOptionsMenu() {  //This function will open the options menu

	bool keepChangingOptions{ true };  //Bool for ending the options loop

	while (keepChangingOptions == true) {  //Whilst the user wants to change options

		system("CLS"); //Clear the console
		
		//Output current options, and what number they correspond to
		cout << "/////////////////////////OPTIONS MENU///////////////////////////" << endl << endl;
		cout << "Existance of Components Library ------- [1] : Currently ";
		if (componentLibraryExists == false) cout << "False";
		else cout << "True";
		cout << endl;
		cout << "Circuit will be drawn ----------------- [2] : Currently ";
		if (willDrawCircuit == false) cout << "False";
		else cout << "True";
		cout << endl;
		cout << "Circuit is ideal ---------------------- [3] : Currently ";
		if (circuitNotIdeal == false) cout << "True";
		else cout << "False";
		cout << endl;
		cout << "Voltage ------------------------------- [4] : Currently " << voltage << " V" << endl;
		cout << "Frequency ----------------------------- [5] : Currently " << frequency << " Hz" << endl;
		cout << "Back to main program ------------------ [6]" << endl << endl;

		int chosenOption{ optionsRequest() };  //Ask the user which option they want to choose

		if (chosenOption == 1) {  //Edit Components Library Exists
			askComponentLibraryExists();
		}
		else if (chosenOption == 2) {  //Edit Circuit Will Be Drawn
			askWillDrawCircuit();
		}
		else if (chosenOption == 3) {  //Edit circuitNotIdeal
			askCircuitNotIdeal();
		}
		else if (chosenOption == 4) {  //Voltage
			askVoltage();
		}
		else if (chosenOption == 5) {  //Frequency
			askFrequency();
		}
		else if (chosenOption == 6) {  //Back to main program
			keepChangingOptions = false;
		}

	}

}