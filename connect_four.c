
#include <stdio.h>
#include <ctype.h>

/*GAME CONFIGURATION*/

#define ROWS 6
#define COLUMNS 7
#define OPEN_CELL_ASCII 46
#define COLUMN_LETTER_START 65

#define OPEN_CELL '.'
#define PLAYER_1_PIECE 'X'
#define PLAYER_2_PIECE 'O'
#define COLORED_PLAYER_1_PIECE 'N'
#define COLORED_PLAYER_2_PIECE 'B'

/*Game board controller*/

/*
 * Function name : initilizeGameBoard()
 * Usage         : initilizeGameBoard(char board[][])
 * Definition    : Sets all of the values in board[][] to OPEN_CELL.
*/
void initilizeGameBoard(char board[][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			board[i][j] = OPEN_CELL;
		}
	}
}

/*
 * Function name : printGameBoard()
 * Usage         : printGameBoard(char board[][])
 * Definition    : Prints a visual representation of board[][].
*/
void printGameBoard(char board[][COLUMNS]) {

	int rowNum = ROWS;
	char columnChar = COLUMN_LETTER_START;

	//Print column letters above board in order a,b,c,d,etc...
	printf("  ");
	for (int k = 0; k< COLUMNS; k++) {
		printf("%c ", columnChar);
		columnChar++;
	}

	printf("\n");

	//Print board and row numbers 1,2,3,5,etc...
	for (int i = 0; i < ROWS; i++) {
		printf("%i " , rowNum);
		rowNum--;

		for (int j = 0; j < COLUMNS; j++)
		{	

			char cellElement = board[i][j];
			if (cellElement == COLORED_PLAYER_1_PIECE) {
				printf("\033[0;31m");
				printf("%c ", PLAYER_1_PIECE);
			} else if (cellElement == COLORED_PLAYER_2_PIECE) {
				printf("\033[0;31m");
				printf("%c ", PLAYER_2_PIECE);
			} else {
				printf("%c ", cellElement);
			}

			printf("\033[0m");

		}
		printf("\n");
	}

}


/*
 * Function name : isValidMove()
 * Usage         : printGameBoard(char board[][], int column)
 * Definition    : Used to check if board[][] has 
 				   an open space at int column.
 * Returns       : _Bool representing if dropping a piece into int column
 				   is a valid choice. 1 = valid, 0 = not valid.
*/
_Bool isValidMove(char board[][COLUMNS], int column) {
	return (board[0][column] == OPEN_CELL);
}

/*
 * Function name : findValidMoves()
 * Usage         : findValidMoves(char board[][], int validMoves[])
 * Definition    : Modifes the validMoves[] array to contain all
 				   of the columns that still have open cells in the
 				   char board[][].
 * Returns       : int representing number of valid moves remaining
 				   on board[][].
*/
int findValidMoves(char board[][COLUMNS], int validMoves[]) {
	
	int numberOfValidMoves = 0;
	for (int c = 0; c < COLUMNS; c++)
	{
		if (isValidMove(board, c)) {
			validMoves[numberOfValidMoves] = c;
			numberOfValidMoves++;
		}
	}

	return numberOfValidMoves;
}

/*
 * Function name : dropPiece()
 * Usage         : dropPiece(char board[][], int column, char piece)
 * Definition    : Sets the the first open row in board[][] at
 				   int column to char piece
*/
void dropPiece(char board[][COLUMNS], int column, char piece) {
	for (int i = ROWS-1; i >= 0; i--)
	{
		char element = board[i][column];
		if (element == OPEN_CELL) {
			board[i][column] = piece;
			return;
		}
	}
}

