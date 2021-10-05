#include<iostream>
using namespace std;
//������
struct Node {
	int data;//�������������������
	struct Node* pNext;//����һ���ṹ��ָ�룬ָ����һ�θ��뵱ǰ�ڵ�����������ͬ�Ľڵ�
};

//utity**************************************
Node* creatNode(int val) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		printf("error: can not creat");
		return NULL;
	}
	else {
		node->data = val;
		node->pNext = NULL;
		return node;
	}
}
bool NullCheckout(struct Node** pHead);
bool NullCheckout(struct Node** pHead) {
	if (pHead == NULL||(*pHead)==NULL) {
		return true;
	}
	else {
		return false;
	}
}
//utity**************************************
bool InitList(struct Node** pHead);
bool ClearList(struct Node** pHead);
void printfNode(struct Node* pHead);
bool ListEmpty(struct Node* pHead);
int ListLength(struct Node* pHead);
int getElement(struct Node* pHead, int index);
int searchNode(struct Node* pHead, int val);
int PriorElem(struct Node* pHead, int item);
int NextElem(struct Node* pHead, int item);
//β��
void insertNode_tail(struct Node** pHead, int val);
void insertNode_tail_recursion(struct Node** pHead, int val);
//ͷ��
void insertNode_head(struct Node** pHead, int val);
//βɾ
void deleteNode_tail(struct Node** pHead);
//ͷɾ
void deleteNode_head(struct Node** pHead);
//���������룬���뵽���ǰ
void insertNode(struct Node** pHead, int val, int location);
//�������ɾ��
void deleteNode_location(struct Node** pHead, int location);
//��ֵɾ��(true:ɾ�����ĵ�һ��;false:all)
void deleteNode_val_Only(struct Node** pHead, int val, bool judge);
bool unionList(struct Node** pHead, struct Node* ListB);//�����������Ա�b�е�����a�еļ��뵽pHead

