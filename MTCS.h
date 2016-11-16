#include <iostream>
#include <list> 
 
class Node;
class MTCS {
	public:
		MTCS(Board board){
			this->board = board;
		}
    	Node Selection(Node current);
	    Node Expansion();
    	Node Simulation();
    	Node Backpropagation();
    	
    	int WhoAmI;
    	Board borad;
};

class Node{
	public:
		Node parent = null;
		list <Node> children;
		int value = 0;
		int visits = 0;
		int depth = 0;
		Node(int value, Node parent, int depth)
		{
			this->value = value;
			this->parent = parent;
			this->depth = depth;
		}
}