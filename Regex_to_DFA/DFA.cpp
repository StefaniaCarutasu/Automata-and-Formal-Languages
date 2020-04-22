#include "DFA.h"
DFA::DFA()
{
	this->q0 = 0;
}
int DFA::getInitialState() { return this->q0; }
set<int> DFA::getFinalState() { return this->F; }
set<int> DFA::getStates() { return this->Q; }
set<char> DFA::getSigma() { return this->Sigma; }
map<pair<int, char>, int> DFA::getDelta() { return this->delta; }

void DFA::REGEXtoDFA(string re)
{
	if (Q.size == 0)
		currentState = q0;
	this->Q.insert(q0);
	int i = 0;
	while(i < re.size())
	{
		if (isalpha(re[i]))
		{
			this->Sigma.insert(re[i]);
			if (re[i + 1] == '*')
			{
				this->delta[{currentState, re[i]}] = re[i];
				i += 2;
			}
			if (re[i + 1] == '+')
			{
				int newState = currentState + 1;
				this->delta[{currentState, re[i]}] = newState;
				i += 2;
			}
		}
		if (re[i] == '(')
		{
			int j = i + 1;
			while (re[j] != ')')
			{

			}

		}

	}
}
