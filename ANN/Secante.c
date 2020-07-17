#include <stdio.h>
#include <math.h>

int main () {
	float x0,x1,erro,errox,errof,r,fx0,fx1,x2,x;
	printf ("Digite o x0\n");
	scanf ("%f", &x0);
	printf ("Digite o x1\n");
	scanf ("%f", &x1);
	printf ("Digite o erro\n");
	scanf ("%f", &erro);
	errox = erro+1;
	errof = erro+1;
	while ((errox>erro) || (errof>erro)) {
		r++;
		x = x0;
		fx0 = (pow(x,2) - 2);
		x = x1;
		fx1 = (pow(x,2) - 2);
		x2 = (x0*fx1-x1*fx0) / (fx1-fx0);
		errox = abs(x1-x0);
		errof = abs(fx1);
		printf ("\nO x da proxima iteracao eh = %f  \n", x2);
		if ((errox<erro) || (errof<erro)) {
			printf ("A raiz eh: %f\n", x2);
			printf ("Os resultados convergiram em %f", r,"iteracoes\n");
		}
		x0 = x1;
		x1 = x2;
	}
}
