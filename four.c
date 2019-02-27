#include <stdio.h>
#include <stdlib.h>
#include "ops.c"

#define MAX_EQN_SIZE 255
#define ERR_OVERSIZE -9999
#define ERR_ZDIV -9998

struct eqn {
	//Stores all or part of an formula, as well as its value
	char rep[MAX_EQN_SIZE]; //((4) + (4)) + ((4) + (4))
	int eval;
};

struct listelem {
	//The linked list link used for counting equal formulas
	int val;
	int count;
	struct listelem *next;
};

struct listelem *head;



void insert(struct eqn i){
	//Insert full equation into the linked list, preserving order
	struct listelem *e = malloc(sizeof(struct listelem));
	e->val = i.eval;
	e->count = 1;
	e->next = NULL;
	if (head == NULL){
		head = e;
	} else {
		struct listelem *t = head;
		struct listelem *prev;
		while (t->val < i.eval && t->next != NULL){
			prev = t;
			t = t->next;
		}
		if (t-> val < i.eval){
			t->next = e;
		} else if (t->val == i.eval){
			free(e);
			t->count++;
		} else {
			e->next = t;
			if(head != t){
				prev->next = e;
			} else {
				head = e;
			}
		}
	}
}

void printlist(){
	//Walk and print the linked list
	struct listelem *t = head;
	int ct = 0;
	printf("value\t:ways to make it\n");
	while(t != NULL){
		ct += t->count;
		printf("%d\t:%d\n", t->val, t->count);
		t = t->next;
	}
	printf("Total\t:%d\n", ct);
}

int merge(struct eqn a, struct eqn b, struct eqn *o){
	//Given two formulas, output an array of new formulas
	//These formulas are formed by joining the subformulas with operators
	sprintf(o -> rep, "(%s) + (%s)", a.rep, b.rep);
	o -> eval = a.eval + b.eval;
	sprintf(o[1].rep, "(%s) - (%s)", a.rep, b.rep);
	o[1].eval = a.eval - b.eval;
	sprintf(o[2].rep, "(%s) / (%s)", a.rep, b.rep);
	if(b.eval != 0) {
		o[2].eval = a.eval / b.eval;
	} else {
		o[2].eval = -999999;
	}
	sprintf(o[3].rep, "(%s) * (%s)", a.rep, b.rep);
	o[3].eval = a.eval * b.eval;
	return 4;
}

int main(int argc, char **argv){
	//Build the possible equations
	struct eqn o[4];
	struct eqn a;
	a.rep[0] = '4'; a.rep[1] = '\0';
	a.eval = 4;
	merge(a, a, o);
	//o now contains all equations with two fours in them
	struct eqn z[4][4][4];
	//z[a][b][c] is the cth element of the list of combinations of elements of o at index a and b
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			merge(o[i], o[j], z[i][j]);
			for (int k=0; k<4; k++){
				insert(z[i][j][k]);
				printf("%s = %d\n", z[i][j][k].rep, z[i][j][k].eval);
			}
		}
	}
	struct eqn x[4][4];
	//x[a][b] is the bth element of the list of combinations of o[a] and another 4
	struct eqn y[4][4][4];
	//y stores combinations of x with a fourth four
	for (int i=0; i<4; i++){
		merge(o[i], a, x[i]);
		for (int j=0; j<4; j++){
			merge(x[i][j], a, y[i][j]);
			for (int k=0; k<4; k++){
				insert(y[i][j][k]);
				printf("%s = %d\n", y[i][j][k].rep, y[i][j][k].eval);
			}
		}
	}
	printlist();
}
