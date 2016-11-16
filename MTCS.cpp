#include "MTCS.h"

int main(int argc, const char * argv[]) {
    Board gameBoard = Board();
    MTCS mtcs = MTCS(gameBoard);
    
    //printf("Who am I? 1 for black, 0 for white\n");
    //scanf("%d", &mtcs.WhoAmI);
    mtcs.WhoAmI = 1;
    srand(time(NULL));
    
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
	Node root = Node(nullptr, 0, rootPos);	//put at middle
	
	//寫入棋盤
	MyBoard.addChess(rootPos.x, rootPos.y);
	
	while(!MyBoard.getState())
    {
        Node current = Selection(&root);
    	int value = Simulation(&current);
        Backpropagation(&current, value);
        printf("==========\n");
        PrintNode(root);
    }
    
    //結束訊息
    if(MyBoard.getTurn() % 2 == 1)
    	printf("Black win\n");
    else
    	printf("White win\n");
}

//----------------------------------------------------------------------
// MTCS::Selection
// 選擇節點，如果走到leaf，就expand，若不是leaf，就從children 
// list裡找最好的(FindBestChild)
//----------------------------------------------------------------------
Node MTCS::Selection(Node *current){
	while(!MyBoard.getState())
	{		
		vector<Points> validMoves = MyBoard.getValidMove();

		//橫向擴張
		if(current->children.size() < 4)
			return Expansion(current);
		else
			*current = FindBestChild(*current);
	}
	
	return *current;
}

//----------------------------------------------------------------------
// MTCS::Expansion
// 從leaf長一個node，從目前可以走的位置random挑一個走，寫入棋盤
// *****應該不能用random，要給weighting
//----------------------------------------------------------------------
Node MTCS::Expansion(Node *current){
	
	vector<Points> validMoves = MyBoard.getValidMove();
	int ranIndex = rand() % validMoves.size();

	Node newNode = Node(current, current->depth+1, validMoves[ranIndex]);	
	current->children.push_back(newNode);
		
	//寫入棋盤
	MyBoard.addChess(validMoves[ranIndex].x, validMoves[ranIndex].y);
	//MyBoard.printBoard();
	return newNode;
}

//----------------------------------------------------------------------
// MTCS::Simulation
// 模擬所有可能
//----------------------------------------------------------------------
int MTCS::Simulation(Node *current){
	int cnt = 0;
	vector<Points> validMoves;
	
	//把真正的棋盤拷貝到模擬的棋盤
	MyBoard.copyTable();
	//模擬
	while(validMoves.size() > 0){
		validMoves = MyBoard.getValidMove();
		int ranIndex = rand() % validMoves.size();
		MyBoard.addChessToFakeTable(validMoves[ranIndex].x, validMoves[ranIndex].y);
	}
	
	//平手
	if(MyBoard.getState() == 0){	
		return 0;
	}
	//我贏
	else if(MyBoard.getTurn() % 2 == WhoAmI){ 
		return 1;
	}
	//我輸
	else{ 
		current->parent->value = -1000;
		return -1;
	}
}

//----------------------------------------------------------------------
// MTCS::Backpropagation
// 走到底之後，回傳這條路徑的值
//----------------------------------------------------------------------
void MTCS::Backpropagation(Node *current, int value){
	if(current != (Node*)NULL){
		current->visits++;
		current->value += value;
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
	Node bestChild = Node(&current, current.depth+1, pos);
	int bestValue = -99999;
	int i;
	
	for (i=0; i<current.children.size(); i++) {
		if(current.children[i].value > bestValue){
			bestChild = current.children[i];
			bestValue = current.children[i].value;
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
	for (int i=0; i<current.children.size(); i++){
		PrintNode(current.children[i]);
	}
}
