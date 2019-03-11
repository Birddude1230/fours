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
	struct eqn *nhead;
	struct eqn *curr = a;
	while (curr->next != NULL){
		
}

void add_binary(struct eqn *out, struct eqn *a, struct eqn *b){
	pass;
}

void insert(struct eqn i){
    //Insert full equation into the linked list, preserving order
    struct listelem *e = malloc(sizeof(struct listelem));
    mpfr_init2(e->val, prec);
    mpfr_set(e->val, i.eval, rnd);
    e->count = 1;
    e->next = NULL;
    if (head == NULL){
        head = e;
    } else {
        struct listelem *t = head;
        struct listelem *prev;
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
            if(head != t){
                prev->next = e;
            } else {
                head = e;
            }
        }
    }
}
