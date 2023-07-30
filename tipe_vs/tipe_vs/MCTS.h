#pragma once




class Node
{
public:
	long long t = 0ll;
	int n = 0;

	int childs_nb = 0;

	Node* parent = nullptr;
	Node* childs[300];

	float val();

	int getMaxUcb1Child();

	void back_propagate(int val);

	void clear();


private:

	const float c = 2; // constante d'exploration
	
	float child_ucb1(int child_id);

};


