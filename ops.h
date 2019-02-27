#define MAX_OP_STR 32

typedef struct bi_op{
	char rep[MAX_OP_STR];
	float (*opfunc)(float, float);
	struct bi_op* next;
} biop;

biop* bi_head;

typedef struct un_op{
	char rep[MAX_OP_STR];
	float (*opfunc)(float);
	struct un_op* next;
} unop;

unop* un_head;
