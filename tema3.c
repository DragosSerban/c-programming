#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmp_header.h"

#define MAX 100

// Structura pentru o poza de tip .bmp
typedef struct {
    bmp_fileheader fh;
    bmp_infoheader ih;
    char**bitMap;
} Tbmp;

// Structura pentru un pixel (format din 3 variabile de tip char)
typedef struct {
    char R;
    char G;
    char B;
} TPixel;

// Functie de alocare dinamica pentru matrice
char**matrixAlloc(int row, int col) {
    char **a = (char**)malloc(row * sizeof(char *));
    if (!a) return NULL;
    for (int i = 0; i < row; i++) {
        a[i] = (char*)malloc(col * sizeof(char));
        if (!a[i]) {
            for (int j = 0; j < i; j++)
                free(a[j]);
            free(a);
            return NULL;
        }
    }
    return a;
}

// Functie pentru citirea din fisierul binar a elementelor
// din interiorul structurii de tip Tbmp
Tbmp*readBmp(FILE *f) {
    // Alocam dinamic o structura de tip Tbmp
    Tbmp *bmp = (Tbmp*)malloc(1 * sizeof(Tbmp));
    if (!bmp)
        return NULL;

    // Citim din fisier elementele din interiorul bmp->fh si bmp->ih
    fread(&bmp->fh.fileMarker1, sizeof(char), 1, f);
    fread(&bmp->fh.fileMarker2, sizeof(char), 1, f);
    fread(&bmp->fh.bfSize, sizeof(unsigned int), 1, f);
    fread(&bmp->fh.unused1, sizeof(unsigned short), 1, f);
    fread(&bmp->fh.unused2, sizeof(unsigned short), 1, f);
    fread(&bmp->fh.imageDataOffset, sizeof(unsigned int), 1, f);

    fread(&bmp->ih.biSize, sizeof(unsigned int), 1, f);
    fread(&bmp->ih.width, sizeof(signed int), 1, f);
    fread(&bmp->ih.height, sizeof(signed int), 1, f);
    fread(&bmp->ih.planes, sizeof(unsigned short), 1, f);
    fread(&bmp->ih.bitPix, sizeof(unsigned short), 1, f);
    fread(&bmp->ih.biCompression, sizeof(unsigned int), 1, f);
    fread(&bmp->ih.biSizeImage, sizeof(unsigned int), 1, f);
    fread(&bmp->ih.biXPelsPerMeter, sizeof(int), 1, f);
    fread(&bmp->ih.biYPelsPerMeter, sizeof(int), 1, f);
    fread(&bmp->ih.biClrUsed, sizeof(unsigned int), 1, f);
    fread(&bmp->ih.biClrImportant, sizeof(unsigned int), 1, f);

    // Alocam dinamic matricea ce reprezinta poza
    bmp->bitMap = matrixAlloc(bmp->ih.height, bmp->ih.width*3);
        if (!bmp->bitMap)
            return NULL;

    // Citim din fisier matricea si eliminam paddingul, daca exista
    char padding = 0;
    for (int i = 0; i < bmp->ih.height; i++)
        for (int j = 0; j < bmp->ih.width*3; j++) {
            fread(&bmp->bitMap[i][j], sizeof(char), 1, f);
            if (j == bmp->ih.width*3-1 && bmp->ih.width%4 != 0) {
                for (int k = 0; k < (4-(bmp->ih.width*3)%4)%4; k++)
                    fread(&padding, sizeof(char), 1, f);
            }
        }
    return bmp;
}

