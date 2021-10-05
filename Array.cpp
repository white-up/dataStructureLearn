#include <iostream>
using namespace std;
//初始化默认大小
static int defaultSize = 16;
struct ArrayList {
	int* pData;//数据域
	int maxSize;//容量
	int nowSize;//现元素个数
};

bool NullCheckout(struct ArrayList** pHead);
bool InitList(struct ArrayList** pHead);
bool InitList(struct ArrayList** pHead, int length);
bool ListEmpty(struct ArrayList* pHead);
int ListLength(struct ArrayList* pHead);
int getElement(struct ArrayList* pHead, int index);
int PriorElem(struct ArrayList* pHead, int item);
int NextElem(struct ArrayList* pHead, int item);
void appendArray(struct ArrayList** pHead);
void addArray(struct ArrayList** pHead, int val);
void insertArray(struct ArrayList** pHead, int pos, int val);
void deleteArray(struct ArrayList** pHead, int pos);
bool isFull(struct ArrayList* pHead);
void sortArray(struct ArrayList** pHead);
void printfArray(struct ArrayList* pHead);
int getIndex(struct ArrayList* pHead,int val);
int Supplement_LocateElem(struct ArrayList** pHead,int other,bool(*untity_Compare)(int,int));
bool Supplement_ListTraverse(struct ArrayList** pHead, void (*untity_Add)(int*, int));
void unionList(struct ArrayList** pHead, struct ArrayList* ListB);//将所有在线性表b中但不在a中的加入到a
void MergeList(struct ArrayList** La, struct ArrayList** Lb, struct ArrayList** Lc);//整合两有序数组
bool untity_Compare(int nowBody, int other);
void untity_Add(int* data, int len);
/*
int main() {
	struct ArrayList* arr0 = (struct ArrayList*)malloc(sizeof(struct ArrayList));
	struct ArrayList** p0 = &arr0;
	InitList(p0);
	struct ArrayList* arr1 = (struct ArrayList*)malloc(sizeof(struct ArrayList));
	struct ArrayList** p1 = &arr1;
	InitList(p1);
	struct ArrayList* arr = (struct ArrayList*)malloc(sizeof(struct ArrayList));
	struct ArrayList** p = &arr;
	InitList(p);
	for (int i = 5; i > 0; i--) {
		addArray(p0, i);
	}
	for (int i = 10; i > 5; i--) {
		addArray(p1, i);
	}
	MergeList(p0,p1,p);
	printfArray(arr);
	
	struct ArrayList* arr = (struct ArrayList*)malloc(sizeof(struct ArrayList));
	struct ArrayList** p = &arr;
	InitList(p);
	cout << NullCheckout(p)<<endl;
	//ClearList(p);
	cout << p<<endl;
	cout << ListEmpty(arr) << endl;
	for (int i = 5; i >0; i--) {
		addArray(p,i);
	}
	//cout << isFull(arr) << "full" << endl;
	cout << ListLength(arr) << endl;
	cout << getElement(arr, 4)<<endl;
	cout << PriorElem(arr,4)<<endl;
	cout << NextElem(arr,3) << endl;
	appendArray(p);
	cout << ListLength(*p) << endl;
	printfArray(arr);
	//insertArray(p,10,9);
	//deleteArray(p,5);
	sortArray(p);
	Supplement_ListTraverse(p,untity_Add);
	printfArray(arr);
	//cout << getIndex(arr, 1) << endl;
	//cout << Supplement_LocateElem(p,1,untity_Compare) << endl;
	struct ArrayList* arr1 = (struct ArrayList*)malloc(sizeof(struct ArrayList));
	struct ArrayList** p1 = &arr1;
	InitList(p1);
	for (int i = 10; i > 5; i--) {
		addArray(p1, i);
	}
	unionList(p,arr1);
	printfArray(arr);
}
*/
//untity*****************************************
void untity_Add(int* data, int len) {
	for (int i = 0; i < len; i++) {
		*(data + i) = *(data + i) + 1;
	}
}
bool untity_Compare(int nowBody, int other) {
	return nowBody > other;
}
//untity*****************************************
//校验空指针异常
bool NullCheckout(struct ArrayList** pHead) {
	if (pHead == NULL || (*pHead) == NULL) {
		return true;
	}
	else {
		return false;
	}
}
bool InitList(struct ArrayList** pHead) {
	if (NullCheckout(pHead)) {
		printf("error: pHead is null");
		return false;
	}
	else {
		(*pHead)->pData = (int*)malloc(sizeof(int) * defaultSize);
		if ((*pHead)->pData == NULL)
		{
			printf("error: 动态内存分配失败!\n");
			return false;
		}
		else {
			printf("动态内存分配成功!\n");
			(*pHead)->maxSize = defaultSize;
			(*pHead)->nowSize = 0;
		}
		return true;
	}
}
bool InitList(struct ArrayList** pHead, int length) {
	if (NullCheckout(pHead)) {
		printf("error: pHead is null");
		return false;
	}
	else {
		(*pHead)->pData = (int*)malloc(sizeof(int) * length);
		if ((*pHead)->pData == NULL)
		{
			printf("error: 动态内存分配失败!\n");
			return false;
		}
		else {
			printf("动态内存分配成功!\n");
			(*pHead)->maxSize = length;
			(*pHead)->nowSize = 0;
		}
		return true;
	}
}
bool ClearList(struct ArrayList** pHead) {
	if (NullCheckout(pHead)) {
		printf("error: pHead is null");
		return false;
	}
	else {
		(*pHead)->nowSize = 0;
	}
}
bool destoryList(struct ArrayList** pHead);
bool destoryList(struct ArrayList** pHead) {
	if (NullCheckout(pHead)) {
		printf("error: list is null\n");
		return false;
	}
	else {
		free((*pHead)->pData);//释放内部内存
		free(*pHead);
		*pHead = NULL;
		return true;
	}

}
bool ListEmpty(struct ArrayList* pHead) {
	if (!NullCheckout(&pHead)) {
		return pHead->nowSize == 0;
	}
	else {
		return true;
	}
}
int ListLength(struct ArrayList* pHead) {
	if (NullCheckout(&pHead)) {
		return -1;
	}
	else if (!ListEmpty(pHead)) {
		return pHead->nowSize;
	}
	else {
		return 0;

	}
}
/*
返回对应角标(省略封装返回结果)
struct ans{
	int data;
	bool flag;判断是否成功返回
};
*/
int getElement(struct ArrayList* pHead, int index) {
	if (NullCheckout(&pHead)) {
		return -1;
	}
	if (index < 0 || index >= pHead->nowSize) {
		printf("error: we do not have data from this index\n");
		return -1;
	}
	else {
		return *(pHead->pData + index);
	}
}
int PriorElem(struct ArrayList* pHead, int item) {
	if (NullCheckout(&pHead)) {
		return -1;
	}
	int* data = pHead->pData;
	int len = pHead->nowSize;
	int prior = *(data);
	for (int i = 1; i < len; i++) {
		if (*(data + i) == item) {
			return prior;
		}
		else {
			prior = *(data + i);
		}
	}
	return -1;
}
int NextElem(struct ArrayList* pHead, int item) {
	if (NullCheckout(&pHead)) {
		return -1;
	}
	int* data = pHead->pData;
	for (int i = 0; i < pHead->nowSize - 1; i++) {
		if (*(data + i) == item) {
			return *(data + i + 1);
		}
	}
	return -1;

}
void appendArray(struct ArrayList** pHead) {
	if (NullCheckout(pHead)) {
		InitList(pHead);
	}
	else {
		int length = (*pHead)->maxSize;
		int* del = (*pHead)->pData;
		(*pHead)->pData = (int*)malloc(sizeof(int) * length * 2);
		(*pHead)->maxSize = 2 * length;
		int* arr = (*pHead)->pData;
		for (int i = 0; i < (*pHead)->nowSize; i++) {

			if (arr+i != NULL) {
				*(arr + i) = *(del + i);
			}
			
		}
		free(del);
	}
}
void addArray(struct ArrayList** pHead, int val) {
	if (NullCheckout(pHead)) {
		InitList(pHead);
		addArray(pHead,val);
	}else if ((*pHead)->maxSize == (*pHead)->nowSize) {
		appendArray(pHead);
		addArray(pHead, val);
	}
	else {
		(*pHead)->nowSize++;
		if ((*pHead)->nowSize == 0) {
			*((*pHead)->pData) = val;
		}
		else {
			*((*pHead)->pData + (*pHead)->nowSize - 1) = val;
		}
	}
}
void insertArray(struct ArrayList** pHead, int pos, int val) {
	if (NullCheckout(pHead)) {
		InitList(pHead);
		addArray(pHead, val);
	}
	if ((*pHead)->maxSize == (*pHead)->nowSize) {
		appendArray(pHead);
		insertArray(pHead, pos, val);
	}
	else if (pos >= (*pHead)->nowSize) {
		addArray(pHead, val);
	}
	else if (pos >= 0) {
		int len = (*pHead)->nowSize;
		for (int i = len; i > pos; i--) {
			*((*pHead)->pData + i) = *((*pHead)->pData + i - 1);
		}
		*((*pHead)->pData + pos) = val;
		(*pHead)->nowSize++;
	}

}
void deleteArray(struct ArrayList** pHead, int pos) {
	if (NullCheckout(pHead)) {
		return;
	}
	else {
		int len = (*pHead)->nowSize;
		if (len <= pos) {
			printf("error: we do not have any index");
		}
		else {
			for (int i = pos; i < len - 1; i++) {
				*((*pHead)->pData + pos) = *((*pHead)->pData + pos + 1);
			}
			*((*pHead)->pData + len - 1) = 0;
			(*pHead)->nowSize--;
		}
	}
}
bool isFull(struct ArrayList* pHead) {
	if (NullCheckout(&pHead)) {
		return false;
	}
	else {
		return pHead->maxSize == pHead->nowSize;
	}
}
void quickSort(int* arr, int l, int r) {
	int mid = *(arr + ((l + r) / 2));
	int i = l, j = r;
	do {
		while (*(arr + i) < mid)i++;
		while (*(arr + j) > mid)j--;
		if (i <= j) {
			int temp = *(arr + i);
			*(arr + i) = *(arr + j);
			*(arr + j) = temp;
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j)quickSort(arr, l, j);
	if (i < r)quickSort(arr, i, r);
}
void sortArray(struct ArrayList** pHead) {
	if (NullCheckout(pHead)) {
		return;
	}
	quickSort((*pHead)->pData, 0, (*pHead)->nowSize - 1);
}
void printfArray(struct ArrayList* pHead) {
	for (int i = 0; i < pHead->nowSize; i++) {
		printf(" id: %d val: %d", i, *(pHead->pData + i));
	}
	printf("\n");
}
int getIndex(struct ArrayList* pHead, int val) {
	if (NullCheckout(&pHead)) {
		return -1;
	}
	else {
		int* arr = pHead->pData;
		for (int i = 0; i < pHead->nowSize; i++) {
			if (*(arr + i) == val) {
				return i;
			}
		}
		return -1;
	}
}
int Supplement_LocateElem(struct ArrayList** pHead, int other, bool(*untity_Compare)(int, int)) {
	if (NullCheckout(pHead)) {
		return -1;
	}
	else {
		int* arr = (*pHead)->pData;
		for (int i = 0; i < (*pHead)->nowSize; i++) {
			if (untity_Compare(*(arr + i), other)) {
				return i;
			}
		}
		return -1;
	
	
	
	}



}
bool Supplement_ListTraverse(struct ArrayList** pHead, void (*untity_Add)(int*, int)) {
	if (NullCheckout(pHead)) {
		return false;
	}else {
		untity_Add((*pHead)->pData,(*pHead)->nowSize);
		return true;
	}

}
void unionList(struct ArrayList** pHead, struct ArrayList* ListB) {
	if (NullCheckout(&ListB)|| ListEmpty(ListB)) {
		return;
	}
	if (NullCheckout(pHead)) {
		InitList(pHead);
		unionList(pHead,ListB);
	}
	else {
		int* arr = ListB->pData;
		for (int i = 0; i < ListB->nowSize; i++) {
			if (getIndex(*pHead, *(arr + i)) == -1) {
				addArray(pHead, *(arr + i));
			}
		}
	}
}
void MergeList(struct ArrayList** La, struct ArrayList** Lb, struct ArrayList** Lc) {
	if (NullCheckout(La) || NullCheckout(Lb) || NullCheckout(Lc)) {
		return;
	}
	else {
		int lenA = (*La)->nowSize;
		int lenB = (*Lb)->nowSize;
		InitList(Lc);
		int a = 0;
		int b = 0;
		while (a< lenA&&b<lenB){
			if (getElement(*La, a) >= getElement(*Lb, b)) {
				addArray(Lc, getElement(*La, a++));
			}
			else {
				addArray(Lc, getElement(*Lb, b++));
			}

		}
		while (a < lenA) {
			addArray(Lc, getElement(*La, a++));
		}
		while (b < lenB) {
			addArray(Lc, getElement(*Lb, b++));
		}
	
	}





}
void deleteAllVal(struct ArrayList** pHead,int val);
void deleteAllVal(struct ArrayList** pHead, int val) {
	if (ListEmpty(*pHead)) {
		return;
	}
	else {
		int write = 0;
		for (int i = 0; i < (*pHead)->nowSize; i++) {
			if (*((*pHead)->pData + i) != val) {
				*((*pHead)->pData + write) = *((*pHead)->pData + i);
				write++;
			}
		}
		(*pHead)->nowSize = write;
	}



}

