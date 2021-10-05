#include <iostream>
using namespace std;
static int MAXSIZE = 16;
struct ArrayNode {
	int data;
	int current;
};
//获取分配空间
int mallocArray(ArrayNode* space);
int mallocArray(ArrayNode* space) {
	//若备用链表非空，则返回分配的结点下标，否则返回0（当分配最后一个结点时，该结点的游标值为0）
	int i = space[0].current;
	if (space[0].current) {
		space[0].current = space[i].current;
	}
	return i;
}
bool errorCheckout(ArrayNode** pHead) {
	if (pHead == NULL || (*pHead)->current < 0 || (*pHead)->current >= MAXSIZE) {
		return true;
	}
	else {
		return false;
	}
}
//创建备用链表
void creatReserveArray(ArrayNode* space);
void creatReserveArray(ArrayNode* space) {
	for (int i = 0; i < MAXSIZE - 1; i++) {
		space[i].current = i + 1;
	}
	space[MAXSIZE - 1].current = 0;

}
//初始化静态链表
/*
array[0]用作备用链表的头结点，array[1]用作存放数据的链表的头结点，所以array[0]和array[6]为备用链表上的结点
 |null|null|1|2|3|...
 |next|2   |3|4|5|...

*/
int initArray(ArrayNode* space){
	creatReserveArray(space);
	int body = mallocArray(space);
	space[body].data = 0;
	/*
	int move = space[body].current;
	for (int i = 1; i < 5; i++){
		int j = mallocArray(space);       //从备用链表中拿出空闲的分量
		space[move].current = j;//将申请的空线分量链接在链表的最后一个结点后面
		space[j].data = 'a' + i - 1;//给新申请的分量的数据域初始化
		move = j;//将指向链表最后一个结点的指针后移
	}
	space[move].current = 0;//新的链表最后一个结点的指针设置为0
	*/
	return body;
}
//获取数据长度
int getLen(ArrayNode* space);
int getLen(ArrayNode* space) {
	if (errorCheckout(&space)) {
		return -1;
	}
	return space[1].data;
}

bool insertArray(ArrayNode* space, int index, int val);
int selectElem(ArrayNode* space,int val);
int selectElem(ArrayNode* space, int val) {
	if (errorCheckout(&space)) {
		return -1;
	}
	int body = space[1].current;
	int move = body;
	for (int i = 0; i < getLen(space); i++) {
		if (space[move].data == val) {
			return move;
		}
		move = space[move].current;
	}
	return - 1;
}
bool changeElem(ArrayNode* space,int oldElem,int nowElem);
bool changeElem(ArrayNode* space, int oldElem, int nowElem) {
	int index = selectElem(space,oldElem);
	if (index == -1) {
		return false;
	}
	else {
		space[index].data = nowElem;
	}

}
//behind
bool insertArray(ArrayNode* space,int index,int val) {
	if (errorCheckout(&space)) {
		return false;
	}
	else {
		if (index > getLen(space)) {
			return false;
		}
		int before = 1;
		int move = space[1].current;
		for (int i = 0; i < index; i++) {
			before = move;
			move = space[move].current;
		}
		int insert = mallocArray(space);
		space[insert - 1].current++;
		space[insert].current = move;
		space[insert].data = val;
		space[before].current = insert;
		space[1].data++;
	}

}
void addArray(ArrayNode* space, int val) {
	int add = mallocArray(space);
	
	space[add].data = val;
	space[1].data++;
}
bool deleteArray(ArrayNode* space, int index);
bool deleteArray(ArrayNode* space, int index) {
	if (errorCheckout(&space)) {
		return false;
	}
	else {
		ArrayNode before = space[1];
		int move = space[1].current;
		if (index > space[1].data || index < 0) {
			return false;
		}
		else {
			for (int i = 0; i < index; i++) {
				before = space[move];
				move = space[move].current;
			}
			before.current = space[move].current;
			space[move].current = space[0].current;
			space[0].current = move;
			space[1].data--;
			return true;
		}
	}

}
bool ClearArray(ArrayNode* space);
bool ClearArray(ArrayNode* space) {
	if (errorCheckout(&space)) {
		return false;
	}
	else {
		initArray(space);
	}
}
void printfArray(ArrayNode* space) {
	if (errorCheckout(&space)) {
		return;
	}
	else {
		int move = space[1].current;
		for (int i = 0; i < space[1].data; i++) {
			cout << "***" << space[move].data;
			move = space[move].current;
		}
		cout << endl;
	
	}

}
void unionArray(ArrayNode* space, ArrayNode* A, ArrayNode*B);
void unionArray(ArrayNode* space, ArrayNode* A, ArrayNode* B) {
	if (errorCheckout(&space)) {
		return;
	}
	if (errorCheckout(&A)) {
		return;
	}
	else {
		int move = A[1].current;
		for (int i = 0; i < A[1].data; i++) {
			addArray(space, A[move].data);
			move = A[move].current;
		}
	}
	if (errorCheckout(&B)) {
		return;
	}else{
		int move = B[1].current;
		for (int i = 0; i < B[1].data; i++) {
			addArray(space, B[move].data);
			move = B[move].current;
		}
	}

}
//获取(a-b)U(b-a)数据集合
void difference(ArrayNode** space, int sizeA,int sizeB,int *A,int *B);
void difference(ArrayNode** space, int sizeA, int sizeB, int* A, int* B) {
	ArrayNode* nodeA = (ArrayNode*)malloc(sizeof(ArrayNode[16]));
	initArray(nodeA);
	for (int i = 0; i < sizeA; i++) {
		addArray(nodeA,*(A+i));
	}
	for (int i = 0; i < sizeB; i++) {
		deleteArray(nodeA,selectElem(nodeA,*(B+i)));
	}
	ArrayNode* nodeB = (ArrayNode*)malloc(sizeof(ArrayNode[16]));
	initArray(nodeB);
	for (int i = 0; i < sizeA; i++) {
		addArray(nodeB, *(B + i));
	}
	for (int i = 0; i < sizeA; i++) {
		deleteArray(nodeB, selectElem(nodeB, *(A + i)));
	}
	unionArray(*space,nodeA,nodeB);
}
/*
int main() {
	ArrayNode* space =(ArrayNode*) malloc(sizeof(ArrayNode[16]));
	initArray(space);
	for(int i =0;i<5;i++)
		addArray(space,i);
	cout << "size: "<<getLen(space) << endl;
	printfArray(space);
	insertArray(space, -1, 9);
	printfArray(space);
	cout << "size: " << getLen(space) << endl;
	cout<<"select: "<<selectElem(space,9)<<endl;
	changeElem(space, 9, 7);
	printfArray(space);
	cout << "size: " << getLen(space) << endl;
	addArray(space,8);
	printfArray(space);
	cout << "size: " << getLen(space) << endl;
}*/