/*
 * Function name : isWinner()
 * Usage         : iswinner(char board[][], char piece)
 * Definition    : Checks if a player has won by looking for
 				   horizontal, vertical, right diagonal,
 				   and left diagonal chains of 4 identical
 				   pieces in a row
 * Returns: 	 : _Bool representing whether the player who
 				   dropped char piece wins the game. 1 = player wins,
 				   0 = player hasn't won.
*/
_Bool isWinner(char board[][COLUMNS], char piece) {

	int winningChunk[4];
	int winningChunkIndex;

	//Horizontal
	for (int i = 0; i < COLUMNS - 3; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (board[j][i] == piece && board[j][i+1] == piece &&  board[j][i+2] == piece &&  board[j][i+3] == piece) {
				
				for (int k = 0; k < 4; k++)
				{
					if (piece == PLAYER_1_PIECE) {
						board[j][i + k] = COLORED_PLAYER_1_PIECE;
					} else {
						board[j][i + k] = COLORED_PLAYER_2_PIECE;
					}
					
				}

				return 1;
			}
		}
	}

	//Vertical
	for (int i = ROWS-1; i >= 3; i--) {
		for (int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j] == piece && board[i-1][j] == piece &&  board[i-2][j] == piece &&  board[i-3][j] == piece) {
				
				for (int k = 3; k >= 0; k--)
				{
					if (piece == PLAYER_1_PIECE) {
						board[i - k][j] = COLORED_PLAYER_1_PIECE;
					} else {
						board[i - k][j] = COLORED_PLAYER_2_PIECE;
					}
					
				}

				return 1;
			}
		}
	}

	//Right diagonal
	for (int i = ROWS-1; i >= 3; i--) {
		for (int j = 0; j < COLUMNS - 3; j++) {
			if (board[i][j] == piece && board[i-1][j+1] == piece &&  board[i-2][j+2] == piece &&  board[i-3][j+3] == piece) {
				
				for (int k = 0; k < 4; k++)
				{
					if (piece == PLAYER_1_PIECE) {
						board[i - k][j + k] = COLORED_PLAYER_1_PIECE;
					} else {
						board[i - k][j + k] = COLORED_PLAYER_2_PIECE;
					}
					
				}

				return 1;
			}
		}
	}

	//Left diagonal
	for (int i = ROWS-1; i >= 3; i--) {
		for (int j = COLUMNS-1; j >= 3; j--) {

			if (board[i][j] == piece && board[i-1][j-1] == piece &&  board[i-2][j-2] == piece &&  board[i-3][j-3] == piece) {
				
				for (int k = 0; k < 4; k++)
				{
					if (piece == PLAYER_1_PIECE) {
						board[i - k][j - k] = COLORED_PLAYER_1_PIECE;
					} else {
						board[i - k][j - k] = COLORED_PLAYER_2_PIECE;
					}
					
				}

				return 1;
			}
		}
	}

	return 0;

}

/*
 * Function name : getColumnIndex()
 * Usage         : getColumnIndex(char column)
 * Definition    : Coverts the char column to an index on a gameBoard[][]
 				   2d array.
 * Returns       : An int which is the column index corresponding 
 				   to char column.
*/
int getColumnIndex(char column) {

	char columnLetter = COLUMN_LETTER_START;
	for (int i = 0; i < COLUMNS; i++) {
		if (columnLetter == column) {
			return i;
		} 
		columnLetter++;
	}

	return -1;

}

/*
 * Function name : getColumnLetter()
 * Usage         : getColumnLetter(int columnIndex)
 * Definition    : Finds the letter corresponding to the
 				   int columnIndex argument.
 * Returns       : A char which is the letter corresponding to
 				   int columnIndex (letter above column on board). 
*/
char getColumnLetter(int columnIndex) {
	char columnLetter = (char) (COLUMN_LETTER_START + columnIndex);
	columnLetter = toupper(columnLetter);

	return columnLetter;
}

/*
 * Function name : cloneBoard()
 * Usage         : cloneBoard(char board[][], char newBoard[][])
 * Definition    : Copies all of the elements from board[][]
 				   into newBoard[][] creating a clone.
*/
void cloneBoard(char board[][COLUMNS], char newBoard[][COLUMNS]) {
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLUMNS; c++)
		{
			newBoard[r][c] = board[r][c];
		}
	}
}


/*AI controller*/

/*
 * Function name : getPiecesInChunk()
 * Usage         : getColumnIndex(char chunk[], char piece)
 * Definition    : Counts how many char piece are in char chunk[]
 				   and returns the count.
 * Returns       : An int representing the number of char piece in
 				   char chunk[].
*/
int getPiecesInChunk(char chunk[4], char piece) {
	int count = 0;
	for (int i = 0; i < 4; i++) {	
		char element = chunk[i];
		if (chunk[i] == piece) {
			count++;
		}
	}
	return count;
}

/*
 * Function name : resetChunk()
 * Usage         : resetChunk(char chunk[4])
 * Definition    : Sets every value in char chunk[4] to
 				   'm' which is a character that is not
 				   used in the game so it represents nothing.
*/
void resetChunk(char chunk[4]) {
	for (int i = 0; i < 4; i++) {
		chunk[i] = 'm';
	}
}

