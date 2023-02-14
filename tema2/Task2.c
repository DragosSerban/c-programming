#include "utils.h"

#define MAX 1002

void cifruCaesar(char firstChar, char lastChar, char S[], int K, int i) {
    int numberOfChars = lastChar - firstChar + 1;
    while (K > numberOfChars)
        K -= numberOfChars;
    if (S[i] - K >= firstChar) {
        S[i] -= K;
    } else {
        int dif = S[i] - firstChar;
        K -= dif;
        S[i] = lastChar + 1 - K;
    }
}

void cifruVigenere(char firstChar, char lastChar, char S[], char K, int i) {
    int numberOfChars = lastChar - firstChar + 1;
    while (K > numberOfChars)
        K -= numberOfChars;
    if (S[i] - K >= firstChar) {
        S[i] -= K;
    } else {
        int dif = S[i] - firstChar;
        K -= dif;
        S[i] = lastChar + 1 - K;
    }
}

void SolveTask2() {
    char type[10];
    char enter;
    scanf("%c", &enter);

    fgets(type, 10, stdin);

    if (strcmp(type, "caesar\n") == 0) {
        int K;
        char S[MAX];

        // Citirea cheii:
        scanf("%d", &K);

        // Pentru apasarea tastei enter:
        char enter;
        scanf("%c", &enter);

        // Se citeste cifrul:
        fgets(S, MAX, stdin);

        int length = strlen(S) - 1;

        for (int i = 0; i <= length; i++) {
            if (S[i] >= 'A' && S[i] <= 'Z')
                cifruCaesar('A', 'Z', S, K, i);
            else if (S[i] >= 'a' && S[i] <= 'z')
                cifruCaesar('a', 'z', S, K, i);
            else if (S[i] >= '0' && S[i] <= '9')
                cifruCaesar('0', '9', S, K, i);
        }

        for (int i = 0; i <= length; i++)
            printf("%c", S[i]);
    } else if (strcmp(type, "vigenere\n") == 0) {
        char K[11];
        char S[MAX];

        // Citirea cheii:
        fgets(K, 12, stdin);

        // Se citeste cifrul:
        fgets(S, MAX, stdin);

        int length = strlen(S) - 1;
        int lengthKey = strlen(K) - 1;

        for (int i = 0; i <= length; i++) {
            int x = i % lengthKey;
            int copyOfK = K[x] - 'A';
            if (S[i] >= 'A' && S[i] <= 'Z')
                cifruVigenere('A', 'Z', S, copyOfK, i);
            if (S[i] >= 'a' && S[i] <= 'z')
                cifruVigenere('a', 'z', S, copyOfK, i);
            if (S[i] >= '0' && S[i] <= '9')
                cifruVigenere('0', '9', S, copyOfK, i);
        }

        for (int i = 0; i <= length; i++)
            printf("%c", S[i]);
    } else if (strcmp(type, "addition\n") == 0) {
    int K;
    char S1[MAX], S2[MAX];

    // Citirea cheii:
    scanf("%d", &K);

    // Pentru apasarea tastei enter:
    char enter;
    scanf("%c", &enter);

    // Se citesc cele 2 nr sub forma de stringuri:
    scanf("%s", S1);
    scanf("%s", S2);

    int length1 = strlen(S1);
    int length2 = strlen(S2);

    for (int i = 0; i < length1; i++)
        cifruCaesar('0', '9', S1, K, i);

    for (int i = 0; i < length2; i++)
        cifruCaesar('0', '9', S2, K, i);

    int newLength;
    if (length1 > length2) {
        int dif = length1 - length2;
        for (int i = length1; i >= dif; i--)
            S2[i] = S2[i - dif];
        for (int i = 0; i < dif; i++)
            S2[i] = '0';
        newLength = length1;
    } else {
        int dif = length2 - length1;
        for (int i = length2; i >= dif; i--)
            S1[i] = S1[i - dif];
        for (int i = 0; i < dif; i++)
            S1[i] = '0';
        newLength = length2;
    }

    int rest = 0;
    char sum[MAX];
    sum[newLength + 1] = '\0';
    for (int i = newLength - 1; i >= 0; i--) {
        if (rest + S1[i] + S2[i] - 2*'0' <= 9) {
            sum[i + 1] = rest + S1[i] + S2[i]- '0';
            rest = 0;
        } else {
                sum[i + 1] = rest + S1[i] + S2[i] - '0' - 10;
                rest = 1;
            }
    }
    if (rest == 1)
        sum[0] = '1';
    else
        sum[0] = '0';

    int itsZero = 1;
    for (int i = 0; i <= newLength; i++) {
        if (sum[i] >= '1' && sum[i] <= '9') itsZero = 0;
        if (itsZero == 0)
            printf("%c", sum[i]);
    }
    if (itsZero == 1)
        printf("%c", '0');
    }
}
