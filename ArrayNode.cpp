#include <iostream>
using namespace std;
static int MAXSIZE = 16;
struct ArrayNode {
	int data;
	int current;
};
//��ȡ����ռ�
int mallocArray(ArrayNode* space);
int mallocArray(ArrayNode* space) {
	//����������ǿգ��򷵻ط���Ľ���±꣬���򷵻�0�����������һ�����ʱ���ý����α�ֵΪ0��
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
//������������
void creatReserveArray(ArrayNode* space);
void creatReserveArray(ArrayNode* space) {
	for (int i = 0; i < MAXSIZE - 1; i++) {
		space[i].current = i + 1;
	}
	space[MAXSIZE - 1].current = 0;

}
//��ʼ����̬����
/*
array[0]�������������ͷ��㣬array[1]����������ݵ������ͷ��㣬����array[0]��array[6]Ϊ���������ϵĽ��
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
		int j = mallocArray(space);       //�ӱ����������ó����еķ���
		space[move].current = j;//������Ŀ��߷�����������������һ��������
		space[j].data = 'a' + i - 1;//��������ķ������������ʼ��
		move = j;//��ָ���������һ������ָ�����
	}
	space[move].current = 0;//�µ��������һ������ָ������Ϊ0
	*/
	return body;
}
//��ȡ���ݳ���
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
//��ȡ(a-b)U(b-a)���ݼ���
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