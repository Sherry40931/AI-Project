#ifndef MTCS_H_
#define MTCS_H_

#include <list> 
#include <vector>
#include "board.h"
#include "boardJudgement.hpp"
 
class Node;
class MTCS {
	public:
		Board *MyBoard;
		MTCS(Board *board){
			this->MyBoard = board;
		};
    	Node Selection(Node *current);
	    Node Expansion(Node *current);
    	int Simulation(Node *current);
    	void Backpropagation(Node *current, int value);
    	Node FindBestChild(Node current);
    	
    	void PrintNode(Node current);
    	
    	void Execute();
    	
    	int WhoAmI;
};

class Node{
	public:
		Node *parent;
		vector<Node> children;
		Points point;
		int value = 0;
		int visits = 0;
		int depth = 0;

		Node(Node *parent, int depth, Points point)
		{
			this->parent = parent;
			this->depth = depth;
			this->point.x = point.x;
			this->point.y = point.y;
		};
		
};

#endif