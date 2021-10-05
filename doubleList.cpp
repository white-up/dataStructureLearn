#include<iostream>
using namespace std;
/*
| ...| 4| 3| 2| 1| 0|left|pHead|right|0 |1 |2 |3 |4 |... |
*/
struct DoubleNode {
	int data;
	struct DoubleNode* left;
	struct DoubleNode* right;
};
bool NullCheckout(DoubleNode** pHead);
bool NullCheckout(DoubleNode** pHead) {
	if (pHead == NULL || (*pHead) == NULL|| (*pHead)->left ==NULL|| (*pHead)->right==NULL) {
		return true;
	}
	else {
		return false;
	}

}
DoubleNode* creatNode(int val);
DoubleNode* creatNode(int val) {
	DoubleNode* ans = (DoubleNode*)malloc(sizeof(DoubleNode));
	if (ans == NULL) {
		printf("error: you do not have any malloc\n");
		exit(1);
	}
		ans->data = val;
		ans->left = NULL;
		ans->right = NULL;
		return ans;
}
bool initList(DoubleNode** pHead);
bool initList(DoubleNode** pHead) {
	if (pHead == NULL) {
		return false;
	}
	else {
		if ((*pHead) == NULL) {
			(*pHead) = creatNode(0);
			DoubleNode* left = creatNode(0);
			DoubleNode * right = creatNode(0);
			(*pHead)->left = left;
			left->right = (*pHead);
			(*pHead)->right = right;
			right->left = (*pHead);
		}
		else {
			(*pHead)->data = 0;
			//if ((*pHead)->left == NULL) {
				DoubleNode* left = creatNode(0);
				(*pHead)->left = left;
				left->right = *pHead;

			/* }
			else {
				(*pHead)->left->data = 0;
				(*pHead)->left->left = NULL;
				(*pHead)->left->right = *pHead;
			}
			if ((*pHead)->right == NULL) {*/
				DoubleNode* right = creatNode(0);
				(*pHead)->right = right;
				right->left = (*pHead);
			/* }
			else {
				(*pHead)->right->data = 0;
				(*pHead)->right->left = (*pHead);
				(*pHead)->right->right = NULL;
			}*/
		}
		
	}


}
void add_tailArray(DoubleNode** pHead,bool isRight,int val);
void add_tailArray(DoubleNode** pHead, bool isRight, int val) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		if (isRight) {
			DoubleNode* move = (*pHead)->right;
			move->data++;
			while (move->right != NULL) {
				move = move->right;
			}
			DoubleNode* creat = creatNode(val);
			creat->left = move;
			move->right = creat;
		}
		else{
			DoubleNode* move = (*pHead)->left;
			move->data++;
			while (move->left != NULL) {
				move = move->left;
			}
			DoubleNode* creat = creatNode(val);
			creat->right = move;
			move->left = creat;
		}
		(*pHead)->data++;
	}
}
void insertArray(DoubleNode** pHead, bool isRight, int val, int index) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		if (index < 0) {
			return;
		}
		if (isRight) {
			DoubleNode* move = (*pHead)->right;
			if (index > move->data) {
				return;
			}
			else {
				move->data++;
				for (int i = 0; i < index; i++) {
					move = move->right;
				}
				DoubleNode* creat = creatNode(val);
				creat->right = move->right;
				if (move->right != NULL) {
					move->right->left = creat;
				}
				creat->left = move;
				move->right = creat;
			}
		}
		else {
			DoubleNode* move = (*pHead)->left;
			if (index > move->data) {
				return;
			}
			else {
				move->data++;
				for (int i = 0; i < index; i++) {
					move = move->left;
				}
				DoubleNode* creat = creatNode(val);
				creat->left = move->left;
				if (move->left != NULL) {
					move->left->right = creat;
				}
				creat->right = move;
				move->left = creat;
			}
		
		}
		(*pHead)->data++;
	
	
	}

}
void deldeteArray(DoubleNode** pHead, bool isRight, int index);
void deldeteArray(DoubleNode** pHead, bool isRight, int index) {
	if (NullCheckout(pHead)|| index < 0) {
		return;
	}
	if (isRight) {
		DoubleNode* move = (*pHead)->right->right;
		int len = (*pHead)->right->data;
		if (index >= len) {
			return;
		}
		else {
			for (int i = 0; i < index; i++) {
				move = move->right;
			}
			DoubleNode* before = move->left;
			DoubleNode* after = move->right;
			free(move);
			move = NULL;
			
			after->left = before;
			before->right = after;
			
			(*pHead)->right->data--;
		}
	}
	else {
		DoubleNode* move = (*pHead)->left->left;
		int len = (*pHead)->left->data;
		if (index >= len) {
			return;
		}
		else {
			for (int i = 0; i < index; i++) {
				move = move->left;
			}
			DoubleNode* before = move->right;
			DoubleNode* after = move->left;
			free(move);
			move = NULL;
			before->left = after;
			after->right = before;
			(*pHead)->left->data--;
		}
	}
	(*pHead)->data--;
}
void printfArray(DoubleNode** pHead);
void printfArray(DoubleNode** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		int lenLeft = (*pHead)->left->data;
		int lenRight = (*pHead)->right->data;
		DoubleNode* moveLeft = (*pHead)->left->left;
		DoubleNode* moveRight = (*pHead)->right->right;
		printf("left\n");
		for (int i = 0; i < lenLeft; i++) {
			printf("**id: %d  val: %d",i,moveLeft->data);
			moveLeft = moveLeft->left;
		}
		printf("\nright\n");
		for (int i = 0; i < lenRight; i++) {
			printf("**id: %d  val: %d",i,moveRight->data);
			moveRight = moveRight->right;
		}
		printf("\n");
	}
}
void conversionCirculation(DoubleNode** pHead);
void conversionCirculation(DoubleNode** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		DoubleNode* left = (*pHead)->left;
		DoubleNode* right = (*pHead)->right;
		while (left->left != NULL) {
			left = left->left;
		}
		while (right->right != NULL) {
			right = right->right;
		}
		left->left = right;
		right->right = left;
	}
}
void ClearList(DoubleNode** pHead);
void ClearList(DoubleNode** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		DoubleNode* left = (*pHead)->left->left;
		DoubleNode* right = (*pHead)->right->right;
		(*pHead)->data = 0;
		(*pHead)->left->left = NULL;
		(*pHead)->left->data = 0;
		(*pHead)->right->right = NULL;
		(*pHead)->right->data = 0;
		while (left != NULL) {
			DoubleNode* temp = left;
			left = left->left;
			free(temp);
			temp = NULL;
		}
		while (right != NULL) {
			DoubleNode* temp = right;
			right = right->right;
			free(temp);
			temp = NULL;
		}
	
	
	}


}
/*
int main() {
	DoubleNode* Head = (DoubleNode*)malloc(sizeof(DoubleNode));
	DoubleNode** pHead = &Head;
	initList(pHead);
	for(int i =0;i<5;i++)
		add_tailArray(pHead,true,i);
	for (int i = 0; i < 5; i++)
		add_tailArray(pHead,false,i);
	printfArray(pHead);
	insertArray(pHead,true,9,0);
	printfArray(pHead);
	insertArray(pHead,false,9,4);
	printfArray(pHead);
	deldeteArray(pHead,false,0);
	printfArray(pHead);
}
*/