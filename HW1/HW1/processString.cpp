#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <gtest\gtest.h>

using namespace std;


// getAscendingStr Function requirement
//
// Take space seperated digit string (ex. "1 2 3 5 4") and 
//   modify input string to ascending order ("1 2 3 4 5").
//
// return 0 if success, (empty string)
//       -1 if exception occur (ex. string containing non-digit character)
int getAscendingStr(string& inputStr)
{
	stringstream ss(inputStr),sstoken;
	string token,convert_str;
	int size, convert_int;
	vector<string> ans;
	vector<int> int_ans;
	while (getline(ss, token, ' ')) {
		ans.push_back(token);				//這次將在取token時就把邊取邊判斷是不是合法的字串給處理好，也順便直接
		sstoken << token;					//將之前轉換整數後再放回矩陣裡面的for迴圈功能整合到這邊的while迴圈中。
		sstoken >> convert_int;
		if (!sstoken)return -1;

		int_ans.push_back(convert_int);
		sstoken.str("");
		sstoken.clear();
	}
	size = ans.size();
	ss.str("");
	ss.clear();
	sort(int_ans.begin(), int_ans.end());
	ans.clear();
	for (int i = 0; i<size; i++) {
		ss.str("");
		ss.clear();
		ss << int_ans[i];
		ss >> convert_str;
		ans.push_back(convert_str);
	}
	inputStr = "";
	for (int i = 0; i<size; i++) {
		if (i != size - 1) {
			inputStr += ans[i];
			inputStr += " ";
		}
		else {
			inputStr += ans[i];
		}
	}
	return 0;
	//finish
}

// solveQ Function requirement
// 
// solve quadratic function ax^2 + bx + c = 0
//
// return 1 if equation has two different real number root 
//          (return vector size should be 2 containing 2 solution.  
//          Greater value should put into smaller vector index)
//        0 there is only one possible solution to the quadratic equation 
//          (return vector size should be 1)
//       -1 complex roots 
//          (return vector size should be 0)
int solveQ(vector<double> &x, double a, double b, double c)
{
	double check, other;
	check = b*b - 4 * a*c;
	if (check<0)return -1;
	else if (check == 0) {
		check = ((-b) + sqrt(b*b - 4 * a*c)) / (2 * a);
		x.push_back(check);
		return 0;
	}
	else {
		check = ((-b) + sqrt(b*b - 4 * a*c)) / (2 * a);
		x.push_back(check);
		other = ((-b) - sqrt(b*b - 4 * a*c)) / (2 * a);
		x.push_back(other);
		return 1;
	}

	return 0;
	//finish
}

int main(int argc, char*argv[]) {
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(getAscendingStr, SimpleAscending)
{//Simple ascending test case

	string inputStr = "1 -3 2195 4 50";
	string tmpStr = inputStr;
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(tmpStr, "-3 1 4 50 2195");
	EXPECT_EQ(err, 0);
}

TEST(getAscendingStr, handleNonDigit)
{//getAscendingStr function should handle non digit case
	string tmpStr = "1 3 2 4 a 7f415";
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(err, -1);
}

TEST(solveQ, twoSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 2, -3);
	EXPECT_EQ(iSol, 1);
	EXPECT_EQ(sol.size(), 2);
	EXPECT_EQ(sol.at(0), 1);
	EXPECT_EQ(sol.at(1), -3);
}

TEST(solveQ, oneSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, -8, 16);
	EXPECT_EQ(iSol, 0);
	EXPECT_EQ(sol.size(), 1);
	EXPECT_EQ(sol.at(0), 4);
}

TEST(solveQ, noSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 1, 16);
	EXPECT_EQ(iSol, -1);
	EXPECT_EQ(sol.size(), 0);
}