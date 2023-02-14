#include "utils.h"

#define MAX 1000

// Functie pentru nr prim:
int prim(int n) {
    if (n == 0 || n == 1) return 0;
    int ok = 1;
    for (int i = 2; i <= n/2; i++)
        if (n % i == 0) ok = 0;
    if (ok == 1)
        return 1;
    else
        return 0;
}

// Functie pentru palindrom:
int palindrom(int n) {
    int nr = n, oglindit = 0, c = 0;
    while (n != 0) {
        c = n % 10;
        oglindit = 10 * oglindit + c;
        n /= 10;
    }
    if (nr == oglindit)
        return 1;
    else
        return 0;
}

void SolveTask1() {
    // Se citesc datele matricei si se declara pozitia de inceput:
    int N, M, a[MAX][MAX] = {0};
    scanf("%d%d", &N, &M);
    a[0][0] = 1;
    int row = 0, column = 0;
    int path = 1;

    // Pentru apasarea tastei enter:
    char enter[MAX];
    fgets(enter, MAX, stdin);

    // Se citeste stringul propriu-zis:
    char str[MAX];
    fgets(str, MAX, stdin);

    unsigned int length = strlen(str);
    // Eliminarea caracterului '\n':
    if (str[length - 1] == '\n')
        str[length - 1] = '\0';

    // Prelucrarea stringului citit:
    for (int i = 0; str[i] != '\0'; i++) {
        // Daca este cuvant care incepe cu a:
        if (str[i] == 'a') {
            path++;
            int max = str[i + 1] - '0';
            int maxPosition = i + 1;
            for (int j = i + 2; j <= i + 4; j++)
                if (str[j] > str[maxPosition]) {
                    max = str[j] - '0';
                    maxPosition = j;
                }
            if (maxPosition == i + 1)
                { column += 1; a[row][column] = path; }
                else if (maxPosition == i + 2)
                    { row -= 1; a[row][column] = path; }
                else if (maxPosition == i + 3)
                    { column -= 1; a[row][column] = path; }
                else if (maxPosition == i + 4)
                    { row += 1; a[row][column] = path; }
            i += 5;
        }

        // Daca este cuvant care incepe cu b:
        if (str[i] == 'b') {
            path++;
            int n = 0, k = 0;
            int j = i + 1;
            while (str[j] != '\0' && str[j] != ' ') {
                n = 10 * n + str[j] - '0';
                j++;
            }
            k = n % 10 + 10 * ((n /10) % 10);
            int pr = prim(k);
            int pal = palindrom(n);
            if (pal == 1 && pr == 0)
                { column += 1; a[row][column] = path; }
                else if (pal == 0 && pr == 1)
                    { row -= 1; a[row][column] = path; }
                else if (pal == 1 && pr == 1)
                    { column -= 1; a[row][column] = path; }
                else if (pal == 0 && pr == 0)
                    { row += 1; a[row][column] = path; }
        }

        // Daca este cuvant care incepe cu c:
        if (str[i] == 'c') {
            path++;
            int n = str[i + 1] - '0';
            int k = str[i + 2] - '0';
            int counter = k;
            while (k > n)
                k -= n;
            int S = 0;
            int start = 0;
            while (counter != 0) {
                for (int j = i + start + 3; j < i + 3 + n; j += k) {
                    S += str[j] - '0';
                    counter--;
                    if (j + k >= i + 3 + n)
                        start = k - (i + 3 + n - j);
                    if (counter == 0) break;
                }
            }
            S %= 4;
            if (S == 2)
                { column += 1; a[row][column] = path; }
                else if (S == 1)
                    { row -= 1; a[row][column] = path; }
                else if (S == 0)
                    { column -= 1; a[row][column] = path; }
                else if (S == 3)
                    { row += 1; a[row][column] = path; }
        }
    }

    // Afisarea matricei:
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
