#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float f(float x);
float bis(float a, float b, float erro);

int main()
{
    float a, b, pm, erro;
    printf("Digite o a: \n ");
    scanf("%f",&a);
    printf("Digite o b: \n");
    scanf("%f",&b);
    printf("Digite o erro: \n");
    scanf("%f",&erro);
    pm=bis(a,b,erro);
    printf("A Raiz eh = %f\n",pm);
    return 0;
}

float func(float x) { 
    float eq;
    eq = pow(x,2)-2;
    return eq;
}

float bis(float a, float b, float erro)
{
    float pm,fpm,fa,fb;
    fa=func(a);
    fb=func(b);
    while((b-a)>erro)
    {
        pm=(a+b)/2;
        fpm=func(pm);
        if(fa*fpm<0)
        {
            b=pm;
            fb=fpm;
        }
        else
        {
            a=pm;
            fa=fpm;
        }
    }
        pm=(a+b)/2;
        return pm;
}
