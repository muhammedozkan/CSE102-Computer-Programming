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
#define KARAKTER_SAYISI 27

char karakterler[KARAKTER_SAYISI] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
char bigram[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1][2]; /*iki tane bosluk durumunu cikardigimiz icin -1*/

double dil1[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1];
double dil2[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1];
double dil3[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1];
double dil4[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1];
double dil5[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1];

double dilx[(KARAKTER_SAYISI * KARAKTER_SAYISI) - 1];

void bigramlari_olustur(void);
void tekrar_sayisi_bul(char *, double *);
void degiskensifirla(double *);
double benzersizlikhesapla(double *, double *);

void main(void)
{
    bigramlari_olustur();

    tekrar_sayisi_bul("language_1.txt", dil1);
    tekrar_sayisi_bul("language_2.txt", dil2);
    tekrar_sayisi_bul("language_3.txt", dil3);
    tekrar_sayisi_bul("language_4.txt", dil4);
    tekrar_sayisi_bul("language_5.txt", dil5);

    tekrar_sayisi_bul("language_x.txt", dilx);

    printf("%lf\n", benzersizlikhesapla(dilx, dil1));
    printf("%lf\n", benzersizlikhesapla(dilx, dil2));
    printf("%lf\n", benzersizlikhesapla(dilx, dil3));
    printf("%lf\n", benzersizlikhesapla(dilx, dil4));
    printf("%lf\n", benzersizlikhesapla(dilx, dil5));

    /* for (int k = 0; k < 728; k++)
    {
        
            printf("%d %c%c %lf\n",k, bigram[k][0], bigram[k][1],dil1[k]);
        
    }*/
}

void bigramlari_olustur(void)
{
    for (int i = 0; i < KARAKTER_SAYISI; i++)
    {
        for (int k = 0; k < KARAKTER_SAYISI; k++)
        {
            if ((i * 27 + k) == 728)
            {
                break; /*iki tane bosluk durumunu atlamak icin*/
            }
            bigram[i * 27 + k][0] = karakterler[i];
            bigram[i * 27 + k][1] = karakterler[k];

            // printf("%d %c%c\n", i * 27 + k, karakterler[i], karakterler[k]);
        }
    }
}

void tekrar_sayisi_bul(char *_diladi, double *_dil)
{
    degiskensifirla(_dil); /*dizi elemanlarina 0 sayisi yaziliyor*/
    FILE *readfilevalues;
    readfilevalues = fopen(_diladi, "r");
    
    int status = 1;
    int toplambigram = 0;
    char ilk = '-', son; /* - isareti ile ilk karakteri, satirbasi ve yazi sonunundaki kelimeleri bosluktan ayirmak icin */
    while (status != EOF)
    {
        status = fscanf(readfilevalues, "%c", &son);
        if (status == EOF)
        {
            son = '-';
        }
        if (son == '\n')
        {
            son = ' ';
        }
        if (son == ' ' && ilk == ' ')
        {
            continue;
        }
        if (son == '-' || ilk == '-')
        {
            ilk = son;
            continue;
        }

        //printf("%c%c\n", ilk, son);

        for (int i = 0; i < 728; i++)
        {
            if (bigram[i][0] == ilk && bigram[i][1] == son)
            {
                _dil[i]++;
                toplambigram++;
            }
        }

        ilk = son;
    }

    //printf("%d\n", toplambigram);

    for (int k = 0; k < 728; k++) /* oran hesabi yapiliyor toplam bigram sayisina bolunuyor*/
    {

        _dil[k] /= toplambigram;
    }

    fclose(readfilevalues);
}

void degiskensifirla(double *_dil)
{
    for (int i = 0; i < 728; i++)
    {
        _dil[i] = 0;
    }
}

double benzersizlikhesapla(double *_dil1, double *_dil2)
{
    double benzerliktoplami = 0;
    for (int i = 0; i < 728; i++)
    {
        benzerliktoplami += fabs(_dil1[i] - _dil2[i]);
    }
    return benzerliktoplami;
}