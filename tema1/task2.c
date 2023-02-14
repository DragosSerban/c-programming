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
    int b[50] = {0};
    dinZecimalInBinar(x, nrBytes, b);

    // Gasim N
    int N = 0;
    for(int i = 0; i <= 2; i++)
        if(b[i] == 1)
            N = N | (1 << (2-i));
    N += 1;

    int operator[10] = {0};
    int k = 0;

    // Convertim in +, -, /, *
    // Codificarea intr-un vector a operanzilor
    for(int i = 3; i < 3+N*2; i+=2)
    {
        if(b[i] == 0 && b[i+1] == 0)
            operator[k] = 0;
        else if(b[i] == 0 && b[i+1] == 1)
            operator[k] = 1;
        else if(b[i] == 1 && b[i+1] == 0)
            operator[k] = 2;
        else if(b[i] == 1 && b[i+1] == 1)
            operator[k] = 3;
        k++;
    }

    // Gasim dimensiunea
    int dim = 0;
    for(int i = 3+N*2; i <= 6+N*2; i++)
        if(b[i] == 1)
            dim = dim | (1 << (6+N*2 - i));
    dim += 1;

    int nrDeIntrodus; // in format integer (numar final)
    float fNrDeIntrodus = (N+1)*dim/16.0; // in format float
    if(fNrDeIntrodus != (int)fNrDeIntrodus)
        nrDeIntrodus = (int)fNrDeIntrodus + 1;
    else nrDeIntrodus = (int)fNrDeIntrodus;

    unsigned short numar[10] = {};
    // Citim numerele din care vor reiesi operanzii:
    for(int i = 0; i < nrDeIntrodus; i++)
        scanf("%hu", &numar[i]);

    unsigned short operand[10] = {0};
    int index = 0;

    for(int i = 0; i < nrDeIntrodus; i++)
    {
        // Transformam numarul numar[i] in binar
        int bit[16] = {};
        int nrBytesShort = sizeof(unsigned short);
        dinZecimalInBinar(numar[i], nrBytesShort, bit);

        // Descompunerea lui numar[i] in 8*nrBytesShort/dim operanzi
        int count = dim;
        int pozitieBit = dim - 1;
        for(int j = 0; j < nrBytesShort*8; j++)
        {
            if(j != count)
            {
                if(bit[j] == 1)
                    operand[index] = operand[index] | (1 << pozitieBit);
                pozitieBit--;
            }
            else if(j == count)
                {
                    count += dim;
                    index++;
                    j--;
                    pozitieBit = dim - 1;
                }
        }
        index++;
    }

    int rezultat = operand[0];
    // Calcularea rezultatului cu ajutorul vectorilor de operanzi si operatii
    for(int i = 0; i < k; i++)
    {
        if(operator[i] == 0)
            rezultat += operand[i+1];
        else if(operator[i] == 1)
            rezultat -= operand[i+1];
        else if(operator[i] == 2)
            rezultat *= operand[i+1];
        else if(operator[i] == 3)
            rezultat /= operand[i+1];
    }

    // Afisarea rezultatului:
    printf("%d\n", rezultat);

    return 0;
}