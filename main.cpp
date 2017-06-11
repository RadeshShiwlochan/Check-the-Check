#include <iostream>
#include <fstream>
using namespace std;

class CheckTheCheck {

private:
	char chessBoard[8][8];

public:
	CheckTheCheck();
	void exeCheckTheCheck(string, string);
	bool endOfInput();	
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
	bool rookCheck(ofstream&);
	bool bishopCheck(ofstream&);
	bool knightCheck(ofstream&);
	bool kingCheck(ofstream&);
	bool queenCheck(ofstream&);
	bool whitePawnCheck(ofstream&);
	bool blackPawnCheck(ofstream&);
	void printCount(ofstream&, int);
};

CheckTheCheck::CheckTheCheck() {
	/**
		initializes the chessBoard to empty spaces( '.'  represent
		empty spaces)
	*/	
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			chessBoard[row][col] = '.';
		}	
	}
}

void CheckTheCheck::exeCheckTheCheck(string inputFile, string outputFile) {
	/**
		-reads the input from inputFile
		-print output to outputFile
		loads the input into chessBoard using the while loop. Then 
		endOfInput() function checks if the loaded input is all empty
		spaces which then breaks the while loop. printCount prints the
		current input number and then all functions are called to 
		determine if a chess piece checks a king of either color.
	*/
	//reads input from inputFile
	ifstream readFile;
	readFile.open(inputFile);
	//prints output to outputFile
	ofstream printToFile;
	printToFile.open(outputFile);
	//char used to read in values from inputFile
	char boardConfig = 'x';
	//count used to keep track of the input number
	int count = 0;
	//while loop runs until end of file or end of input ( 64 '.' read)
	while(readFile.good()) {
		count++;
		for(int row = 0; row < 8; ++row) {
			for(int col = 0; col < 8; ++col) {
				readFile >> boardConfig;
				chessBoard[row][col] = boardConfig;
			}//for col
		}//for row
		//checks if the input is all '.' in which case breaks the loop
		if(endOfInput())
			break;
		//print the current Game number to file
		printCount(printToFile, count); 
		//call functions to check if respective pieces have king in check
		if(rookCheck(printToFile)         ||
		   bishopCheck(printToFile)       ||
		   queenCheck(printToFile)        ||
		   knightCheck(printToFile)       ||
		   kingCheck(printToFile)         ||
		   blackPawnCheck(printToFile)    ||
		   whitePawnCheck(printToFile)      )
			cout << "";
		//if either color king is not in check, display as such
		else  
			printToFile << "no king is in check.\n";
		
	}
	//close files
	readFile.close();
	printToFile.close();	 
}//end of exeCheckTheCheck

bool CheckTheCheck::endOfInput() {
	/**
		uses a flag to check if all empty spaces are read in from
		input which signifies that the input is reached. If all 
		empty spaces are read in, returns true, else returns false
	*/
	bool flag = true;
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] != '.')
				flag = false;
		}//for col
	}// for row
	return flag;
}//end of endOfInput

