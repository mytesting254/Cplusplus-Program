#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void displayMenu() {
	cout << "1. Display list of items and frequency of purchase." << endl;
	cout << "2. Display how many times a specific items is purchased." << endl;
	cout << "3. Produce a text-based histogram" << endl;
	cout << "4. Exit." << endl;
}

string removeSpaces(string str)
{   //removing the leading spaces from the integer
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

void histogramData()
{	
	string myText, itemFrequency, listItem;

	// Read from the text file
	ifstream MyReadFile("frequency.dat");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		
		// split string into two 
		itemFrequency = myText.substr(myText.find(" "), myText.length());

		listItem = myText.substr(0, myText.find(" "));
		// print the histogram
		cout << listItem << " " << string(stoi(removeSpaces(itemFrequency)), '*') << endl;
	}
	// close file when done
	MyReadFile.close();
}

void main()
{
	
	// variable declaration
	string userSelection;
	bool userValidation;

	// call to display the menu to the user
	displayMenu();
	cin >> userSelection;

	// validate user input to ensure only the right response is entered
	userValidation = !(userSelection >= "1" && userSelection <= "4");

	// utilize while loop to continously prompt the user for choices
	while (userValidation) {
		cout << "Invalid selection. Try again: " << endl;

		displayMenu();
		cin >> userSelection;

		userValidation = !(userSelection >= "1" && userSelection <= "4");
	}
	// deteremine what the user is trying to do based on the choices provided
	userValidation = (userSelection >= "1" && userSelection <= "4");

	while (userValidation)
	{	// print item list with frequency
		if (userSelection == "1") {
	
			CallProcedure("readData");
		}
		// look up item frequency
		if (userSelection == "2") {
			string userInput;

			cout << "Enter item to look up: " << endl;
			cin >> userInput;
			cout << callIntFunc("readData", userInput);
		}
		// display a histogram
		if (userSelection == "3") {
			CallProcedure("plotData");
			histogramData();
		}
		// break from code
		if (userSelection == "4") {
			break;
		}

		cout << endl;
		// prompt the user to keep them in the loop until they exit the sequence
		displayMenu();
		cin >> userSelection;
	}
}

