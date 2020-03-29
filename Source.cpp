#include <iostream>
#include <set>
#include <string>
#include <queue>
using namespace std;
struct Node
{
	int state;
	int action;
	int cost;
	Node* parent;
	
};

struct States
{
	string stateName;
	int stateNum;
};

struct Actions
{
	string actName;
	int actNum;
};

int main()
{
	cout << "give the input file:" << endl;
	set<int> exploredSet;
	//int exploredSet[50];
	queue<Node> frontier;
	string strTemp;
	int m, n, t;
	cin >> m >> n >> t;
	
	States* sts = new States[m];

	Node initialNode;
	Node* nods = new Node[m];
	for (int i = 0; i < m; i++)
	{
		cin >> strTemp;
		sts[i].stateName = strTemp;
		sts[i].stateNum = i;
		nods[i].state = i;
	//	nods[i].cost = 0;
	}

	Actions* acts = new Actions[n];
	for (int i = 0; i < n;i++)
	{
		getline(cin,acts[i].actName);
		acts[i].actNum = i;
	}

	int** transMat = new int* [m];
	for (int i = 0; i < m; i++)
	{
		transMat[i] = new int[n];
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> transMat[i][j];
		}
	}

	string* initialStates = new string[t];
	string* finalStates = new string[t];
	int initialStateNum=-1;
	int finalStateNum=-1;

	for (int i = 0; i < m; i++)
	{
		if (sts[i].stateName == initialStates[0])
		{
			initialStateNum = i;
			break;
		}
	}
	for (int i = 0; i < m; i++)
	{
		if (sts[i].stateName == finalStates[0])
		{
			finalStateNum = i;
			break;
		}
	}



	for (int i = 0; i < t; i++)
	{
		cin >> initialStates[i];
		cin >> finalStates[i];

		string first, second;
		char delimeter('\t');
		getline(cin, initialStates[i], delimeter);
		getline(cin, finalStates[i]);
	}
	/*for (int i = 0; i < t; i++)
	{
		cout<< initialstates[i];
		cout<< finalstates[i];
		cout << endl;
	}
	*/
	int x = 0;
	initialNode.cost = 0;
	initialNode.parent = nullptr;
	initialNode.action = -1;
	for (int i = 0; i < m; i++)
	{
		if (sts[i].stateName == initialStates[0])
		{
			initialNode.state = i;
			initialNode.cost = 0;
			break;
		}
	}
	frontier.push(initialNode);




	int tempInt;
	while (!frontier.empty())
	{
		if (frontier.empty())
		{
			cout << "no goal path exists"<<endl;
			break;
		}
		else
		{
			if(frontier.front().state==finalStateNum);
			{
				exploredSet.insert(frontier.front().state);
				tempInt = frontier.front().state;
				frontier.pop();
			}
			set<int>::iterator it = exploredSet.begin();
			for (; it != exploredSet.end(); it++)
			{
				if (tempInt != *it)
				{
					for (int i = 0; i < m; i++)
					{
						if (nods[i].state == tempInt)
						{
							for (int j = 0; j < n; j++)
							{
								if (transMat[initialStateNum][j] == tempInt)
								{
									nods[i].action = j;
									nods[i].cost = nods[initialStateNum].cost + nods[i].cost;
									nods[i].parent = &nods[tempInt];
									frontier.push(nods[i]);
								}
							}
						}
					}
				}
			}
			
			
			
		}
	}
	return 0;
}