bool CheckTheCheck::advRowLftToRght(int rowPos, int colPos, 
														char chessPiece) {
	/**
		iterates through the current row until colPos == 6 or until a 
		chessPiece is reached. Then checks if the next position (column)
		 == chessPiece which will be k or K. Used by rookCheck and
		 queenCheck
	*/
	while(colPos + 1 < 7 && chessBoard[rowPos][colPos + 1] == '.')
		colPos++;
	return chessBoard[rowPos][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advRowRghtToLft(int rowPos, int colPos, 
														char chessPiece) {
	/**
		iterates through the current row until colPos == 1 or until a 
		chessPiece is reached. Then checks if the next position (column)
		== chessPiece which will be k or K. Used by rookCheck and
		 queenCheck
	*/
	while(colPos - 1 > 0 && chessBoard[rowPos][colPos - 1] == '.')
		colPos--;
	return chessBoard[rowPos][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advColDownToTop(int rowPos, int colPos, 
														char chessPiece) {

	/**
		iterates through the current col until rowPos == 0 or until a 
		chessPiece is reached. Then checks if the next position (row)
		 == chessPiece which will be k or K. Used by rookCheck and
		 queenCheck
	*/
	while(rowPos - 1 > 0 && chessBoard[rowPos - 1][colPos] == '.')
		rowPos--;
	return chessBoard[rowPos - 1][colPos] == chessPiece;
}

bool CheckTheCheck::advColTopToDown(int rowPos, int colPos, 
														char chessPiece) {

	/**
		iterates through the current col until rowPos == 6 or until a 
		chessPiece is reached. Then checks if the next position (row)
		 == chessPiece which will be k or K. Used by rookCheck and
		 queenCheck
	*/
	while(rowPos + 1 < 8 && chessBoard[rowPos + 1][colPos] == '.')
		rowPos++;
	return chessBoard[rowPos + 1][colPos] == chessPiece;
}

bool CheckTheCheck::advDiagDownTopLftRght(int rowPos, int colPos, 
														char chessPiece) {
	/**
		iterates through the chessBoard in a diagonal going to the upper
		right corner of the board. Checks that the rowPos and colPos are
		within bounds and that the next spot is not occupied by another
		chess piece. When while loop is false it checks the next position
		if it is == chessPiece which will be k or K.Used by bishopCheck and
		queenCheck
	*/
	while(rowPos - 1 > 0 && colPos + 1 < 7 && 
		             chessBoard[rowPos - 1][colPos + 1] == '.' ) {
		rowPos--;
		colPos++;
	}
	return chessBoard[rowPos - 1][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advDiagTopDownLftRght(int rowPos, int colPos, 
														char chessPiece) {
	/**
		iterates through the chessBoard in a diagonal going to the lower
		right corner of the board. Checks that the rowPos and colPos are
		within bounds and that the next spot is not occupied by another
		chess piece. When while loop is false it checks the next position
		if it is == chessPiece which will be k or KUsed by bishopCheck and
		queenCheck
	*/
	while(rowPos + 1 < 7 && colPos + 1 < 7 && 
					chessBoard[rowPos + 1][colPos + 1] == '.') {
		rowPos++;
		colPos++;
	}
	return chessBoard[rowPos + 1][colPos + 1] == chessPiece;
}

bool CheckTheCheck::advDiagDownTopRghtLft(int rowPos, int colPos, 
														char chessPiece) {

	/**
		iterates through the chessBoard in a diagonal going to the upper
		left corner of the board. Checks that the rowPos and colPos are
		within bounds and that the next spot is not occupied by another
		chess piece. When while loop is false it checks the next position
		if it is == chessPiece which will be k or K.Used by bishopCheck and
		queenCheck
	*/
	while(rowPos - 1 > 0 && colPos - 1 > 0 &&
						chessBoard[rowPos - 1][colPos - 1] == '.') {
		rowPos--;
		colPos--;
	}
	return chessBoard[rowPos - 1][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advDiagTopDownRghtLft(int rowPos, int colPos, 
														char chessPiece) {

	/**
		iterates through the chessBoard in a diagonal going to the lower
		left corner of the board. Checks that the rowPos and colPos are
		within bounds and that the next spot is not occupied by another
		chess piece. When while loop is false it checks the next position
		if it is == chessPiece which will be k or K. Used by bishopCheck and
		queenCheck
	*/
	while(rowPos + 1 < 7 && colPos - 1 > 0 && chessBoard[rowPos + 1][colPos - 1]) {
		rowPos++;
		colPos--;
	}
	return chessBoard[rowPos + 1][colPos - 1] == chessPiece;
}

bool CheckTheCheck::advOnePosAllDir(int rowPos, int colPos,
													char chessPiece) {

	/**
		iterates one position in all directions to check if the spot next
		to the current position == checkPiece. Used by kingCheck
	*/

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
	
	/**
		Used by knighCheck to move in a 'L' shape meaning two spaces in one
		direction and one direction at the end of the two space advancement.
		The if statement is used to check if that if the knight moves from its
		current position, will it check a king. It checks that the colPos and 
		rowPos are within bounds and if a king can be taked from current position. 
	*/
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

	/**
		Used by knighCheck to move in a 'L' shape meaning one space in one
		direction and two spaces in another direction at the end of the two space 
		advancement.The if statement is used to check if that if the knight moves from 
		its current position, will it check a king. It checks that the colPos and 
		rowPos are within bounds and if a king can be taked from current position. 
	*/
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

bool CheckTheCheck::rookCheck(ofstream& printToFile) {

	/**
		used to check if a rook chess piece has a king in check. The first
		if statement checks for a white rook and uses the four functions to
		check if a black king can be taken from the current position of the rook.
		The second if statement does the same thing as the first except that it 
		checks for a black rook and a white king
	*/
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'R') {
				if(advRowLftToRght(row, col, 'k') ||
				   advRowRghtToLft(row, col, 'k') ||
				   advColTopToDown(row, col, 'k') ||
				   advColDownToTop(row, col, 'k')   ) {
					printToFile << "black king is in check.\n";
					return true;
			    }
			}
			if(chessBoard[row][col] == 'r') {
				if(advRowLftToRght(row, col, 'K') ||
				   advRowRghtToLft(row, col, 'K') ||
				   advColTopToDown(row, col, 'K') ||
				   advColDownToTop(row, col, 'K')   ) {
				   	printToFile << "white king is in check.\n";
					return true;
			    }
			}
		}
	}
	return false;
}

bool CheckTheCheck::bishopCheck(ofstream& printToFile) {

	/**
		used to check if a bishop chess piece has a king in check. The first
		if statement checks for a white bishop and uses the four functions to
		check if a black king can be taken from the current position of the bishop.
		The second if statement does the same thing as the first except that it 
		checks for a black bishop and a white king
	*/
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'B') {
				if(advDiagTopDownLftRght(row, col, 'k') ||
				   advDiagDownTopLftRght(row, col, 'k') ||
				   advDiagTopDownRghtLft(row, col, 'k') ||
				   advDiagDownTopRghtLft(row, col, 'k')   ) {
					printToFile << "black king is in check.\n";
					return true;
			    }
			}
			if(chessBoard[row][col] == 'b') {
				if(advDiagTopDownLftRght(row, col, 'K') ||
				   advDiagDownTopLftRght(row, col, 'K') ||
				   advDiagTopDownRghtLft(row, col, 'K') ||
				   advDiagDownTopRghtLft(row, col, 'K')   ) {
				   	printToFile << "white king is in check.\n";
					return true;
			    }
			}
		}
	}
	return false;
}

bool CheckTheCheck::knightCheck(ofstream& printToFile) {

	/**
		used to check if a knight chess piece has a king in check. The first if 
		statement checks for a white knight and uses the longLShapeDir and 
		shortLShapeDir functions to check if a black king can be taken from the 
		current position of the rook. A knight can move in 16 directions from its
		current positon, hence the need of two functions to check all the possible 
		moves. The second if statement does the same thing as the first except that 
		it checks for a black knight and a white king
	*/
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'N' && longLShapeDir(row, col, 'k') &&
				shortLShapeDir(row, col, 'k')) {
				printToFile << "black king is in check.\n";
				return true;
			}
				
			if(chessBoard[row][col] == 'n' && longLShapeDir(row, col, 'K') &&
				shortLShapeDir(row, col, 'K')) {
				printToFile << "white king is in check.\n";
				return true;
			}		 
		}
	}
	return false;
}

