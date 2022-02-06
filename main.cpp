#include <string>
#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

void textColor(int colorID) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);

	return;
}

string lowerCase(string input) {
	for (int i = 0; i < input.length(); i++)
		if (input[i] >= 'A' && input[i] <= 'Z')
			input[i] += 32;

	return input;
}

int main() {
	int correctChars = 0;
	int instanceCount = 0;
	int instances[50];
	bool optionsLoop = true;
	bool containsH = false;
	bool verbosity = false;
	bool insensitivity = false;
	bool count = false;
	string options = "d";

	string input;
	cout << "Input: ";
	getline(cin, input);
	cout << endl;

	string substr;
	cout << "Substring: ";
	getline(cin, substr);
	cout << endl;

	cout << setw(120) << setfill('-') << '-' << endl << endl;

	// Options - additional criteria, edits to input/output
	while (optionsLoop) {
		cout << "Options may be entered as a single string (e.g. vci)" << endl;
		cout << "Use option \"h\" for additional information." << endl;
		cout << "Use option \"d\" for default settings." << endl << endl;

		cout << "Options: ";
		getline(cin, options);
		cout << endl;

		cout << setw(120) << setfill('-') << '-' << endl << endl;

		options = lowerCase(options);

		for (int i = 0; i < options.length(); i++) { // iterates through string for "h" option
			if (options[i] == 'h') {
				cout << "Option \"d\" prints locations of the substr." << endl;
				textColor(15);
				cout << "Option \"c\" prints number of occurances." << endl;
				textColor(7);
				cout << "Option \"i\" turns the search to case-insensitive." << endl;
				textColor(15);
				cout << "Option \"v\" prints the complete string with substrings highlighted." << endl;
				textColor(7);
				containsH = true;
				system("pause >nul");
				system("cls");
				break;
			}
			else if (options[i] == 'd') {
				break;
				optionsLoop = false;
			}
			else
				containsH = false;
		}

		if (containsH == true)
			continue;
		else
			optionsLoop = false;

		for (int i = 0; i < options.length(); i++)
			if (options[i] == 'i') { // case insensitive
				input = lowerCase(input);
				substr = lowerCase(substr);
				break;
			}

	}
	// End of Options

	// Start of Foundation - base code 
	for (int i = 0; i < input.length(); i++)
		if (input[i] == substr[0])
			for (int n = 0; n < substr.length(); n++) {
				if (substr[n] == input[i + n]) {
					correctChars++; // checks if section of input is the same as substr
					if (correctChars == substr.length()) {
						instances[instanceCount] = i; // stores index into array
						instanceCount++;
						correctChars = 0;
					}
				}
			}

	for (int i = 0; i < options.length(); i++)
		if (options[i] == 'v' && verbosity == false) { // verbosity
			for (int k = 0; k < instanceCount; k++)
				for (int l = 0; l < input.length(); l++) {
					if (l == instances[k]) {
						textColor(63);
						for (int q = 0; q < substr.length(); q++) {
							cout << input[l + q]; // prints substr in a different color
							if (q == substr.length() - 1)
								l += substr.length();
						}
						textColor(7);
					}
					else
						cout << input[l];
				}
			verbosity = true;
			cout << endl << endl;
		}
		else if (options[i] == 'c' && count == false) { // instance count
			cout << "The substring occurs this many times: " << instanceCount << endl;
			count = true;
			cout << endl << endl;
		}
		else if (options[i] == 'i') // insensitive checked already ahead
			continue;
		else { // default
			cout << "The substring occurs at the following indices of your input: " << endl;
			for (int j = 0; j < instanceCount; j++) {
				if (j != instanceCount - 1)
					cout << instances[j] << ", ";
				else
					cout << instances[j] << endl;
			}
		}
	// End of Foundation

	system("pause >nul");

	return 0;
}