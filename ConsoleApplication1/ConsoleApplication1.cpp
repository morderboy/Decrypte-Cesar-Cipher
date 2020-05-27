#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int MassivAlfabFill(char* alfabet, char fillmod);
int MassivFillForSopost(int* sopost);
int MaxForAlfabSopost(int* sopost, int &maximum);
int KeyCalculation(char* alfabet, int maximum, int& keyf);
int SopostForAlfabCount(int len, string str, char* alfabet, char* alfabetBig, int* sopost);
int StrDecryption(int len, string &str, int key);

int main()
{
	ifstream input;
	ofstream output;
	string pathTOfileInput;
	string pathTofileOutput;
	string intermediatValue;
	char s;
	char alfab[26];
	char alfabBig[26];
	int SopostforAlfab[26];


	if (MassivAlfabFill(alfab, 's') != 0) {
		cout << "error 1";
		return 1;
	}
	if (MassivAlfabFill(alfabBig, 'B') != 0) {
		cout << "error 1";
		return 1;
	}
	if (MassivFillForSopost(SopostforAlfab) != 0) {
		cout << "error 1";
		return 1;
	}


	cout << "Enput absolut path to your file with ciphertext: \n";
	if (cout.fail()) {
		cout.clear();
		cout << "error 2";
		return 2;
	}
	if (!(getline(cin, pathTOfileInput))) {
		cout << "error 3";
		return 3;
	}
	

	cout << "Enput absolut path to your output file: \n";
	if (cout.fail()) {
		cout.clear();
		cout << "error 2";
		return 2;
	}
	if (!(getline(cin, pathTofileOutput))) {
		cout << "error 3";
		return 3;
	}



	input.open(pathTOfileInput, ios::in);
	if (!input.is_open()) {
		cout << "error 4";
		return 4;
	}

	output.open(pathTofileOutput, ios::out);
	if (!output.is_open()) {
		cout << "error 4";
		return 4;
	}

	if (input.seekg(0, ios::end).fail() == 1)
	{
		cout << "error 5";
		return 5;
	}

	int lenght = input.tellg();
	if (input.fail() == 1) {
		cout << "error 5";
		return 5;
	}

	if (input.seekg(0, ios::beg).fail() == 1)
	{
		cout << "error 5";
		return 5;
	}


	while (!input.eof()) {
		if (input.get(s).bad() == 1) { cout << "error 6"; return 6; }
		intermediatValue += s;
	}


	lenght = (int)intermediatValue.length();

	if (SopostForAlfabCount(lenght, intermediatValue, alfab, alfabBig, SopostforAlfab) != 0) { cout << "error 7"; return 7; }


	int max = 0;
	if ((MaxForAlfabSopost(SopostforAlfab, max) != 0)) { cout << "error 8"; return 8; }



	int key = 0;
	if (KeyCalculation(alfab, max, key) != 0) { cout << "error 9"; return 9; }



	if (StrDecryption(lenght, intermediatValue, key) != 0) { cout << "error 10"; return 10; };
	
	output << intermediatValue;
	if (output.fail()) { cout << "error 11"; return 11; }

	input.close();
	if (input.bad()) {
		cout << "error 12";
		return 12;
	}
	output.close();
	if (output.bad()) {
		cout << "error 12";
		return 12;
	}
	
	return 0;
}




int MassivAlfabFill(char *alfabet, char fillmod) {
	if (!alfabet) {
		cout << "error 1";
		return 1;
	}
	if ((fillmod != 's') && (fillmod != 'B')) { cout << "error 2"; return 2; }
	int i;
	if (fillmod == 's') {
		for (i = 0; i < 26; i++) alfabet[i] = (char)('a' + i);
		for (i = 0; i < 26; i++) {
			if ((alfabet[i] < 'a') | (alfabet[i] > 'z')) {
				cout << "error 3";
				return 3;
			}
		}
	}
	else {
		for (i = 0; i < 26; i++) alfabet[i] = (char)('A' + i);
		for (i = 0; i < 26; i++) {
			if ((alfabet[i] < 'A') | (alfabet[i] > 'Z')) {
				cout << "error 3";
				return 3;
			}
		}
	}
	return 0;
}

int MassivFillForSopost(int* sopost) {
	if (!sopost) {
		cout << "error 1";
		return 1;
	}
	for (int i = 0; i < 26; i++) {
		sopost[i] = 0;
	}
	return 0;
}

int MaxForAlfabSopost(int* sopost, int &maximum) {
	if (!sopost)
	{
		cout << "error 1";
		return 1;
	}
	if (maximum) {
		cout << "error 2";
		return 2;
	}
	for (int i = 0; i < 26; ++i) {
		if (sopost[i] > sopost[maximum]) {
			maximum = i;
		}
	}
	if (maximum <= 0) {
		cout << "error 3";
		return 3;
	}
	return 0;
}

int KeyCalculation(char *alfabet, int maximum, int &keyf) {
	if (!alfabet)
	{
		cout << "error 1";
		return 1;
	}
	if (maximum < 0 || maximum > 25) {
		cout << "error 2";
		return 2;
	}
	if (keyf) {
		cout << "error 3";
		return 3;
	}
	keyf = (int)(alfabet[maximum] - 'e');
	if (keyf < 0)keyf = -1 * keyf;
	if ((keyf < 0) | (keyf > 25)) {
		cout << "error 4";
		return 4;
	}
	return 0;
}

int SopostForAlfabCount(int len, string str, char *alfabet, char *alfabetBig, int *sopost) {
	if (len < 0) { cout << "error 1"; return 1; }
	if (str.empty()) { cout << "error 2"; return 2; }
	if (!alfabet) { cout << "error 3"; return 3; }
	if (!alfabetBig) { cout << "error 4"; return 4; }
	if (!sopost) { cout << "error 5"; return 5; }
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 26; j++) {
			if ((str[i] == alfabet[j]) | (str[i] == alfabetBig[j]))sopost[j] += 1;
		}

	}
	return 0;
}

int StrDecryption(int len, string &str, int key) {
	if (len < 0) { cout << "error 1"; return 1; }
	if (str.empty()) { cout << "error 2"; return 2; }
	if (key < 0 || key > 26){ cout << "error 3"; return 3; }
	char k;
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') {
			if ((char)(str[i] - key) < 'a') {
				k = (char)(str[i] - key + 26);
				if ((k < 'a') | (k > 'z')) {
					cout << "error 4";
					return 4;
				}
				str[i] = k;
			}
			else {
				k = (char)(str[i] - key);
				if ((k < 'a') | (k > 'z')) {
					cout << "error 4";
					return 4;
				}
				str[i] = k;
			}
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			if ((char)(str[i] - key) < 'A') {
				k = (char)(str[i] - key + 26);
				if ((k < 'A') | (k > 'Z')) {
					cout << "error 4";
					return 4;
				}
				str[i] = k;
			}
			else {
				k = (char)(str[i] - key);
				if ((k < 'A') | (k > 'Z')) {
					cout << "error 4";
					return 4;
				}
				str[i] = k;
			}
		}
	}
	return 0;
}