bool CheckTheCheck::kingCheck(ofstream& printToFile) {
	/**
		used to check if a king chess piece has a king of the opposite color 
		in check. The first if statement checks for a white king and uses the 
		function to check if a black king can be taken from the current position
		 of the king. The second if statement does the same thing as the first 
		 except that it checks for a black king and a white king
	*/
	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'K' && 
				advOnePosAllDir(row, col, 'k')) {
				printToFile << "black king is in check.\n";
				return true;
		    }
			if(chessBoard[row][col] == 'k' && 
				advOnePosAllDir(row, col, 'K')) {
				printToFile << "white king is in check.\n";
				return true;
			}
		}
	}
	return false;
}

bool CheckTheCheck::queenCheck(ofstream& printToFile) {
	/**
		reads the chessboard and searches for a queen. 
		The first if statement checks solely for Q (white queen),
		then calls methods to check if k (black king) can be
		taken from the queen's current position. The second 
		if statement does the same as the first except it 
		checks for q (black queen) and check if K (white king)
		can be taken from current posit
	*/

	for(int row = 0; row < 8; ++row) {
		for(int col = 0; col < 8; ++col) {
			if(chessBoard[row][col] == 'Q')                {     
				if(advColDownToTop(row,  col,'k'       ) ||
					advColTopToDown(row, col,'k'       ) ||
					advRowLftToRght(row, col,'k'       ) ||
					advRowRghtToLft(row, col,'k'       ) ||
					advDiagDownTopLftRght(row, col, 'k') ||
					advDiagTopDownLftRght(row, col, 'k') ||
					advDiagDownTopRghtLft(row, col, 'k') ||
					advDiagTopDownRghtLft(row, col, 'k')   )
					{
						printToFile << "black king is in check.\n";
						return true;
					} //if
					
            }//if
			if(chessBoard[row][col] == 'q')                 {
				if(advColDownToTop(row,  col, 'K'      ) ||
				   advColTopToDown(row,  col, 'K'      ) ||
					advRowLftToRght(row, col, 'K'      ) ||
					advRowRghtToLft(row, col, 'K'      ) ||
					advDiagDownTopLftRght(row, col, 'K') ||
					advDiagTopDownLftRght(row, col, 'K') ||
					advDiagDownTopRghtLft(row, col, 'K') ||
					advDiagTopDownRghtLft(row, col, 'K')    ) {
					printToFile << "white king is in check.\n";
					return true;
			    }// end of if with method calls
		    }// end of if with searching for q
		}// for col
	}//for row
	return false;
}// end of queenCheck

