int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

{
    int i,j,resultado;

    print("Digite o valor de a:");
    read(i);
    print("Digite o valor de b:");
    read(j);

    print("Resultado:");
    resultado = max(i,j);
    print(resultado);
}
