#include <stdio.h>
#include <stdlib.h>

typedef struct List{
	void* entry;
	struct List* next;
	int truth;
}List;

List* createList();
int isEmpty(List* list);
List* prepend(List* new, List* list);
List* append(List* new, List* list);
List* head(List* list);
List* tail(List* list);
int length(List* list);
void insert(List* newL, int location, List* list);
void Remove(int location, List* list);
List* retreive(int location, List* list);