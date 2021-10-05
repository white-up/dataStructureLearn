#include<iostream>
using namespace std;
//先进后出
//|base|...|...|...|...|top|
struct StackArray {
	int* dataTop;
	int* dataBase;
	int maxSize;
	int nowSize;
};


bool NullCheckout(struct StackArray* stack) {
	return stack == NULL;
}
void initStack(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		stack = (struct StackArray*)malloc(sizeof(StackArray));
	}
	stack->nowSize = 0;
	stack->maxSize = 16;
	stack->dataBase = (int*)malloc(sizeof(int [16]));
	stack->dataTop = stack->dataBase;
}
void DestoryStack(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		return;
	}
	else {
		free(stack->dataTop);
		stack->dataBase = NULL;
		stack->dataTop = NULL;
		free(stack);
		stack = NULL;
	}
}
void ClearStack(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		return;
	}
	else {
		free(stack->dataTop);
		
		stack->dataTop = (int*)malloc(sizeof(int[16]));
		stack->dataBase = stack->dataTop;
		stack->maxSize = 16;
		stack->nowSize = 0;
	
	}

}
bool StackEmpty(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		return true;
	}
	else {
		return stack->nowSize == 0;
	}
}
int StackLength(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		return -1;
	}
	else {
		return stack->nowSize;
	}
}
int Pop(struct StackArray* stack) {
	if (StackEmpty(stack)) {
		return 0;
	}
	else {
		stack->nowSize--;
		//int* temp = stack->dataTop;
		stack->dataTop--;
		int ans = *(stack->dataTop);
		*(stack->dataTop) = 0;
		return ans;
	}
}
bool isFull(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		return false;
	}
	else {
		return stack->nowSize == stack->maxSize;
	}
}
bool Push(struct StackArray* stack,int val) {
	if (NullCheckout(stack)) {
		return false;
	}
	else {
		if (isFull(stack)) {
		
		}
		else {
			*(stack->dataTop) = val;
			stack->dataTop++;
			stack->nowSize++;
		}
	}
}
int getTop(struct StackArray* stack) {
	if (NullCheckout(stack)) {
		return -1;
	}
	else {
		return *(stack->dataTop-1);
	}
}
void PrintfArray(struct StackArray* stack) {
	if(NullCheckout(stack)){
		return;
	}
	int* move = stack->dataBase;
	for (int i = 0; i < stack->nowSize; i++) {
		printf("| %d ",*move);
		move++;
	}
	printf("\n");
}
void conversion(struct StackArray* stack);
void lineedit(struct StackArray* stack);

/*
int main() {
	struct StackArray* stack = (struct StackArray*)malloc(sizeof(StackArray));
	initStack(stack);
	PrintfArray(stack);
	for (int i = 0; i < 5; i++)
		Push(stack,i);
	PrintfArray(stack);
	printf("%d\n",getTop(stack));
	Push(stack, 9);
	PrintfArray(stack);
	cout<<Pop(stack)<<endl;
	PrintfArray(stack);

}
*/