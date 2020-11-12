/*  Cam_Frey_Lab2.cpp
*   Cameron Frey - CISC220 Lab 2
*   3/1/2020
*   Functions defined per the requirements of the "CISC220 Lab 1" Document
*/

#include <iostream>             //Pre-processor commands 
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

// getSize: (2 pts)
// function getSize uses call by reference to modify the integer input parameter to a random
// number between 7 and 20 (not including 20).  This will be the size of your board
void getSize(int &size);

// makeBoard: ( 5 pts)
// Function makeboard takes as input an integer: which is the length and width of the board
// (it's a square board).  The function should create an integer matrix (a 2-d array) on the heap, fill
// matrix with 0s (that's the number, not the letter 'O') and return a pointer to the matrix
int **makeBoard(int size);

// printBoard: (5 pts)
// This method takes as input a pointer to a matrix (a 2-D function) of integers and an
// integer for the size (the length and the width - it's a square).  It returns nothing.
// It should print out the matrix, only it should print a space instead of a 0 (in other words, I don't
// want to see a board of 0's - I'd rather just see blank spaces for the 0s).
// NOTE: to print out the board, I used tabs instead of endl's, e.g., cout << x << "\t";
// NOTE2: I also printed out the indices around the edges so the game would be
// easier to check when I was debugging, not to mention easier to play.
void printBoard(int *board[],int size);

//placeBombs: (4 pts)
//This function takes as an input parameter a pointer to the 2-D matrix of integers (the board) and an
// integer (the size).
//It places size + 1 "bombs" randomly on the 2-D matrix.  My bombs were the 9 value (because the board 
// is a board of integers and that kind of looks like an upside down 'b').  It made sure that a bomb hadn't
// already been placed in the randomly selected place
//on the board before placing it, and, if it had, it chose another spot to place the bomb
// NOTE: if you'd like to write a helper function for this, I'm okay with that.
void placeBombs(int **board, int size);

//placeCounts: (9 pts)
//This function takes as input parameters a pointer to the 2-D integer matrix that is the board, an int
// representing the size of the board.  It returns nothing.
//This function places the counts on the board - in minesweeper, when you select a square, that square
//becomes "visible" and should contain the numbe of "bombs" that are adjacent to that square.
//This function calculates the number of adjacent bombs for each square on the matrix and places those
//counts on the matrix, making sure not to overwrite a bomb.
//Again, if you'd like to write a helper function for this one, feel free.
void placeCounts(int **board,int size);

//makeVisibleBoard: (3 pts)
//This function takes as an input parameter the integer for the size of the 2-D matrix of characters that will 
// be created in this function and returned from this function.  The 2-D matrix will be initialized to all '-'
//This function is similar to the makeBoard function.  It will be the board that is displayed to the user as 
// the user plays the game (because you don't want the user to see all the bombs and counts)
char **makeVisibleBoard(int size);

// printVisible: (3 pts)
// Almost exactly like printMatrix (templates anyone??):
// This method takes as input a pointer to a matrix (a 2-D function) of Chars and an
// integer for the size (the length and the width - it's a square).  It returns nothing.
// It should print out the matrix.
// NOTE: like with printMatrix, I printed out the indices around the edges so the game would be
// easier to check when I was debugging, not to mention easier to play.
void printVisible(char *board[], int size);

//chooseSquare: (6 pts)
//This function takes as input parameters the pointer to the board matrix of ints, the pointer to the visible
// matrix of chars, and the size.
//It uses cout and cin to allow the user to choose a square (the x and the y position on the matrix 
// respectively) and then sets the visible matrix at that square to be the value in the board matrix.
//This function returns a boolean - false if the square chosen was a bomb, and true otherwise.
bool chooseSquare(int **intBoard, char **charBoard, int size);

//addBomb: (5 pts)
//This function takes as input parameters the pointer to the visible matrix of chars, the size int, and a pointer
// to the number of bombs found.  It returns a boolean value (true if the number of bombs found is equal
// to size + 1, false otherwise.
//this function is allowing the user to choose a square where they think a bomb is and mark it as bomb in 
// the visible matrix.
//It allows the user to choose a square, using cout and cin to get the x and y values, respectively, and then
//modifies that square in the visible matrix (I marked it with the '9' character, but you could make it be an 
// X or anything you feel makes it obvious that you think there's abomb there.  It then increases the third 
// parameter by 1 (the pointer to the number of bombs found so far).  It checks if the number of bombs 
// found is equal to the total number of bombs and, if so, returns True.  Otherwise it returns false
bool addBomb(char **charBoard, int size, int *numBombs);

//removeBomb: (4 pts)
//This function takes as input parameters the pointer to the visible matrix of chars, the size int, and a pointer
//to the number of bombs found.  It returns nothing.
//this function is allowing the user to choose a square where they previously placed a bomb and unmark the
//square.
//It allows the user to choose a square, using cout and cin to get the x and y values, respectively, and then
//modifies that square if it is a '9' (how I marked my bombs) to be a '-'. It also decreases the count of the
//number of bombs found.
//Note that it checks to make sure the user had previously marked that square as where they thought a bomb
//was.
void removeBomb(char **charBoard, int size, int *numBombs);

