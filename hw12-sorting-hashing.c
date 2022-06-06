#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 13	// prime number
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE

int initialize(int **a);  // 배열 생성
int freeArray(int *a); // 배열 해제
void printArray(int *a); // 배열 출력

int selectionSort(int *a); // 선택정렬
int insertionSort(int *a); // 삽입정렬
int bubbleSort(int *a);    // 버블정렬
int shellSort(int *a);     // 셸정렬
int quickSort(int *a, int n);  // 퀵정렬
int hashCode(int key);         // 해시 코드 생성
int hashing(int *a, int **ht); // 배열 a에 대한 hash table 생성
int search(int *ht, int key);  // hash table 에서 key를 찾아 hash table의 인덱스 반환


int main()
{
	char command; 
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
    printf("[----- [노관범] [2020039102] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) {
		case 'z': case 'Z': 
			initialize(&array);
			break;
		case 'q': case 'Q': 
			freeArray(array);
			break;
		case 's': case 'S': 
			selectionSort(array);
			break;
		case 'i': case 'I': 
			insertionSort(array);
			break;
		case 'b': case 'B': 
			bubbleSort(array);
			break;
		case 'l': case 'L': 
			shellSort(array);
			break;
		case 'k': case 'K': 
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);
			break;

		case 'h': case 'H': 
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': 
			printf("Your Key = ");
			scanf("%d", &key); 
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': 
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); 
	return 1;
}


int initialize(int** a) // 배열 생성
{
	int *temp = NULL;
	
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // temp에 int type으로 주소 받기
		*a = temp;  // 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else
		temp = *a; // temp 에 a 안의 주소 삽입

	
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 랜덤값을 배열 값으로 저장
        

	return 0;
}


int freeArray(int *a) // 배열 해제
{
	if(a != NULL) // a가 NULL이 아닐 경우
		free(a); // 해제
	return 0;
}


void printArray(int *a) // 배열 출력
{
	if (a == NULL) { // a가 NULL일 경우
		printf("nothing to print.\n"); // 경고문 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); // 값 출력
	printf("\n");
}


int selectionSort(int *a) // 선택 정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	for (i = 0; i < MAX_ARRAY_SIZE; i++){
		minindex = i; 
		min = a[i]; 
		for(j = i+1; j < MAX_ARRAY_SIZE; j++){
			if (min > a[j]){ 
				min = a[j];
				minindex = j;
			}}
		a[minindex] = a[i];
		a[i] = min; 
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬한  배열 출력
	return 0;
}


int insertionSort(int *a) // 삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	for(i = 1; i < MAX_ARRAY_SIZE; i++){
		t = a[i]; 
		j = i;
		while (a[j-1] > t && j > 0){
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}

int bubbleSort(int *a) // 버블 정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	for(i = 0; i < MAX_ARRAY_SIZE; i++){ // 첫번째 값 부터 마지막 값까지 반복
		for (j = 0; j < MAX_ARRAY_SIZE; j++){
			if (a[j-1] > a[j]){ // 앞의 값이 뒤의 값보다 클 경우
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t; 
			}}}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}


int shellSort(int *a) // 셸 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2){
		for (i = 0; i < h; i++){
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h){
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v){
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}}}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}


int quickSort(int *a, int n) // 퀵 정렬
{
	int v, t;
	int i, j;

	if (n > 1){
		v = a[n-1]; 
		i = -1; // i 를 -1 로
		j = n - 1; // j 에 n-1 삽입
		while(1){
			while(a[++i] < v); // 피봇보다 작은 key값 찾기 
			while(a[--j] > v); // 피봇보다 큰 key값 찾기 
			if (i >= j) break; // i 가 j 이상이면 멈춤
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		quickSort(a, i); // pivot 값 중심으로 왼쪽 재귀적 정렬
		quickSort(a+i+1, n-i-1); // pivot 값 중심으로 오른쪽 재귀적 정렬
	}
	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; 
}

int hashing(int *a, int **ht) // hash table 생성
{
	int *hashtable = NULL; // hash table 이 NULL 이면 할당
	if(*ht == NULL) { // ht 가 NULL 이면
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // hashtable에 int type으로 주소 삽입
		*ht = hashtable; // 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else {
		hashtable = *ht; // hash table 이 NULL 이 아니면
	}
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;



	int key = -1; // key -1 초기화
	int hashcode = -1; // hashcode -1 초기화
	int index = -1; // index -1 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // MAX_ARRAY_SIZE 만큼 실행
	{
		key = a[i];
		hashcode = hashCode(key); // 결과인 hash code 삽입
		if (hashtable[hashcode] == -1){
			hashtable[hashcode] = key;
		} else 	{
			index = hashcode; // index 에 hash code 삽입
			while(hashtable[index] != -1){
				index = (++index) % MAX_HASH_TABLE_SIZE; 
			} hashtable[index] = key; // key 값 삽입
		}} 
	return 0;
}

int search(int *ht, int key) // 인덱스 반환
{
	int index = hashCode(key); // 생성되는 hash code 삽입
	if(ht[index] == key) // ht[index] 값이 key 값과 같으면
		return index; // 반환
	while(ht[++index] != key) // ht[index] 값이 key 값과 같지 않으면
		index = index % MAX_HASH_TABLE_SIZE; 
	return index; // 반환
}