#include <argp.h>

#include "fours.h"
#include "ops.c"
#include "proc.c"

mpfr_prec_t prec = PRECISION;

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
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = {options, parse_opt, 0, doc};

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
	struct arguments arguments;
	arguments.heq = 0;
	arguments.hval = 0;
	arguments.input = "4";
	arguments.ops = "+-/*n";
	arguments.prec = PRECISION;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
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
