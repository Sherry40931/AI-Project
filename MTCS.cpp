#include "MTCS.h"

Board gameBoard = Board();
boardJudgement bj = boardJudgement(&gameBoard);
MTCS mtcs = MTCS(&gameBoard);

int main(int argc, const char * argv[]) {

	char r;
    int row, col;
    int player;
    
    srand(time(NULL));
    
    cout << "Black or White Chess? (Black: 1, White: -1)";
    cin  >> player;
    bj.setMe(-player);
    if(player == 1)
    	mtcs.WhoAmI = 1;
    else
    	mtcs.WhoAmI = 0;
    
    while(true){
        if(((gameBoard.getTurn() % 2) * 2 - 1) == player){
            if(player == 1) cout << "Black: ";
            else cout << "White: ";
            
            cin >> r;
            row = r - 'A';
            if(row == -1) break;
            cin >> col;
            if(col == -1) break;
            
            gameBoard.addChess(row, col);
        }
        else{
            if(player == 1) cout << "White: ";
            else cout << "Black: ";
            
            
            if(gameBoard.getTurn() == 1) {
            	gameBoard.addChess(6, 7);
            	cout << "G 7" << endl;
            }
            else{
                mtcs.Execute();
            }
            
        }
        
        if(gameBoard.getState() == 0) gameBoard.printBoard();
        else if(gameBoard.getState() == 1) break;
        else if(gameBoard.getState() == -1) cout << "Repeated Chess!" << endl;
        else cout << "Error Input!" << endl;
    //end of while
    }
    
    if(gameBoard.getState() == 1) {
        if(gameBoard.getTurn()%2) cout << "Game Over! Winner: Black" << endl;
        else cout << "Game Over! Winner: White" << endl;
    }
    else cout << "Game Over! Winner: N/A" << endl;
    gameBoard.printBoard();
            
    
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

    Node current = Selection(&root);
    int value = Simulation(&current);
    Backpropagation(&current, value);
    cout << (char)(current.point.x + 'A') << " " << current.point.y << endl;
    //printf("==========\n");
    //PrintNode(root);
}

//----------------------------------------------------------------------
// MTCS::Selection
// 選擇節點，如果走到leaf，就expand，若不是leaf，就從children 
// list裡找最好的(FindBestChild)
//----------------------------------------------------------------------
Node MTCS::Selection(Node *current){
	while(MyBoard->getState() == 0)
	{		
		vector<Points> validMoves = MyBoard->getValidMove();

		//橫向擴張
		if(current->children.size() < validMoves.size())
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
	
	bj.Judge();
	vector<Points> validMoves;
	Points bestPos;
	//printf("MAX: %d\n", bj.max);
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			if(bj.weight[i][j] == bj.max && MyBoard->table[i][j] == 0){
				bestPos.x = i;
				bestPos.y = j;
				validMoves.push_back(bestPos);
			}
		}
	}
	int ranIndex = rand() % validMoves.size();
	
	Node newNode = Node(current, current->depth+1, validMoves[ranIndex]);	
	current->children.push_back(newNode);
		
	//寫入棋盤
	MyBoard->addChess(validMoves[ranIndex].x, validMoves[ranIndex].y);
	//MyBoard->printBoard();
	return newNode;
}

//----------------------------------------------------------------------
// MTCS::Simulation
// 模擬所有可能
//----------------------------------------------------------------------
int MTCS::Simulation(Node *current){
	int cnt = 0;
	int MAX_CNT = 500000;
	vector<Points> validMoves = MyBoard->getValidMove();
	
	//把真正的棋盤拷貝到模擬的棋盤
	MyBoard->copyTable();
	//模擬
	while(validMoves.size() > 0 && cnt < MAX_CNT){
		validMoves = MyBoard->getValidMove();
		int ranIndex = rand() % validMoves.size();
		MyBoard->addChessToFakeTable(validMoves[ranIndex].x, validMoves[ranIndex].y);
		cnt++;
	}
	
	//平手
	if(MyBoard->getState() == 0){	
		return 0;
	}
	//我贏
	else if(MyBoard->getTurn() % 2 == WhoAmI){ 
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
	printf("PrintNode: %c %d %d %lu\n", current.point.x+'A', current.point.y, current.depth, current.children.size());
	for (int i=0; i<current.children.size(); i++){
		PrintNode(current.children[i]);
	}
}
