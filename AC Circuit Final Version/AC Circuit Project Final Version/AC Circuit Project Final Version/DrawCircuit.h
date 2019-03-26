#pragma once
//Normal includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

//User created headers
#include "CircuitObject.h"
#include "Options.h"

//This function will draw the circuit, it takes a circuit object, the options meny, and the component library
void drawCircuit(circuitObject* newCircuit, options options, vector<circuitObject*> components);