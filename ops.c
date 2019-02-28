#include <string.h>
#include "fours.h"

void add_bi_op(char* rep, float(*opfunc)(float, float)){
	biop *nop = malloc(sizeof(biop));
	if (nop == NULL){
		perror("Malloc");
	}
	strncpy(nop->rep, rep, MAX_OP_STR-1);
	nop->rep[MAX_OP_STR] = '\0';
	nop->opfunc = opfunc;
	nop->next = NULL;
	if (bi_head == NULL){
		bi_head = nop;
	} else {
		biop *curr = bi_head;
		while (curr->next != NULL){
			curr = curr->next;
		}
		curr->next = nop;
	}
}

void add_un_op(char* rep, float(*opfunc)(float)){
	unop *nop = malloc(sizeof(unop));
	if (nop == NULL){
		perror("Malloc");
	}
	strncpy(nop->rep, rep, MAX_OP_STR-1);
	nop->rep[MAX_OP_STR] = '\0';
	nop->opfunc = opfunc;
	nop->next = NULL;
	if (un_head == NULL){
		un_head = nop;
	} else {
		unop *curr = un_head;
		while (curr->next != NULL){
			curr = curr->next;
		}
		curr->next = nop;
	}
}

float func_add(float a, float b){
	return a + b;
}
float func_sub(float a, float b){
	return a - b;
}
float func_mult(float a, float b){
	return a * b;
}
float func_div(float a, float b){
	return a / b;
}
float func_neg(float a){
	return -a;
}

void load_ops(char *subs){
	if (strchr(subs, '+') != NULL){
		add_bi_op("(%s) + (%s)", &func_add);
	}
	if (strchr(subs, '-') != NULL){
		add_bi_op("(%s) - (%s)", &func_sub);
	}
	if (strchr(subs, '*') != NULL){
		add_bi_op("(%s) * (%s)", &func_mult);
	}
	if (strchr(subs, '/') != NULL){
		add_bi_op("(%s) / (%s)", &func_div);
	}
	if (strchr(subs, 'n') !=NULL){
		add_un_op("(-%s)", &func_neg);
	}
}
