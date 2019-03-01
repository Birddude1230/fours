#include "fours.h"

void add_unary(struct eqn *out, struct eqn *a){
	pass;
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
