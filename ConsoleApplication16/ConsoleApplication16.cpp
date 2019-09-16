/**

   @author ZOHAIB ALI
   sudoku.cpp
   Purpose: SUDOKU CODE
   @version 1.0 13/09/19
*/

#include "pch.h"
#include <iostream>  
#include <vector>
#include <string>
#include <sstream> 
#include <time.h> 
#include <conio.h>
using namespace std;
/*
  Sudoku class
*/
class sudoku
{
	//private members
private:
	int board[9][9];
	int board_row = 9;
	int board_column = 9;
	const int check_number = 0;
	string board_input;
	string temp_input;
	int new_count = 0;

	//publuic members
public:
	sudoku()
	{
		//intializtion  
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				board[i][j] = 0;
			}
		}
	}
	/*
	   functions declaration
	*/
	void generate_board();
	bool generate_check(int check_num, int row, int col);
	void display_board();
	bool sudoku_solver();
	bool chack_unfilled_numbers(int &row, int &column);
	bool solve_the_row(int column, int compare_num);
	bool solve_the_column(int row, int compare_num);
	bool check_block_matrix(int new_row, int new_column, int compare_num);

};

/**
function of this code is to generate the game boardthrough user input
@param
@return
*/

void sudoku::generate_board()
{

	int col = 0;
	int temp_numb = 0;
	//row matrix 1 to 9
	for (int row = 0; row < 9; row++)
	{
		//complete row user input in a string
		cout << "Enter the " << row + 1 << " row" << endl;
		getline(cin, board_input);
		stringstream conv_string(board_input); // converting the string  into stream  
		if (board_input.size() == 17)//  condition to check the numbers in a string should be  9 including spaces
		{
			//row matrix 1 to 9
			for (int col = 0; col < 9; col++)
			{
				//separate the string on the basis of space
				while (getline(conv_string, temp_input, ' '))
				{
					//condition to check the space
					if (temp_input != " ")
					{
						//convert into integer
						temp_numb = stoi(temp_input);
						// check user must follow before input
						if (generate_check(temp_numb, row, col) == false)
						{
							cout << "Please follow th sudokou rules" << endl;
							row--;
						}
						//check the numbers in betwee 1 to 9
						else if (temp_numb >= 0 && temp_numb < 10)
						{
							board[row][col] = stoi(temp_input);
							col++;
						}
						//condition to display error inuser input
						else
						{
							cout << "Please enter the row again ,number  between 0 to 9 , length of row shold be 9 and it also include space" << endl;
							//row will be minus becus row has a error and will ask through user again
							row--;
						}

					}
					//condition to display error user input
					else
					{
						//row will be minus becus row has a error and will ask through user again
						cout << "Please enter the row again ,number  between 0 to 9 , length of row shold be 9 and it also include space" << endl;
						row--;
					}

				}
			}


			cout << endl;
		}
		else
		{
			//row will be minus becus row has a error and will ask through user again
			cout << "Please enter the row again ,number  between 0 to 9 , length of row shold be 9 and it also include space" << endl;
			row--;

		}
	}

}

/**
function of this code is to look for space or zero on a user matrix;
@param roow number and column number which is used to identify the zero on a index
@return boolean (true or false)
*/

bool sudoku::chack_unfilled_numbers(int &row, int &col)
{
	//look for space or zero in the matrix
	for (row = 0; row < 9; row++)
	{

		for (col = 0; col < 9; col++)
		{

			if (board[row][col] == 0)
			{

				return false;
			}

		}


	}
	return true;

}

/**
 Compare the parameters number on a row (look for number in a row)

 @param row number and compare number
 @return boolean (true or false)

*/

bool sudoku::solve_the_row(int row, int compare_num)
{
	int count = 0;
	for (int col = 0; col < 9; col++)
	{
		// check the number doesnot exit in the particular row
		if (board[row][col] != compare_num)
		{

			count++;
		}
		//if number match
		else if (board[row][col] == compare_num)
		{
			return true;
		}
		//check the by comparing from 1 to 9
		if (count == 9)
		{
			return false;
		}
	}

	return true;

}

