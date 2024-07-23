/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			printf("%d ", values[i][j]);
		}
		printf("\n");
	}
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
    int i;
    int j; 

	int temp;

    for(i = 0; i < MAP_SIZE; i++) {
        for(j = 0; j < MAP_SIZE; j++) {
            map[i][j] = 0;
        }
    }

	for(i = 0; i < MAP_SIZE; i++) {
		for(j = 0; j < MAP_SIZE; j++) {
			if(i == 0 && j == 0) {
				temp = i;
				for(i = 0; i <= 1; i++) {
					map[i][j] = 2;
				}
				i = temp;
			}
			if(i == 2 && j == 1) {
				temp = j;
				for(j = 1; j <= 3; j++) {
					map[i][j] = 3;
				}
				j = temp;
			}
			if(i == 5 && j == 0) {
				temp = j;
				for(j = 0; j <= 3; j++) {
					map[i][j] = 4;
				}
				j = temp;
			}
			if(i == 1 && j == 5) {
				temp = i;
				for(i = 1; i <= 5; i++) {
					map[i][j] = 5;
				}
				i = temp;
			}
		}
	}
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int pos_c;
	int pos_r;
	int max_c;
	int max_r;
	int orientation;

	orientation = rand() %2 + 1;

	if(orientation == 1) {
		max_c = MAP_SIZE - size + 1;
		max_r = MAP_SIZE;
	}
	else if(orientation == 2) {
		max_c = MAP_SIZE;
		max_r = MAP_SIZE - size + 1;
	}
	pos_c = rand() %max_c;
	pos_r = rand() %max_r;

    if(size == 5 && orientation == 2 && pos_c == 5) {
        printf("ROW: %d\n",pos_r);
    }

	if(orientation == 1) {
		for(int i = pos_c; i < (pos_c + size); i++) {
			map[pos_r][i] = size;
		}
	}
	else if(orientation == 2) {
		for(int i = pos_r; i < (pos_r + size); i++) {
			map[i][pos_c] = size;
		}
	}
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int count = 0;

	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			if(map[i][j] == value) {
				count += 1;
			}
		}
	}
	return count;
}