void writeBmp(FILE *f, Tbmp *bmp) {
    // Scrierea in fisier a datelor din bmp->fh si bmp->ih
    fwrite(&bmp->fh.fileMarker1, sizeof(char), 1, f);
    fwrite(&bmp->fh.fileMarker2, sizeof(char), 1, f);
    fwrite(&bmp->fh.bfSize, sizeof(unsigned int), 1, f);
    fwrite(&bmp->fh.unused1, sizeof(unsigned short), 1, f);
    fwrite(&bmp->fh.unused2, sizeof(unsigned short), 1, f);
    fwrite(&bmp->fh.imageDataOffset, sizeof(unsigned int), 1, f);

    fwrite(&bmp->ih.biSize, sizeof(unsigned int), 1, f);
    fwrite(&bmp->ih.width, sizeof(signed int), 1, f);
    fwrite(&bmp->ih.height, sizeof(signed int), 1, f);
    fwrite(&bmp->ih.planes, sizeof(unsigned short), 1, f);
    fwrite(&bmp->ih.bitPix, sizeof(unsigned short), 1, f);
    fwrite(&bmp->ih.biCompression, sizeof(unsigned int), 1, f);
    fwrite(&bmp->ih.biSizeImage, sizeof(unsigned int), 1, f);
    fwrite(&bmp->ih.biXPelsPerMeter, sizeof(int), 1, f);
    fwrite(&bmp->ih.biYPelsPerMeter, sizeof(int), 1, f);
    fwrite(&bmp->ih.biClrUsed, sizeof(unsigned int), 1, f);
    fwrite(&bmp->ih.biClrImportant, sizeof(unsigned int), 1, f);

    // Adaugarea paddingului (daca exista) dupa fiecare linie
    char padding = 0;
    for (int i = 0; i < bmp->ih.height; i++)
        for (int j = 0; j < bmp->ih.width*3; j++) {
            fwrite(&bmp->bitMap[i][j], sizeof(char), 1, f);
            if (j == bmp->ih.width*3-1 && bmp->ih.width%4 != 0) {
                for (int k = 0; k < (4-(bmp->ih.width*3)%4)%4; k++)
                    fwrite(&padding, sizeof(char), 1, f);
            }
        }
}

// Functie pentru dezalocarea memoriei ocupate de o structura de tip Tbmp
void deallocate(Tbmp *bmp) {
    for (int i = 0; i < bmp->ih.height; i++)
        free(bmp->bitMap[i]);
    free(bmp->bitMap);
    free(bmp);
    bmp = NULL;
}

// Functie de inserare a pozei in poza principala
char**insert(int x, int y, Tbmp*bmp, Tbmp*addBmp) {
    int i = 0, j = 0;
    for (i = 0; i < addBmp->ih.height&&x+i < bmp->ih.height; i++)
    for (j = 0; j < 3*addBmp->ih.width&&3*y+j < 3*bmp->ih.width; j++)
        bmp->bitMap[i+x][j+3*y] = addBmp->bitMap[i][j];
    return bmp->bitMap;
}

// Functie de swap a doua variabile de tip int
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Functie pentru inserarea unui punct de dimensiuni x*x la o anumita adresa
char**insertDot(int xCenter, int yCenter, int x, TPixel*RGB, Tbmp*bmp) {
    int x0 = xCenter-x/2;
    int y0 = yCenter-x/2;
    for (int i = 0; i < x && x0+i < bmp->ih.height; i++)
        for (int j = 0; j < 3*x && 3*y0+j < 3*bmp->ih.width; j++)
            if (j%3 == 0 && 3*y0+j >= 0 && i+x0 >= 0) {
                bmp->bitMap[i+x0][j+3*y0] = RGB->B;
            } else if (j%3 == 1 && 3*y0+j >= 0 && i+x0 >= 0) {
                bmp->bitMap[i+x0][j+3*y0] = RGB->G;
            } else if (j%3 == 2 && 3*y0+j >= 0 && i+x0 >= 0) {
                bmp->bitMap[i+x0][j+3*y0] = RGB->R;
            }
    return bmp->bitMap;
}