//checkForWin: (7 pts) 
//this function takes as input the pointer to the board matrix of integers, the pointer to the visible matrix
//of characters, and the int size.
//It checks to make sure that each bomb in the board matrix has been marked as a bomb on the visible
//matrix.  It returns a boolean value - true if all the bombs have been found, and false otherwise.
bool checkForWin(int **intBoard, char **charBoard, int size);

//removeBoard: (5 pts)
//This function takes as input parameters the pointer to the 2-D integer matrix that is the board, along with the
// size integer, and removes the matrix from the heap.  It returns nothing.
void removeBoard(int **intBoard,int size);

//removeVisible: (3 pts)
//This function takes as input parameters the pointer to the 2-D integer matrix that is the board, along with the
// size integer, and removes the matrix from the heap.  It returns nothing.
void removeVisible(char **charBoard,int size);

int main() {
	srand(time(NULL));
	int size = 0;
	int bombsfound = 0;
	getSize(size);
	cout << "Size is " << size << endl;
	int **mat = makeBoard(size);
	//printBoard(mat, size);  - for testing purposes
	placeBombs(mat,size);
	//printBoard(mat, size);  - for testing purposes
	placeCounts(mat, size);
	//printBoard(mat, size);  //for testing purposes
	char **visible = makeVisibleBoard(size);

	/*  For testing purposes:  */
	// printVisible(visible,size);
	// chooseSquare(mat,visible,size);
	// printVisible(visible,size);
	// addBomb(visible, size, &bombsfound);
	// printVisible(visible,size);
	// removeBomb(visible, size, &bombsfound);
	// printVisible(visible,size);
	// checkForWin(mat, visible, size);
	/*  End of testing */


	char c;
	bool flag = true;
	char again = 'n';
	while (flag) {
		printVisible(visible,size);
        //printBoard(mat,size);
		cout << "Choose: A for choose square, B for add Bomb, C for remove bomb: " << endl;
		cin >> c;
		if (c == 'A' || c == 'a') {
			flag = chooseSquare(mat, visible, size);
			if (!flag) {
				cout << "YOU LOSE!  YOU HIT  A BOMB!!" << endl;
				printBoard(mat, size);
				cout << "\n\nDo you want to play again?" <<endl;
				cin >> again;
			}
		}
		if (c == 'B' || c == 'b') {

			if (addBomb(visible, size, &bombsfound)) {
				cout << "Bombs found: " << bombsfound << endl;
				cout << "You appear to think you've found all the bombs" << endl;
				cout << "Choose: D for check for Win, or C for remove bomb:" << endl;
				cin >> c;
				if (c == 'D' || c == 'd') {
					if (checkForWin(mat, visible, size)) {
						cout <<"YOU WON!!!  WOO WOO!!!" << endl;
						printBoard(mat, size);
					}
					else {
						cout <<"Sorry, you were wrong.  Boo hoo." << endl;
						printBoard(mat, size);
					}
					removeBoard(mat, size);
					removeVisible(visible, size);
					bombsfound = 0;
					flag = false;
				}

				cout << "\n\nDo you want to play again? (y or n)" <<endl;
				cin >> again;

			}
		}
		if (c == 'C' || c == 'c') {
			removeBomb(visible, size, &bombsfound);
		}
		if (!flag && (again == 'y' || again == 'Y')) {
			flag = true;
			bombsfound = 0;
			getSize(size);
			cout << "Size is " << size << endl;
			mat = makeBoard(size);
			//printBoard(mat, size);  - for testing purposes
			placeBombs(mat,size);
			//printBoard(mat, size);  - for testing purposes
			placeCounts(mat, size);
			//printBoard(mat, size);  - for testing purposes
			visible = makeVisibleBoard(size);

		}
	}
	return 0;
}
void getSize(int &size){
    size = rand() % 12 + 7;
    return;
}//getSize

int **makeBoard(int size){
    int **board = new int*[size];
    for(int i=0;i<size;i++){
        board[i] = new int[size];
    }//end for
    for(int i=0; i<size;i++){
        for(int j=0; j <size;j++){
            board[i][j] = 0;
        }//end for
    }//end for
    return board;
}//makeBoard

void printBoard(int *board[], int size){
    cout<<' '<< '\t';
    for(int row=0; row < size;row++){
        cout<<row<< '\t';
    }//end for
    cout<<endl;
    for(int i=0; i<size;i++){
        cout<<i<<'\t';
        for(int j=0; j <size;j++){
            if(board[i][j] == 0){
                cout<<' ';
            }//end if
            else{
                cout<<board[i][j];
            }//end else
            cout<<'\t';
        }//end for
        cout<<endl;
    }//end for
    return;
}//printBoard

