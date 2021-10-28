#include "grid.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

//required methods
bool hasCorrectForm(string plan);
int determineSafeDistance(int r, int c, char dir, int maxSteps);
int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps);

//helper methods
string capitalize(string str);
bool isValidPortion(string str);
bool areValidInputs(int r, int c, char dir, int maxSteps);
bool isDirectionLetter(char a);

//tests
void testHasCorrectForm();
void testSafeDistance();
void testObey();

int main()
{
	setSize(3, 4);      // make a 3 by 4 grid
	setWall(1, 4);      // put a wall at (1,4)
	setWall(2, 2);      // put a wall at (2,2)
	if (!isWall(3, 2))  // if there's no wall at (3,2)  [there isn't]
		setWall(3, 2);  //    put a wall at (3,2)
	draw(3, 1, 3, 4);    // draw the grid, showing an S at (3,1) start
					   //    position, and an E at (3,4) end position
	testHasCorrectForm();
	testSafeDistance();
	testObey();
}

bool hasCorrectForm(string plan)
{
	if (plan.size() == 0) //if empty string, return true
		return true;
	if (plan.size() == 1) //if a single digit, return false
	{
		char planChar = plan[0];
		if (!isalnum(planChar))
			return false;
	}
	if (isdigit(plan[plan.size() - 1]))
		return false;
	plan = capitalize(plan);
	for (;;)
	{
		int index = 0; //determine portion from plan
		string portion;
		while (isdigit(plan.at(index)))
			index++;
		if (index == plan.size() - 1)
			portion = plan.substr(0);
		else
			portion = plan.substr(0, index + 1);

		if (!isValidPortion(portion)) //test portion
		{
			return false;
		}
		if (index == plan.size() - 1) //truncate portion from plan and continue until plan is 0
			break;
		plan = plan.substr(index + 1);
	}
	return true;
}

int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
	if (!areValidInputs(r, c, dir, maxSteps)) //check valid inputs first
		return -1;
	int max = 0;
	dir = toupper(dir);
	switch (dir) //switch case for determining proper direction
	{
	case 'N':
		while ((r != 1) && (!isWall(r - 1, c)))
		{
			r--;
			max++;
		}
		break;
	case 'E':
		while ((c != getCols()) && (!isWall(r, c + 1)))
		{
			c++;
			max++;
		}
		break;
	case 'W':
		while ((c != 1) && (!isWall(r, c - 1)))
		{
			c--;
			max++;
		}
		break;
	case 'S':
		while ((r != getRows()) && (!isWall(r + 1, c)))
		{
			r++;
			max++;
		}
		break;
	}
	return max;
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{
	dir = toupper(dir);
	if (!hasCorrectForm(plan) || !areValidInputs(sr, sc, dir, 0) || !areValidInputs(er, ec, dir, 0) || isWall(sr, sc) || isWall(er, ec))
		return 2;
	plan = capitalize(plan);
	int steps = 0;
	int cr = sr; //current row
	int cc = sc; //current col
	for (;;)
	{
		int index = 0;
		string portion;
		while (isdigit(plan.at(index)))
			index++;
		if (index == plan.size() - 1)
			portion = plan.substr(0);
		else
			portion = plan.substr(0, index + 1); //from 0 to index is the digits

		if (index > 0) //there are spaces to move forward
		{
			int numStepsToTake = stoi(portion.substr(0, index)); //parse int from string
			switch (dir)
			{
			case 'N': //r--
				for (int s = 0; s < numStepsToTake; s++)
				{
					if ((cr != 1) && (!isWall(cr - 1, cc)))
					{
						cr--;
						steps++;
					}
					else
					{
						nsteps = steps;
						return 3;
					}
				}
				break;
			case 'E': //c++
				for (int s = 0; s < numStepsToTake; s++)
				{
					if ((cc != getCols()) && (!isWall(cr, cc + 1)))
					{
						cc++;
						steps++;
					}
					else
					{
						nsteps = steps;
						return 3;
					}
				}
				break;
			case 'W': //c--
				for (int s = 0; s < numStepsToTake; s++)
				{
					if ((cc != 1) && (!isWall(cr, cc - 1)))
					{
						cc--;
						steps++;
					}
					else
					{
						nsteps = steps;
						return 3;
					}
				}
				break;
			case 'S': //r++
				for (int s = 0; s < numStepsToTake; s++)
				{
					if ((cr != getRows()) && (!isWall(cr + 1, cc)))
					{
						cr++;
						steps++;
					}
					else
					{
						nsteps = steps;
						return 3;
					}
				}
				break;
			}
			portion = portion.substr(index);
		}							//at this point, the car has moved in the direction dir, and portion is a direction letter
		if (portion.size() == 1)	//at this point, there is only a direction letter, change directions
		{
			char directionFromPlan = portion[0];
			switch (directionFromPlan)
			{
			case 'L':
				if (dir == 'N') {
					dir = 'W'; break;
				}
				if (dir == 'E') {
					dir = 'N'; break;
				}
				if (dir == 'S') {
					dir = 'E'; break;
				}
				if (dir == 'W') {
					dir = 'S'; break;
				}
				break;
			case 'R':
				if (dir == 'N') {
					dir = 'E'; break;
				}
				if (dir == 'E') {
					dir = 'S'; break;
				}
				if (dir == 'S') {
					dir = 'W'; break;
				}
				if (dir == 'W') {
					dir = 'N'; break;
				}
				break;
			}
		}					
		//at this point the car has obeyed the portion of the plan

		if (index == plan.size() - 1) //truncate portion from plan and continue until plan is 0
			break;
		plan = plan.substr(index + 1);
	}
	//if it made it out of this loop, then it has successfully completed the plan
	nsteps = steps;
	if ((cc != ec) || (cr != er))
		return 1;
	return 0;

}

