#include "DFA.h"

DFA::DFA() 
{
	this->q0 = 0;
}
DFA::DFA(set<int> Q, set<char> Sigma, map<pair<int, char>, int> delta, int q0, set<int> F)
{
	this->Q = Q;
	this->Sigma = Sigma;
	this->delta = delta;
	this->q0 = q0;
	this->F = F;
	
}
int DFA::getInitialState() { return this->q0; }
set<int> DFA::getFinalState() { return this->F; }
set<int> DFA::getStates() {	return this->Q; }
set<char> DFA::getSigma() { return this->Sigma; }
map<pair<int, char>, int> DFA::getDelta() { return this->delta; }
istream& operator >> (istream& f, DFA& M)
{
	int noOfStates;
	f >> noOfStates;
	for (int i = 0; i < noOfStates; ++i)
	{
		int q;
		f >> q;
		M.Q.insert(q);
	}

	int noOfLetters;
	f >> noOfLetters;
	for (int i = 0; i < noOfLetters; ++i)
	{
		char ch;
		f >> ch;
		M.Sigma.insert(ch);
	}

	int noOfTransitions;
	f >> noOfTransitions;
	for (int i = 0; i < noOfTransitions; ++i)
	{
		int s, d;
		char ch;
		f >> s >> ch >> d;
		M.delta[{s, ch}] = d;
	}

	f >> M.q0;

	int noOfFinalStates;
	f >> noOfFinalStates;
	for (int i = 0; i < noOfFinalStates; ++i)
	{
		int q;
		f >> q;
		M.F.insert(q);
	}

	return f;
}
void DFA::initializarePartitii()
{
	partitii = new int* [this->Q.size() - 1];
	for (int i = 0; i < this->Q.size(); i++)
		partitii[i] = new int[this->Q.size() - 1];
	for (int i = 0; i < this->Q.size(); i++)
		for (int j = 0; j < this->Q.size(); j++)
			partitii[i][j] = 0;

	for (auto& i : this->getFinalState())
	{
		for (auto& j : this->getStates())
			if (isFinalState(j) == false)
			{
				if (i < j)
					partitii[j][i] = 1;
				else partitii[i][j] = 1;
			}
	}
}
int** DFA::getPartitii() { return this->partitii; }

bool DFA::isFinalState(int q)
{
	return F.find(q) != F.end();
}

void DFA::Partitii()
{
	int ok = 0;
	for(auto& i: this->getStates())
		for (auto& j : this->getStates())
			for (auto& a : this->getSigma())
			{
				if (i != j && (partitii[i][j]==0 && partitii[j][i]==0))
				{
					pair<int, int > p = { getDelta()[{i,a}], getDelta()[{j,a}] };
					if (partitii[p.first][p.second] == 1 || partitii[p.second][p.first] == 1)
					{
						if (i < j)
							partitii[j][i] = 1;
						else partitii[i][j] = 1;
						ok = 1;
					} 			
				}
			}
	if (ok == 1)
	{
		ok = 0;
		Partitii();
	}
}

void DFA::minimizareDFA()
{
	Partitii();
	int l =this->getStates().size();
	set<set<int>> states;
	set<int> p;
	for(int i=1; i<l; i++)
	{
		p.insert(i);
		for (int j = 0; j < l; j++)
		{
			if (partitii[i][j] == 0 && i > j)
				p.insert(j);
		}
		if (p.size() > 0)
		{
			states.insert(p);
			p.clear();
		}
	}
	cout << "Starea initiala este: ";
	for (auto& i : states)
	{
		int ok = 0;
		for (auto& j : i)
		{
			if (j == this->q0)
			{
				ok = 1;
				break;
			}
		}
		if (ok)
		{
			cout << "( ";
			for (auto& j : i)
				cout << j << " ";
			cout << ")";
		}
	}
	cout << '\n';

	cout << "Alfabetul este: ";
	for (auto& a : this->getSigma())
		cout << a << " ";
	cout << '\n';

	cout << "Starile finale sunt: ";
	for(auto& i: states)
	{
		int ok = 0;
		for (auto& j : i)
		{
			if (this->isFinalState(j) == true)
				ok = 1;
			if (ok)
				break;
		}
		if (ok)
		{
			cout << "(";
			for (auto& j : i)
				cout << j << " ";
			cout << ") ";
		}
	}
	cout << '\n';

	cout << "Starea din care pleaca" << "     " << "litera" << "     " << "starea in care ajunge"<<'\n';
	for (auto& i : states)
	{
		for (auto& a : this->getSigma())
		{
			for (auto& j : i)
				cout << j << " ";
			cout << "                           ";
			cout << a << "                     ";
			cout << this->getDelta()[{*i.begin(), a}];
			cout << '\n';

		}
	}
}