#include "utils.h"

#define MAX 10000
#define SMALL 10

void SolveTask3() {
    char enter;
    scanf("%c", &enter);
    char str[MAX], s[MAX], *v[MAX], sep[] = " ,.!;\n", *p = NULL;
    char output[MAX];
    int numberOf2grams = 0;
    while (fgets(str, MAX, stdin)) {
        strncat(s, str, strlen(str));
    }
    int numberOfWords = 0;
    p = strtok(s, sep);
    while (p) {
        v[numberOfWords] = p;
        numberOfWords++;
        p = strtok(NULL, sep);
    }
    for (int i = 0; i < numberOfWords - 1; i++) {
        char word1[MAX];
        char word2[MAX];
        strncpy(word1, v[i], strlen(v[i]));
        word1[strlen(v[i])] = '\0';
        strncpy(word2, v[i+1], strlen(v[i+1]));
        word2[strlen(v[i+1])] = '\0';
        int numberOfAppearances = 1;
        for (int j = i + 1; j < numberOfWords - 1; j++) {
            if (!(strcmp(word1, v[j])) && !(strcmp(word2, v[j+1])))
                numberOfAppearances++;
        }
        int dontPrint = 0;
        for (int  k = 0; k < i - 1; k++) {
            if (!(strcmp(word1, v[k])) && !(strcmp(word2, v[k+1])))
                dontPrint = 1;
        }
        if (dontPrint == 0) {
            numberOf2grams++;
            char intToString[SMALL];
            strncat(output, word1, strlen(word1));
            strncat(output, " ", 1);
            strncat(output, word2, strlen(word2));
            strncat(output, " ", 1);
            snprintf(intToString, SMALL, "%d\n", numberOfAppearances);
            strncat(output, intToString, strlen(intToString));
        }
    }
    printf("%d\n%s", numberOf2grams, output);
}
