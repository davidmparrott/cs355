#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

int MAX_WORD_SIZE = 255;
char* 	readStates( FILE *fd );
char* 	readClauses( FILE *fd );
char* 	getNextWord(FILE *fd);
int 	evalVar(List* state, char* var);
int 	evalClause(List* clause, List* state);
void 	getVars(List* clause);
List* 	getAllVars(List* clauses);

/*
takes a list of states and a char* that is a variable we want to return the truth value for.
If the variable is not found in the list of states -1 is returned.
*/
int evalVar(List* state, char* var){
	while(state->next != NULL){								//walk the list until the end
		if(strcmp(var, state->entry) == 0){return state->truth;}
		else{state = state->next;}
	}
	return(-1);												//if not found return -1
}
/*
takes a list of clauses and states, OR's the truth values of the clauses and returns
Assumptions:
each clausesList is assumed to be exactly three members long
truth values for states and clauses are stored as 1 for TRUE and 0 for FALSE
*/
int evalClause(List* clause, List* state){
	List* x;												//separate list into discrete items											
	List* y;
	List* z;
	x = clause;
	y = x->next;
	z = y->next;
															//OR truth values
	return((x->truth == evalVar(state, x->entry)) || (y->truth == evalVar(state, y->entry)) || (z->truth == evalVar(state, z->entry)));
}

void getVars(List* clause){
	printf("(");
	while(clause->next != NULL){
		printf("%s ", clause->entry);
		clause = clause->next;
	}
	printf("%s",clause->entry);
	printf(")\n");
}

int isIn(char* var, List* clause){
	while(clause->next != NULL){
		if(strcmp(var, clause->entry) == 0){
			return 1;
		}else{
			clause = clause->next;
		}
	}
	return 0;
}

List* getAllVars(List* clauses){
	List* new = createList();
	while(clauses->next != NULL){
		if(isIn(clauses->entry, new) == 1){
			continue;
		}else{
			append(new, clauses);
		}
	}
	return new;
}

List* unsatClauses(List* clauses, List* state){
	List* x;												//separate list into discrete items											
	List* y;
	List* z;
	x = clauses;
	y = x->next;
	z = y->next;

	List* new = createList();
	while(x != NULL){
		printf("1\n");
		if( (x->truth == evalVar(state, x->entry)) || (y->truth == evalVar(state, y->entry)) || (z->truth == evalVar(state, z->entry))){
			append(new, x);
		}
		x = z->next;
	}
	return new;	
}

char* readStates( FILE *fd ) {
  int j = 0;
  char c;
  while ( ( c = fgetc( fd ) ) != EOF ){
	if ( isspace( c ) ) {
      continue;
    }
    if ( isalnum ( c ) ) {

      return (char*) strdup(&c);
  	}
  }
  return NULL;
}


char* readClauses(FILE *fd){
  char string[MAX_WORD_SIZE];
  char c;
  int j = 0;
  while((c = fgetc(fd)) != EOF){
  	if(!isalpha(c)){
  		continue;
  	}
  }
  return NULL;
}
/*
begin code written by Dr. Lang
*/
char* getNextWord(FILE* fd) {
	char ch;								/* holds current character */
	char wordBuffer[MAX_WORD_SIZE];			/* buffer for build a word */
	int putChar = 0;						/* current pos in buffer   */

	//assert(fd != NULL);		/* the file descriptor better not be NULL */

	/* read characters until we find an alphabetic one (or an EOF) */
	while ((ch = fgetc(fd)) != EOF) {
		if (isalpha(ch)) break;
	}
	if (ch == EOF) return NULL;		/* if we hit an EOF, we're done */

	/* otherwise, we have found the first character of the next word */
	wordBuffer[putChar++] = ch;

	/* loop, getting more characters (unless there's an EOF) */
	while ((ch = fgetc(fd)) != EOF) {
		/* the word is ended if we encounter whitespace */
		/* or if we run out of room in the buffer       */
		if (isspace(ch) || putChar >= MAX_WORD_SIZE - 1) break;

		/* otherwise, copy the (lowercase) character into the word   */
		/* but only if it is alphanumeric, thus dropping punctuation */
		if (isalnum(ch)) {
			wordBuffer[putChar++] = ch;
		}
	}

	wordBuffer[putChar] = '\0';		/* terminate the word          */
	return strdup(wordBuffer); 	/* re-allocate it off the heap */
}


