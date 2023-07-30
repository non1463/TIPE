#include "MCTS.h"
#include <math.h>

using namespace std;


float Node::val()
{
	
	return t * 1.f / n;
}


float Node::child_ucb1(int child_id)
{
	return childs[child_id]->val() + c * sqrt(log(n) * 1.f / childs[child_id]->n);
}


int Node::getMaxUcb1Child()
{
	float max_ucb1 = -9999.f;
	float ucb1;
	int best_child_id = 0;
	for (int i = 0; i < childs_nb; i++)
	{
		if (childs[i]->n == 0)
		{
			return i;
		}
		ucb1 = child_ucb1(i);
		if (ucb1 > max_ucb1)
		{
			max_ucb1 = ucb1;
			best_child_id = i;
		}
	}
	return best_child_id;
}



void Node::back_propagate(int value)
{
	n += 1;
	t += value;
	if (parent != nullptr)
	{
		parent->back_propagate(value);
	}
}

void Node::clear()
{
	for (int i = 0; i < childs_nb; i++)
	{
		childs[i]->clear();
		delete (childs[i]);
	}
	childs_nb = 0;
	n = 0;
	t = 0;
	parent = nullptr;
}