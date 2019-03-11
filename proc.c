#include <stdlib.h>
#include <stdio.h>
#include <mpfr.h>

#include "fours.h"

int check_exclusive(struct eqn *a, struct eqn *b){
	for (int i=0;i<sig_bytes;i++){
		if (a->exc[i] & b->exc[i]){
			return 1;
		}
	}
	return 0;
}

void add_unary(struct eqn *out, struct eqn *a){
	//for i in list at a
	//apply each op and append new
	struct eqn *curr = a;
	while (curr->next != NULL){
		unop *cop = un_head;
		if (cop == NULL){
			break;
		}
		while (cop != NULL){
			struct eqn *neweq = malloc(sizeof(struct eqn));
			neweq->exc = malloc(sizeof(char)*sig_bytes);
			for (int i=0;i<sig_bytes;i++){
				neweq->exc[i] = curr->exc[i];
			}
			snprintf(neweq->rep, MAX_EQN_SIZE, cop->rep, curr->rep);
			mpfr_init_set(neweq->eval, curr->eval, rnd);
			cop->opfunc(neweq->eval);
			neweq->next = out;
			out = neweq;
		}
	}
}

void add_binary(struct eqn *out, struct eqn *a, struct eqn *b){
	struct eqn *curr = a;
	while (curr != NULL){
		struct eqn *other = b;
		while (other != NULL){
			biop *cop = bi_head;
			if (cop == NULL){
				break;
			}
			while (cop != NULL){
				struct eqn *neweq = malloc(sizeof(struct eqn));
				neweq->exc = malloc(sizeof(char)*sig_bytes);
				for (int i=0;i<sig_bytes;i++){
					neweq->exc[i] = curr->exc[i];
				}
				snprintf(neweq->rep, MAX_EQN_SIZE, cop->rep, curr->rep);
				printf("%s", neweq->rep);
				mpfr_init_set(neweq->eval, curr->eval, rnd);
				cop->opfunc(neweq->eval, curr->eval, other->eval);
				neweq->next = out;
				out = neweq;
				cop = cop->next;
			}
		other = other->next;
		}
	curr = curr->next;
	}
}

void insert(struct eqn i){
    //Insert full equation into the linked list, preserving order
    struct agg_ele *e = malloc(sizeof(struct agg_ele));
    mpfr_init2(e->val, prec);
    mpfr_set(e->val, i.eval, rnd);
    e->count = 1;
    e->next = NULL;
    if (agg_list == NULL){
        agg_list = e;
    } else {
        struct agg_ele *t = agg_list;
        struct agg_ele *prev;
        while (mpfr_less_p(t->val, i.eval) && t->next != NULL){
            prev = t;
            t = t->next;
        }
        if (mpfr_less_p(t-> val, i.eval)){
            t->next = e;
        } else if (mpfr_equal_p(t->val, i.eval)){
            free(e);
            t->count++;
        } else {
            e->next = t;
            if(agg_list != t){
                prev->next = e;
            } else {
                agg_list = e;
            }
        }
    }
}
