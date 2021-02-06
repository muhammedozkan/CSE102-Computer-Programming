/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h> /* definitions of printf,scanf */

/* definitions of constants used in the program */

#define BOARDSIZEMINX 0.0
#define BOARDSIZEMINY 0.0

#define BOARDSIZEMAXX 200.0 /* board size*/
#define BOARDSIZEMAXY 300.0

#define DETECTORSIZEX 25.0 /* detector tool size*/
#define DETECTORSIZEY 30.0

#define MARKEDREGIONSIZEX 15.0 /* marked area size*/
#define MARKEDREGIONSIZEY 20.0

#define MARKEDREGIONCOORDINATEX 75.0 /* marked area center points */
#define MARKEDREGIONCOORDINATEY 95.0


/* function prototype*/

double readcoordinate(char);  /*functions that get data from the user*/
double readcoordinatex(void);
double readcoordinatey(void);

int checkuserinput(double ,double ,double ,double); /* check of the input data by the size of the board */

int detectfullyoverlaps(double ,double ,double ,double ,double ,double ,double ,double); /* completely overlap detection */

int detectpartialoverlap(double ,double ,double ,double ,double ,double ,double ,double); /* partial overlap detection */

int intersectareacoordinate(double ,double ,double ,double ,double ,double ,double ,double ,double *,double *,double *,double *); /* find intersecting area coordinate */

double max(double ,double); /* find maximum minimum value */
double min(double ,double);



int main(void)
{
    double boardx,boardy,detectorx,detectory,markedregionx,markedregiony,markedx,markedy;
    double userinputx,userinputy;

    double newmarkedx=0,newmarkedy=0,newmarkedregionx=0,newmarkedregiony=0;

    /* allocation of constants to variables */
    boardx=BOARDSIZEMAXX;
    boardy=BOARDSIZEMAXY;

    detectorx=DETECTORSIZEX;
    detectory=DETECTORSIZEY;

    markedregionx=MARKEDREGIONSIZEX;
    markedregiony=MARKEDREGIONSIZEY;

    markedx=MARKEDREGIONCOORDINATEX;
    markedy=MARKEDREGIONCOORDINATEY;


    printf("> Board = [%lf x %lf], marked region = [%lf x %lf], Detector = [%lf x %lf]\n",boardx,boardy,markedregionx,markedregiony,detectorx,detectory);

    for(int i=9;i>=0;i--)
        {
            userinputx=readcoordinatex(); /* get coordinates from the user */
            userinputy=readcoordinatey();

            if(checkuserinput(userinputx,userinputy,detectorx,detectory)) /* control of coordinates */
            {

                if(detectfullyoverlaps(userinputx,userinputy,detectorx,detectory,markedx,markedy,markedregionx,markedregiony)) /* control of fully overlaps */
                {
                    printf("> Congratulations User Wins.\n");
                    break; /* for the end of the game */
                }
                else
                {
                    if(detectpartialoverlap(userinputx,userinputy,detectorx,detectory,markedx,markedy,markedregionx,markedregiony)) /* control of partial overlaps */
                    {
                        if(i!=0) /* remaining attempts count control , zero will end the game */
                        {
                            /*section that receives intersecting coordinates*/
                                                                                                             /* new coordinates are taken using pointers */

                            intersectareacoordinate(userinputx,userinputy,detectorx,detectory,markedx,markedy,markedregionx,markedregiony,&newmarkedx,&newmarkedy,&newmarkedregionx,&newmarkedregiony);

                            markedregionx = newmarkedregionx;
                            markedregiony = newmarkedregiony;
                            markedx = newmarkedx;
                            markedy = newmarkedy;              /* The part where necessary calculations are made for intersecting coordinates */

                            detectorx = (detectorx/2) ; /* detector tool is decreased to half*/
                            detectory = (detectory/2) ;

                            /* you can open the center coordinates of the new intersecting area if you want to see it on the screen. */
                            /*
                            printf("x=%lf y=%lf\n",markedx,markedy);
                            */

                            if(markedregionx == 0 && markedregiony == 0) /* If the width of the marked field is zero, the user wins */
                            {
                                printf("> Congratulations User Wins.\n");
                                break; /* for the end of the game */
                            }
                            else
                            { /* the user is informed about the intersection */
                             printf("> Partial hit! marked region was shirked to [%lf x %lf], detector was shirked to [%lf x %lf] attempts remaining: %d\n",markedregionx,markedregiony,detectorx,detectory,i);
                            }



                        }
                        else
                        {  /*  zero will end the game */
                            printf("> Unfortunately, Game Over.\n");
                        }
                    }
                    else
                    {
                        if(i!=0)
                        {
                            printf("> You missed the target, attempts remaining: %d\n",i);

                        }
                        else
                        { /*  zero will end the game */
                            printf("> Unfortunately, Game Over.\n");
                        }


                    }

                }



            }
            else
            {

                printf("> Error, move is not valid. Try again. Attempts remaining: %d\n",i);
                i++;
            }

        }

    return 0;
}

