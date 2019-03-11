#ifndef FOURS_H
#define FOURS_H
#include <stdio.h>
#include <stdlib.h>
#include </usr/include/mpfr.h>

#define MAX_OP_STR 32
#define MAX_EQN_SIZE 256
#define MAX_INP 64
#define PRECISION 64

mpfr_rnd_t rnd;
mpfr_prec_t prec;

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
	struct eqn *next;
};

struct agg_ele {
	mpfr_t val;
	int count;
	struct agg_ele *next;
};

struct agg_ele *agg_list;

int sig_bytes;

void load_ops(char *);
void add_unary(struct eqn *, struct eqn *);
void add_binary(struct eqn *, struct eqn *, struct eqn *);

#endif /* FOURS_H */
