#include "ComponentLibraryCreator.h"  //Need the function definition

vector<circuitObject*> createComponentsLibrary(options options) {  //Function to create the component library given options

	vector<circuitObject*> components;  //Creates a vector of base class pointers

	int tempX{ 100 };  //Temp x position
	int tempY{ 100 };  //Temp y position

	bool endComponentCreationLoop{ false };  //bool for ending the creation loop

	while (endComponentCreationLoop == false) {  //Whilst the creation loop should continue

		system("CLS");  //Clear the screen
		
		cout << "Creating Component Library" << endl << endl;

		cout << "Current Components:" << endl << endl;
		for (int i{ 0 }; i < (int)components.size(); i++) {  //For all the components in the components vector

			cout << "[" << i + 1 << "] ";  //Output number of component
			components[i]->displayCircuitInformation(options);  //Output the information about that component
			cout << endl;

		}

		cout << endl;

		int desiredComponent{ componentRequest() };  //Ask what kind of component the user wants

		//Push back desired component into components vector
		if (desiredComponent == 1) components.push_back(new resistor(tempX, tempY, options));
		else if (desiredComponent == 2) components.push_back(new capacitor(tempX, tempY, options));
		else if (desiredComponent == 3) components.push_back(new inductor(tempX, tempY, options));

		string endLoop{ addAnotherComponent() };  //Does the user want to add another component

		if (endLoop == "N" || endLoop == "n") {  //If they don't want to add another component

			endComponentCreationLoop = true;  //end the loop

		}

	}

	return components;  //Return the components library

}