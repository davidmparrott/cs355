/*
David Parrott
11239947
CS 351 hw5 3-SAT in C

This is the ADT for the list.
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
mallocs space for a new list, sets head and tail to be NULL since there are no nodes
associated with it yet, sets length to 0, since there are no nodes yet and returns
it.
*/
List* createList(){
	List* new = (List*)malloc(sizeof(List));
	new->entry = NULL;
	new->next = NULL;
	new->truth = 0;
	return new;
}

/*
checks the length counter of a list and returns 1 (true) if length == 0
else returns 0 (false) if length > 1;
if length is < 0 then it is a corrupted list and -1 is returned.
*/
int isEmpty(List* list){
	if(list->next == NULL && list->entry == NULL){
		return 1;
	}else{
		return 0;
	}
}
/*
a node* and List* are passed into prepend. The next pointer for node is set to the head of
the list, the prev pointer from the head is set to be node, finally, node is set as the 
head of list and list is returned.
*/
List* prepend(List* new, List* list){
	new->next = list;
	return new;
}

/*
a Node* and List* are passed into append. node.prev is set to the last node in the list,
the next pointer for the last node is set to node and the last pointer is update to node
before list is returned.
*/
List* append(List* new, List* list){
	if(list->next == NULL){
		list->next = new;
		return list;
	}
	List* temp = list;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new;
	return list;
}

/*
returns the first node in a list
*/
List* head(List* list){
	List* newL = createList();
	newL->entry = list->entry;
	newL->next = NULL;
	newL->truth = list->truth;
	return newL;
}

/*
chops off the head node by moving the head pointer to head.next then setting the prev 
pointer for the new head to be NULL and returning the shortened list
*/
List* tail(List* list){
	List* newL = createList();
	newL->next = (list->next)->next;
	newL->truth = (list->next)->truth;
	newL->entry = (list->next)->entry;
	return newL;
}

/*
returns an int length cached in the list struct
*/
int length(List* list){
	int length = 0;
	if(list->next == NULL && list->entry == NULL){
		return length;
	}else{
		List* temp = list;
		while(temp->next != NULL){
			temp = temp->next;
			length++;
		}
	}
	return length;
}

/*
assumption is that you are inserting a new node after the node specified by location.
prev pointer from location.next is updated to new, new.next is updated to location.next,
location.next is updated to point to new and new.prev is updated to point to location.

The list containing these nodes must also have it's length updated.
*/
void insert(List* newL, int location, List* list){
	if(location == 0){
		newL->next = list;
		list = newL;
		return;
	}
	int i = 0;
	while(i < (location - 1) && list->next != NULL){
		list = list->next;
		i++;
	}
	newL->next = list->next;
	list->next = newL;
}
/*
removes a node from a list by updating pointers from the previous and next nodes to 
'skip over' the node passed. A pointed to the list containing these nodes must be
included to update the length of the list.
*/
void Remove(int location, List* list){
	if(location == 0){
		*list = *list->next;
		return;
	}
	int i = 0;
	while(i < location && list->next != NULL){
		list = list->next;
		i++;
	}
	*list = *list->next;
}

/*
walks the list a number of steps specified in location. Checks to ensure i does
not walk past the end of the list. Returns the node at the specified location.
*/
List* retreive(int location, List* list){
	if(location == 0){return list;}
	List* temp = list;
	int i = 0;
	while(i < location && temp->next != NULL){
		temp = temp->next;
		i++;
	}
	return temp;
}
/*
int main(){
	List* list = createList();
	list->entry = "A";
	list->truth = 1;
	List* temp = retreive(0, list);
	printf("%s\n", temp->entry);
	printf("%i\n", temp->truth);

	for(int i = 1; i < 10; i++){
		List* newL = createList();
		newL->entry = "test";
		newL->truth = i;
		append(newL, list);
	}
	printf("length: %i\n", length(list));
	temp = retreive(5, list);
	printf("value at 5: %i\n", temp->truth);
	Remove(5, list);
	temp = retreive(5, list);
	printf("value at 5: %i\n", temp->truth);
	Remove(5, list);
	temp = retreive(5, list);
	printf("value at 5: %i\n", temp->truth);
	int i = 0;
	while(i < length(list)){
		temp = retreive(i,list);
		printf("value at %i: %i\n", i, temp->truth);
		i++;
	}
	List* insertL = createList();
	insertL->truth = 999;
	printf("   %i\n",insertL->truth);
	insert(insertL, length(list), list);
	temp = retreive(length(list) - 1, list);
	printf("list length: %i\n", length(list));
	printf("value of insertL: %i\n", temp->truth);

	return 0;
}*/