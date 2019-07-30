#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float pf(float a, float b, float erro);
float func(float x);

int main()
{
    float a,b,erro,raiz;
    printf("Digite o valor de a:");
    scanf("%f",&a);
    printf("Digite o valor de b:");
    scanf("%f",&b);
    printf("Digite o valor do erro:");
    scanf("%f",&erro);
    raiz = pf(a,b,erro);
    printf("A raiz eh = %0.3f \n",raiz);
    return 0;
}

float func(float x)
{
    float eq;
    eq = pow(x,2) - 2;
    return eq;
}

float pf(float a, float b, float erro)
{
    float fa,fb,raiz,fraiz;
    fa=func(a);
    fb=func(b);
    raiz = (b*func(a)-func(b)*a)/(func(a)-func(b));
    fraiz=func(raiz);
    while(func(raiz)>erro)
    {
        raiz = (b*func(a)-func(b)*a)/(func(a)-func(b));
        fraiz=func(raiz);
        if(fa*fraiz<0)
        {
            b=raiz;
            fb=fraiz;
        }
        else
        {
            a=raiz;
            fa=fraiz;
        }
    }

    return raiz;
}
