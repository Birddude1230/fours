#include <stdio.h>
#include <stdlib.h>

struct eqn {
	char rep[26]; //((4) + (4)) + ((4) + (4))
	int eval;
	int cnt;
};

int merge(struct eqn a, struct eqn b, struct eqn *o){
	o = malloc(sizeof(struct eqn)* 4);
	sprintf(o -> rep, "(%s) + (%s)", a.rep, b.rep);
	o -> eval = a.eval + b.eval;
	sprintf(o[1].rep, "(%s) - (%s)", a.rep, b.rep);
	o[1].eval = a.eval - b.eval;
	sprintf(o[2].rep, "(%s) / (%s)", a.rep, b.rep);
	o[2].eval = a.eval / b.eval;
	sprintf(o[3].rep, "(%s) * (%s)", a.rep, b.rep);
	o[4].eval = a.eval * b.eval;
	return 4;
}

int main(int argc, char **argv){
	int count[256];	
	struct eqn *o;
	struct eqn a;
	struct eqn b;
	a.rep[0] = '4'; a.rep[1] = '\0';
	b.rep[0] = '4'; b.rep[1] = '\0';
	a.eval = 4;
	b.eval = 4;
	merge(a, b, o);
	for(int i=0; i<4; i++){
		printf("%s = %d", o[i]->rep, o[i]->eval);
	}
}
}