/*
 * Function name : getChunkValue()
 * Usage         : getChunkValue(char chunk[4], char piece)
 * Definition    : Calculates the value of a chunk containing game
 				   pieces and blank spaces and returns this value. This
 				   function is used by the ai to determine where it
 				   should place it's piece.
 * Returns       : An int representing the value the ai 
                   placed on char chunk[].
*/
int getChunkValue(char chunk[4], char piece) {

	int chunkValue = 0;

	//Get #pieces, #opencells, #playerpieces in chunk
	int piecesInChunk = getPiecesInChunk(chunk, piece);
	int numberOfOpenCells = getPiecesInChunk(chunk, OPEN_CELL);
	int playerPiecesInChunk; 
	if (piece == PLAYER_1_PIECE) {
		playerPiecesInChunk = getPiecesInChunk(chunk, PLAYER_2_PIECE);
	} else {
		playerPiecesInChunk = getPiecesInChunk(chunk, PLAYER_1_PIECE);
	}

	//Value the chunk based on what it contains
	if (piecesInChunk == 2 && numberOfOpenCells == 2) {
		chunkValue+= 1;
	} else if (piecesInChunk == 3 && numberOfOpenCells == 1) {
		chunkValue += 5;
	} else if (piecesInChunk == 4) {
		chunkValue += 100000000;
	}

	if (playerPiecesInChunk == 3 && numberOfOpenCells == 1) {
		chunkValue -= 1000000;
	} else if (playerPiecesInChunk == 2 && numberOfOpenCells == 2) {
		chunkValue -= 100;
	}

	return chunkValue;

}	

/*
 * Function name : findBoardValue()
 * Usage         : findBoardValue(char board[][], char piece)
 * Definition    : Iterates through the board creating arrays 
 				   of size 4 and fills them with all possible locations 
 				   a connect 4 could be found. It then collects the total
 				   value of every array and returns this value.
 * Returns       : An int representing the total value the ai places
 				   on char board[][].
*/
int findBoardValue(char board[][COLUMNS], char piece) {

	int boardValue = 0;

	//Check horizontal direction
	for (int r = 0; r < ROWS; r++) {

		char chunk[4];
		resetChunk(chunk);

		for (int c = 0; c < COLUMNS - 3; c++) {

			for (int i = 0; i < 4; i++) {
				chunk[i] = board[r][c + i];
			}

			boardValue += getChunkValue(chunk, piece);
			resetChunk(chunk);
		}
	}

	//Check vertical direction
	for (int c = 0; c < COLUMNS; c++) {
		
		char chunk[4];
		resetChunk(chunk);

		for (int r = ROWS-1; r >= 3; r--) {
			
			for (int i = 0; i < 4; i++) {
				chunk[i] = board[r - i][c];
			}
			
			boardValue += getChunkValue(chunk, piece);
			resetChunk(chunk);

		}
	}

	//Check right diagonal
	for (int r = ROWS - 1; r >= 3; r--) {

		char chunk[4];
		resetChunk(chunk);

		for (int c = 0; c < COLUMNS - 3; c++) {

			for (int i = 0; i < 4; i++) {
				chunk[i] = board[r - i][c + i];
			}

			boardValue += getChunkValue(chunk, piece);
			resetChunk(chunk);

		}
	}

	//Check left diagonal
	for (int r = ROWS - 1; r > ROWS-3; r--) {

		char chunk[4];
		resetChunk(chunk);

		for (int c = COLUMNS-1; c >= 3; c--) {

			for (int i = 0; i < 4; i++) {
				chunk[i] = board[r - i][c - i];
			}
			
			boardValue += getChunkValue(chunk, piece);
			resetChunk(chunk);

		}
	}
	
	return boardValue;
}

/*
 * Function name : takeTurn()
 * Usage         : takeTurn(char board[][], char piece)
 * Definition    : Iterates through every valid move the ai
 				   could make during their turn, performs this move
 				   and then calculates the value of the resulting board.
 				   From every board value it chooses the highest one and
 				   makes its final move based on this one.
 * Returns       : A char that corresponds to the letter of the column
 				   that the ai dropped their piece into.
*/
char takeTurn(char board[][COLUMNS], char piece) {

	printf("Taking turn\n");

	//Variables for determining highest board value
	int validMoves[COLUMNS];
	int numberOfValidMoves = findValidMoves(board, validMoves);
	int bestMoveChoice = -1;
	int highestBoardValue;

	if (numberOfValidMoves > 0) {
		//Iterate through valid moves
		for (int i = 0; i < numberOfValidMoves; i++) {
			
			//Clone the board, and make the move
			char clonedBoard[ROWS][COLUMNS];
			cloneBoard(board, clonedBoard);
			dropPiece(clonedBoard, validMoves[i], piece);
			int boardValue = findBoardValue(clonedBoard, piece);

			/* Compare board values, choosing 
			   the move that produced the highest one */
			if (bestMoveChoice == -1 || boardValue > highestBoardValue) {
				highestBoardValue = boardValue;
				bestMoveChoice = validMoves[i];
			}

		}

		//Drop the piece at the best choice location
		printf("Best move choice: %i\n", bestMoveChoice);
		dropPiece(board, bestMoveChoice, piece);
		highestBoardValue = 0;

		return getColumnLetter(bestMoveChoice);
	}

	return -1;

}

/*Game controller*/

