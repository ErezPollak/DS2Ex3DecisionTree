#include "tree.h"

//func to search qestion in the decition tree
Node* Tree::search(Node* p, string val, Node*& parent)
{	
	//if the qestion is first, no father, return the root of the tree.
	if (p->value == val)
	{
		//p must be the root
		parent = nullptr;
		return p;
	}
	//check if the node id desition or not, if node isnt leaf -> chek qestion
	if (!p->isLeaf) 
	{
		//chek the list with iterator
		for (auto i = p->answersList.begin(); i != p->answersList.end(); i++)
		{
			cout << (*i)->son->value << endl;

			if ((*i)->son->value == val) {
				parent = p;
				return (*i)->son;
			}

			return search((*i)->son, val, parent);

		}
	}
	//if no find match
	parent = nullptr;
	return nullptr;
}

//serch qestion in tree, and print path.
bool Tree::searchAndPrint(Node* p, string val)
{
	//if the root is the qestion's search ->print root
	if (p->value == val) {
		cout << p->value;
		return true;
	}
	else
	{
		//if we came to end of tree, decition, and not found -> false
		if (p->isLeaf)
		{
			return false;
		}
		else
		{
			//chek the list with iterator
			for (auto i = p->answersList.begin(); i != p->answersList.end(); i++)
			{
				// print path.
				if (searchAndPrint((*i)->son, val))
				{
					cout << " " <<  (*i)->ans << "   " << p->value  << endl;
					return true;
				}
			}
		}
	}
}
//print all qestion in tree, whith spase.
void Tree::print(Node* p, int level)
{
	for (int i = 0; i < level; i++){cout << " ";}
	cout << p->value << endl;
	if (!p->isLeaf)
	{
		for (auto i = p->answersList.begin(); i != p->answersList.end(); i++)
		{
			for (int i = 0; i < level; i++) { cout << " "; }
			cout << (*i)->ans << endl;
			print((*i)->son, level + 1);
		}
	}
}

//func that run qestion and bring the next matches qestion 
void Tree::process(Node* p)
{
	cout << p->value;
	if (!p->isLeaf){
		string ans;
		cin >> ans;
		for (auto i = p->answersList.begin(); i != p->answersList.end(); i++)
		{
			if (ans == (*i)->ans)
			{
				process((*i)->son);
			}
		}
	}

}
//delete sub tree with recorsia 
void Tree::deleteAllSubTree(Node* t)
{
	if (!t->isLeaf)
	{
		for (auto i = t->answersList.begin(); i != t->answersList.end(); i++){
			if ((*i)->son->isLeaf) {
				delete(*i)->son;
			}
			else {
				deleteAllSubTree((*i)->son);
			}
			delete* i;
		}
	}
	else
	{
		//if p is the root itself
		delete t;
	}

}

//create node to root
void Tree::addRoot(string newval)
{
	this->root = new Node(newval);
}

//add qestion to list of father qestion.
bool Tree::addSon(string fatherquestion, string newanswer, string newval)
{
	Node* p;
	//run trre to find the given qestion 
	Node *father = search(root, fatherquestion, p);
	//if no father -> false
	if (father == nullptr)
	{
		return false;
	}
	else {
		//if the father is a leaf,  we need to change its status to not leaf.
		if (father->isLeaf)
		{
			father->isLeaf = false;
		}
		//add answer to the qestion's list
		Node* n = new Node(newval);
		father->answersList.push_back(new Answer(newanswer, n));
		return true;
	}

}

void Tree::deleteSubTree(string val)
{
	Node* p;
	deleteAllSubTree(search(root , val , p));
}
