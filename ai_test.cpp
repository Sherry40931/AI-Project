#include<stdio.h>
#include<iostream>
using namespace std;
int size = 4;
int board[4][4]=
	{ {1, 1, 0, 0},
	  {0, 0, 1, 0},
	  {0, 1, 0, 0},
	  {0, 0, 0, 0}
	};

int* CheckX(int, int, int);
int* CheckY(int, int, int);
int* CheckXY(int, int, int);
int* CheckYX(int, int, int);

int main(){
	int i, j, n;
	int *check1, *check2, *check3, check4;
	int *check[4];
	int me=1;
	
	//CheckX(0,2,1);
	
	for(i=0; i<size;i++){
		for(j=0; j<size; j++){
			if(board[i][j] == 0){
				check[0] = CheckX(i, j, me);//�ˬd�o�Ӧ�m���X��(?) 	
				check[1] = CheckY(i, j, me);
				check[2] = CheckXY(i, j, me);
				check[3] = CheckYX(i, j, me);
				printf("%d ", *check[1]);			
			}
			else{
				printf("- ");
			}			
		}
		puts("");
	}
	return 0;
}
int* CheckX(int m, int n, int me){ //me:�ڬO�´�(1)�Υմ�(-1) 
	static int result[2] = {}; //�s�l�� & ��������  
	int flag = 0;//������: 0���䬡 1�@�䬡�@�䦺 2���䳣���� 
	int num = 1; //�s�l�� 
	int i, j;
	//�������V�s�l
	i = n+1;
	while(i<size){
		if(board[m][i] == me){
			num++;
			i++; 
		} 
		else{
			break;
		}
	}
	if(board[m][i] == -me || i == size){
		flag++; 
	}
	i = n-1;
	while(i>=0){
		if(board[m][i] == me){
			num++;
			i--; 
		} 
		else{
			break;
		}	
	}
	if(board[m][i] == -me || i == -1){
		flag++;
	}
	result[0] = num;
	result[1] = flag;
	
	return result;
}
int* CheckY(int m, int n, int me){ /*������V*/ 
	static int result[2] = {}; //�s�l�� & ��������  
	int flag = 0;//������: 0���䬡 1�@�䬡�@�䦺 2���䳣���� 
	int num = 1; //�s�l�� 
	int i, j;

	i = m+1;
	while(i<size){
		if(board[i][n] == me){
			num++;
			i++; 
		} 
		else{
			break;
		}
	}
	if(board[i][n] != me || i == size){
		flag++; 
	}
	i = m-1;
	while(i>=0){
		if(board[i][n] == me){
			num++;
			i--; 
		} 
		else{
			break;
		}	
	}
	if(board[i][n] != me || i == -1){
		flag++; 
	}
	result[0] = num;
	result[1] = flag;
	
	return result;
}
int* CheckXY(int m, int n, int me){ /*���W�k�U*/
	static int result[2] = {}; //�s�l�� & ��������  
	int flag = 0;//������: 0���䬡 1�@�䬡�@�䦺 2���䳣���� 
	int num = 1; //�s�l�� 
	int i, j;

	i = m+1;
	j = n+1;
	while(i<size && j<size){
		if(board[i][j] == me){
			num++;
			i++; 
			j++;
		} 
		else{
			break;
		}
	}
	if(board[i][j] != me || i == size || j==size){
		flag++; 
	}
	i = m-1;
	j = n-1;
	while(i>=0 && j>=0){
		if(board[i][j] == me){
			num++;
			i--; 
			j--;
		} 
		else{
			break;
		}	
	}
	if(board[i][j] != me || i == -1 || j==-1){
		flag++; 
	}
	result[0] = num;
	result[1] = flag;	
	
	return result;
}

int* CheckYX(int m, int n, int me){ /*�k�W���U*/
	static int result[2] = {}; //�s�l�� & ��������  
	int flag = 0;//������: 0���䬡 1�@�䬡�@�䦺 2���䳣���� 
	int num = 1; //�s�l�� 
	int i, j;

	i = m-1;
	j = n+1;
	while(i>=0 && j<size){ //�k�W 
		if(board[i][j] == me){
			num++;
			i--; 
			j++;
		} 
		else{
			break;
		}
	}
	if(board[i][j] != me || i == -1 || j==size){
		flag++; 
	}
	i = m+1;
	j = n-1;
	while(i<size && j>=0){ //���U 
		if(board[i][j] == me){
			num++;
			i++; 
			j--;
		} 
		else{
			break;
		}	
	}
	if(board[i][j] != me || i == size || j==-1){
		flag++; 
	}
	result[0] = num;
	result[1] = flag;	
	
	return result;
}
