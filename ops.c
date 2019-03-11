#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpfr.h>

#include "fours.h"

void add_bi_op(char* rep, void(*opfunc)(mpfr_t, mpfr_t, mpfr_t)){
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

void add_un_op(char* rep, void(*opfunc)(mpfr_t)){
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

void func_add(mpfr_t r, mpfr_t a, mpfr_t b){
	mpfr_add(r, a, b, rnd);
}
void func_sub(mpfr_t r, mpfr_t a, mpfr_t b){
	mpfr_sub(r, a, b, rnd);
}
void func_mult(mpfr_t r, mpfr_t a, mpfr_t b){
	mpfr_mul(r, a, b, rnd);
}
void func_div(mpfr_t r, mpfr_t a, mpfr_t b){
	mpfr_div(r, a, b, rnd);
}
void func_neg(mpfr_t a){
	mpfr_neg(a, a, rnd);
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