int main(int argc, char** argv){
/*
declare storag containers used in building lists
*/	
	char* buff = NULL;
	char** list[1000];
/*
Begin building list of states.
Assumptions: file containing list of states is passed in as first argument from command line
states are passed as a list of pairs ie (A T)(B F) there can be whitespace or a non-alphanumeric
character separating the variable from the truth value associated with it or both. 

If the file can not be opened, exit with -1
Store variables and truth values in a string buffer, list. When creating list entries we alternate
between assuming a string is a variable name and assuming it is a truth value. Any assumed truth
value that is not "T" is stored as 0 for false.
*/	
	FILE *file = fopen( argv[1], "r" );
    if ( file == 0 ) {										//error checking
	  printf ( "Could not open file\n" );
	  exit (-1);
    }
    int i = 0;

    while((buff = getNextWord(file)) != NULL){				//store tokens in string array
    	list[i] = buff;
    	i++;
	}

	List* state = createList();								//create list of states
/*
first entry is set outside of for loop so that append can be used on a non-empty
list entry.
*/
	state->entry = list[0];
	if(!strcmp(list[1], "T")){
		state->truth = 1;
	}else{
		state->truth = 0;
	}
	
	for(int j = 2; j < i; j++){								//add all entries to stateList
		List* new = createList();
		new->entry = list[j];
		char* truth = list[j+1];							//every other entry is assumed to represent a truch value
		if(!strcmp(truth, "T")){
			new->truth = 1;
		}else{
			new->truth = 0;
		}
		append(new, state);									//append to list
		j++;												//j must be incremented twice each time through
	}

/*
display list of states and associated truth values
*/
/*
	for(int j = 0; j < (i/2); j++){
		List* new;
		new = retreive(j, stateList);
		printf("%s : %i\n", new->entry, new->truth);
	}
*/
/*
Begin building list of clauses.
Assumptions: file containing list of clauses is passed as second argument from the command line.

If the file can not be opened, exit with -1.
Similarly to when we build our list of states we begin by reading everything from the clause file
into an array of strings. If a negation is detected "NOT" the truth value associated with the variable
that immediately follows it will be 0, else it will be 1. In this manner we can reuse the same list 
node structure for for the states and clauses while not have to make the list nodes overly generic
in the first place.
*/
	file = fopen( argv[2], "r" );
    if ( file == 0 ) {										//error checking
	  printf ( "Could not open file\n" );
	  exit (-1);
    }
    
    i = 0;													//set i back to 0
    
    while((buff = getNextWord(file)) != NULL){				//read tokens into string array
    	list[i] = buff;
    	i++;
	}

	List* clause = createList();							//create causeList

	int j = 0;
	int nots = i;											//track how many "NOT" tokens are seen
	if(strcmp(list[j], "NOT") == 0){						//manually set first entry
		clause->truth = 0;
		j++;
		nots--;
	}else{
		clause->truth = 1;
	}
	clause->entry = list[j];
	j++;

	for(; j < i; j++){										//append remainder of list entries
		List* new = createList();
		if(strcmp(list[j], "NOT") == 0){
			new->truth = 0;
			j++;
			nots--;
		}else{
			new->truth = 1;
		}
		new->entry = list[j];
		append(new, clause);
	}
/*
display list of clauses and associated truth values
*/
/*
	for(int j = 0; j < nots; j++){							
		List* new;
		new = retreive(j, clauseList);
		printf("%s : %i\n", new->entry, new->truth);
	}
*/
	char* ch = "A";
	printf("A : %i\n",evalVar(state, ch));
	printf("(A (NOT B) C) : %i\n", evalClause(clause, state));

	getVars(clause);
	List* T = getAllVars(clause);
	int L = length(T);
	j = 0;
	while(j < L){
		printf("%s ", T->entry);
		j++;
	}
	List* unsat = unsatClauses(clause, state);

}

