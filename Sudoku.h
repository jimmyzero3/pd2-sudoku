#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Sudoku
{



	public:

		Sudoku();

		Sudoku(const int MakeBoard[]);


		bool CheckUnity(int InBoard[]);

		bool CheckInput(int FirstZero, int value);

		bool CheckReadIn(int FirstZero, int value);

		void SetBoard(const int MakeBoard[]);

		void giveQuestion();

		void readIn();

		void Display();

		void DisplayAns();

		bool Solve();

		bool solve();

		int GetFirstZeroIndex();

		void SetNumber(int index, int value);

		int GetNumber(int index);

		void transform();

		void Change();

		void changeNum(int a, int b);

		void changeRow(int a, int b);
		
		void changeCol(int a, int b);

		void rotate(int n);

    	void flip(int n);

		bool isCorrect();

			static const int BoardSize = 81;
			int RowMem[9][9];
			int ColMem[9][9];
			int BlockMem[9][9];

	private:
			int ansnum;
			int Board[BoardSize];
			int FZI;
			int Ans[BoardSize];
			int ChangeTempA[27];
			int ChangeTempB[27];
			
};