// BubbleAlgorithmCppTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;



class Bubble{
	public:
		int X; //leading edge
		int Y; //trailing edge
};

Bubble ArrayOfBubbles_S1[1000];
Bubble ArrayOfBubbles_S2[1000];

void Populate1()
{
	

	std::ifstream infile("S1_file.txt");

	int b1, b2;
	int index = 0;
	int currentLeadingE = 0;
	int currentTrailingE = 0;

	int S1_index = 0;

	//if (!(infile >> b1)) { /* error, could not read first line! Abort. */ }

	while (infile >> b2)
	{
		if ((int)b2 == 1) {
			if (currentLeadingE == 0) {
				currentLeadingE = index; //set current leading edge equal to current index value
			}
			else if (currentLeadingE != 0) {
				currentTrailingE = index; //set current trailing edge equal to current index value
			}
		}
		
		if ((int)b2 == 0 && currentTrailingE != 0) {	//break between bubbles after last bubble recorded
			ArrayOfBubbles_S1[S1_index].X = currentLeadingE;
			ArrayOfBubbles_S1[S1_index].Y = currentTrailingE;
			
			S1_index++;
			currentLeadingE = 0;
			currentTrailingE = 0;

		}
		index++;
		// successfully extracted one line, data is in x1, ..., x4, c.
	}
}

void Populate2()
{


	std::ifstream infile2("S2_file.txt");

	int b1, b2;
	int index = 0;
	int currentLeadingE = 0;
	int currentTrailingE = 0;

	int S1_index = 0;

	//if (!(infile >> b1)) { /* error, could not read first line! Abort. */ }

	while (infile2 >> b2)
	{
		if ((int)b2 == 1) {
			if (currentLeadingE == 0) {
				currentLeadingE = index; //set current leading edge equal to current index value
			}
			else if (currentLeadingE != 0) {
				currentTrailingE = index; //set current trailing edge equal to current index value
			}
		}

		if ((int)b2 == 0 && currentTrailingE != 0) {	//break between bubbles after last bubble recorded
			ArrayOfBubbles_S2[S1_index].X = currentLeadingE + 421;
			ArrayOfBubbles_S2[S1_index].Y = currentTrailingE + 421;

			S1_index++;
			currentLeadingE = 0;
			currentTrailingE = 0;

		}
		index++;
		// successfully extracted one line, data is in x1, ..., x4, c.
	}
}


int main()
{
	int C = 0;
	int Cmax = 0;
	int N = 0;
	//int D = 30;
	int D = 4;
	int X = 0;
	int Y = 0;
	int equal_158 = 0;

	//int limit1 = ArrayOfBubbles_S1.size();
	//int limit2 = sizeof(ArrayOfBubbles_S2);
	int limit1 = 1000;
	int limit2 = 1000;

	int tester1 = 0;
	//int tester2 = 0;
	


	Populate1();
	Populate2();

	ofstream outfile1;
	outfile1.open("S1Bubbles.txt");

	for (int a = 0; a < limit2 - 1; a++) {
		
		int temp1 = ArrayOfBubbles_S1[a].X;
		int temp2 = ArrayOfBubbles_S1[a].Y;

		outfile1 << temp1 <<" "<< temp2 << "\n";
		
	}

	outfile1.close();

	ofstream outfile2;
	outfile2.open("S2Bubbles.txt");

	for (int b = 0; b < limit1 - 1; b++) {
		

		int temp1 = ArrayOfBubbles_S2[b].X;
		int temp2 = ArrayOfBubbles_S2[b].Y;

		outfile2 << temp1 << " " << temp2 << "\n";

	}

	outfile2.close();

	
	for (int n = D * 25; n < D * 250; n++) {
		C = 0;
		for (int i = 0; i < limit2 -1; i++) {
			for (int j = 0; j < limit1 -1; j++) {
				X = std::max(ArrayOfBubbles_S1[j].X + n, ArrayOfBubbles_S2[i].X);
				Y = std::min(ArrayOfBubbles_S1[j].Y + n, ArrayOfBubbles_S2[i].Y);
				if (Y > X) { 
					C += Y - X; //adjust cross correlation variable
				}
			}

			if (C > Cmax) {
				Cmax = C;
				N = n;
				tester1 = i;
				//tester
			}
			else if (C == 158) { 
				equal_158++; 
			}
		
		
		}
	
	
	} 
	cout << "Cmax:" + Cmax;
	cout << "Delay samples:" + N;
	cout << "Tester1" + tester1;
	cout << "158:" + equal_158;

	

 	return 0;
}

