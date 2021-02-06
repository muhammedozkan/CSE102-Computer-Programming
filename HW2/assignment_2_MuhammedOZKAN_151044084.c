/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h> /* definitions of printf,scanf */

/* definitions of constants used in the program */

double textdata[1024];//read file into array
int datacount=0;

double chunk[1024][1024];
int chunkcount=0;
double chunksize[1024];

double avgchunk[1024][2];


/* function prototype*/


 void   readtext(void); /*function that gets data from input.txt*/
 void   createchunk(void); /*function that divides the data stack*/
 void   averagechunk(void); /*average function*/
 void   averagesort(void); /*sorting average / using bubble sort algoritms*/
 void   writetext(void); /*function that stores data in output.txt*/




int main(void)
{
    readtext();
    createchunk();
    averagechunk();
    averagesort();
    writetext();
}




void readtext(void)
{
    FILE *readfile;
    readfile = fopen("input.txt", "r");

    int status=1;

  while(status>0)
    {
    status=fscanf(readfile, "%lf", &textdata[datacount]);
    if(status>0)
        {
            datacount++;
        }
    }

fclose(readfile);
}


void writetext(void)
{
    FILE *writefile;
    writefile = fopen("output.txt", "w");

         for(int i=0;i<=chunkcount;i++)
         {
             for(int j=0;j<chunksize[(int)avgchunk[i][0]];j++)// data convert double to int
             {
                 fprintf(writefile, "%lf ",chunk[(int)avgchunk[i][0]][j]);
             }
             fprintf(writefile, "\n");
         }


    fclose(writefile);
}




void createchunk(void)
{
    int row=0;
    int col=0;

    int lock=0;

    for(int i=0;i<datacount;i++)
		{
        if(textdata[i]!=0.0 && lock==0)
			{
            lock=0;
            chunk[row][col]=textdata[i];
            col++;
            chunksize[row]=col;
			}
        else
        {
            if(textdata[i]==0.0 && textdata[i + 1]==0.0 && textdata[i + 2]==0.0 && lock==0)
				{
                row++;
                chunkcount++;
                col=0;
                i+=2;
                lock=1;

				}
            else if(textdata[i]==0.0 )
				{
                chunk[row][col]=textdata[i];
                col++;
                chunksize[row]=col;
				}
	
        }

        if(textdata[i]!=0.0 && lock==1)
			{
            lock=0;
            chunk[row][col]=textdata[i];
            col++;
            chunksize[row]=col;
			}


    }


}

void averagechunk(void)
{
 double sumchunk;
    for(int i=0;i<=chunkcount;i++)
      {
             sumchunk=0;
             for(int j=0;j<chunksize[i];j++)
             {
                 sumchunk+=chunk[i][j];
             }
             avgchunk[i][0]=i;
             avgchunk[i][1]=sumchunk/chunksize[i];
      }
}

 void averagesort(void)
 {
 double tempavg,tempid;

 for (int i = 0; i <= (chunkcount - 1); i++)
 {
      for (int j = 0; j <= (chunkcount - 1 - i); j++ )
      {
           if (avgchunk[j][1] > avgchunk[j+1][1])
           {
                tempavg = avgchunk[j+1][1]; //transfer average
                avgchunk[j+1][1] = avgchunk[j][1];
                avgchunk[j][1] = tempavg;

                tempid = avgchunk[j+1][0];  //transfer chunk id
                avgchunk[j+1][0] = avgchunk[j][0];
                avgchunk[j][0] = tempid;
           }
      }
 }
 }