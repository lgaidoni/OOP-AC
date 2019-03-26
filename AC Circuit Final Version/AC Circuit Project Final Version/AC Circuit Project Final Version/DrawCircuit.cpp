#include "DrawCircuit.h"  //Need the function definition

//This function will draw the circuit, it takes a circuit object, the options meny, and the component library
void drawCircuit(circuitObject* newCircuit, options options, vector<circuitObject*> components) {

	int sizeX{ 80 };  //Size of the width
	int sizeY{ 25 };  //Size of the height

	system("CLS");  //Clear the console

	for (int y{ 0 }; y < sizeY; y++) {  //For every y position

		for (int x{ 0 }; x < sizeX; x++) {  //For every x position

			bool componentExists{ newCircuit->circuitObjectXYPositionCheck(x, y) };  //Check if a component exists there
			bool parallelLinkExists{ newCircuit->checkParallelLinkLocations(x, y) };  //Check is a parallel link exists there

			//Draw the border
			if (y == 0 && x != 0 && x != sizeX - 1) cout << "-";
			else if (y == sizeY - 1 && x != 0 && x != sizeX - 1) cout << "-";
			else if (x == 0 && y != 0 && y != sizeY - 1) cout << "|";
			else if (x == sizeX - 1 && y != 0 && y != sizeY - 1) cout << "|";
			//If the component exists at that position
			else if (componentExists == true) {
				string objectType{ newCircuit->circuitObjectXYTypeGet(x, y) };  //Get its type
				cout << objectType;  //Draw component
			}
			else if (parallelLinkExists == true) cout << "_";  //Of a parallel linker exists, draw it
			else cout << " ";  //Otherwise, draw a space

		}

		if (options.getComponentLibraryExists() == true) {	//If the component library exists

			if (y <= (int)components.size()) {  //If y is less than number of components

				if (y == 0) cout << "        COMPONENTS:";  //output the head line
				if (y != 0) {  //output the y-1 th component in the list (0 to max)
					cout << " [" << y << "] ";
					components[y - 1]->displayCircuitInformation(options);
				}

			}

		}

		cout << endl;

	}

}