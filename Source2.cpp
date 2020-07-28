#include<iostream>
#include<string>
#include<set>
#include<queue>
#include<typeinfo>
#include<stack>
using namespace std;
string states[8] = { "(AgentInRoom1, Room1Dusty, Roam2Dusty)",
	"(AgentInRoom1, Room1Dusty, Roam2Clean)",
	"(AgentInRoom1, Room1Clean, Roam2Dusty)",
	"(AgentInRoom1, Room1Clean, Roam2Clean)",
	"(AgentInRoom2, Room1Dusty, Roam2Dusty)",
	"(AgentInRoom2, Room1Dusty, Roam2Clean)",
	"(AgentInRoom2, Room1Clean, Roam2Dusty)",
	"(AgentInRoom2, Room1Clean, Roam2Clean)" };
string actions[3] = { "Clean","MoveToRoom1","MoveToRoom2" };
int transitionModel[8][3];

class Node {
public:
	Node* parent;
	int state;
	int action;
	int cost;
	Node()
	{
	}
	void display()
	{
		cout << "Parent : " << parent << endl;
		cout << "State : " << state << endl;
		cout << "Action : " << action << endl;
		cout << "Cost : " << cost << endl;
		cout << "####################################\n";
	}
	bool goalTest(int a)
	{
		if (this->state == a)
		{
			return true;
		}
		return false;
	}

};
queue<Node>frontier;
set<int>exploredSet;
bool exp(int a)
{
	set<int>::iterator it;
	for (auto it = exploredSet.begin(); it != exploredSet.end(); it++)
	{
		if (*it == a)
		{
			return false;
		}
	}
	return true;
}
bool front(int a)
{
	return true;
}
Node search(string startState, string finalState)
{
	bool array[8];
	for (int i = 0; i < 8; i++)
	{
		array[i] = false;
	}
	int goal = 0;
	Node n;
	for (int i = 0; i < 8; i++)
	{
		if (startState == states[i])
		{
			n.state = i;
			n.action = -1;
			n.cost = 0;
			n.parent = NULL;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (finalState == states[i])
		{
			goal = i;
		}
	}
	if (n.goalTest(goal))
	{
		return n;
	}
	else
	{
		frontier.push(n);
		array[n.state] = true;
	}
	Node child;
	do {
		exploredSet.insert(frontier.front().action);
		frontier.pop();
		for (int i = 0; i < 3; i++)
		{

			child.state = transitionModel[n.state][i];
			child.cost = n.cost + 1;
			child.action = i;
			child.parent = &n;
			if (child.goalTest(goal))
			{
				return child;
			}
			else
			{
				if (!array[child.state])
				{
					frontier.push(child);
					array[child.state] = true;
				}
			}
		}
		n = frontier.front();
	} while (!frontier.empty());

}
void display(string startState, string finalState)
{
	Node result;
	result = search(startState, finalState);
	if (result.action == -1)
	{
		cout << "Robot is already in its Position\n";
	}
	else
	{
		set<int>::iterator it;
		for (auto it = exploredSet.begin(); it != exploredSet.end(); it++)
		{
			if ((*it == 0))
				cout << "Clean ->";
			if (*it == 1)
				cout << "Move to Room 1 ->";
			if (*it == 0)
				cout << "Move to Room 2 ->";
		}
		if (result.action == 0)
			cout << "Clean";
		if (result.action == 1)
			cout << "Move to Room 1";
		if (result.action == 2)
			cout << "Move to Room 2";
	}
	cout << endl;
}
int main()
{
	transitionModel[0][0] = 2;
	transitionModel[0][1] = 0;
	transitionModel[0][2] = 4;
	transitionModel[1][0] = 3;
	transitionModel[1][1] = 1;
	transitionModel[1][2] = 5;
	transitionModel[2][0] = 2;
	transitionModel[2][1] = 2;
	transitionModel[2][2] = 6;
	transitionModel[3][0] = 3;
	transitionModel[3][1] = 3;
	transitionModel[3][2] = 7;
	transitionModel[4][0] = 5;
	transitionModel[4][1] = 0;
	transitionModel[4][2] = 4;
	transitionModel[5][0] = 5;
	transitionModel[5][1] = 1;
	transitionModel[5][2] = 5;
	transitionModel[6][0] = 7;
	transitionModel[6][1] = 2;
	transitionModel[6][2] = 6;
	transitionModel[7][0] = 7;
	transitionModel[7][1] = 3;
	transitionModel[7][2] = 7;

	cout << "States\n";
	for (int i = 0; i < 8; i++)
	{
		cout << states[i] << endl;
	}
	string startState;
	string finalState;
	cout << "Enter start state : ";
	getline(cin, startState);
	cout << "Enter final state : ";
	getline(cin, finalState);
	display(startState, finalState);
	system("pause");
	return 0;
}