/*
 * Function name : printMoveLog()
 * Usage         : printMoveLog(char log[], int turns)
 * Definition    : Prints a formatted list of the turns
 				   that took place in the game.
*/
void printMoveLog(char log[], int turns) {

	printf("Moves: [");
	for (int i = 0; i < turns; i++) {

		printf("%c", log[i]);
		if (i != (turns - 1)) {
			printf(", ");
		}

	}
	printf("]\n");

}

/*
 * Function name : newGame()
 * Usage         : newGame()
 * Definition    : Starts a new game and directs gameplay.
*/
char currentPiece = PLAYER_1_PIECE;
void newGame(void) {

	//Main game loop
	while (1) {

		//Player choice, used for char inputs
		char playerChoice;
		printf("New game: Y/N\n");
		scanf(" %c", &playerChoice);

		playerChoice = tolower(playerChoice);

		if (playerChoice == 'y') {

			_Bool validPiece = 0;
			char playerPiece, aiPiece;
			while (!validPiece) {

				printf("Select your piece: %c/%c, or type 'N' to quit\n", PLAYER_1_PIECE, PLAYER_2_PIECE);
				scanf(" %c", &playerChoice);
				playerChoice = toupper(playerChoice);

				if (playerChoice == PLAYER_2_PIECE) {

					printf("HERE\n");
					playerPiece = PLAYER_2_PIECE;
					aiPiece = PLAYER_1_PIECE;
					validPiece = 1;

				} else if (playerChoice == PLAYER_1_PIECE) {

					playerPiece = PLAYER_1_PIECE;
					aiPiece = PLAYER_2_PIECE;
					validPiece = 1;

				} else if (playerChoice == 'N') {
					return;
				} else {
					printf("Invalid choice\n");
				}
			}

			//Setup gameboard
			char gameBoard[ROWS][COLUMNS];
			initilizeGameBoard(gameBoard);
			printGameBoard(gameBoard);

			//Round variables
			_Bool hasWon = 0, aiHasTakenTurn = 0;
			int turnNumber = 0;
			char moveLog[COLUMNS*ROWS];
			while (!hasWon) {

				//If the ai is player 1, it goes first
				if (playerPiece == PLAYER_2_PIECE) {
					//AI takes turn
					char aiTargetColumn = takeTurn(gameBoard, aiPiece);

					if (aiTargetColumn != -1) {
						moveLog[turnNumber] = aiTargetColumn;
						turnNumber++;
					}

					aiHasTakenTurn = 1;
					hasWon = isWinner(gameBoard, aiPiece);

					if (hasWon) {
						printGameBoard(gameBoard);
						printf("AI WINS!!!\n");
						printMoveLog(moveLog, turnNumber);
						break;
					}

				}


				//Check if there is atleast one valid move remaining
				int validMoves[COLUMNS];
				int numValidMoves = findValidMoves(gameBoard, validMoves);
			
				if (numValidMoves == 0) {
					printf("DRAW!!!\n");
					break;	
				} 

				//Player takes turn
				printf("Your turn: \n");
				scanf(" %c", &playerChoice);
				playerChoice = toupper(playerChoice);

				/*Convert the player's char input (column letter)
				 to gameboard column index
				*/
				int playerTargetColumn;
				playerTargetColumn = getColumnIndex(playerChoice);

				while (playerTargetColumn == -1 || !isValidMove(gameBoard, playerTargetColumn)) {

					printf("Invalid column choice\n");
					printf("Your turn: \n");
					printGameBoard(gameBoard);
					scanf(" %c", &playerChoice);
					playerChoice = toupper(playerChoice);
					playerTargetColumn = getColumnIndex(playerChoice);

				}
				
				//dropPiece(gameBoard, playerTargetColumn, playerPiece);
				dropPiece(gameBoard, playerTargetColumn, playerPiece);
				
				moveLog[turnNumber] =playerChoice;
				turnNumber++;
				
				hasWon = isWinner(gameBoard, playerPiece);

				if (hasWon) {
					printGameBoard(gameBoard);
					printf("YOU WIN!!!\n");
					printMoveLog(moveLog, turnNumber);
					break;
				}

				if (!aiHasTakenTurn) {
					
					char aiTargetColumn = takeTurn(gameBoard, aiPiece);
					aiHasTakenTurn = 1;

					if (aiTargetColumn != -1) {
						moveLog[turnNumber] = aiTargetColumn;
						turnNumber++;
					}

					hasWon = isWinner(gameBoard, aiPiece);

					if (hasWon) {
						printGameBoard(gameBoard);
						printf("AI WINS!!!\n");
						printMoveLog(moveLog, turnNumber);
						break;
					}

				}

				printGameBoard(gameBoard);
				aiHasTakenTurn = 0;
			}

		} else {
			return;
		}
	}
}


/* Main */

int main()
{

	newGame();
	return 0;
}




