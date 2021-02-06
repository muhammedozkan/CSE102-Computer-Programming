/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>

double valuesdata[128];      /*x degerleri*/
int valuesdatacount = 0;     /*x degerlerinin sayisi*/
double evaluationsdata[128]; /*hesaplanan degerlerin tutuldugu dizi*/

char polynomialdata[1024];   /*polinomun saklandigi degisken*/
int polynomialdatacount = 0; /*polinomun karakter saiyisi*/

char termdata[1024][1024];   /*polinomun terimlerinin saklandigi degisken*/
int termdatacharcount[1024]; /*polinomun terimlerinin karakter sayisi*/
int termdatacount = 0;       /*terim sayisi*/

double termvalue[1024][5]; /*terimlerin sayisal karsiliklari*/

void readvaluesfile(void);
void readpolynomialfile(void);
void writeevaluationsfile(void);

void divideterm(void);
void saveterm(int, int);

void puttermvalue(void);
void changexvalue(double);
void calctermvalue(void);
void sumterm(int);

void removewhitespace(char *);
int counting(char *);

void main(void)
{
    readvaluesfile();
    readpolynomialfile();
    divideterm();
    puttermvalue();

    for (int i = 0; i < valuesdatacount; i++)
    {
        changexvalue(valuesdata[i]);
        calctermvalue();
        sumterm(i);
    }

    writeevaluationsfile();
}

void readvaluesfile(void) /*x degerlerinin okundugu fonksiyon*/
{
    FILE *readfilevalues;
    readfilevalues = fopen("values.txt", "r");

    int status = 1;

    while (status > 0)
    {
        status = fscanf(readfilevalues, "%lf", &valuesdata[valuesdatacount]);
        if (status > 0)
        {
            valuesdatacount++;
        }
    }

    fclose(readfilevalues);
}

void readpolynomialfile(void) /*polinomun okundugu fonksiyon*/
{
    FILE *readfilepolynomial;
    readfilepolynomial = fopen("polynomial.txt", "r");

    int status = 1;

    while (status > 0)
    {
        status = fscanf(readfilepolynomial, "%c", &polynomialdata[polynomialdatacount]);
        if (status > 0)
        {
            polynomialdatacount++;
        }
    }

    fclose(readfilepolynomial);

    removewhitespace(polynomialdata);
    polynomialdatacount = counting(polynomialdata);
}

void writeevaluationsfile() /*sonuclarin kayit edildigi kisim*/
{
    FILE *writefilevalues;
    writefilevalues = fopen("evaluations.txt", "w");

    for (int i = 0; i < valuesdatacount; i++)
    {
        fprintf(writefilevalues, "%.2f\n", evaluationsdata[i]);
    }

    fclose(writefilevalues);
}

void divideterm(void) /*okunan polinomu terimlere ayirma kismi*/
{
    int firstindex = 0;
    int lastindex = 0;
    for (int i = 0; i < polynomialdatacount; i++)
    {
        if (polynomialdata[i] == 'x' || polynomialdata[i] == 'X')
        {
            firstindex = lastindex;
            lastindex = i;
            while (1)
            {
                lastindex++;
                if (polynomialdata[lastindex] == '+' || polynomialdata[lastindex] == '-' || lastindex == polynomialdatacount)
                {
                    i = lastindex;
                    saveterm(firstindex, lastindex); /*terimin ilk ve son index degerine gore ilgili fonskiyona gonderir*/
                    break;
                }
            }
        }
    }
}

void saveterm(int _firstindex, int _lastindex) /*terimlerin ilgili dizilere yerlestirme islemi*/
{
    int k = 0;
    for (int i = _firstindex; i < _lastindex; i++, k++)
    {
        termdata[termdatacount][k] = polynomialdata[i];
    }

    termdatacharcount[termdatacount] = _lastindex - _firstindex;

    if (termdatacount == 0)
    {
        if (termdata[termdatacount][0] != '-' && termdata[termdatacount][0] != '+')
        {
            for (int j = _lastindex + 1; j > 0; j--)
            {
                termdata[termdatacount][j] = termdata[termdatacount][j - 1];
            }
            termdata[termdatacount][0] = '+';
            termdatacharcount[termdatacount]++;
        }
    }

    termdatacount++; /*terim sayisinin artirilma islemi*/
}

void puttermvalue(void) /*karakterlerin taninlama isleminden sonra sayilar verilere donusturulerek diziye aktarilmasi*/
{
    int firstindex = 1;
    int lastindex = 0;
    char temp[128];
    for (int i = 0; i < termdatacount; i++)
    {
        if (termdata[i][0] == '+')
        {
            termvalue[i][0] = 1;
        }
        else if (termdata[i][0] == '-')
        {
            termvalue[i][0] = -1;
        }
        for (int k = 1; k < termdatacharcount[i]; k++)
        {
            if (termdata[i][k] == 'x' || termdata[i][k] == 'X')
            {
                lastindex = k;
                if (lastindex == 1)
                {
                    termvalue[i][1] = 1;
                }
                else
                {
                    strncpy(temp, &termdata[i][1], lastindex); /*ilgili degerlerin alinmasi*/
                    sscanf(temp, "%lf", &termvalue[i][1]);
                }
                break;
            }
        }
        if (termdata[i][lastindex + 1] == '^')
        {
            strncpy(temp, &termdata[i][lastindex + 2], termdatacharcount[i]);
            sscanf(temp, "%lf", &termvalue[i][3]);
        }
        else if (lastindex + 1 == termdatacharcount[i])
        {
            termvalue[i][3] = 1;
        }
    }
}

void changexvalue(double _values) /*x degerlerinin degistirilmesi*/
{
    for (int i = 0; i < termdatacount; i++)
    {
        termvalue[i][2] = _values;
    }
}

void calctermvalue(void) /*dizideki degerlerin hesaplanmasi*/
{
    for (int i = 0; i < termdatacount; i++)
    {
        termvalue[i][4] = termvalue[i][0] * termvalue[i][1] * (pow(termvalue[i][2], termvalue[i][3]));
    }
}

void sumterm(int _valuesid) /*polinomun terimlerinin degerlerinin toplanmasi*/
{
    for (int i = 0; i < termdatacount; i++)
    {
        evaluationsdata[_valuesid] += termvalue[i][4];
    }
}

void removewhitespace(char *src) /*bosluklari silme fonksiyonu*/
{
    char *dest;
    char t;
    dest = src;
    while ((t = *src) != '\0')
    {
        if (t == ' ')
            src++;
        else
            *dest++ = *src++;
    }
    *dest = '\0'; /* sonlandirma karakteri*/
}

int counting(char *poly) /*polinomun karakter sayisi bulan fonksiyon*/
{
    int i = 0;
    while (1)
    {
        if ('\0' != poly[i])
        {
            i++;
        }
        else
        {

            break;
        }
    }
    return i;
}