bool InitList(struct Node** pHead) {
	if (pHead == NULL) {
		printf("error: pHead is null");
		return false;
	}
	else {
		*pHead = creatNode(0);
		return true;
	}

}
bool ClearList(struct Node** pHead) {
	if (NullCheckout(pHead)) {
		return false;
	}
	else {
		struct Node* move = (*pHead)->pNext;
		struct Node* after = move->pNext;
		(*pHead)->pNext = NULL;
		(*pHead)->data = 0;
		while (after != NULL) {
			free(move);
			move = after;
			after = after->pNext;
		}
		free(move);
		move = NULL;
		after = NULL;
		return true;
	}
}
bool DestoryList(struct Node** pHead) {
	if (NullCheckout(pHead)) {
		return false;
	}
	else {
		struct Node* move = (*pHead);
		struct Node* after = move->pNext;
		(*pHead) = NULL;
		while (after != NULL) {
			free(move);
			move = after;
			after = after->pNext;
		}
		free(move);
		move = NULL;
		after = NULL;
		return true;
	}
}
void printfNode(struct Node* pHead) {
	int count = 0;
	for (Node* move = pHead->pNext; move != NULL; move = move->pNext) {
		printf(" id:%d val:%d -->", count, move->data);
		count++;
	}
	printf(" end\n");
}
bool ListEmpty(struct Node* pHead) {
	if (NullCheckout(&pHead)) {
		return true;
	}
	else {
		return pHead->data == 0;
	}
}
int ListLength(struct Node* pHead) {
	if (NullCheckout(&pHead)) {
		return -1;
	}
	else {
		return pHead->data;
	}
}
int getElement(struct Node* pHead, int index) {
	if (NullCheckout(&pHead)) {
		printf("error: list is null\n");
		return -1;
	}
	else {
		if (index < 0) {
			printf("error: index is not true\n");
			return -1;
		}
		else if (pHead->data<=index) {
			printf("error: index is too max");
			return -1;
		}
		else {
			Node* move = pHead->pNext;
			for (int i = 0; i < index; i++) {
				move = move->pNext;
			}
			return move->data;
		}
	
	}
}
int searchNode(struct Node* pHead, int val) {
	if(NullCheckout(&pHead)){
		return -1;
	}
	int count = -1;
	Node* move = pHead->pNext;
	for (int i = 0; i < pHead->data; i++) {
		if (move->data == val) {
			count = i;
			break;
		}
		move = move->pNext;
	}
	return count;
}
int PriorElem(struct Node* pHead, int item) {
	int search = searchNode(pHead,item);
	if (search != -1) {
		return getElement(pHead,item-1);
	}
	else {
		return -1;
	}
}
int NextElem(struct Node* pHead, int item) {
	int search = searchNode(pHead, item);
	if (search != -1) {
		return getElement(pHead, item + 1);
	}
	else {
		return -1;
	}
}
void insertNode_tail(struct Node** pHead, int val) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		Node* move = *pHead;
		move->data++;
		while (move->pNext != NULL) {
			move = move->pNext;
		}
		move->pNext = creatNode(val);
	}
}
void insertNode_tail_recursion_body(struct Node** pHead, int val) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		//�ж��Ƿ���Ϊ��
		if ((*pHead)->pNext != NULL) {
			insertNode_tail_recursion(&((*pHead)->pNext), val);
		}
		else {
			(*pHead)->pNext = creatNode(val);
		}
	}
}
void insertNode_tail_recursion(struct Node** pHead, int val) {
	(*pHead)->data++;
	insertNode_tail_recursion_body(pHead, val);
}
void insertNode_head(struct Node** pHead, int val) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		(*pHead)->data++;
		if ((*pHead)->pNext == NULL) {
			(*pHead)->pNext = creatNode(val);
		}
		else {
			Node* right = (*pHead)->pNext;
			(*pHead)->pNext = creatNode(val);
			(*pHead)->pNext->pNext = right;
		}
	}
}
void deleteNode_tail(struct Node** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	if ((*pHead)->pNext == NULL) {
		printf("error: we don not have any Node");
		return;
	}
	else {
		(*pHead)->data--;
		Node* move = *pHead;
		while (move->pNext->pNext != NULL) {
			move = move->pNext;
		}

		//���ý���ڴ��ͷ�
		move->pNext = NULL;
	}
}
void deleteNode_head(struct Node** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	if ((*pHead)->pNext == NULL) {
		printf("error: we don not have any Node");
		return;
	}
	else {
		Node* left = (*pHead)->pNext;//��������
		Node* right = (*pHead)->pNext->pNext;
		(*pHead)->pNext = right;
		(*pHead)->data--;
	}
}
void insertNode(struct Node** pHead, int val, int location) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		if (location == 1) {
			insertNode_head(pHead, val);
		}
		else if (location < 1) {
			printf("error: please input right index");
			return;
		}
		else if (location > (*pHead)->data) {
			insertNode_tail(pHead, val);
		}
		else {
			Node* move = *pHead;
			for (int i = 1; i < location; i++) {
				move = move->pNext;
			}
			Node* temp = move->pNext;
			move->pNext = creatNode(val);
			move->pNext->pNext = temp;
		}
		(*pHead)->data++;
	}
}
void deleteNode_location(struct Node** pHead, int location) {
	if (location == 1) {
		deleteNode_head(pHead);
	}
	else if (location < 1 || location >(*pHead)->data) {
		printf("error: please input right index");
		return;
	}
	else if (location == (*pHead)->data) {
		deleteNode_tail(pHead);
	}
	else {
		Node* move = *pHead;
		for (int i = 1; i < location; i++) {
			move = move->pNext;
		}
		Node* center = move->pNext;//����ɾ��
		Node* end = move->pNext->pNext;
		move->pNext = end;
		(*pHead)->data--;
	}
	

}
void deleteNode_val_Only(struct Node** pHead, int val, bool judge) {
	if (NullCheckout(pHead)) {
		return;
	}
	int flag = searchNode(*pHead, val);
	cout << flag << endl;
	if (flag != -1) {
		deleteNode_location(pHead, flag);
	}
	if (!judge) {
		flag = searchNode(*pHead, val);
		while (flag != -1) {
			deleteNode_location(pHead, flag);
			flag = searchNode(*pHead, val);
		}
	}
}
bool unionList(struct Node** pHead, struct Node* ListB) {
	if (NullCheckout(pHead) || ListEmpty(ListB)) {
		return false;
	}
	else {
		struct Node* move = ListB->pNext;
		while (move != NULL) {
			if (searchNode(*pHead, move->data) == -1) {
				insertNode_head(pHead, move->data);
			}
			move = move->pNext;
		}
		return true;
	}
}
/*
int main() {
	struct Node* list = (struct Node*)malloc(sizeof(struct Node));
	struct Node** List = &list;
	InitList(List);
	for (int i = 0; i < 5; i++) {
		insertNode_head(List,i);
	}
	//ClearList(List);
	//DestoryList(List);
	//cout << ListEmpty(list);
	printfNode(list);
	cout<<PriorElem(list,1);
	
	insertNode_tail(List,9);
	printfNode(list);
	insertNode(List, 10, 1);
	printfNode(list);
	cout << searchNode(list, 10) << endl;
	
}
*/














