#include <stdio.h>

// Transformam numarul din zecimal in binar
void dinZecimalInBinar(unsigned int x, int nrBytes, int b[50])
{
    // Introducerea in vector a tuturor bitilor
    for(int i = nrBytes*8 - 1; i >= 0; i--)
        b[nrBytes*8 - 1 - i] = ((1 << i) & x) != 0;
}

int main()
{
    unsigned int x;
    scanf("%u", &x);
    int nrBytes = sizeof(unsigned int);
    int b[32] = {0};
    dinZecimalInBinar(x, nrBytes, b);

    // Gasim si afisam N
    int N = 0;
    for(int i = 0; i <= 2; i++)
        if(b[i] == 1)
            N = N | (1 << (2-i));
    N += 1;
    printf("%d ", N);

    // Convertim in +, -, /, * si afisam
    for(int i = 3; i < 3+N*2; i+=2)
    {
        if(b[i] == 0 && b[i+1] == 0)
            printf("+ ");
        else if(b[i] == 0 && b[i+1] == 1)
            printf("- ");
        else if(b[i] == 1 && b[i+1] == 0)
            printf("* ");
        else if(b[i] == 1 && b[i+1] == 1)
            printf("/ ");
    }

    // Gasim dimensiunea si o afisam
    int dim = 0;
    for(int i = 3+N*2; i <= 6+N*2; i++)
        if(b[i] == 1)
            dim = dim | (1 << (6+N*2 - i));
    dim += 1;
    printf("%d\n", dim);

    return 0;
}