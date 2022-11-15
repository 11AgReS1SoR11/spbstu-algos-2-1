#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba1.h"

/*
* ������� ���������� ����� ������
*/
int LEN(char* a) {
	int i = 0;
	while (a[i++] != '\0');
	return --i;
}

/*
* ������� ��������� �� ����� �� ��������� ������ ��������� NULL (������ �� ������)
*/
int isEmpty(Listptr sPtr) {
	return sPtr == NULL;
}

/*
* ������� ��� ����� ������ (������� � �������, ������� �� ���������)
* ���� ������ ����, �� ������� ��������� �� ������
*/
void PrintList(Listptr currentPtr) {
	if (isEmpty(currentPtr)) {
		puts("List is empty.");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			printf("%s\n", currentPtr->a);
			currentPtr = currentPtr->next;
		}
	}
}

/*
* �������, ������� ���������� 1 � ������, ���� ������ ������ ������ � ������������������ �������
* ����� 0
* �����! ���������� ������ ������ ������ �����
*/
int comp(char* first, char* second, int length) {
	for (int i = 0; i < length; i++) {
		if (first[i] < second[i]) return 1;
		if (first[i] > second[i]) return 0;
	}
	return 0;
}

/*
* ������� ������� ������ ���� � ������
* ������� ���������� ����� � ������ ���� ������� � ������ �������:
* � ������� ������������ �����, � � ������ ��������� ���� � ��������� �������
*/
void Insert(char* a, int length, Listptr* Ptr) {
	Listptr new, prev, cur;

	new = (Listptr)malloc(sizeof(List));
	if (new == NULL) printf("No memory avaible.\n");
	else {
		new->a = a;
		new->length = length;
		new->next = NULL;

		prev = NULL;
		cur = *Ptr;
		while (cur != NULL && length > cur->length)  // �������� �� �����
		{
			prev = cur;
			cur = cur->next;
		}

		while ((cur != NULL) && (!comp(a, cur->a, length)) && (length == cur->length)) // �������� �� �������
		{
			prev = cur;
			cur = cur->next;
		}

		if (prev == NULL) {
			new->next = *Ptr;
			*Ptr = new;
		}
		else {
			prev->next = new;
			new->next = cur;
		}
	}
}


/*
* ������ ����� ������
*/
void FIRST(Listptr currentPtr) {
	int N;
	printf("������� N � ��� ��������� ����� > N: ");
	scanf("%d", &N);
	while (currentPtr != NULL) {
		if (currentPtr->length > N) printf("%s\n", currentPtr->a);
		currentPtr = currentPtr->next;
	}
}

/*
* ������ ����� ������
*/
void SECOND(Listptr currentPtr) {
	int N;
	printf("������� N � ��� ��������� ����� = N: ");
	scanf("%d", &N);
	while (currentPtr != NULL && currentPtr->length <= N) {
		if (currentPtr->length == N) printf("%s\n", currentPtr->a);
		currentPtr = currentPtr->next;
	}
}

/*
* ������� ���������� �� �����, ���������� ������
*/
Listptr ReadText(char const* filename) {
	Listptr start = NULL;
	char* a = (char*)malloc(sizeof(char));
	if (a == NULL) return NULL;
	FILE* f = fopen(filename, "r");
	if (f == NULL) return NULL;
	while (fscanf(f, "%s", a) == 1) {
		Insert(a, LEN(a), &start);
		a = (char*)malloc(sizeof(char));
		if (a == NULL) return NULL;
	}
	fclose(f);
	return start;
}

void list_free(Listptr A) {
	Listptr cur = A;
	Listptr prev = NULL;
	while (cur != NULL)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}