#include "MTCS.h"

int main(int argc, const char * argv[]) {
    
    Board gameBoard = Board();
    MTCS mtcs = MTCS(gameBoard);
    
    /*
    gameBoard.addChess(1, 5);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(2, 4);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(3, 3);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(4, 2);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(5, 1);
    */
    
    mtcs.Execute();
    
    return 0;
}


//----------------------------------------------------------------------
// MTCS::Execute
// MTCS 執行流程
//----------------------------------------------------------------------
void MTCS::Execute(){
	Points rootPos;
	rootPos.x = 7;
	rootPos.y = 7;
	Node root = Node(NULL, 0, rootPos);	//put at middle
	Node one = Node(&root, 1, rootPos);
	root.children.push_back(one);
	
	//寫入棋盤
	MyBoard.addChess(rootPos.x, rootPos.y);
	//MyBoard.printBoard();
	
	for (int iteration = 0; iteration < 10; iteration++)
    {
    	printf("Execute\n");
        Node current = Selection(root);
        Backpropagation(current, 1);
        PrintNode(root);
    }
}

//----------------------------------------------------------------------
// MTCS::Selection
// 選擇節點，如果走到leaf，就expand，若不是leaf，就從children 
// list裡找最好的(FindBestChild)
//----------------------------------------------------------------------
Node MTCS::Selection(Node current){
	while(!MyBoard.getState()){
			
		list <Points> validMoves = MyBoard.getValidMove();
		printf("Selection %lu %lu\n", validMoves.size(), current.children.size());

		if(validMoves.size() > current.children.size())	//is leaf
			return Expansion(current);
		else
			current = FindBestChild(current);
	}
	
	return current;
}

//----------------------------------------------------------------------
// MTCS::Expansion
// 長一個node，從目前可以走的位置挑一個走，寫入棋盤
//----------------------------------------------------------------------
Node MTCS::Expansion(Node current){
	printf("Expansion\n");
	
	list <Points> validMoves = MyBoard.getValidMove();
	for(list<Points>::iterator i = validMoves.begin(); i != validMoves.end(); i++){
		Node newNode = Node(&current, current.depth, *i);	
		current.children.push_back(newNode);
		//printf("DO I ADD? %d %d\n", current.point.x, current.point.y);
		
		//寫入棋盤
		MyBoard.addChess(i->x, i->y);
		//MyBoard.printBoard();
		return newNode;
	}
	return current;
}

//----------------------------------------------------------------------
// MTCS::Simulation
// ？？？？？？？
//----------------------------------------------------------------------
Node MTCS::Simulation(Node current){
	return current;
}

//----------------------------------------------------------------------
// MTCS::Backpropagation
// 走到底之後，回傳這條路徑的值
//----------------------------------------------------------------------
void MTCS::Backpropagation(Node current, int value){
	if(&current != (Node*)NULL){
		//printf("TEST\n");
		current.visits++;
		current.value += value;
		Backpropagation(*current.parent, value);
	}
}

//----------------------------------------------------------------------
// MTCS::FindBestChild
// 用在Selection，找children裡面最好的node
//----------------------------------------------------------------------
Node MTCS::FindBestChild(Node current){
	printf("FindBestChild\n");
	
	Points pos;
	pos.x = -1;
	pos.y = -1;
	Node bestChild = Node(&current, current.depth, pos);
	int bestValue = -99999;
	int i;
	
	for (list<Node>::iterator i = current.children.begin(); i != current.children.end(); i++) {
		if(i->value > bestValue){
			bestChild = *i;
			bestValue = i->value;
		}
	}
	
	return bestChild;
}


//----------------------------------------------------------------------
// MTCS::PrintNode
// 印出目前的tree
//----------------------------------------------------------------------
void MTCS::PrintNode(Node current){
	printf("PrintNode: %d %d %d %lu\n", current.point.x, current.point.y, current.depth, current.children.size());
	for (list<Node>::iterator i = current.children.begin(); i != current.children.end(); i++){
		PrintNode(*i);
	}
}
