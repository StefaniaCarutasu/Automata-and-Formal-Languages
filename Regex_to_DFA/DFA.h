#pragma once
#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<vector>
#include<string>
using namespace std;
class DFA
{
	set<int> Q, F;
	set<char> Sigma;
	int q0;
	map< pair< int, char>, int> delta;
	int currentState;
public:
	DFA();
	int getInitialState();
	set<int> getStates();
	set<int> getFinalState();
	set<char> getSigma();
	map<pair<int, char>, int> getDelta();
	bool isFinalState(int);
	void REGEXtoDFA(string);
};

