/* Jiaqi_Kaylee.c
 *
 * CS 313 HW 4 -- Implement random Connect 4 Player
 *
 * With modified code from Professor Scharstein
 *
 * Jiaqi Li and Kaylee Thumann
 *
 * External sources:
 * https://codeforwin.org/2015/07/c-program-to-search-element-in-array.html
 * https://stackoverflow.com/questions/46675878/random-number-from-array-c
 * https://codeforwin.org/2015/07/c-program-to-find-frequency-of-each-element-in-array.html
 * https://www.geeksforgeeks.org/c-program-find-largest-element-array/
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define CENTER 4
#define ROWS 6
#define COLS 7


int player; // set player to 1 or 2, or 0 if doesn't matter
int board[ROWS][COLS] = {{0}};
char sym[] = {' ', 'X', 'O'};
int choose[42];
int freq[42];
int i = 0; //place within choose
int y = 0;

// simple assert function, quits program with error message if assertion fails
void assert(int cond, char *msg)
{
    if (!cond) {
	fprintf(stderr, "failed assertion %s\n", msg);
	exit(1);
    }
}

// seed random number generator based on on current time in microseconds and board state
void randseed() {
    struct timeval t1;
    gettimeofday(&t1, NULL);
    unsigned int s = t1.tv_usec * t1.tv_sec; // tv_sec seconds of elapsed time; tv_usec microseconds of elapsed time
    int row, col;
    for (col = 0; col < COLS; col++) {
    	for (row = 0; row < ROWS; row++) {
    	    int b = board[row][col];
    	    s += (b+1) * (13*row + 37*col);
    	}
    }
    srand(s);
}

// read encoded board from stdin:
// 7 strings of 'X' and 'O', representing columns from bottom up
// followed by single X/O representing player to move
// returns player num (1=X, 2=O)
int read_board()
{
    int row = 0, col = 0;
    char c;
    while (col < COLS) {
	c = getchar();
        if (c == '\r') { // carriage return (on Windows)
            continue;
        }
	if (c == 'X' || c == 'O') {
	    assert(row < ROWS, "row < ROWS");
	    board[row++][col] = (c == 'X' ? 1 : 2);
	} else if (c == '\n') {
	    row = 0;
	    col++;
	} else {
	    assert(0, "input symbols must be 'X', 'O', or '\\n'");
	}
    }
    // read one more symbol indicating whose move it is
    c = getchar();
    assert(c == 'X' || c == 'O', "last input symbol must 'X' or 'O'");
    randseed(); // seed random number generator based on board state and current time
    return (c == 'X' ? 1 : 2);
}

int get_board(int r, int c)
{
    if ((r<ROWS) && (c<COLS) && (r>=0) && (c>=0))
        return board[r][c];
    else{
        printf ("r:%d, c:%d, Array out of bounds getting the board\n", r,c);
        return 0;
    }
}

// prints board (for debugging)
void print_board()
{
    int row, col;
    for (row = ROWS-1; row >= 0; row--) {
    	printf("| ");
    	for (col = 0; col < COLS; col++)
    	    printf("%c ", sym[board[row][col]]);
    	printf("|\n");
    }
    printf("+---------------+\n");
    printf("  1 2 3 4 5 6 7  \n");
}

// check connected at given location
void check_connected (int nconnect, int r0, int c0, int dr, int dc, int player)
{
    int r = r0, c = c0;
    int n = 0; // number of connected chips
    int old = -1;
    int cur; // current board number

    while ((r >= 0) && (r<ROWS) && (c >= 0) && (c<COLS)){
        //printf("row: %d, col: %d, count: %d\n", r, c, n);
        cur = get_board(r,c);
        if (cur != old){
            n = 1;
            old = cur;
        } else
            n ++;
        r += dr;
        c += dc;
        int condition;
        switch(player){
            case 0 : condition = cur>0; break;
            case 1 : condition = cur==1; break;
            case 2 : condition = cur==2; break;
        }
        if (condition && (n == nconnect) && (r<ROWS) && (c<COLS) && (r>=0) && (c>=0)){
            // found connected chips and array's not out of bounds
            if ((get_board(r,c) == 0) && (r == 0 || (get_board(r-1,c) > 0)))
            // if there is no chip in the direction of the connected chip
            // and there is chip or floor below that position
            {
            //printf ("Column: %d, chip: %d\n",c, cur);
            freq[i] = -1;
            choose[i] = c;
            //printf ("Array place: %d, value: %d\n",i, choose[i]);
            i++;
            //return c;
            }
        }
    }
    //return -1;
}

void check_all (int nconnect, int player)
{
    int r,c;
    for (r=0; r<ROWS; r++){
        //printf ("increasing rows, c=0\n");
        check_connected (nconnect, r,0,0,1, player); // horizontal from left
        check_connected (nconnect, r,0,1,1, player); //check diag / from left
        check_connected (nconnect, r,0,-1,1, player); //check diag \ from left

        check_connected (nconnect, r,COLS-1,0,-1, player); // horizontal from right
        check_connected (nconnect, r,COLS-1,-1,-1, player); // check diag / from right
        check_connected (nconnect, r,COLS-1,1,-1, player); // check diag \ from right
    }
    for (c=0; c<COLS; c++){
        //printf ("increasing columns, c=0\n");
        check_connected (nconnect, 0,c,1,0, player); // check vertical
        check_connected (nconnect, 0,c,1,1, player); // check diag / from bottom
        check_connected (nconnect, ROWS-1,c,-1,0, player); //check diag \ from top

        check_connected (nconnect, ROWS-1,c,-1,-1, player); // check diag / from top
        check_connected (nconnect, 0,c,1,-1, player); //check diag \ from bottom
    }
}

int choose_col()
{
  //int size = 42;
  int m = 0;
  int k, j, l, count;
  int max = freq[0]; // Initialize maximum element

  for(k=0; k<i; k++)
  {
        count = 1;
        for(j=k+1; j<i; j++)
        {
            // If duplicate element is found
            if(choose[k]==choose[j])
            {
                count++;
                freq[j] = 0;
            }
        }
        // If frequency of current element is not counted
        if(freq[k] != 0)
            freq[k] = count;
    }

  // Traverse array elements from second and compare every element with current max
  for (l = 0; l < i; l++)
  {
      if (freq[l] > max) {
        max = freq[l];
        m = l;
      }
  }

  for(k=0; k<i; k++)
  {
      if(freq[k] > 1) { //if there are repeats in the array
          printf("%d\n", choose[m] + 1);
          return choose[m] + 1;
          //choose the most frequent repeats
      } else {
        //generates a random number to choose from array of columns
        randseed();
        int randomIndex = rand() % i;
        int randomValue = choose[randomIndex];
        printf("%d\n", randomValue + 1);
        return randomValue;
      }
  }
  return 0;
}

int main()
{
    player = read_board();
    int opponent = 3-player;
    print_board();

    check_all (3, player);

    if (i != 0)
        choose_col();      //printf("3 comp's connected"); //print_array();
    else {
        check_all (3, opponent);
        if (i != 0)
            choose_col();         //printf("3 opp's connected"); //print_array();
        else {
            check_all (2, player);
            if (i != 0)
                choose_col();
            else {
                check_all (2, opponent);
                if (i != 0)
                    choose_col();
                else {
                    //printf("None are connected");
                    check_all (1, player);
                    if (i != 0)
                        choose_col();
                    else
                        printf("%d\n", CENTER);
                }
            }
        }
    }
    return 0;
}
