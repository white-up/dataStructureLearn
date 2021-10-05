#include<iostream>
using namespace std;
struct QueueArray{
	int* data;
	int front;
	int rear;
	int count;
};
bool NullCheckout(struct QueueArray** pHead);
bool NullCheckout(struct QueueArray** pHead) {
	if (pHead == NULL || (*pHead) == NULL) {
		return true;
	}
	return false;
}
void initQueue(struct QueueArray** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	(*pHead)->data = (int*)malloc(sizeof(int[10]));
	(*pHead)->count = 0;
	(*pHead)->front = 0;
	(*pHead)->rear = 0;
}
bool isFull(struct QueueArray* pHead) {
	if (NullCheckout(&pHead)) {
		return true;
	}
	//set max = 10
	if ((pHead->rear + 1) % 10 == pHead->front) {
		return true;
	}
	else {
		return false;
	}
}
void EnQueue(struct QueueArray** pHead,int val);
void EnQueue(struct QueueArray** pHead,int val) {
	if (isFull(*pHead)) {
		return;
	}
	else {
		//printf("%d", (*pHead)->rear);
		(*pHead)->data[(*pHead)->rear] = val;
		(*pHead)->rear = ((*pHead)->rear + 1) % 10;
		(*pHead)->count++;
	}

}
int DelQueue(struct QueueArray** pHead) {
	if (NullCheckout(pHead)) {
		return -1;
	}
	int ans = (*pHead)->data[(*pHead)->front];
	(*pHead)->front = ((*pHead)->front + 1) % 10;
	return ans;
}
void printfQueue(struct QueueArray* pHead) {
	if (NullCheckout(&pHead) || pHead->count == 0) {
		return;
	}
	int move = pHead->front;
	while (move != pHead->rear) {
		printf(" %d",pHead->data[move]);
		move = (move + 1) % 10;
	}
	printf("\n");
}
/*
int main() {
	struct QueueArray* Head = (struct QueueArray*)malloc(sizeof(struct QueueArray));
	struct QueueArray** pHead = &Head;
	initQueue(pHead);
	for (int i = 0; i < 5; i++) {
		EnQueue(pHead,i);
	}
	printfQueue(Head);
	for (int i = 0; i < 5; i++) {
		cout<<DelQueue(pHead)<<endl;
	}
	printfQueue(Head);

}
*/