double readcoordinate(char axis)
{
    double coordinate;

    if(axis == 'x')
    {
     printf("> Enter the x coordinate of the move:\n");
    }
    else if(axis == 'y')
    {
     printf("> Enter the y coordinate of the move:\n");
    }

    scanf("%lf",&coordinate);

    return coordinate;
}

double readcoordinatex(void)
{
    return readcoordinate('x');
}

double readcoordinatey(void)
{
    return readcoordinate('y');
}

int checkuserinput(double coordinatex,double coordinatey,double detectorx,double detectory)
{
    if( BOARDSIZEMINX<=(coordinatex-(detectorx/2)) && BOARDSIZEMAXX>=(coordinatex+(detectorx/2)) && BOARDSIZEMINY<=(coordinatey-(detectory/2)) && BOARDSIZEMAXY>=(coordinatey+(detectory/2)) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int detectfullyoverlaps(double coordinatex,double coordinatey,double detectorx,double detectory,double markedx,double markedy,double markedregionx,double markedregiony)
{
    if( (markedx-(markedregionx/2)) >= (coordinatex-(detectorx/2)) && (markedx+(markedregionx/2)) <= (coordinatex+(detectorx/2)) && (markedy-(markedregiony/2)) >= (coordinatey-(detectory/2)) && (markedy+(markedregiony/2)) <= (coordinatey+(detectory/2)) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int detectpartialoverlap(double coordinatex,double coordinatey,double detectorx,double detectory,double markedx,double markedy,double markedregionx,double markedregiony)
{
    double detectorx1=(coordinatex-(detectorx/2));
    double detectory1=(coordinatey-(detectory/2));
    double detectorx2=(coordinatex+(detectorx/2));
    double detectory2=(coordinatey+(detectory/2));

    double markedx1=(markedx-(markedregionx/2));
    double markedy1=(markedy-(markedregiony/2));
    double markedx2=(markedx+(markedregionx/2));
    double markedy2=(markedy+(markedregiony/2));




    if((detectorx1 <= markedx2) && (detectorx2 >= markedx1) && (detectory1 <= markedy2) && (detectory2 >= markedy1))
    {
        return 1;
    }
    else
    {
        return 0;
    }


}

int intersectareacoordinate(double coordinatex,double coordinatey,double detectorx,double detectory,double markedx,double markedy,double markedregionx,double markedregiony,double *newmarkedx,double *newmarkedy,double *newmarkedregionx,double *newmarkedregiony)
{
    double detectorx1=(coordinatex-(detectorx/2));
    double detectory1=(coordinatey-(detectory/2));
    double detectorwidth=detectorx;
    double detectorheight=detectory;

    double markedx1=(markedx-(markedregionx/2));
    double markedy1=(markedy-(markedregiony/2));
    double markedwidth=markedregionx;
    double markedheight=markedregiony;


    double newmarkedx1,newmarkedy1,newmarkedx2,newmarkedy2;


    newmarkedx1=max(detectorx1,markedx1);
    newmarkedy1=max(detectory1,markedy1);

    newmarkedx2=min(detectorx1+detectorwidth,markedx1+markedwidth);
    newmarkedy2=min(detectory1+detectorheight,markedy1+markedheight);

    /* you can open it to see the calculated values */

    /*

    printf("%lf\n",markedx1);
    printf("%lf\n",markedy1);
    printf("%lf\n",markedwidth);
    printf("%lf\n",markedheight);


    printf("%lf\n",newmarkedx1);
    printf("%lf\n",newmarkedy1);
    printf("%lf\n",newmarkedx2);
    printf("%lf\n",newmarkedy2);


    printf("%lf\n",*newmarkedx);
    printf("%lf\n",*newmarkedy);
    printf("%lf\n",*newmarkedregionx);
    printf("%lf\n",*newmarkedregiony);

    */
	
    /* new values are assigned to pointers */
	
    *newmarkedx=newmarkedx1+((newmarkedx2-newmarkedx1)/2);
    *newmarkedy=newmarkedy1+((newmarkedy2-newmarkedy1)/2);

    *newmarkedregionx=(newmarkedx2-newmarkedx1);
    *newmarkedregiony=(newmarkedy2-newmarkedy1);



    return 0;
}

double max(double a,double b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double min(double a,double b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
