#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

const int SIZE = 20;
char board1[SIZE][SIZE];
char board2[SIZE][SIZE];
const char DEAD = ' ';
const char LIVE = 'o';

void initboard()
{
	srand(time(0));
	int rnd = 0;

	for (int r = 0; r < SIZE; ++r)
	{
		for (int c = 0; c < SIZE; ++c)
		{
			rnd = rand();
			if (rnd % 2 == 0)
				board1[r][c] = DEAD;
			else
				board1[r][c] = LIVE;
		}
	}
}

void printboard(bool b1)
{
	system("cls");
	for (int r = 0; r < SIZE; ++r)
	{
		for (int c = 0; c < SIZE; ++c)
		{
			if(b1)
				cout << board1[r][c] << " ";
			else
				cout << board2[r][c] << " ";
		}
		cout << endl;
	}
}

bool validcell(int r, int c)
{
	if (r >= 0 && r < SIZE && c >= 0 && c < SIZE)
		return true;
	return false;
}

int numberofliveneighbors(int row, int col, char board[SIZE][SIZE])
{
	int liveneighbors = 0;

	int r = row - 1;
	int c = col - 1;

	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row - 1; c = col;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row -1; c = col+1;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row; c = col-1;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row; c = col+1;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row + 1; c = col-1;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row +1; c = col;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;

	r = row +1; c = col+1;
	if (validcell(r, c) && board[r][c] == LIVE)
		++liveneighbors;
	
	return liveneighbors;
}

void rungenerations(bool b1)
{
	for (int r = 0; r < SIZE; ++r)
	{
		for (int c = 0; c < SIZE; ++c)
		{
			if (b1)
			{
				if (numberofliveneighbors(r, c, board1) <= 1)
					board2[r][c] = DEAD;
				else if (numberofliveneighbors(r, c, board1) == 2)
					board2[r][c] = board1[r][c];
				else if (numberofliveneighbors(r, c, board1) == 3)
				{
					board2[r][c] = LIVE;
				}
				else if (numberofliveneighbors(r, c, board1) == 4)
				{
					board2[r][c] = DEAD;
				}
			}
			else
			{
				if (numberofliveneighbors(r, c, board2) <= 1)
					board1[r][c] = DEAD;
				else if (numberofliveneighbors(r, c, board2) == 2)
					board1[r][c] = board2[r][c];
				else if (numberofliveneighbors(r, c, board2) == 3)
				{
					board1[r][c] = LIVE;
				}
				else if (numberofliveneighbors(r, c, board2) == 4)
				{
					board1[r][c] = DEAD;
				}
			}
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	int numgens = 100;
	if (argc > 1)
	{
		numgens = atoi(argv[1]);
	}
	if (numgens == 0)
		numgens = 100;
	initboard();
	printboard(true);

	bool b1 = true;
	for (int i = 0; i < numgens; ++i)
	{
		rungenerations(b1);
		printboard(!b1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		b1 = !b1;
	}

}