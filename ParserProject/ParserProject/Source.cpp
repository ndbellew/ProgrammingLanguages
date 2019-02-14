//Nathan Bellew
//Programming Languages
//Basic Line Parser.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

ofstream outf("output.ot");
ifstream inf("input.txt");
string line = "";
char Token = 0;
int Index = 0;
bool Error = false;
int EndOfLine = 0;

string here = "Here";

void Expression();
void Term();
void Factor();
void Number();
void Digit();
void Parse();
void getToken();

void main() {
	
	while (!inf.eof()) {
		Parse();
	}
}


void Expression() {
	outf << "<exp> ";
	Term();
	while (Token == '+') {
		getToken();
		Term();
	}
}

void Term() {
	outf << "<term> ";
	Factor();
	while (Token == '*') {
		getToken();
		Factor();
	}
}

void Factor() {
	outf << "<factor> ";
	if (Token == '(') {
		getToken();
		Expression();
		if (Token == ')')
			getToken();
		else {
			Error = true;
			outf << "Error during Factor!" << endl;
		//	return 0;
		}

	}
	else
		Number();
}

void Number() {
	outf << "<number> ";
	Digit();
	while (isdigit(Token))Digit();

}

void Digit() {
	outf << "<digit> ";
	if (isdigit(Token))
		getToken();
	else {
		Error = true;
		outf << "Error in Digit!" << endl;
		//return 0;
	}
}
void Parse() {
	while (getline(inf, line)) {

		outf << endl<<"Line to Parse -> "<<line<< endl << "<parse>";
		Index = 0;
		EndOfLine = 0;
		while (!EndOfLine) {
			getToken();
			Expression();
			if (Error) {
				outf <<  "There was an error in Parsing" << endl;
				Error = false;
			}
			else
				outf <<endl << "The parse has been completed with no problems!" << endl;

		}
	}
}
void getToken() {
	if (Index < line.length()) {
		do {
			Token = line[Index];
			Index++;
		} while (Token == ' ');
		outf << endl << "<gettoken> ";
		outf << Token<<" ";
	}
	else {
		Token = '@';
		EndOfLine = 1;
	}
}