/**
 Compare the parameters number on  a column (look for number in a column)

 @param column number and compare number
 @return boollean (true or false)

*/

bool sudoku::solve_the_column(int col, int compare_num)
{
	int count = 0;
	for (int row = 0; row < 9; row++)
	{
		// check the number doesnot exit in the particular column 
		if (board[row][col] != compare_num)
		{

			count++;
		}
		//if number match
		else if (board[row][col] == compare_num)
		{
			return true;
		}
		//check the by comparing from 1 to 9
		if (count == 9)
		{
			return false;
		}
	}
	return true;

}

/**
 Compare the parameters number on  a column 3*3 through modulus (look for number in a a matrix)

 @param row , column and compare number
 @return boollean (true or false)

*/

bool sudoku::check_block_matrix(int new_row, int new_column, int compare_num)
{
	//counter intializtion 
	int count = 0;
	// check the number doesnot exit in the matrix through row and column
	for (int i = new_row; i < new_row + 3; i++)
	{
		for (int j = new_column; j < new_column + 3; j++)
		{
			//if number doesnot match
			if (board[i][j] != compare_num)
			{

				count++;
			}
			//if number match
			else if (board[i][j] == compare_num)
			{
				return true;
			}
			//check the by comparing from 1 to 9
			if (count == 9)
			{
				return false;
			}

		}
	}
	return true;

}

/**
 solve the sudoku matrix by following the suodku rules

 @param
 @return boollean (true or false)

*/
bool sudoku::sudoku_solver()
{
	//intiliztion of from start of matrix
	int row = 0;
	int column = 0;

	//if matrix fullfill the rules then it will true
	if (chack_unfilled_numbers(row, column))
	{
		return true;
	}
	else
	{
		int check_num = 1;
		///comparing the values from 1 to 9
		while (check_num <= 9)
		{
			// apply the rules fo sudoku to check value doesnot exit 
			//modulus will give us the 3*3 matrix of particular matrix(row,col) 
			if (solve_the_row(row, check_num) == false && check_block_matrix(row - (row % 3), column - (column % 3), check_num) == false && solve_the_column(column, check_num) == false)
			{

				board[row][column] = check_num;
				// recursive functon .It will call functions untill come to the last value and then restart returning the values
				if (sudoku_solver())
				{

					return true;
				}

				if (board[row][column] != 0)//checking the if values other than 0 if we have to reset to zero
				{
					board[row][column] = 0;
				}
			}
			check_num++;
		}
	}
	return false;
}

/**
check the user input  matrix by through sudoku rules

 @param value,row,col
 @return boollean (true or false)

*/
bool sudoku::generate_check(int check_num, int row, int col)
{
	// checking the values other than zero and apply the sudoku rules
	if (check_num != 0)
	{
		// checking the values if match in matrix through  the the sudoku rules
		if (solve_the_row(row, check_num) == true && solve_the_column(col, check_num) == true && check_block_matrix(row - (row % 3), col - (col % 3), check_num) == true)
		{
			return false;
		}
	}

	return true;
}

/**
display the sudoku matrix

 @param
 @return

*/

void sudoku::display_board()
{
	// display the current matix values
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
}

/**
main unction to call the function

 @param value,row,col
 @return  int

*/
int main()
{
	cout << "Follow the sudoku rules and it sholude follow by using input" << endl;
	cout << "Particular row must not have no duplicate  present" << endl;
	cout << "* * * * * * * * *" << endl;
	cout << "Particular collumn must have have no duplicate  present" << endl;
	cout << "*\n*\n*\n*\n*\n*\n*\n*\n*" << endl;
	cout << "Particular matrix  must have have no duplicate  present and it is find by through modulus of row anad column" << endl;

	sudoku game;
	cout << "Initial sudoku matrix is " << endl;
	game.display_board();
	game.generate_board();
	cout << "User Generate sudoku matrix is " << endl;
	game.display_board();
	cout << endl;
	clock_t startTime = clock();
	if (game.sudoku_solver())
	{
		cout << "Correct sudoku matrix is " << endl;
		game.display_board();
	}
	cout << double(clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000) << " milliseconds" << endl;

}//main

