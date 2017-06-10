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
	bool advRowLftToRght(int, int, char);
	bool advRowRghtToLft(int, int, char);
	bool advColDownToTop(int, int, char);
	bool advColTopToDown(int, int, char);
	bool RookCheck();
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
	if(RookCheck()) {
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

bool CheckTheCheck::advRowLftToRght(int rowPos, int colPos, char chessPiece) {

	while(colPos + 1 < 7 && chessBoard[rowPos][colPos + 1] == '.')
		colPos++;
	return chessBoard[rowPos][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advRowRghtToLft(int rowPos, int colPos, char chessPiece) {

	while(colPos - 1 > 0 && chessBoard[rowPos][colPos - 1] == '.')
		colPos--;
	return chessBoard[rowPos][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advColDownToTop(int rowPos, int colPos, char chessPiece) {

	while(rowPos - 1 > 0 && chessBoard[rowPos - 1][colPos] == '.')
		rowPos--;
	return chessBoard[rowPos - 1][colPos] == chessPiece;
}

bool CheckTheCheck::advColTopToDown(int rowPos, int colPos, char chessPiece) {

	while(rowPos + 1 < 8 && chessBoard[rowPos + 1][colPos] == '.')
		rowPos++;
	return chessBoard[rowPos + 1][colPos] == chessPiece;
}

bool CheckTheCheck::RookCheck() {

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'R') {
				if(advRowLftToRght(row, col, 'k') ||
				   advRowRghtToLft(row, col, 'k') ||
				   advColTopToDown(row, col, 'k') ||
				   advColDownToTop(row, col, 'k')   )
					return true;
			}
			if(chessBoard[row][col] == 'r') {
				if(advRowLftToRght(row, col, 'K') ||
				   advRowRghtToLft(row, col, 'K') ||
				   advColTopToDown(row, col, 'K') ||
				   advColDownToTop(row, col, 'K')   )
					return true;
			}
		}
	}
	return false;
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