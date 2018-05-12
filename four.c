#include <stdio.h>
#include <stdlib.h>

struct eqn {
	char rep[26]; //((4) + (4)) + ((4) + (4))
	int eval;
};

struct listelem {
	int val;
	int count;
	struct listelem *next;
};

struct listelem *head;

void insert(struct eqn i){
	struct listelem *e = malloc(sizeof(struct listelem));
	e->val = i.eval;
	e->count = 1;
	e->next = NULL;
	if (head == NULL){
		head = e;
	} else {
		struct listelem *t = head;
		struct listelem *prev;
		while (t->val < i.eval && t->next != NULL){
			prev = t;
			t = t->next;
		}
		if (t-> val < i.eval){
			t->next = e;
		} else if (t->val == i.eval){
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

void printlist(){
	struct listelem *t = head;
	printf("value\t:ways to make it\n");
	while(t != NULL){
		printf("%d\t:%d\n", t->val, t->count);
		t = t->next;
	}
}
int merge(struct eqn a, struct eqn b, struct eqn *o){
	sprintf(o -> rep, "(%s) + (%s)", a.rep, b.rep);
	o -> eval = a.eval + b.eval;
	sprintf(o[1].rep, "(%s) - (%s)", a.rep, b.rep);
	o[1].eval = a.eval - b.eval;
	sprintf(o[2].rep, "(%s) / (%s)", a.rep, b.rep);
	if(b.eval != 0) {
		o[2].eval = a.eval / b.eval;
	} else {
		o[2].eval = -999999;
	}
	sprintf(o[3].rep, "(%s) * (%s)", a.rep, b.rep);
	o[3].eval = a.eval * b.eval;
	return 4;
}

int main(int argc, char **argv){
	struct eqn o[4];
	struct eqn a;
	a.rep[0] = '4'; a.rep[1] = '\0';
	a.eval = 4;
	merge(a, a, o);
	struct eqn z[4][4][4];
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			merge(o[i], o[j], z[i][j]);
			for (int k=0; k<4; k++){
				insert(z[i][j][k]);
				printf("%s = %d\n", z[i][j][k].rep, z[i][j][k].eval);
			}
		}
	}
	struct eqn x[4][4];
	struct eqn y[4][4][4];
	for (int i=0; i<4; i++){
		merge(o[i], a, x[i]);
		for (int j=0; j<4; j++){
			merge(x[i][j], a, y[i][j]);
			for (int k=0; k<4; k++){
				insert(y[i][j][k]);
				printf("%s = %d\n", y[i][j][k].rep, y[i][j][k].eval);
			}
		}
	}
	printlist();
}