// Functie pentru a desena linia intre punctele (x1,y1) si (x2,y2)
char**draw(int x1, int y1, int x2, int y2, int x, TPixel*RGB, Tbmp*bmp) {
    if (abs(x2-x1) >= abs(y2-y1)) {
        if (x1 > x2) {
            swap(&x1, &x2);
            swap(&y1, &y2);
        }
        for (int xCenter = x1; xCenter <= x2; xCenter++) {
            double temporary = 1.0*(xCenter-x1)*(y2-y1)/(x2-x1)+y1;
            int yCenter = (int)temporary;
            bmp->bitMap = insertDot(xCenter, yCenter, x, RGB, bmp);
        }
    } else {
        if (y1 > y2) {
            swap(&x1, &x2);
            swap(&y1, &y2);
        }
        for (int yCenter = y1; yCenter <= y2; yCenter++) {
            double temporary = 1.0*(yCenter-y1)*(x2-x1)/(y2-y1)+x1;
            int xCenter = (int)temporary;
            bmp->bitMap = insertDot(xCenter, yCenter, x, RGB, bmp);
        }
    }
    return bmp->bitMap;
}

// Functie recursiva pentru a umple o zona din matrice care are pixelii identici
char**fill(char**a, int height, int width, int x, int y, TPixel*RGB, TPixel*p) {
    a[x][3*y] = RGB->B;
    a[x][3*y+1] = RGB->G;
    a[x][3*y+2] = RGB->R;

    // Verificam recursiv daca exista pixeli vecini de aceeasi culoare
    // cu pixelul initial si le modificam culoarea
    if (x-1 >= 0)
      if (a[x-1][3*y] == p->R && a[x-1][3*y+1] == p->G && a[x-1][3*y+2] == p->B)
        a = fill(a, height, width, x-1, y, RGB, p);

    if (3*(y-1) >= 0)
      if (a[x][3*y-3] == p->R && a[x][3*y-2] == p->G && a[x][3*y-1] == p->B)
        a = fill(a, height, width, x, y-1, RGB, p);

    if (x+1 < height)
      if (a[x+1][3*y] == p->R && a[x+1][3*y+1] == p->G && a[x+1][3*y+2] == p->B)
        a = fill(a, height, width, x+1, y, RGB, p);

    if (3*(y+1)+2 < 3*width)
      if (a[x][3*y+3] == p->R && a[x][3*y+4] == p->G && a[x][3*(y+1)+2] == p->B)
        a = fill(a, height, width, x, y+1, RGB, p);

    return a;
}

