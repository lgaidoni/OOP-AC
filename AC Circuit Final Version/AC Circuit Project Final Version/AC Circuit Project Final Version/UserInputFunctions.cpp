#include "UserInputFunctions.h"

using namespace std;


//This function will ask the user what circuit they wish to enter next
const int circuitRequest() {

	cout << "Would you like a series node[1], a parallel node[2], or a component[3]: ";

	string request{ "" };  //String for asking what number the user would like
						   ///This is a string because there's a phenomenon that happens when asking for ints where if one were to enter 1abcde it would accept the number 1

	cin >> request;  //Ask the user what kind of node they'd like

	while (cin.fail() || !(request == "1" || request == "2" || request == "3")) {  //Whilst the user hasn't entered the correct input

		cout << "Would you like a series node[1], a parallel node[2], or a component[3]: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	stringstream toInt{ request };  //Stringstream for turning this into an int
	int toReturn;  //Integer to return
	toInt >> toReturn;  //Place the stringstream into the int value toReturn

	return toReturn;  //Return the int value

}

//This function will ask the user what kind of component they would like to enter
const int componentRequest() {

	cout << "Available Components:" << endl;
	cout << "Resistor ---------[1]" << endl;
	cout << "Capacitor --------[2]" << endl;
	cout << "Inductor ---------[3]" << endl;

	cout << endl;
	cout << "Please create a component: ";

	string request{ "" };  //String for asking what number the user would like
						   ///This is a string because there's a phenomenon that happens when asking for ints where if one were to enter 1abcde it would accept the number 1

	cin >> request;  //Ask the user what kind of component they'd like

	while (cin.fail() || !(request == "1" || request == "2" || request == "3")) {  //Whilst the user hasn't entered the correct input

		cout << "Please create a component[1-3]: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	stringstream toInt{ request };  //Stringstream for turning this into an int
	int toReturn;  //Integer to return
	toInt >> toReturn;  //Place the stringstream into the int value toReturn

	return toReturn;  //Return the int value

}

const int nodeNumber() {  //This function asks how many nodes are connected to this node

	cout << "Please enter the number of nodes connected to this node: ";

	int request;

	cin >> request;

	while (cin.fail() || !(request >= 1 && request <=5)) {

		cout << "Please enter the number of nodes connected to this node: ";
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	return request;

}

const string createLibrary() {  //This function asks if the library is to be made

	cout << "Would you like to create a component library? Y/N: ";

	string request{ "" };
	cin >> request;

	while (cin.fail() || !(request == "Y" || request == "N" || request == "y" || request == "n")) {  //Whilst the user hasn't entered the correct input

		cout << "Would you like to create a component library? Y/N: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	return request;  //Return the string

}

const string addAnotherComponent() {  //This function asks whether the user wants to add more components

	cout << "Would you like to add another component? Y/N: ";

	string request{ "" };
	cin >> request;

	while (cin.fail() || !(request == "Y" || request == "N" || request == "y" || request == "n")) {  //Whilst the user hasn't entered the correct input

		cout << "Would you like to add another component? Y/N: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	return request;  //Return the string

}

const int optionsRequest() {  //This function asks which option the user would like to choose

		cout << "Which option would you like to select: ";

		string request{ "" };  //String for asking what number the user would like
							   ///This is a string because there's a phenomenon that happens when asking for ints where if one were to enter 1abcde it would accept the number 1

		cin >> request;  //Ask the user what kind of nore they'd like

		while (cin.fail() || !(request == "1" || request == "2" || request == "3" || request == "4" || request == "5" || request == "6")) {  //Whilst the user hasn't entered the correct input

			cout << "Which option would you like to select [1-6]: ";  //Tell the user what the options are
			cin.clear();  //Clear the cin error
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
			cin >> request;  //Accept user input once more

		}

		stringstream toInt{ request };  //Stringstream for turning this into an int
		int toReturn;  //Integer to return
		toInt >> toReturn;  //Place the stringstream into the int value toReturn

		return toReturn;  //Return the int value

}

const int mainProgramRequest() {  //This function asks whether the user wants to open the options menu

	cout << "          Please select an option: ";

	string request{ "" };  //String for asking what number the user would like
						   ///This is a string because there's a phenomenon that happens when asking for ints where if one were to enter 1abcde it would accept the number 1

	cin >> request;  //Ask the user what kind of nore they'd like

	while (cin.fail() || !(request == "1" || request == "2")) {  //Whilst the user hasn't entered the correct input

		cout << "          Please select an option [1-2]: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	stringstream toInt{ request };  //Stringstream for turning this into an int
	int toReturn;  //Integer to return
	toInt >> toReturn;  //Place the stringstream into the int value toReturn

	return toReturn;  //Return the int value

}

const string saveToLibrary() {  //This function asks whether to save the circuit to a component and add to library

	cout << "Would you like to save this circuit as a component in the component library and continue? Y/N: ";

	string request{ "" };
	cin >> request;

	while (cin.fail() || !(request == "Y" || request == "N" || request == "y" || request == "n")) {  //Whilst the user hasn't entered the correct input

		cout << "Would you like to save this circuit as a component in the component library and continue? Y/N: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	return request;  //Return the string

}

const string usingWindows7() {  //This function asks if the library is to be made

	cout << "Are you using Windows 7? Y/N: ";

	string request{ "" };
	cin >> request;

	while (cin.fail() || !(request == "Y" || request == "N" || request == "y" || request == "n")) {  //Whilst the user hasn't entered the correct input

		cout << "Are you using Windows 7? Y/N: ";  //Tell the user what the options are
		cin.clear();  //Clear the cin error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore what was previously in cin
		cin >> request;  //Accept user input once more

	}

	return request;  //Return the string

}