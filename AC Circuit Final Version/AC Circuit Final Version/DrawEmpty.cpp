#include "DrawEmpty.h"  //Need the function definition

//This function will draw the empty circuit (just box and components)
void drawEmpty(options options, vector<circuitObject*> components) {

	int sizeX{ 80 };  //Size of the width
	int sizeY{ 25 };  //Size of the height

	system("CLS");  //Clear the console

	for (int y{ 0 }; y < sizeY; y++) {  //For every y position

		for (int x{ 0 }; x < sizeX; x++) {  //For every x position

			//Draw the border
			if (y == 0 && x != 0 && x != sizeX - 1) cout << "-";
			else if (y == sizeY - 1 && x != 0 && x != sizeX - 1) cout << "-";
			else if (x == 0 && y != 0 && y != sizeY - 1) cout << "|";
			else if (x == sizeX - 1 && y != 0 && y != sizeY - 1) cout << "|";
			else cout << " ";
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