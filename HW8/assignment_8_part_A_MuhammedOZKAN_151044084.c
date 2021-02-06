/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int **cell;
} face;

void print_file(face *, face *, face *, face *, face *, face *, int, int); /*sonuclari dosyaya yazdiran fonksiyon*/
void rotate_matrix(face *, int, int);                                      /*yuzleri her seferinde 90 derece sola ceviren fonksiyon*/

/*kupun yuzlerini ceviren fonskiyonlar*/
void rotate_right(face *, face *, face *, face *, int, int, int);
void rotate_left(face *, face *, face *, face *, int, int, int);
void rotate_up(face *, face *, face *, face *, int, int, int);
void rotate_down(face *, face *, face *, face *, int, int, int);

void main(void)
{
    FILE *readfile;
    readfile = fopen("commands.txt", "r");
    int dimension;
    int shrink = 0;
    int status;
    char data1[16], data3[16], data5[16];
    int data2, data4;
    int i, j, k;
    status = fscanf(readfile, "%d", &dimension);

    /*dinamik olarak dizilerin olusturulmasi*/
    face *face0 = malloc(sizeof(face));
    face *face1 = malloc(sizeof(face));
    face *face2 = malloc(sizeof(face));
    face *face3 = malloc(sizeof(face));
    face *face4 = malloc(sizeof(face));
    face *face5 = malloc(sizeof(face));

    face0->cell = malloc(sizeof(int *) * dimension);
    face1->cell = malloc(sizeof(int *) * dimension);
    face2->cell = malloc(sizeof(int *) * dimension);
    face3->cell = malloc(sizeof(int *) * dimension);
    face4->cell = malloc(sizeof(int *) * dimension);
    face5->cell = malloc(sizeof(int *) * dimension);

    for (j = 0; j < dimension; j++)
    {
        face0->cell[j] = malloc(sizeof(int) * dimension);
        face1->cell[j] = malloc(sizeof(int) * dimension);
        face2->cell[j] = malloc(sizeof(int) * dimension);
        face3->cell[j] = malloc(sizeof(int) * dimension);
        face4->cell[j] = malloc(sizeof(int) * dimension);
        face5->cell[j] = malloc(sizeof(int) * dimension);
    }

    /*kupun yuzlerine gerekli degerlerin veilmesi*/
    for (i = 0; i < dimension; i++)
    {
        for (k = 0; k < dimension; k++)
        {
            face0->cell[i][k] = 0;
            face1->cell[i][k] = 1;
            face2->cell[i][k] = 2;
            face3->cell[i][k] = 3;
            face4->cell[i][k] = 4;
            face5->cell[i][k] = 5;
        }
    }

    /*komutlarin adim adim okuyarak isletilmesi*/
    do
    {
        status = fscanf(readfile, "%s", &data1);

        if (strcmp(data1, "rotate") == 0) /*okunan data rotate ise geri kalan verileri okuyan kisim*/
        {
            status = fscanf(readfile, "%d %s %d %s", &data2, &data3, &data4, &data5);
        }

        if (status == EOF)
        {
            break;
        }

        if (strcmp(data1, "shrink") == 0) /*okunan veri shrink ise bir index i bir kaydirma*/
        {
            shrink++;
        }
        else if (strcmp(data1, "rotate") == 0)
        { /*okunan verilerin durumuna gore gerekli fonksiyonlarin cagirilmasi*/
            if (data2 == 0)
            {
                if (strcmp(data3, "row") == 0)
                {
                    if (strcmp(data5, "left") == 0)
                    {
                        rotate_left(face0, face1, face2, face3, data4, dimension, shrink);
                    }
                    else if (strcmp(data5, "right") == 0)
                    {
                        rotate_right(face0, face1, face2, face3, data4, dimension, shrink);
                    }
                }
                else if (strcmp(data3, "column") == 0)
                {
                    if (strcmp(data5, "up") == 0)
                    {
                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);

                        rotate_up(face0, face5, face2, face4, data4, dimension, shrink);

                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);
                    }
                    else if (strcmp(data5, "down") == 0)
                    {
                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);

                        rotate_down(face0, face5, face2, face4, data4, dimension, shrink);

                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);
                    }
                }
            }
            else if (data2 == 1)
            {
                if (strcmp(data3, "row") == 0)
                {
                    if (strcmp(data5, "left") == 0)
                    {
                        rotate_left(face1, face2, face3, face0, data4, dimension, shrink);
                    }
                    else if (strcmp(data5, "right") == 0)
                    {
                        rotate_right(face1, face2, face3, face0, data4, dimension, shrink);
                    }
                }
                else if (strcmp(data3, "column") == 0)
                {
                    if (strcmp(data5, "up") == 0)
                    {
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_up(face1, face5, face3, face4, data4, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                    }
                    else if (strcmp(data5, "down") == 0)
                    {
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_down(face1, face5, face3, face4, data4, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                    }
                }
            }
            else if (data2 == 2)
            {
                if (strcmp(data3, "row") == 0)
                {
                    if (strcmp(data5, "left") == 0)
                    {
                        rotate_left(face2, face3, face0, face1, data4, dimension, shrink);
                    }
                    else if (strcmp(data5, "right") == 0)
                    {
                        rotate_right(face2, face3, face0, face1, data4, dimension, shrink);
                    }
                }
                else if (strcmp(data3, "column") == 0)
                {
                    if (strcmp(data5, "up") == 0)
                    {

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face0, dimension, shrink);
                        rotate_matrix(face0, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_up(face2, face5, face0, face4, data4, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face0, dimension, shrink);
                        rotate_matrix(face0, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                    }
                    else if (strcmp(data5, "down") == 0)
                    {
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face0, dimension, shrink);
                        rotate_matrix(face0, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_down(face2, face5, face0, face4, data4, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face0, dimension, shrink);
                        rotate_matrix(face0, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                    }
                }
            }
            else if (data2 == 3)
            {
                if (strcmp(data3, "row") == 0)
                {
                    if (strcmp(data5, "left") == 0)
                    {
                        rotate_left(face3, face0, face1, face2, data4, dimension, shrink);
                    }
                    else if (strcmp(data5, "right") == 0)
                    {
                        rotate_right(face3, face0, face1, face2, data4, dimension, shrink);
                    }
                }
                else if (strcmp(data3, "column") == 0)
                {
                    if (strcmp(data5, "up") == 0)
                    {
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);

                        rotate_up(face3, face5, face1, face4, data4, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                    }
                    else if (strcmp(data5, "down") == 0)
                    {
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);

                        rotate_down(face3, face5, face1, face4, data4, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);
                    }
                }
            }
            else if (data2 == 4)
            {
                if (strcmp(data3, "row") == 0)
                {
                    if (strcmp(data5, "left") == 0)
                    {
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);

                        rotate_left(face4, face1, face5, face3, data4, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                    }
                    else if (strcmp(data5, "right") == 0)
                    {
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);

                        rotate_right(face4, face1, face5, face3, data4, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face5, dimension, shrink);
                        rotate_matrix(face5, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                    }
                }
                else if (strcmp(data3, "column") == 0)
                {
                    if (strcmp(data5, "up") == 0)
                    {
                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);

                        rotate_up(face4, face0, face5, face2, data4, dimension, shrink);

                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);
                    }
                    else if (strcmp(data5, "down") == 0)
                    {
                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);

                        rotate_down(face4, face0, face5, face2, data4, dimension, shrink);

                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);
                    }
                }
            }
            else if (data2 == 5)
            {
                if (strcmp(data3, "row") == 0)
                {
                    if (strcmp(data5, "left") == 0)
                    {
                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);

                        rotate_left(face5, face1, face4, face3, data4, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);
                    }
                    else if (strcmp(data5, "right") == 0)
                    {
                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);
                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);

                        rotate_right(face5, face1, face4, face3, data4, dimension, shrink);

                        rotate_matrix(face1, dimension, shrink);

                        rotate_matrix(face4, dimension, shrink);
                        rotate_matrix(face4, dimension, shrink);

                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);
                        rotate_matrix(face3, dimension, shrink);
                    }
                }
                else if (strcmp(data3, "column") == 0)
                {
                    if (strcmp(data5, "up") == 0)
                    {
                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);

                        rotate_up(face5, face2, face4, face0, data4, dimension, shrink);

                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);
                    }
                    else if (strcmp(data5, "down") == 0)
                    {
                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);

                        rotate_down(face5, face2, face4, face0, data4, dimension, shrink);

                        rotate_matrix(face2, dimension, shrink);
                        rotate_matrix(face2, dimension, shrink);
                    }
                }
            }
        }

    } while (status != -1);

    fclose(readfile);

    print_file(face0, face1, face2, face3, face4, face5, dimension, shrink);

    /*dizilerin bellekten free edilmesi*/
    for (j = 0; j < dimension; j++)
    {
        free(face0->cell[j]);
        free(face1->cell[j]);
        free(face2->cell[j]);
        free(face3->cell[j]);
        free(face4->cell[j]);
        free(face5->cell[j]);
    }

    free(face0->cell);
    free(face1->cell);
    free(face2->cell);
    free(face3->cell);
    free(face4->cell);
    free(face5->cell);

    free(face0);
    free(face1);
    free(face2);
    free(face3);
    free(face4);
    free(face5);
}