void placeBombs(int **board, int size){
    int x = rand() % size;
    int y = rand() % size;
    for(int i=0; i < size+1; i++){
        if(board[x][y]==9){
            while(board[x][y] == 9){
                x = rand() % size;
                y = rand() % size;
            }//end while
        }//end if
        board[x][y] = 9;
    }//end for
    return;
}//placeBombs

void placeCounts(int **board, int size){
    for(int y=0;y<size;y++){
        for(int x=0;x<size;x++){
            if(board[y][x]==9){             //Finds bomb in matrix then adds 1 to each surrounding place
                int toplx = x-1;            //as long as it is not a bomb
                int toply = y-1;
                int topy = y-1;
                int toprx = x+1;
                int topry = y-1;
                int leftx = x-1;
                int rightx = x+1;
                int botlx = x-1;
                int botly = y+1; 
                int boty = y+1;
                int botrx = x+1;
                int botry = y+1;
                if(toplx >= 0 && toply >= 0){
                    if(board[toply][toplx] != 9){
                        board[toply][toplx]++;
                    }
                }
                if(topy >= 0){
                    if(board[topy][x] != 9){
                        board[topy][x]++;
                    }
                }
                if(toprx < size && toply >= 0){
                    if(board[topry][toprx] != 9){
                        board[topry][toprx]++;
                    }
                }
                if(leftx >= 0){
                    if(board[y][leftx] != 9){
                        board[y][leftx]++;
                    }
                }
                if(rightx < size){
                    if(board[y][rightx] != 9){
                        board[y][rightx]++;
                    }
                }
                if(botlx >= 0 && botly < size){
                    if(board[botly][botlx] != 9){
                        board[botly][botlx]++;
                    }
                }
                if(boty < size){
                    if(board[boty][x] != 9){
                        board[boty][x]++;
                    }
                }
                if(botrx < size && botry < size){
                    if(board[botry][botrx] != 9){
                        board[botry][botrx]++;
                    }
                }
            }//end if
        }//end x for
    }//end y for
    return;
}//placeCounts

char **makeVisibleBoard(int size){
    char **board = new char*[size];
    for(int i=0;i<size;i++){
        board[i] = new char[size];
    }//end for
    for(int i=0; i<size;i++){
        for(int j=0; j <size;j++){
            board[i][j] = '-';
        }//end for
    }//end for
    return board;
}//makeVisibleBoard

void printVisible(char *board[], int size){
    cout<<' '<< '\t';
    for(int row=0; row < size;row++){
        cout<<row<< '\t';
    }//end for
    cout<<endl;
    for(int i=0; i<size;i++){
        cout<<i<<'\t';
        for(int j=0; j <size;j++){
            if(board[i][j] == 0){
                cout<<' ';
            }//end if
            else{
                cout<<board[i][j];
            }//end else
            cout<<'\t';
        }//end for
        cout<<endl;
    }//end for
    return;
}//printVisible

bool chooseSquare(int **intBoard, char **charBoard, int size){
    int x,y;
    bool bomb = true;
    cout<<"Choose square - Enter a X coordinate:"<<endl;
    cin>>x;
    cout<<"Choose square - Enter a Y coordinate:"<<endl;
    cin>>y;
    if(intBoard[y][x] == 9){
        bomb = false;
    }//end if
    charBoard[y][x] = '0' + intBoard[y][x];
    return bomb;
}//chooseSquare

bool addBomb(char **charBoard, int size, int *numBombs){
    bool allFound = false;
    int x,y;
    cout<< "Add bomb - Enter a X coordinate:"<<endl;
    cin>> x;
    cout<< "Add bomb - Enter a Y coordinate:"<<endl;
    cin >> y;
    *numBombs+=1;
    if(*numBombs >= size +1){
        allFound = true;
    }//end if
    charBoard[y][x] = 'X';
    return allFound;
}//addBomb

void removeBomb(char **charBoard, int size, int *numBombs){
    int x,y;
    cout<< "Remove bomb - Enter a X coordinate:"<<endl;
    cin>> x;
    cout<< "remove bomb - Enter a Y coordinate:"<<endl;
    cin >> y;
    if(charBoard[y][x] == 'X'){
        *numBombs--;
        charBoard[y][x] = '-';
    }//end if
    return;
}//removeBomb

bool checkForWin(int **intBoard, char **charBoard, int size){
    bool win = false;
    int bombCount = 0;
    for(int y=0; y<size;y++){
        for(int x=0;x<size;x++){
            if((intBoard[y][x] == 9) && (charBoard[y][x] == 'X')){
                bombCount++;
            }//end if
        }//end x for
    }//end y for
    if(bombCount == (size+1)){
        win = true;
    }//end if
    return win;
}//checkForWin

void removeBoard(int **intBoard,int size){
    for(int x=0; x<size;x++){
        delete[] intBoard[x];
    }//end for
    delete[] intBoard;
    return;
}//removeBoard

void removeVisible(char **charBoard,int size){
    for(int x=0; x<size;x++){
        delete[] charBoard[x];
    }//end for
    delete[] charBoard;
    return;
}//removeVisible