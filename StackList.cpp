#include<iostream>
using namespace std;
//()<->[]<->[]<->[]...
struct StackNode{
	int data;
	struct StackNode* top;
};
bool NullCheckout(StackNode** pHead);
bool NullCheckout(StackNode** pHead) {
	if (pHead == NULL || (*pHead) == NULL) {
		return true;
	}
	else {
		return false;
	}
}
struct StackNode* creatNode(int val) {
	struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
	if (NullCheckout(&node)) {
		printf("error");
	}
	else {
		node->data = val;
		node->top = NULL;
	}
	return node;
}
void initStack(struct StackNode** pHead) {
	if (NullCheckout(pHead)) {
		printf("error");
	}
	else {
		(*pHead)->data = 0;
		(*pHead)->top = NULL;
	}
}
void add(struct StackNode** pHead,int val) {
	if (NullCheckout(pHead)) {
		printf("error");
		return;
	}
	(*pHead)->data++;
	struct StackNode* creat = creatNode(val);
	struct StackNode* move = (*pHead)->top;
	(*pHead)->top = creat;
	creat->top = move;
	
}
int del(struct StackNode** pHead) {
	if (NullCheckout(pHead)) {
		return -1;
	}
	(*pHead)->data--;
	int ans = (*pHead)->top->data;
	struct StackNode* temp = (*pHead)->top;
	(*pHead)->top = (*pHead)->top->top;
	free(temp);
	temp = NULL;
	return ans;
}
void printfArray(struct StackNode* pHead) {
	if (NullCheckout(&pHead)) {
		return;
	}
	struct StackNode* move = pHead->top;
	printf("Top: ");
	while (move != NULL) {
		printf("-> %d ", move->data);
		move = move->top;
	}
	printf("\n");

}
/*
int main() {
	StackNode* Head = creatNode(0);
	StackNode** pHead = &Head;
	initStack(pHead);
	for (int i = 0; i < 5; i++) {
		add(pHead,i);
	}
	printfArray(Head);
	for (int i = 0; i < 5; i++) {
		printf(" *%d* ",del(pHead));
		printfArray(Head);
	}


}
*/