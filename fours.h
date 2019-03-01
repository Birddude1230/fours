#ifndef FOURS_H
#define FOURS_H
#include <stdlib.h>
#include <stdio.h>
#include <mpfr.h>

#define MAX_OP_STR 32
#define MAX_EQN_SIZE 256
#define PRECISION 64

mpfr_rnd_t rnd = MPFR_RNDN;
mpfr_prec_t prec = PRECISION;

typedef struct bi_op{
	char rep[MAX_OP_STR];
	void (*opfunc)(mpfr_t, mpfr_t, mpfr_t);
	struct bi_op* next;
} biop;

biop* bi_head;

typedef struct un_op{
	char rep[MAX_OP_STR];
	void (*opfunc)(mpfr_t);
	struct un_op* next;
} unop;

unop* un_head;

struct eqn {
	char rep[MAX_EQN_SIZE];
	mpfr_t eval;
	unsigned char *exc;
};

struct agg_ele {
	mpfr_t val;
	int count;
	struct agg_ele *next;
};

struct agg_ele *agg_list;

#endif /* FOURS_H */
