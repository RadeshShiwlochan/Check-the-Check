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
	bool whitePawnCheck();
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
	if(whitePawnCheck()) {
		cout << "In Check\n";
	} else
		cout << "King is safe\n"; 
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

bool CheckTheCheck::whitePawnCheck() {

	int takeRwPos = 0;
	int takeColPosLeft = 0;
	int takeColPosRight = 0;
	for(int row = 7; row > 0; --row) {
		for(int col = 7; col >= 0; --col) {
			if(chessBoard[row][col] == 'P') {
				takeRwPos = row - 1;
				takeColPosLeft = col + 1;
				takeColPosRight = col - 1;
				cout << "row: " << row << " col: " << col << 
				" takeColPosLeft: " << takeColPosLeft << " takeColPosRight: "
				<<takeColPosRight << endl;
				if((takeColPosLeft  >= 0 && takeColPosLeft  <= 7    &&
				    chessBoard[takeRwPos][takeColPosLeft]   == 'k') ||
			   	   (takeColPosRight >= 0 && takeColPosRight <= 7    &&
			   		chessBoard[takeRwPos][takeColPosRight]  == 'k'    )) {
						return true;
				}
		    }//if value == "P"
		}//for
	}//for
	return false;
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