void rotate_matrix(face *yr, int dimension, int shrink)
{
    int temp;

    for (int x = shrink; x < dimension / 2; x++)
    {
        for (int y = x; y < dimension - x - 1; y++)
        {
            temp = yr->cell[x][y];
            yr->cell[x][y] = yr->cell[y][dimension - 1 - x];
            yr->cell[y][dimension - 1 - x] = yr->cell[dimension - 1 - x][dimension - 1 - y];
            yr->cell[dimension - 1 - x][dimension - 1 - y] = yr->cell[dimension - 1 - y][x];
            yr->cell[dimension - 1 - y][x] = temp;
        }
    }
}

void rotate_right(face *y1, face *y2, face *y3, face *y4, int row, int dimension, int shrink)
{
    row += shrink;
    int temp;
    for (int i = shrink; i < dimension; i++)
    {
        temp = y4->cell[row][i];
        y4->cell[row][i] = y3->cell[row][i];
        y3->cell[row][i] = y2->cell[row][i];
        y2->cell[row][i] = y1->cell[row][i];
        y1->cell[row][i] = temp;
    }
}

void rotate_left(face *y1, face *y2, face *y3, face *y4, int row, int dimension, int shrink)
{
    row += shrink;
    int temp;
    for (int i = shrink; i < dimension; i++)
    {
        temp = y1->cell[row][i];
        y1->cell[row][i] = y2->cell[row][i];
        y2->cell[row][i] = y3->cell[row][i];
        y3->cell[row][i] = y4->cell[row][i];
        y4->cell[row][i] = temp;
    }
}

