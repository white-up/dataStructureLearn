#include<iostream>
using namespace std;
//head->0->1->...tail  Î²Ìí¼Ó Í·É¾
struct QueueList{
	int data;
	struct QueueList* next;
};
struct QueueList* creatNode(int val);
struct QueueList* creatNode(int val) {
	struct QueueList* node = (struct QueueList*)malloc(sizeof(struct QueueList));
	node->next = NULL;
	node->data = val;
	return node;
}
bool NullCheckout(struct QueueList** pHead);
bool NullCheckout(struct QueueList** pHead) {
	if (pHead == NULL || (*pHead) == NULL) {
		return true;
	}
	return false;
}
void initQueue(struct QueueList** pHead);
void initQueue(struct QueueList** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		(*pHead)->data = 0;
		(*pHead)->next = NULL;
	}

}
void addQueue(struct QueueList** pHead,int val);
void addQueue(struct QueueList** pHead,int val) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		struct QueueList* move = *pHead;
		while (move->next != NULL) {
			move = move->next;
		}
		move->next = creatNode(val);
		(*pHead)->data++;
	}

}
bool isEmpty(struct QueueList* pHead) {
	if (NullCheckout(&pHead)||pHead->data == 0) {
		return true;
	}
	else
	{
		return false;
	}
}
int delQueue(struct QueueList** pHead);
int delQueue(struct QueueList** pHead) {
	if (isEmpty(*pHead)) {
		return -1;
	}
	else {
		struct QueueList* temp = (*pHead)->next;
		int ans = (*pHead)->next->data;
		(*pHead)->next = temp->next;
		(*pHead)->data--;
		free(temp);
		temp = NULL;
	}

}
void printfQueue(struct QueueList* pHead);
void printfQueue(struct QueueList* pHead) {
	if (isEmpty(pHead)) {
		return;
	}
	else {
		printf("head:");
		struct QueueList* move = pHead;
		while (move->next != NULL) {
			printf(" %d ",move->next->data);
			move = move->next;
		}
		printf("tail\n");
	}
}
/*
int main() {
	struct QueueList* aQueue = (struct QueueList*)malloc(sizeof(struct QueueList));
	struct QueueList** Queue = &aQueue;
	initQueue(Queue);
	for (int i = 0; i < 5; i++) {
		addQueue(Queue,i);
	}
	printfQueue(aQueue);
	cout<<delQueue(Queue)<<endl;
	printfQueue(aQueue);


}*/