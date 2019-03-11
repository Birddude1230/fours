#include <argp.h>

#include "fours.h"
#include "ops.c"
#include "proc.c"

const char *prog_ver = "fours 0.0";
static char doc[] = "A bruteforcer for the generalized fours problem";

static struct argp_option options[] = {
	{"input", 'i', "INPUT", 0, "Specify starting numbers as CSV"},
	{"ops", 'o', "OPS", 0, "Specify allowed operators via a string of operator symbols"},
	{"precision", 'p', "BITS", 0, "Specify the precision, in bits, of equation values (default: PRECISION)"},
	{"hide-eqns", 'E', 0, 0, "Do not display the list of equations"},
	{"hide-vals", 'V', 0, 0, "Do not display the list of values and equation counts"},
	{0}
}

struct arguments {
	int heq, hval;
	char *input, ops, prec;
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
		case 'i':
			arguments->input = arg;
			break;
		case 'o':
			arguments->ops = arg;
			break;
		case 'p':
			prec = strtol(arg, NULL, 10);
			break;
		default:
			fprinf(stderr, "Unknown option %c! Use --help for help.\n");
			exit(1);
	}
	return 0;
}

static struct argp argp = {options, parse_opt, 0, doc};

void printlist(struct eqn *ceq){
	while (ceq != NULL){
		mpfr_printf("%.2f=\t%s", ceq->eval, ceq->rep);
		ceq = ceq -> next;
	}
}

void aggregate(){
	//Walk and print the linked list
	struct agg_ele *t = agg_list;
	int ct = 0;
	printf("value\t:ways to make it\n");
	while(t != NULL){
		ct += t->count;
		mpfr_printf("%.2f\t:%d\n", t->val, t->count);
		t = t->next;
	}
	printf("Total\t:%d\n", ct);
}

int main(int argc, char **argv){
	struct arguments arguments;
	arguments.heq = 0;
	arguments.hval = 0;
	arguments.input = "4";
	arguments.ops = "+-/*n";
	arguments.prec = PRECISION;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	load_ops(arguments.ops);
	//Initialize the one-value equations
	char *valoc = arguments.input;
	char *ctr = valoc;
	int nvals = 0;

	do {
		nvals += 1;
		ctr = strchr(',', ctr);
		
	} while (ctr != NULL);
	
	sig_bytes = nvals/8 + 1
`
	struct eqn *eqnh;
	struct eqn *res[nvals];

	for (int i=0;i<nvals;i++){
		struct eqn neq;
		mpfr_init2(neq.eval, prec)
		mpfr_strtofr(neq.eval, valoc, &valoc, 10, rnd);
		unsigned char exc[sig_bytes];
		for (int j=0;j<sig_bytes; j++){
			exc[j] = 0;
		}
		exc[i/8] = 1 << (i % 8);
		sprintf(neq.rep, "%d", vals[i]);
		neq.rep[MAX_EQN_SIZE-1] = '\0';
		neq.next = eqnh;
		eqnh = &neq;
		res[i] = struct eqn *a;
	}
	res[0] = eqnh;

	//Combine equations to get all equations
	for (int i=0;i<nvals;i++){
		add_unary(res[i], res[i]);
		for (int j=0;j<=i;j++){
			add_binary(res[i], res[j], res[i-j]);
		}
	}	
	printlist(res[nvals-1]);
}