int TopLeftPosition (int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{
    int direction = 0;
    int j;
    int i;

    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == size) {
                if (map[i + 1][j] == size) {
                    direction = 2;
                    *row = i;
                    *col = j;

                }
                else if (map[i][j + 1] == size)
        		{
                    direction = 1;
                    *row = i;
                    *col = j;

        		}
                return direction;
            }
        }
    }
    return direction;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int direction;
	int row;
	int col;
	int j;

	if(CountValues(size,map) == size) {
		direction = TopLeftPosition(size, &row, &col, map);
        /*Horizontal*/
		if(direction == 1) {
			for(j = col; j < (col + size); j++) {
                if(j == col) {
                    /*If left is edge and top is edge*/
                    if(j == 0 && row == 0) {
                        if(map[row + 1][j] != 0) {
                            return 0;
                        }
                    }
                    /*If left is not edge but top is edge*/
                    else if(row == 0) {
                        if(map[row][j - 1] != 0 || map[row + 1][j] != 0) {                    
                            return 0;
                        }
                    }
                    /*If left is edge and bottom is edge*/
                    else if(j == 0 && row == (MAP_SIZE - 1)) {
                        if(map[row - 1][j] != 0) {                     
                            return 0;
                        }
                    }
                    /*If left is not edge but bottom is edge*/
                    else if(row == (MAP_SIZE - 1)) {
                        if(map[row][j - 1] != 0 || map[row - 1][j] != 0) {                      
                            return 0;
                        }
                    }
                    /*If left is edge and bottom and top is NOT edge*/
                    else if(j == 0) {
                        if(map[row + 1][j] != 0 || map[row - 1][j] != 0) {          
                            return 0;
                        }
                    } 
                    /*If left is not a edge*/
                    else {
                        if(map[row + 1][j] != 0 || map[row - 1][j] != 0 || map[row][j - 1] != 0) {                 
                            return 0;
                        }
                    }
                }
                else if(j == (col + size - 1)) {
                    /*If right is edge and top is edge*/
                    if(j == (MAP_SIZE - 1) && row == 0) {
                        if(map[row + 1][j] != 0) {                     
                            return 0;
                        }
                    }
                    /*If top is edge but right is not edge*/
                    else if(row == 0) {
                        if(map[row][j + 1] != 0 || map[row + 1][j] != 0) {                      
                            return 0;
                        }
                    }
                    /*If right is edge and bottom is edge*/
                    else if(j == (MAP_SIZE - 1) && row == (MAP_SIZE - 1)) {
                        if(map[row - 1][j] != 0) {                      
                            return 0;
                        }
                    }
                    /*If bottom is edge but right is not edge*/
                    else if(row == (MAP_SIZE - 1)) {
                        if(map[row][j + 1] != 0 || map[row - 1][j] != 0) {                      
                            return 0;
                        }
                    }
                    /*If right is edge and bottom and top is NOT edge*/
                    else if(j == (MAP_SIZE - 1)) {
                        if(map[row + 1][j] != 0 || map[row - 1][j] != 0) {                    
                            return 0;
                        }
                    } 
                    /*If right is not a edge*/
                    else {
                        if(map[row + 1][j] != 0 || map[row - 1][j] != 0 || map[row][j + 1] != 0) {                    
                            return 0;
                        }
                    }
                }
                /*If top or bottom is not edge*/
				else {
                    /*If top is edge*/
                    if(row == 0) {
                        if(map[row + 1][j] != 0) {
					        return 0;
				        }
                    }
                    /*If bottom is edge*/
                    else if(row == (MAP_SIZE - 1)) {
                        if(map[row - 1][j] != 0) {
					        return 0;
				        }
                    }
                    /*If bottom and top are both not edge.*/
                    else {
                        if(map[row - 1][j] != 0 || map[row + 1][j] != 0) {
					        return 0;
				        }
                    }
                }
			}
            /*Return 1 if all tests pass*/
			return 1;
		}
        /*Vertical*/
		else if(direction == 2) {
			for(j = row; j < (row + size); j++) {
                if(j == row) {
                    /*If left is edge and top is edge*/
                    if(j == 0 && col == 0) {
                        if(map[j][col + 1] != 0) {                       
                            return 0;
                        }
                    }
                    /*If top is not edge but left is edge*/
                    else if(col == 0) {
                        if(map[j][col + 1] != 0 || map[j - 1][col] != 0) {                       
                            return 0;
                        }
                    }
                    /*If right is edge and top is edge*/
                    else if(j == 0 && col == (MAP_SIZE - 1)) {
                        if(map[j][col - 1] != 0) {                    
                            return 0;
                        }
                    }
                    /*If top is not edge but right is edge*/
                    else if(col == (MAP_SIZE - 1)) {
                        if(map[j][col - 1] != 0 || map[j - 1][col] != 0) {                    
                            return 0;
                        }
                    }
                    /*If top is edge and left and right is NOT edge*/
                    else if(j == 0) {
                        if(map[j][col + 1] != 0 || map[j][col - 1] != 0) {                   
                            return 0;
                        }
                    } 
                    /*If top is not edge and sides are not edge*/
                    else {
                        if(map[j][col + 1] != 0 || map[j][col - 1] != 0 || map[j - 1][col] != 0) {                   
                            return 0;
                        }
                    }
                }
                else if(j == (row + size - 1)) {
                    /*If left is edge and bottom is edge*/
                    if(j == (MAP_SIZE - 1) && col == 0) {
                        if(map[j][col + 1] != 0) {                       
                            return 0;
                        }
                    }
                    /*If left is edge but bottom is not edge*/
                    else if(col == 0) {
                        if(map[j][col + 1] != 0 || map[j + 1][col] != 0) {    
                            return 0;
                        }
                    }
                    /*If right is edge and bottom is edge*/
                    else if(j == (MAP_SIZE - 1) && col == (MAP_SIZE - 1)) {
                        if(map[j][col - 1] != 0) {                       
                            return 0;
                        }
                    }
                    /*If right is edge but bottom is not edge*/
                    else if(col == (MAP_SIZE - 1)) {
                        if(map[j][col - 1] != 0 || map[j + 1][col] != 0) {                       
                            return 0;
                        }
                    }
                    /*If bottom is edge and left and right is NOT edge*/
                    else if(j == (MAP_SIZE - 1)) {
                        if(map[j][col + 1] != 0 || map[j][col - 1] != 0) {                     
                            return 0;
                        }
                    } 
                    /*If bottom is not edge*/
                    else {
                        if(map[j][col + 1] != 0 || map[j][col - 1] != 0 || map[j + 1][col] != 0) {                     
                            return 0;
                        }
                    }
                }
                /*If right or left is not edge*/
				else {
                    /*If left is edge*/
                    if(col == 0) {
                        if(map[j][col + 1] != 0) {
					        return 0;
				        }
                    }
                    /*If right is edge*/
                    else if(col == (MAP_SIZE - 1)) {
                        if(map[j][col - 1] != 0) {
					        return 0;
				        }
                    }
                    /*If botton and top are not edge*/
                    else {
                        if(map[j][col - 1] != 0 || map[j][col + 1] != 0) {
					        return 0;
				        }
                    }
                }
			}
            /*Return 1 if all tests pass*/
			return 1;
		}
        /*If no direction (1 singular digit) then fail*/
        else {
            return 0;
        }
	}
    /*If number of ship values does not equal ship value (3 4s instead of 4 4s) then fail*/
	else {
		return 0;
	}
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{   
    int success = 0;
	int success1 = 0;
    int success2 = 0;
    int success3 = 0;
    int success4 = 0;
    
    while(success == 0) {
        
        for(int i = 0; i < MAP_SIZE; i++) {
            for(int j = 0; j < MAP_SIZE; j++) {
                map[i][j] = 0;
            }
        }
        
        AddRandomShip(2,map);
        AddRandomShip(3,map);
        AddRandomShip(4,map);
        AddRandomShip(5,map);
        
        success1 = IsShipValid(2,map);
        if(success1 == 1) {
            success2 = IsShipValid(3,map);
            if(success2 == 1) {
                success3 = IsShipValid(4,map);
                if(success3 == 1) {
                    success4 = IsShipValid(5,map);
                    if(success4 == 1) {
                        success = 1;
                    }
                }
            }
        }
    }
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{

	int shot = 1;
    int count = 0;

    int direction2;
    int direction3;
    int direction4;
    int direction5;

    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++) {
            if(shots[i][j] > 0) {
                count++;
            }
        }
    }
    shot = shot + count;
    if(shots[row][col] == 0) {
        shots[row][col] = shot;
    }
    
    if(map[row][col] > 0 && shots[row][col] < 1000) {
        shots[row][col] = (shots[row][col] + 1000);
    }

    //Checking if a ship is destroyed
    direction2 = TopLeftPosition(2, &row, &col, map);
    direction3 = TopLeftPosition(3, &row, &col, map);
    direction4 = TopLeftPosition(4, &row, &col, map);
    direction5 = TopLeftPosition(5, &row, &col, map);

    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++) {
            // Ship size 2
            if(direction2 == 1 && map[i][j] == 2 && map[i][j + 1] == 2 && shots[i][j] < 1999 && shots[i][j + 1] < 1999) {
                if(shots[i][j] > 1000 && shots[i][j + 1] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 2 - 1000);
                    shots[i][j + 1] = shots[i][j + 1] + (1000 * 2 - 1000);
                }
            }
            else if(direction2 == 2 && map[i][j] == 2 && map[i + 1][j] == 2 && shots[i][j] < 1999 && shots[i + 1][j] < 1999) {
                if(shots[i][j] > 1000 && shots[i + 1][j] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 2 - 1000);
                    shots[i + 1][j] = shots[i + 1][j] + (1000 * 2 - 1000);
                }
            }
            // Ship size 3
            else if(direction3 == 1 && map[i][j] == 3 && map[i][j + 1] == 3 && map[i][j + 2] == 3 && shots[i][j] < 1999 && shots[i][j + 1] < 1999 && shots[i][j + 2] < 1999) {
                if(shots[i][j] > 1000 && shots[i][j + 1] > 1000 && shots[i][j + 2] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 3 - 1000);
                    shots[i][j + 1] = shots[i][j + 1] + (1000 * 3 - 1000);
                    shots[i][j + 2] = shots[i][j + 2] + (1000 * 3 - 1000);
                }
            }
            else if(direction3 == 2 && map[i][j] == 3 && map[i + 1][j] == 3 && map[i + 2][j] == 3 && shots[i][j] < 1999 && shots[i + 1][j] < 1999 && shots[i + 2][j] < 1999) {
                if(shots[i][j] > 1000 && shots[i + 1][j] > 1000 && shots[i + 2][j] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 3 - 1000);
                    shots[i + 1][j] = shots[i + 1][j] + (1000 * 3 - 1000);
                    shots[i + 2][j] = shots[i + 2][j] + (1000 * 3 - 1000);
                }
            }
            // Ship size 4
            else if(direction4 == 1 && map[i][j] == 4 && map[i][j + 1] == 4 && map[i][j + 2] == 4 && map[i][j + 3] == 4 && shots[i][j] < 1999 && shots[i][j + 1] < 1999 && shots[i][j + 2] < 1999 && shots[i][j + 3] < 1999) {
                if(shots[i][j] > 1000 && shots[i][j + 1] > 1000 && shots[i][j + 2] > 1000 && shots[i][j + 3] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 4 - 1000);
                    shots[i][j + 1] = shots[i][j + 1] + (1000 * 4 - 1000);
                    shots[i][j + 2] = shots[i][j + 2] + (1000 * 4 - 1000);
                    shots[i][j + 3] = shots[i][j + 3] + (1000 * 4 - 1000);
                }
            }
            else if(direction4 == 2 && map[i][j] == 4 && map[i + 1][j] == 4 && map[i + 2][j] == 4 && map[i + 3][j] == 4 && shots[i][j] < 1999 && shots[i + 1][j] < 1999 && shots[i + 2][j] < 1999 && shots[i + 3][j] < 1999) {
                if(shots[i][j] > 1000 && shots[i + 1][j] > 1000 && shots[i + 2][j] > 1000 && shots[i + 3][j] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 4 - 1000);
                    shots[i + 1][j] = shots[i + 1][j] + (1000 * 4 - 1000);
                    shots[i + 2][j] = shots[i + 2][j] + (1000 * 4 - 1000);
                    shots[i + 3][j] = shots[i + 3][j] + (1000 * 4 - 1000);
                }
            }
            // Ship size 5
            else if(direction5 == 1 && map[i][j] == 5 && map[i][j + 1] == 5 && map[i][j + 2] == 5 && map[i][j + 3] == 5 && map[i][j + 4] == 5 && shots[i][j] < 1999 && shots[i][j + 1] < 1999 && shots[i][j + 2] < 1999 && shots[i][j + 3] < 1999 && shots[i][j + 4] < 1999) {
                if(shots[i][j] > 1000 && shots[i][j + 1] > 1000 && shots[i][j + 2] > 1000 && shots[i][j + 3] > 1000 && shots[i][j + 4] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 5 - 1000);
                    shots[i][j + 1] = shots[i][j + 1] + (1000 * 5 - 1000);
                    shots[i][j + 2] = shots[i][j + 2] + (1000 * 5 - 1000);
                    shots[i][j + 3] = shots[i][j + 3] + (1000 * 5 - 1000);
                    shots[i][j + 4] = shots[i][j + 4] + (1000 * 5 - 1000);
                }
            }
            else if(direction5 == 2 && map[i][j] == 5 && map[i + 1][j] == 5 && map[i + 2][j] == 5 && map[i + 3][j] == 5 && map[i + 4][j] == 5 && shots[i][j] < 1999 && shots[i + 1][j] < 1999 && shots[i + 2][j] < 1999 && shots[i + 3][j] < 1999 && shots[i + 4][j] < 1999) {
                if(shots[i][j] > 1000 && shots[i + 1][j] > 1000 && shots[i + 2][j] > 1000 && shots[i + 3][j] > 1000 && shots[i + 4][j] > 1000) {
                    shots[i][j] = shots[i][j] + (1000 * 5 - 1000);
                    shots[i + 1][j] = shots[i + 1][j] + (1000 * 5 - 1000);
                    shots[i + 2][j] = shots[i + 2][j] + (1000 * 5 - 1000);
                    shots[i + 3][j] = shots[i + 3][j] + (1000 * 5 - 1000);
                    shots[i + 4][j] = shots[i + 4][j] + (1000 * 5 - 1000);
                }
            }
        }
    }
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
    int slotvalue;

	for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++) {
            slotvalue = map[i][j];
            if(shots[i][j] > (slotvalue * 1000) && shots[i][j] < (slotvalue * 1000 + 1000)) {
            }
            else {
                return 0;
            }
        }
    }
    return 1;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













