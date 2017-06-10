#include <iostream>
#include <fstream>
using namespace std;

class CheckTheCheck {

private:
	char chessBoard[8][8];

public:
	CheckTheCheck();
	void exeCheckTheCheck(string, string);
	void readInput(string);	
	void printBoard(string);
};

CheckTheCheck::CheckTheCheck() {

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			chessBoard[row][col] = '.';
		}	
	}
}

void CheckTheCheck::exeCheckTheCheck(string inputFile, string outputFile) {

	readInput(inputFile);
	printBoard(outputFile);
}

void CheckTheCheck::readInput(string inputFile) {

	ifstream readFile;
	readFile.open(inputFile);
	char boardConfig = 'x';
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			readFile >> boardConfig;
			chessBoard[row][col] = boardConfig;
		}
	}
	readFile.close();
}

void CheckTheCheck::printBoard(string outputFile) {

	ofstream printToFile;
	printToFile.open(outputFile);
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			printToFile << chessBoard[row][col] << "  ";
		}
		printToFile << endl;
	}
	printToFile.close();
}

int main(int argc, char* argv[]) {

	if(argc != 3) {
		cout << "Program needs 2 input: an input " <<
		" file with the board configurations and " <<
		" an output file, Terminating!\n";
		return 0;
	}
	CheckTheCheck checkTheCheck;
	checkTheCheck.exeCheckTheCheck(argv[1], argv[2]);
	return 0;
}