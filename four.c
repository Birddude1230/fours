#include <stdio.h>
#include <stdlib.h>

struct eqn {
	char rep[26]; //((4) + (4)) + ((4) + (4))
	int eval;
	int cnt;
};

int merge(struct eqn a, struct eqn b, struct eqn *o){
	sprintf(o -> rep, "(%s) + (%s)", a.rep, b.rep);
	o -> eval = a.eval + b.eval;
	sprintf(o[1].rep, "(%s) - (%s)", a.rep, b.rep);
	o[1].eval = a.eval - b.eval;
	sprintf(o[2].rep, "(%s) / (%s)", a.rep, b.rep);
	if(b.eval != 0) {
		o[2].eval = a.eval / b.eval;
	} else {
		o[2].eval = -99;
	}
	sprintf(o[3].rep, "(%s) * (%s)", a.rep, b.rep);
	o[3].eval = a.eval * b.eval;
	return 4;
}

int main(int argc, char **argv){
	int count[256];	
	struct eqn o[4];
	struct eqn a;
	struct eqn b;
	struct eqn c;
	struct eqn d;
	a.rep[0] = '4'; a.rep[1] = '\0';
	b.rep[0] = '4'; b.rep[1] = '\0';
	c.rep[0] = '4'; b.rep[1] = '\0';
	d.rep[0] = '4'; b.rep[1] = '\0';
	a.eval = 4;
	b.eval = 4;
	c.eval = 4;
	d.eval = 4;
	merge(a, b, o);
	struct eqn z[4][4][4];
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			merge(o[i], o[j], z[i][j]);
			for (int k=0; k<4; k++){
				printf("%s = %d\n", z[i][j][k].rep, z[i][j][k].eval);
			}
		}
	}
}
