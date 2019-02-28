#include <stdio.h>
#include <stdlib.h>
#include <stderr.h>
#include "ops.c"

#define MAX_EQN_SIZE 256
#define PRECISION 50

mpfr_prec_t prec = PRECISION;

struct eqn {
	//Stores all or part of an formula, as well as its value
	char rep[MAX_EQN_SIZE]; 
	mpfr_t eval;
	unsigned char *exc;
};

struct listelem {
	//The linked list link used for counting equal formulas
	mpfr_t val;
	int count;
	struct listelem *next;
};

struct listelem *head;



void insert(struct eqn i){
	//Insert full equation into the linked list, preserving order
	struct listelem *e = malloc(sizeof(struct listelem));
	mpfr_init2(e->val, prec);
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

int main(int argc, char **argv){
	//Build the possible equations
	char mode;
	int nvals;
	int *vals;
	parse_args(argc, argv, &nvals, &vals, &mode);
	struct eqn *res[nvals];
	for (int i=0;i<nvals;i++){
		struct eqn neq;
		mpfr_init2(neq.eval, prec);
		unsigned char exc[nvals/8 + 1];
		exc[i/8] = 1 << (i % 8);
		sprintf(neq.rep, "%d", vals[i]);
		neq.rep[MAX_EQN_SIZE-1] = '\0';
	}
	for (int i=0;i<nvals;i++){
		add_unary(res[i], res[i]);
		for (int j=0;j<=i;j++){
			if (check_exclusive(res[j], res[i-j])){
				add_binary(res[i], res[j], res[i-j]);
			}
		}
	}	
	printlist();
}
