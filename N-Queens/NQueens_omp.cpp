#include <iostream>
#include <stdlib.h>
#include <time.h> 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

//number of queens
#define QN 35//16//8
//board dimensions
#define N 35//16//8

int board[N][N] = {0};

int queenPositions[QN][2] = {-1};
int queenIndex = 0;

int checked[N][N] = {0};

//https://stackoverflow.com/questions/21890627/drawing-a-rectangle-with-sdl2
void PrintBoard()
{
	//Initialize SDL and window
	int SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
	"N-Queens", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	640,
	480,
	SDL_WINDOW_SHOWN
	);

	// Setup renderer
	SDL_Renderer* renderer = NULL;
	renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	// Draw background
	// Set render color to brown ( background will be rendered in this color )
	SDL_SetRenderDrawColor( renderer, 101, 67, 33, 255 );
	// Clear winow
	SDL_RenderClear( renderer );

	//Draw the board -------------------------------------------------------------
	// Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 50;
	r.h = 50;

	bool color = true;

	for(int i = 0; i < QN; i++)
	{	
		for(int j = 0; j < QN; j++)
		{
			if (color)
				SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );	
			else
				SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

			color = not color;

			r.x += 50;
			// Render rect
			SDL_RenderFillRect( renderer, &r );
		}		
		r.y += 50;
		r.x = 0;
		if ( i % 2 == 1)
			color = true;
		else
			color = false;
	}

	//Draw the board (end) --------------------------------------------------------

	//Draw the queens----------------------

	r.w = 10;
	r.h = 10;
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
	//for (int i = 0; i < queenIndex-1; i++)
	for (int i = 0; i < QN; i++)
	{
		r.y = queenPositions[i][0] * 50 + 15 + r.w / 2;
		r.x = queenPositions[i][1] * 50 + 65 + r.h / 2;
		//cout << r.x << "," << r.y << endl;
		SDL_RenderFillRect( renderer, &r );
	}
	//Draw the queens (end) ---------------

	// Render the rect to the screen
	SDL_RenderPresent(renderer);

	//Check if [x] button is clicked and if so, exit
	//https://stackoverflow.com/questions/29706885/the-correct-way-to-test-sdl-pollevent-in-a-while
	SDL_Event e;
	int quit=0;
	while(!quit){
		while (SDL_PollEvent(&e)){
			if (e.type==SDL_QUIT)
				quit=1;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

}

bool CheckHorizontal(int x, int y)
{
	for (int i = 1; i < N; i++)
	{
		if( (y - i) < 0 )
		{
			//Out of bounds
			return false;
		}

		//cout << "board: " << board[x][y - i] << endl;

		if(board[x][y - i] == 1)
		{
			//has horizontal collision
		    	return true;
		}
	}

	return false;
}

//Returns true if there is a vertical collision
//bool CheckVertical(int x, int y, int col)
bool CheckVertical(int x, int y)
{
	//For given x position check all rows except the current
	for (int i = 0; i < N; i++)
	{
		//Exclude the current row
		if (i != x)
		{
		    if (board[i][y] == 1)
		    {
			return true;
		    }
		}
	}

	return false;
}

//returns true if there a collision exists
//otherwise returns false
bool CheckUpperLeftDiagonal(int x, int y)
{
/*
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)	
			cout << board[i][j] << ' ';
		cout << endl;
	}
*/
	for (int i = 1; i < N; i++)
	{
		if( ((x - i) < 0) or ((y - i) < 0) )
		{
			//Out of bounds
			return false;
		}

		//cout << "board: " << board[x - i][y - i] << endl;

		if(board[x - i][y - i] == 1)
		{
			//has collision at the upper left diagonal
		    	return true;
		}
	}

	return false;
}

bool CheckLowerRightDiagonal(int x, int y)
{
	for (int i = 1; i < N; i++)
	{
		if (((x + i) >= N) or ((y + i) >= N))
		{
			//Out of bounds
			return false;
		}

		//cout << "board: " << board[x + i][y + i] << endl;

		if (board[x + i][y + i] == 1)
		{
			//has collision at lower right diagonal
			return true;
		}
	}

	return false;
}

bool CheckLowerLeftDiagonal(int x, int y)
{
	for (int i = 1; i < N; i++)
	{
		if (((x + i) >= N) or ((y - i) < 0))
		{
			//Out of bounds
			return false;
		}

		//cout << "board: " << board[x + i][y - i] << endl;

		if (board[x + i][y - i] == 1)
		{
			//has collision at lower left diagonal
			return true;
		}
	}

	return false;
}

bool CheckUpperRightDiagonal(int x, int y)
{
	for (int i = 1; i < N; i++)
	{
		if ( ((x - i) < 0) or ((y + i) >= N) )
		{
			//Out of bounds
			return false;
		}

		//cout << "board: " << board[x - i][y + i] << endl;

		if (board[x - i][y + i] == 1)
		{
			//has collision at upper right diagonal
			return true;
		}
	}

	return false;
}

//returns true if there is at least one collision
//otherwise returns false
bool CheckCollisions(int x, int y)
{
	bool flag = false;
	#pragma omp parallel sections reduction(|:flag)
	{
		#pragma omp section
		{
			//cout << "check horizontal" << endl;
			flag = CheckHorizontal(x, y);
		}
		#pragma omp section
		{
			//cout << "check vertical" << endl;
			flag = flag | CheckVertical(x, y);
		}
		#pragma omp section
		{
			//cout << "check upper left" << endl;
			flag = flag | CheckUpperLeftDiagonal(x, y);
		}
		#pragma omp section
		{
			//cout << "check lower left" << endl;
			flag = flag | CheckLowerLeftDiagonal(x, y);
		}
		#pragma omp section
		{
			//cout << "check upper right" << endl;
			flag = flag | CheckUpperRightDiagonal(x, y);
		}
		#pragma omp section
		{
			//cout << "check lower right" << endl;
			flag = flag | CheckLowerRightDiagonal(x, y);
		}
	}
	//cout << "flag: " << flag << endl;
	return flag;
}


void Place(int x, int y)
{
	//place on board
	//cout << "x " << x << "---" << "y " << y << endl;
	board[x][y] = 1;
	checked[x][y] = 1;
	queenPositions[y][0] = x;
	queenPositions[y][1] = y;
}

int Full_Search7(void)
{
	int steps = 0;
	for(int col = 0; col < N; col++)
	{
		bool placed = false;
		for(int row2 = 0; row2 < 2*N; row2++)
		{
			int row = rand() % N;
			if ( checked[row][col] == 1 )
			{
				continue;
			}
			if ( CheckCollisions(row, col) == false )
			{
				Place(row, col);
				placed = true;
				break;
			}
			steps++;
			//cout << steps << endl;
		}
		if ( placed == false )
		{
			//could not place last queen - backtrack
			//remove previous queen if exists
			if ( (col - 1) >= 0 ) 
			{
				int j = col;
				board[queenPositions[j-1][0]][queenPositions[j-1][1]] = 0;
				checked[queenPositions[j-1][0]][queenPositions[j-1][1]] = 1;
				for(int k = 0; k < N; k++)
				{
					checked[k][j] = 0;
				}
				queenPositions[j-1][0] = -1;
				queenPositions[j-1][1] = -1;
				col -=2;
			}
		}
		//break;
	}
	return steps;
}

int main(void)
{	
	//depending on the seed, a different solution (out of 92 possible) is returned
	auto t = 42;//time(NULL);
	srand(t);

	int steps = Full_Search7();	
	
	cout << "Final board: " << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)	
			cout << board[i][j] << ' ';
		cout << endl;
	}

	cout << "Queen positions: " << endl;
	for (int i = 0; i < QN; i++)
	{
		cout << queenPositions[i][0] << "," << queenPositions[i][1] << "----";
	}
	cout << endl;

	cout << "seed: " << t << endl;
	cout << "Steps took: " << steps << endl;

	//display graphical representation
	//Is setup for N = QN = 8
	//PrintBoard();
	return 0;
}

