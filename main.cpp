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
	bool advDiagDownTopLftRght(int, int, char);
	bool advDiagTopDownLftRght(int, int, char);
	bool advDiagDownTopRghtLft(int, int, char);
	bool advDiagTopDownRghtLft(int, int, char);
	bool advOnePosAllDir(int, int, char);
	bool longLShapeDir(int, int, char);
	bool shortLShapeDir(int, int, char);
	bool rookCheck();
	bool bishopCheck();
	bool knightCheck();
	bool kingCheck();
	bool queenCheck();
	bool whitePawnCheck();
	bool blackPawnCheck();
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
	if(knightCheck()) 
		cout << "In Check\n";
	else
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

bool CheckTheCheck::advRowLftToRght(int rowPos, int colPos, 
														char chessPiece) {

	while(colPos + 1 < 7 && chessBoard[rowPos][colPos + 1] == '.')
		colPos++;
	return chessBoard[rowPos][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advRowRghtToLft(int rowPos, int colPos, 
														char chessPiece) {

	while(colPos - 1 > 0 && chessBoard[rowPos][colPos - 1] == '.')
		colPos--;
	return chessBoard[rowPos][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advColDownToTop(int rowPos, int colPos, 
														char chessPiece) {

	while(rowPos - 1 > 0 && chessBoard[rowPos - 1][colPos] == '.')
		rowPos--;
	return chessBoard[rowPos - 1][colPos] == chessPiece;
}

bool CheckTheCheck::advColTopToDown(int rowPos, int colPos, 
														char chessPiece) {

	while(rowPos + 1 < 8 && chessBoard[rowPos + 1][colPos] == '.')
		rowPos++;
	return chessBoard[rowPos + 1][colPos] == chessPiece;
}

bool CheckTheCheck::advDiagDownTopLftRght(int rowPos, int colPos, 
														char chessPiece) {

	while(rowPos - 1 > 0 && colPos + 1 < 7 && 
		             chessBoard[rowPos - 1][colPos + 1] == '.' ) {
		rowPos--;
		colPos++;
	}
	return chessBoard[rowPos - 1][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advDiagTopDownLftRght(int rowPos, int colPos, 
														char chessPiece) {

	while(rowPos + 1 < 7 && colPos + 1 < 7 && 
					chessBoard[rowPos + 1][colPos + 1] == '.') {
		rowPos++;
		colPos++;
	}
	return chessBoard[rowPos + 1][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advDiagDownTopRghtLft(int rowPos, int colPos, 
														char chessPiece) {

	while(rowPos - 1 > 0 && colPos - 1 > 0 &&
						chessBoard[rowPos - 1][colPos - 1] == '.') {
		rowPos--;
		colPos--;
	}
	return chessBoard[rowPos - 1][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advDiagTopDownRghtLft(int rowPos, int colPos, 
														char chessPiece) {

	while(rowPos + 1 < 7 && colPos - 1 > 0 && chessBoard[rowPos + 1][colPos - 1]) {
		rowPos++;
		colPos--;
	}
	return chessBoard[rowPos + 1][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advOnePosAllDir(int rowPos, int colPos,
													char chessPiece) {

	if((rowPos - 1 >= 0 && chessBoard[rowPos - 1][colPos] == chessPiece) ||
	   (colPos - 1 >= 0 && chessBoard[rowPos][colPos - 1] == chessPiece) ||
	   (colPos + 1 <= 7 && chessBoard[rowPos][colPos + 1] == chessPiece) ||
	   (rowPos + 1 <= 7 && chessBoard[rowPos + 1][colPos] == chessPiece) ||
	   (rowPos - 1 >= 0 && colPos - 1 >= 0 && 
	                  chessBoard[rowPos - 1][colPos - 1] == chessPiece) ||
	   (rowPos - 1 >= 0 && colPos + 1 <= 7 &&
	   				  chessBoard[rowPos - 1][colPos + 1] == chessPiece) ||
	   (rowPos + 1 <= 7 && colPos + 1 <= 7 &&
	   				  chessBoard[rowPos + 1][colPos + 1] == chessPiece) ||
	   (rowPos + 1 <= 7 && colPos - 1 >= 0 && 
	                  chessBoard[rowPos + 1][colPos - 1] == chessPiece)    )
	   return true;
	return false;
}

bool CheckTheCheck::longLShapeDir(int rowPos, int colPos, 
												  char chessPiece) {
	
	if((colPos + 2 <= 7 && colPos + 2 >= 0 && rowPos + 1 <= 7 && 
	    rowPos + 1 >= 0 && chessBoard[rowPos + 1][colPos + 2] == chessPiece)  || 
	   (colPos + 2 <= 7 && colPos + 2 >= 0 && rowPos - 1 <= 7 && 
	    rowPos - 1 >= 0 && chessBoard[rowPos - 1][colPos + 2] == chessPiece)  ||
	   (rowPos + 2 <= 7 && rowPos + 2 >= 0 && colPos - 1 >= 0 && 
	   	colPos - 1 <= 7 && chessBoard[rowPos + 2][colPos - 1] == chessPiece)  ||
	   (rowPos + 2 <= 7 && rowPos + 2 >= 0 && colPos + 1 >= 0 && 
	   	colPos + 1 <= 7 && chessBoard[rowPos + 2][colPos + 1] == chessPiece)  ||
	   (rowPos - 2 <= 7 && rowPos - 2 >= 0 && colPos - 1 >= 0 && 
	   	colPos - 1 <= 0 && chessBoard[rowPos - 2][colPos - 1] == chessPiece)  ||
	   (rowPos - 2 <= 7 && rowPos - 2 >= 0 && colPos + 1 >= 0 && 
	   	colPos + 1 <= 0 && chessBoard[rowPos - 2][colPos + 1] == chessPiece)  ||
	   (colPos - 2 <= 7 && colPos - 2 >= 0 && rowPos + 1 <= 7 && 
	    rowPos + 1 >= 0 && chessBoard[rowPos + 1][colPos - 2] == chessPiece ) ||
	   (colPos - 2 <= 7 && colPos - 2 >= 0 && rowPos - 1 <= 7 && 
	    rowPos - 1 >= 0 && chessBoard[rowPos - 1][colPos - 2] == chessPiece)    ) 
		return true;
	return false;
}

bool CheckTheCheck::shortLShapeDir(int rowPos, int colPos,
												   char chessPiece) {

	if((colPos + 1 <= 7 && colPos + 1 >= 0 && rowPos + 2 <= 7 &&
		rowPos + 2 >= 0 && chessBoard[rowPos + 2][colPos + 1] == chessPiece)  || 
	   (colPos - 1 <= 7 && colPos - 1 >= 0 && rowPos + 2 <= 7 &&
		rowPos + 2 >= 0 && chessBoard[rowPos + 2][colPos - 1] == chessPiece)  ||
	   (colPos + 1 <= 7 && colPos + 1 >= 0 && rowPos - 2 <= 7 &&
		rowPos - 2 >= 0 && chessBoard[rowPos - 2][colPos + 1] == chessPiece)  || 
	   (colPos - 1 <= 7 && colPos - 1 >= 0 && rowPos - 2 <= 7 &&
		rowPos - 2 >= 0 && chessBoard[rowPos - 2][colPos - 1] == chessPiece)  ||
	   (colPos + 2 <= 7 && colPos + 2 >= 0 && rowPos - 1 >= 7 &&
	   	rowPos - 1 <= 0 && chessBoard[rowPos - 1][colPos + 1] == chessPiece)  ||
	   (colPos + 2 <= 7 && colPos + 2 >= 0 && rowPos + 1 >= 7 &&
	   	rowPos + 1 <= 0 && chessBoard[rowPos + 1][colPos + 1] == chessPiece)  ||
	   (colPos - 2 <= 7 && colPos - 2 >= 0 && rowPos - 1 <= 7 && 
	   	rowPos - 1 >= 0 && chessBoard[rowPos - 1][colPos - 2] == chessPiece)  ||
	   (colPos + 2 <= 7 && colPos + 2 >= 0 && rowPos - 1 <= 7 && 
	   	rowPos - 1 >= 0 && chessBoard[rowPos - 1][colPos + 2] == chessPiece)    )
	   	return true;
	return false;   	

} 

bool CheckTheCheck::rookCheck() {

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

bool CheckTheCheck::bishopCheck() {

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'B') {
				if(advDiagTopDownLftRght(row, col, 'k') ||
				   advDiagDownTopLftRght(row, col, 'k') ||
				   advDiagTopDownRghtLft(row, col, 'k') ||
				   advDiagDownTopRghtLft(row, col, 'k')   )
					return true;
			}
			if(chessBoard[row][col] == 'b') {
				if(advDiagTopDownLftRght(row, col, 'K') ||
				   advDiagDownTopLftRght(row, col, 'K') ||
				   advDiagTopDownRghtLft(row, col, 'K') ||
				   advDiagDownTopRghtLft(row, col, 'K')   )
					return true;
			}
		}
	}
	return false;
}

bool CheckTheCheck::knightCheck() {

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'N' && longLShapeDir(row, col, 'k') &&
				shortLShapeDir(row, col, 'k'))
				return true;
			if(chessBoard[row][col] == 'n' && longLShapeDir(row, col, 'K') &&
				shortLShapeDir(row, col, 'K'))
				return true;	 
		}
	}
	return false;
}

bool CheckTheCheck::kingCheck() {

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'K' && 
				advOnePosAllDir(row, col, 'k'))
				return true;
			if(chessBoard[row][col] == 'k' && 
				advOnePosAllDir(row, col, 'K'))
				return true;
		}
	}
	return false;
}

bool CheckTheCheck::queenCheck() {

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'Q'  )                {     
				if(advColDownToTop(row,  col,'k'      )  ||
					advColTopToDown(row, col,'k'      )  ||
					advRowLftToRght(row, col,'k'      )  ||
					advRowRghtToLft(row, col,'k'      )  ||
					advDiagDownTopLftRght(row, col, 'k') ||
					advDiagTopDownLftRght(row, col, 'k') ||
					advDiagDownTopRghtLft(row, col, 'k') ||
					advDiagTopDownRghtLft(row, col, 'k')) 
					return true;
            }
			if(chessBoard[row][col] == 'q')                 {
				if(advColDownToTop(row,  col, 'K'      ) ||
				   advColTopToDown(row,  col, 'K'      ) ||
					advRowLftToRght(row, col, 'K'      ) ||
					advRowRghtToLft(row, col, 'K'      ) ||
					advDiagDownTopLftRght(row, col, 'K') ||
					advDiagTopDownLftRght(row, col, 'K') ||
					advDiagDownTopRghtLft(row, col, 'K') ||
					advDiagTopDownRghtLft(row, col, 'K')    )
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
				if((takeColPosLeft  >= 0 && takeColPosLeft  <= 7    &&
				    chessBoard[takeRwPos][takeColPosLeft]   == 'k') ||
			   	   (takeColPosRight >= 0 && takeColPosRight <= 7    &&
			   		chessBoard[takeRwPos][takeColPosRight]  == 'k')    ) {
						return true;
				}
		    }//if value == "P"
		}//for
	}//for
	return false;
}

bool CheckTheCheck::blackPawnCheck() {

	int takeRwPos = 0;
	int takeColPosLeft = 0;
	int takeColPosRight = 0;
	for(int row = 0; row < 7; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'p') {
				takeRwPos = row + 1;
				takeColPosLeft = col + 1;
				takeColPosRight = col - 1;
				if((takeColPosLeft  >= 0 && takeColPosLeft  <= 7    &&
				    chessBoard[takeRwPos][takeColPosLeft]   == 'K') ||
			   	   (takeColPosRight >= 0 && takeColPosRight <= 7    &&
			   		chessBoard[takeRwPos][takeColPosRight]  == 'K')    ) {
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