bool CheckTheCheck::whitePawnCheck(ofstream& printToFile) {
	/**
		reads the chessBoard from right to left and bottom to top.
		Since a pawn can take a king if the king is diagonal to 
		it, check positions row - 1 col + 1 and row + 1, col - 1
		for k (black king).
		-takeRwPos: used for row - 1
		-takeColPosLeft: used for col + 1
		-take ColPosRight: used for col - 1
	*/

	int takeRwPos = 0;
	int takeColPosLeft = 0;
	int takeColPosRight = 0;
	for(int row = 7; row > 0; --row) {
		for(int col = 7; col >= 0; --col) {
			/**
				if a white pawn is found, set takeRwPos, takeColPosLeft
				and takeColPosRight	
			*/
			if(chessBoard[row][col] == 'P') {
				takeRwPos = row - 1;
				takeColPosLeft = col + 1;
				takeColPosRight = col - 1;
				/**
					checks if takeRwPos, takeColPosLeft and takeColPosRight
					are in bounds and if any of the diagonals are k
				*/
				if((takeColPosLeft  >= 0 && takeColPosLeft  <= 7    &&
				    chessBoard[takeRwPos][takeColPosLeft]   == 'k') ||
			   	   (takeColPosRight >= 0 && takeColPosRight <= 7    &&
			   		chessBoard[takeRwPos][takeColPosRight]  == 'k')    ) {
						printToFile << "black king is in check.\n";
						return true;
				}// if
		    }//if value == "P"
		}//for
	}//for
	return false;
}

bool CheckTheCheck::blackPawnCheck(ofstream& printToFile) {
	/**
		reads the chessBoard from left to right and top to bottom.
		Since a pawn can take a king if the king is diagonal to 
		it, check positions row + 1 col + 1 and row + 1, col - 1
		for K (white king).
		-takeRwPos: used for row + 1
		-takeColPosLeft: used for col + 1
		-take ColPosRight: used for col - 1
	*/

	int takeRwPos = 0;
	int takeColPosLeft = 0;
	int takeColPosRight = 0;
	for(int row = 0; row < 7; ++row) {
		for(int col = 0; col < 8; ++col) {
			/**
				if a black pawn is found, set takeRwPos, takeColPosLeft
				and takeColPosRight	
			*/
			if(chessBoard[row][col] == 'p') {
				takeRwPos = row + 1;
				takeColPosLeft = col + 1;
				takeColPosRight = col - 1;
				/**
					checks if takeRwPos, takeColPosLeft and takeColPosRight
					are in bounds and if any of the diagonals are K
				*/
				if((takeColPosLeft  >= 0 && takeColPosLeft  <= 7    &&
				    chessBoard[takeRwPos][takeColPosLeft]   == 'K') ||
			   	   (takeColPosRight >= 0 && takeColPosRight <= 7    &&
			   		chessBoard[takeRwPos][takeColPosRight]  == 'K')    ) {
						printToFile << "white king is in check.\n";
						return true;
				}//if
		    }//if value == "P"
		}//for
	}//for
	return false;
}//end of blackPawnCheck

void CheckTheCheck::printCount(ofstream& printToFile, int count) {
    /**
    	prints the Game count before the individual functions are
    	called to check the board.
    */
    printToFile << "Game #" << count <<": ";
}//end of printCount

int main(int argc, char* argv[]) {

	//check to ensure 2 files are provided, input and output.
	if(argc != 3) {
		cout << "Program needs 2 inputs: an input" <<
		" file with the board configurations and"  <<
		" an output file, Terminating!\n";
		return 0;
	}
	CheckTheCheck checkTheCheck;
	checkTheCheck.exeCheckTheCheck(argv[1], argv[2]);
	return 0;
}//end of main