/*
* Method capitalize(string str) takes in a string and returns the same string with all characters capitalized
*/
string capitalize(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]) && islower(str[i]))
		{
			str[i] = toupper(str[i]);
		}
	}
	return str;
}

/*
* Method isValidPortion(string str) takes in a string and determines if the string obeys the definition of a plan portion (0,1,2 digits followed by 'L' or 'R')
*/
bool isValidPortion(string str)
{
	int numDigits = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]))
		{
			numDigits++;
		}
	}
	if (numDigits > 2 || numDigits == str.size())
		return false;
	
	if (str[numDigits] != 'L' && str[numDigits] != 'R')
		return false;

	return true;
}

bool isDirectionLetter(char a)
{
	a = toupper(a);
	return (a == 'N' || a == 'E' || a == 'S' || a == 'W');
}

/*
* Method areValidInputs(int r, int c, char dir, int maxSteps) takes in a row int r, a col int c, a character direction, and an int maxSteps and determines if the:
* int r is within the total amount of rows
* int c is within the total amount of cols
* char dir is one of the 4 cardinal directions (N, S, E, W)
* int maxSteps is negative
*/
bool areValidInputs(int r, int c, char dir, int maxSteps)
{
	if (r < 1 || r > getRows())
		return false;
	if (c < 1 || c > getCols()) 
		return false;
	if (isWall(r,c))
		return false;
	dir = toupper(dir);
	if (!isDirectionLetter(dir))
		return false;
	if (maxSteps < 0)
		return false;
	return true;
}

void testHasCorrectForm()
{
	string a = "LL2R02LR0r2L1R";
	string b = "LL2R2r2L1R";
	string c = "";
	string d = "R0FL";
	string e = "LLR23R1432R";
	string f = "LL2R02LR RL1";
	string g = "614731096437864198273";
	cout << hasCorrectForm(a); //yes
	cout << hasCorrectForm(b); //yes
	cout << hasCorrectForm(c); //yes
	cout << hasCorrectForm(d); //no
	cout << hasCorrectForm(e); //no
	cout << hasCorrectForm(f); //no
	cout << hasCorrectForm(g) << endl; //no
	cout << "Test correctForm: 1110000" << endl;
}
void testSafeDistance()
{
	if (determineSafeDistance(3, 1, 'N', 2) == 2)
		cout << "Passed determineSafeDistance test 1" << endl;
	else
		cout << "Failed determineSafeDistance test 1";

	if (determineSafeDistance(3, 3, 'E', 2) == 1)
		cout << "Passed determineSafeDistance test 2" << endl;
	else
		cout << "Failed determineSafeDistance test 2";

	if (determineSafeDistance(-2, 2, 'E', 2) == -1)
		cout << "Passed determineSafeDistance test 3" << endl;
	else
		cout << "Failed determineSafeDistance test 3";

	if (determineSafeDistance(2, 1, 'E', 4) == 0)
		cout << "Passed determineSafeDistance test 4" << endl;
	else
		cout << "Failed determineSafeDistance test 4";

	if (determineSafeDistance(1, 1, 'E', 2) == 2)
		cout << "Passed determineSafeDistance test 5" << endl;
	else
		cout << "Failed determineSafeDistance test 5";

}
void testObey()
{
	int len;
	len = -999;  
	if (obeyPlan(3, 1, 3, 4, 'S', "LL2R2r2L1R", len) == 0 && len == 7)
		cout << "Passed obeyPlan test 1" << endl;
	len = -999;  
	if (obeyPlan(3, 1, 3, 4, 'N', "1Lx", len) == 2 && len == -999)
		cout << "Passed obeyPlan test 2" << endl;
	len = -999; 
	if (obeyPlan(2, 4, 1, 1, 'w', "3R1L", len) == 3 && len == 1)
		cout << "Passed obeyPlan test 3" << endl;
	len = -999;
	if (obeyPlan(1, 1, 2, 4, 's', "L2R2l1r", len) == 1 && len == 5)
		cout << "Passed obeyPlan test 4" << endl;
	len = -999;
	if (obeyPlan(1, 5, 3, 4, 'n', "2r2l", len) == 2 && len == -999)
		cout << "Passed obeyPlan test 5" << endl;
}
