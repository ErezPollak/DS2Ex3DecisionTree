#include "tree.h"


Node* Tree::search(Node* p, string val, Node*& parent)
{	
	if (p->value == val) {
		//p must be the root
		parent = nullptr;
		return p;
	}
	if (!p->isLeaf) {
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
	parent = nullptr;
	return nullptr;
}

bool Tree::searchAndPrint(Node* p, string val)
{
	if (p->value == val) {
		cout << p->value;
		return true;
	}
	else {
		if (p->isLeaf) {
			return false;
		}
		else {
			for (auto i = p->answersList.begin(); i != p->answersList.end(); i++)
			{
				if (searchAndPrint((*i)->son, val)) {
					cout << " " <<  (*i)->ans << "   " << p->value  << endl;
					return true;
				}
			}
		}
	}
}

void Tree::print(Node* p, int level)
{
	for (int i = 0; i < level; i++){cout << " ";}
	cout << p->value << endl;
	if (!p->isLeaf) {
		for (auto i = p->answersList.begin(); i != p->answersList.end(); i++)
		{
			for (int i = 0; i < level; i++) { cout << " "; }
			cout << (*i)->ans << endl;
			print((*i)->son, level + 1);
		}
	}
}

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
		//cout << "not a valid answer" << endl;
		//process(p);
	}

}

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

void Tree::addRoot(string newval)
{
	this->root = new Node(newval);
}

bool Tree::addSon(string fatherquestion, string newanswer, string newval)
{
	Node* p;
	Node *father = search(root, fatherquestion, p);
	//cout << father->value << endl;
	if (father == nullptr) {
		return false;
	}
	else {
		//if the father is a leaf,  we need to change its status to not leaf.
		if (father->isLeaf) {
			father->isLeaf = false;
		}
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