int main() {
    char *instruction = NULL;
    Tbmp *bmp = NULL;
    TPixel RGB;
    char x = 0;

    // Alocam memorie pentru instructiune (string)
    instruction = (char*)malloc(MAX * sizeof(char));
    if (!instruction)
        return -1;

    while (fgets(instruction, MAX, stdin)) {
        // Eliminarea lui '\n' de la finalul stringului citit
        if (instruction[strlen(instruction) - 1] == '\n')
            instruction[strlen(instruction) - 1] = '\0';

        // Impartim stringul citit in cuvinte cu strtok
        char *p = strtok(instruction, " ");

        if (strncmp("save", p, strlen(p)) == 0) {
            // Cream fisierul binar in care dorim sa salvam poza
            p = strtok(NULL, " ");
            FILE *f = fopen(p, "wb");
            if (!f)
                return -1;
            // Apelam functia de scriere a datelor pozei intr-un nou fisier
            writeBmp(f, bmp);
        } else if (strncmp("edit", p, strlen(p)) == 0) {
            // Deschidem fisierul binar corespunzator pozei
            p = strtok(NULL, " ");
            FILE *f = fopen(p, "rb");
            if (!f)
                return -1;
            // Apelam functia de citire a datelor din fisierul de tip .bmp
            bmp = readBmp(f);
            if (!bmp)
                return -1;
        } else if (strncmp("insert", p, strlen(p)) == 0) {
            p = strtok(NULL, " ");
            FILE *f = fopen(p, "rb");
            if (!p)
                return -1;
            // Transformam prin atoi numerele din string in int-uri
            p = strtok(NULL, " "); int y = atoi(p);
            p = strtok(NULL, " "); int x = atoi(p);

            // Facem o noua structura pentru poza pe care dorim sa o inseram
            Tbmp *addBmp = readBmp(f);
            if (!addBmp)
                return -1;

            // Inseram poza in poza principala
            bmp->bitMap = insert(x, y, bmp, addBmp);

            // Dezalocam memoria pentru poza ce a fost inserata
            deallocate(addBmp);
        } else if (strncmp("set", p, strlen(p)) == 0) {
            p = strtok(NULL, " ");
            if (strncmp("draw_color", p, strlen(p)) == 0) {
                // Citim valorile R, G, B pentru a forma culoarea cautata
                p = strtok(NULL, " "); RGB.R = (char)atoi(p);
                p = strtok(NULL, " "); RGB.G = (char)atoi(p);
                p = strtok(NULL, " "); RGB.B = (char)atoi(p);
            } else if (strncmp("line_width", p, strlen(p)) == 0) {
                // Aflam grosimea liniei
                p = strtok(NULL, " ");
                x = (char)atoi(p);
            }
        } else if (strncmp("draw", p, strlen(p)) == 0) {
            p = strtok(NULL, " ");
            if (strncmp("line", p, strlen(p)) == 0) {
                p = strtok(NULL, " "); int y1 = atoi(p);
                p = strtok(NULL, " "); int x1 = atoi(p);
                p = strtok(NULL, " "); int y2 = atoi(p);
                p = strtok(NULL, " "); int x2 = atoi(p);

                // Apelam functia de desenare a liniei
                // intre (x1, y1) si (x2, y2)
                bmp->bitMap = draw(x1, y1, x2, y2, x, &RGB, bmp);
            } else if (strncmp("rectangle", p, strlen(p)) == 0) {
                p = strtok(NULL, " "); int y1 = atoi(p);
                p = strtok(NULL, " "); int x1 = atoi(p);
                p = strtok(NULL, " "); int width = atoi(p);
                p = strtok(NULL, " "); int height = atoi(p);
                int x2 = x1 + height, y2 = y1;
                int x3 = x1, y3 = y1 + width;
                int x4 = x2, y4 = y3;

                // Apelam de 4 ori functia de desenare a unei linii pentru ca
                // dorim sa desenam toate cele 4 laturi ale dreptunghiului
                bmp->bitMap = draw(x1, y1, x2, y2, x, &RGB, bmp);
                bmp->bitMap = draw(x1, y1, x3, y3, x, &RGB, bmp);
                bmp->bitMap = draw(x2, y2, x4, y4, x, &RGB, bmp);
                bmp->bitMap = draw(x3, y3, x4, y4, x, &RGB, bmp);
            } else if (strncmp("triangle", p, strlen(p)) == 0) {
                p = strtok(NULL, " "); int y1 = atoi(p);
                p = strtok(NULL, " "); int x1 = atoi(p);
                p = strtok(NULL, " "); int y2 = atoi(p);
                p = strtok(NULL, " "); int x2 = atoi(p);
                p = strtok(NULL, " "); int y3 = atoi(p);
                p = strtok(NULL, " "); int x3 = atoi(p);

                // Apelam de 3 ori functia de desenare a unei linii pentru ca
                // dorim sa desenam toate cele 3 laturi ale triunghiului
                bmp->bitMap = draw(x1, y1, x2, y2, x, &RGB, bmp);
                bmp->bitMap = draw(x2, y2, x3, y3, x, &RGB, bmp);
                bmp->bitMap = draw(x3, y3, x1, y1, x, &RGB, bmp);
            }
        } else if (strncmp("fill", p, strlen(p)) == 0) {
            p = strtok(NULL, " "); int y = atoi(p);
            p = strtok(NULL, " "); int x = atoi(p);

            // Schimbam culoarea pixelilor prin structura de tip TPixel
            // si prin functia recursiva fill
            TPixel pixel;
            pixel.R = bmp->bitMap[x][3*y];
            pixel.G = bmp->bitMap[x][3*y+1];
            pixel.B = bmp->bitMap[x][3*y+2];

            char**bitMap = bmp->bitMap;
            int height = bmp->ih.height;
            int width = bmp->ih.width;
            bmp->bitMap = fill(bitMap, height, width, x, y, &RGB, &pixel);
        } else if (strncmp("quit", p, strlen(p)) == 0) {
            // Eliberam memoria si inchidem programul
            deallocate(bmp);
            free(instruction);
            instruction = NULL;
            break;
        }
    }
    return 0;
}

