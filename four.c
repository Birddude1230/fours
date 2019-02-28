#include <stdio.h>
#include <stdlib.h>
#include <stderr.h>
#include <argp.h>
#include "ops.c"

#define MAX_EQN_SIZE 256
#define PRECISION 50

mpfr_prec_t prec = PRECISION;

const char *prog_ver = "fours 0.0";
static char doc[] = "A bruteforcer for the generalized fours problem";

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

static struct argp_option options[] = {
	{"square", 's', 0, 0, "Repeats the first input number that many times (e.x., four fours). Not functional without the input option"},
	{"input", 'i', "INPUT", 0, "Specify starting numbers as CSV"},
	{"ops", 'o', "OPS", 0, "Specify allowed operators via a string of operator symbols"},
	{"hide-eqns", 'E', 0, 0, "Do not display the list of equations"},
	{"hide-vals", 'V', 0, 0, "Do not display the list of values and equation counts"},
	{0}
}

struct arguments {
	int square, heq, hval;
	char *input, ops;
}

static error_t parse_opt(int key, char *arg, struct argp_state *state){
	struct arguments *arguments = state->input;
	switch (key) {
		case 'E':
			arguments->heq = 1;
			break;
		case 'V':
			arguments->hval = 1;
			break;
		case 's':
			arguments->square = 1;
			break;
		case 'i':
			arguments->input = arg;
			break;
		case 'o':
			argument->ops = arg;
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

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

	char mode;
	int nvals = 0;

	error_t err = argp_parse(argp, argc, argv, NULL, NULL, NULL);
	if (err){fprintf(stderr, "Argument parsing error!\n");exit(1);}
	//Initialize the one-value equations
	for (int i=0;i<nvals;i++){
		struct eqn neq;
		mpfr_init2(neq.eval, prec);
		unsigned char exc[nvals/8 + 1];
		exc[i/8] = 1 << (i % 8);
		sprintf(neq.rep, "%d", vals[i]);
		neq.rep[MAX_EQN_SIZE-1] = '\0';
	}

	//Combine equations to get all equations
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
