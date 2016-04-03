#include "Sudoku.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

		Sudoku::Sudoku()
			{
				for(int i=0;i<81;i++)
					{Board[i]=0;}
				FZI = 0;
				ansnum=0;
			}

		Sudoku::Sudoku(const int MakeBoard[])
			{
				for(int i=0;i<81;i++)
					{Board[i]=MakeBoard[i];}

			}

		bool Sudoku::CheckUnity(int InBoard[])
				{
					int counter[9]={0};

					for(int i=0;i<9;i++)
						{
							++counter[InBoard[i]-1];
							if(counter[InBoard[i]-1]>1)
								return false;
						}

						return true;
				}

		bool Sudoku::CheckInput(int FirstZero, int value)
				{

					if(RowMem[FirstZero/9][value-1]>=1)
						return false;
					if(ColMem[FirstZero%9][value-1]>=1)
						return false;
					if(BlockMem[((FirstZero%9)/3+((FirstZero/9)/3)*3)][value-1]>=1)
						return false;
					
					return true;
				}

		bool Sudoku::CheckReadIn(int FirstZero, int value)
				{

					if(RowMem[FirstZero/9][value-1]>1)
						return false;
					if(ColMem[FirstZero%9][value-1]>1)
						return false;
					if(BlockMem[((FirstZero%9)/3+((FirstZero/9)/3)*3)][value-1]>1)
						return false;
					
					return true;
				}

		void Sudoku::SetBoard(const int MakeBoard[])
				{
					for(int i=0;i<81;i++)
					{Board[i]=MakeBoard[i];}
				}


		void Sudoku::giveQuestion()
				{

					cout<<"5 0 0 1 0 0 0 0 0 0 9 6 0 0 0 8 2 0 0 0 0 0 0 7 0 0 9 0 0 0 0 0 3 0 0 6 0 7 4 0 0 0 9 1 0 2 0 0 5 0 0 0 0 0 7 0 0 6 0 0 0 0 0 0 8 3 0 0 0 5 7 0 0 0 0 0 0 4 0 0 1";

				}

		void Sudoku::readIn()
				{

						//~
						for(int i=0;i<9;i++)
                            for(int j = 0; j < 9; j++)
                            {
                                RowMem[i][j] = 0;
                                ColMem[i][j] = 0;
                                BlockMem[i][j] = 0;
                            }
                        //~

						for(int i=0;i<81;i++)
						{
							cin >> Board[i];

							//~
                            if( !Board[i] )
                                continue;
							++RowMem[(i/9)][Board[i]-1];
                            ++ColMem[(i%9)][Board[i]-1];
                            ++BlockMem[((i%9)/3+((i/9)/3)*3)][Board[i]-1];
                            //~

						}
				}


		void Sudoku::Display()
				{
					for(int i=0;i<81;i++)
						{
							cout<<Board[i]<<" ";
								if(i%9==8)
									cout<<endl;
						}
				}

		void Sudoku::DisplayAns()
				{
					for(int i=0;i<81;i++)
						{
							cout<<Ans[i]<<" ";
								if(i%9==8)
									cout<<endl;
						}
				}

		bool Sudoku::solve()
				{
					for(int i=0;i<81;i++)
					{
						    if(CheckReadIn(i,Board[i])==false)
                            {
                            	cout<<"0";
                            	return false;
                            }

					}
					Solve();
					if(ansnum==1)
						{
							cout<<ansnum<<endl;	
							DisplayAns();
						}
					else
					cout<<"2";

				}

		bool Sudoku::Solve()
				{
				    int line[9];
					int FirstZero;

					FirstZero = GetFirstZeroIndex();


					FZI = FirstZero;
					if(FirstZero == -1)
					{
						if(isCorrect())
						{
							for(int i=0;i<81;i++)
							{
								Ans[i]=Board[i];
							}
							return true;
						}

						else
							cout<<"0";
							return false;
					}

					else
					{
						for(int num = 1; num<=9 ; num ++)
						{
							SetNumber(FirstZero, num);

                                if(CheckInput(FirstZero,num))
                                {
                                    //~
                                    ++RowMem[(FirstZero/9)][num-1];
                                    ++ColMem[(FirstZero%9)][num-1];
                                    ++BlockMem[((FirstZero%9)/3+((FirstZero/9)/3)*3)][num-1];
                                    //~

                                    if(Solve())
                                        ansnum++;

                                    //~
                                    --RowMem[(FirstZero/9)][num-1];
                                    --ColMem[(FirstZero%9)][num-1];
                                    --BlockMem[((FirstZero%9)/3+((FirstZero/9)/3)*3)][num-1];
                                    //~
                                }
                            //}


						}
						//~
                        FZI = FirstZero;
                        SetNumber(FirstZero, 0);
                        //~
						return false;
					}

				}

		int Sudoku::GetFirstZeroIndex()
				{
						//int i;
						for(int i=FZI;i<81;++i)
							{
								if(Board[i] == 0)
								return i;
							}
						return -1;

				}





		void Sudoku::SetNumber(int index, int value)
				{
						Board[index] = value;
				}

		int Sudoku::GetNumber(int index)
				{
					return Board[index];
				}





		void Sudoku::transform()
			{
				readIn();
				Change();
				Display();
			}

		void Sudoku::Change()
		{
			srand(time(NULL));
			changeNum(rand()%9+1,rand()%9+1);
			changeRow(rand()%3, rand()%3);
			changeCol(rand()%3, rand()%3);
			rotate(rand()%101);
			flip(rand()%2);
		}

		void Sudoku::changeNum(int a, int b)
				{
					for(int i=0;i<81;i++)
					{
						if(Board[i] == a)
							Board[i] = b;

						if(Board[i] == b)
							Board[i] = a;
					}

				}
		void Sudoku::changeRow(int a, int b)
			{

				if(a!=b)
				{
						for(int i=0 ; i<27 ;i++)
						{
							ChangeTempA[i]=Board[i+a*27];
							ChangeTempB[i]=Board[i+b*27];
							Board[i+a*27]=ChangeTempB[i];
							Board[i+b*27]=ChangeTempA[i];
						}
				}
			}

	
			
		void Sudoku::changeCol(int a, int b)
			{
				if(a != b)
				{
					for(int i=0 ; i<9 ;i++)
					{
						
							ChangeTempA[i]=Board[i*9+a*3];
							ChangeTempB[i]=Board[i*9+b*3];

							ChangeTempA[i+9]=Board[i*9+a*3+1];
							ChangeTempB[i+9]=Board[i*9+b*3+1];

							ChangeTempA[i+18]=Board[i*9+a*3+2];
							ChangeTempB[i+18]=Board[i*9+b*3+2];
					}

					for(int i=0 ; i<9 ;i++)
					{
							Board[i*9+a*3]=ChangeTempB[i];
							Board[i*9+a*3+1]=ChangeTempB[i+9];
							Board[i*9+a*3+2]=ChangeTempB[i+18];

							Board[i*9+b*3]=ChangeTempA[i];
							Board[i*9+b*3+1]=ChangeTempA[i+9];
							Board[i*9+b*3+2]=ChangeTempA[i+18];
					}

				}

			}


		void Sudoku::rotate(int n)
    		{
		        int RotateBoard[BoardSize];
		        int ToPlace;

		            for(int i=0;i<81;i++)
		            	{
			                ToPlace=i;
			                for (int j=0;j<4-n%4;j++)
			                {
			                    ToPlace=(8-ToPlace/9)+(ToPlace%9)*9;

			                }

			                RotateBoard[i]=Board[ToPlace];
		           		 }
		            for (int i = 0; i < 81; ++i)
		            	{
		               		 Board[i]=RotateBoard[i];
		            	}
    		}


    	void Sudoku::flip(int n)
		    {
		        int FlipBoard[BoardSize];
		        int Row, Col, ToPlace;
		        for (int i = 0; i < 81; ++i)
		        {
		            Row=i%9;
		            Col=i/9;
		            if(n==1)
		            {
		                if (Row>=4)
		                {
		                    ToPlace=Col*9+4-(Row-4);
		                }
		                else
		                {
		                    ToPlace=Col*9+4+(4-Row);
		                }
		            }
		            else if (n==0)
		            {
		                if (Col>=4)
		                {
		                    ToPlace=Row+(4-(Col-4))*9;
		                }
		                else
		                {
		                    ToPlace=Row+(4+(4-Col))*9;
		                }
		            }
		            FlipBoard[i]=Board[ToPlace];
		        }
		        for (int i = 0; i < 81; ++i)
		        {
		            Board[i]=FlipBoard[i];
		        }
		    }



			bool Sudoku::isCorrect()
			{
				//Check row
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
							{
							    //~
								if(RowMem[i][j]>1)
                                    return false;
                                //~
							}
				}

				//Check col
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
							{
							    //~
								if(ColMem[i][j]>1)
									return false;
                                //~
							}
				}

				//Check block
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
							{
							    //~
								if(BlockMem[i][j]>1)
									return false;
                                //~
							}
				}


				return true;
			}