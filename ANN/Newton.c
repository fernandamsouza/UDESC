#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float func (float x);
float deriv (float x);

int main () {
	float fpn,fdpn,raiz,pn;
	printf ("Qual eh o x inicial?\n");
	scanf ("%f", &pn);
	int i=0;
	while (i!=7) {
		fpn = func(pn);
		fdpn = deriv(pn);
		raiz = pn - (fpn/(fdpn));
		i++;
		printf ("n= %d // Raiz = %f\n",i, raiz);
		pn = raiz;
	}
		return 0;
}

float func (float x) {
	float eq;
	eq = pow(x,2) - 2;
	return eq;
}

float deriv (float x) {
	float eq;
	eq = 2*x;
	return eq;
}
