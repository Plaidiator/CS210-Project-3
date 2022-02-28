#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>

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
void CallProcedure(string pName, string param = "a")       // param is given default value a to allow for access without a parameter
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* pValue = Py_BuildValue("(i)", param);                      // Added as per announcements
	PyObject* my_result = PyObject_CallObject(my_function, pValue);
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
int callIntFunc(string proc, string param)  // This function is used to return a value from python, CallProcedure is used when return is not needed
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

int menu() {
	int userInput;
	// Open text list
	ifstream listIn("grocceryItems.txt");
	// Initialize vector for items
	vector<string> listVec;

	string item;
	// Put each item from the .txt file into the vector
	while (listIn >> item) {
		listVec.push_back(item);
	}

	// Display menu to user
	cout << "Select an option: " << endl;
	cout << "1: Show items purchased today" << endl;
	cout << "2: Show number of purchases of item" << endl;
	cout << "3: Display item purchases as graph" << endl;
	cout << "4: Exit" << endl << endl;
	cout << "Enter selection: ";

	// Take input
	cin >> userInput;
	// Show user their input
	cout << "You entered: " << userInput << endl;
	// Wait for user to continue
	cout << "Press any key to continue..." << endl;
	getch();   // proceed when user presses a key
	cout << endl;

	// call python function based on user input
	if (userInput == 1) {
		// call allFrequency
		CallProcedure("allFrequency");
	}
	else if (userInput == 2) {
		string userItem;

		cout << "Which item would you like to serach?" << endl;
		// Converting to lower case was breaking program
		cout << "(capitalize first letter)" << endl;
		cin >> userItem;
		// validate item is on list
		if (count(listVec.begin(), listVec.end(), userItem)) {
			int count;

			cout << "Item exists" << endl;
			// call itemFrequency
			count = callIntFunc("itemFrequency", userItem);

			// Display count to user
			cout << count << " " << userItem << " were purchased today." << endl;
		}
		else {
			// Show error message for item not on list
			cout << "Item does not exist!" << endl;
		}		
	}
	else if (userInput == 3) {
		// Initialize vector for frequency.dat data
		vector<string> graphVec;
		int i = 0;

		CallProcedure("itemGraph"); // Call function

		ifstream graphIn("frequency.dat"); // Read data 

		// Write each item to vector
		while (graphIn >> item) {
			graphVec.push_back(item);
		}

		// Add title to graph
		cout << "    Items Purchased Today" << endl;

		while (i < graphVec.size()) {
			// If/else statements to separate name and number from vector
			if (i % 2 == 0) {
				// gets name of items
				int num = 12 - graphVec[i].length(); // Add spaces for uniformity
				cout << graphVec[i] << string(num, ' ');
			}
			else {
				// gets num of items
				cout << "|" << string(stoi(graphVec[i]), 'I') << endl;
			}			
			i++;  // Increment i
		}	
		cout << string(12, ' ') << "0    5    10" << endl; // Print graph scale

		graphIn.close(); // Close file
	}
	else if (userInput == 4) {
		return 1;  // Return 1 to tell main() to close program
		exit;
	}
	else {
		// display error
		cout << "Invalid selection!" << endl;
		exit;
	}

	listIn.close(); // Close file

	cout << endl; // Add newline for next menu output

	return 0;
}

void main()
{
	// initialize variable for loop
	int call = 0;

	// Loop until user exits in menu() function
	while (call == 0) {
		call = menu();
	}
}