void rotate_down(face *y1, face *y2, face *y3, face *y4, int column, int dimension, int shrink)
{
    column += shrink;
    int temp;
    for (int i = shrink; i < dimension; i++)
    {
        temp = y4->cell[i][column];
        y4->cell[i][column] = y3->cell[i][column];
        y3->cell[i][column] = y2->cell[i][column];
        y2->cell[i][column] = y1->cell[i][column];
        y1->cell[i][column] = temp;
    }
}

void rotate_up(face *y1, face *y2, face *y3, face *y4, int column, int dimension, int shrink)
{
    column += shrink;
    int temp;
    for (int i = shrink; i < dimension; i++)
    {
        temp = y1->cell[i][column];
        y1->cell[i][column] = y2->cell[i][column];
        y2->cell[i][column] = y3->cell[i][column];
        y3->cell[i][column] = y4->cell[i][column];
        y4->cell[i][column] = temp;
    }
}

void print_file(face *y0, face *y1, face *y2, face *y3, face *y4, face *y5, int dimension, int shrink)
{
    FILE *writefile;

    writefile = fopen("result.txt", "w");
    int i, k;

    for (i = shrink; i < dimension; i++)
    {
        for (k = shrink; k < dimension; k++)
        {
            fprintf(writefile, "%d", y0->cell[i][k]);
            if (dimension - 1 > k)
            {
                fprintf(writefile, " ");
            }
        }
        fprintf(writefile, "\n");
    }
    fprintf(writefile, "\n");

    for (i = shrink; i < dimension; i++)
    {
        for (k = shrink; k < dimension; k++)
        {
            fprintf(writefile, "%d", y1->cell[i][k]);
            if (dimension - 1 > k)
            {
                fprintf(writefile, " ");
            }
        }
        fprintf(writefile, "\n");
    }
    fprintf(writefile, "\n");

    for (i = shrink; i < dimension; i++)
    {
        for (k = shrink; k < dimension; k++)
        {
            fprintf(writefile, "%d", y2->cell[i][k]);
            if (dimension - 1 > k)
            {
                fprintf(writefile, " ");
            }
        }
        fprintf(writefile, "\n");
    }
    fprintf(writefile, "\n");

    for (i = shrink; i < dimension; i++)
    {
        for (k = shrink; k < dimension; k++)
        {
            fprintf(writefile, "%d", y3->cell[i][k]);
            if (dimension - 1 > k)
            {
                fprintf(writefile, " ");
            }
        }
        fprintf(writefile, "\n");
    }
    fprintf(writefile, "\n");

    for (i = shrink; i < dimension; i++)
    {
        for (k = shrink; k < dimension; k++)
        {
            fprintf(writefile, "%d", y4->cell[i][k]);
            if (dimension - 1 > k)
            {
                fprintf(writefile, " ");
            }
        }
        fprintf(writefile, "\n");
    }
    fprintf(writefile, "\n");

    for (i = shrink; i < dimension; i++)
    {
        for (k = shrink; k < dimension; k++)
        {
            fprintf(writefile, "%d", y5->cell[i][k]);
            if (dimension - 1 > k)
            {
                fprintf(writefile, " ");
            }
        }
        if (dimension - 1 > i)
        {
            fprintf(writefile, "\n");
        }
    }

    fclose(writefile);
}