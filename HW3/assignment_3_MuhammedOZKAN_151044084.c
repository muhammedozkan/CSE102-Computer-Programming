/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h> /* definitions of printf,scanf */

/* definitions of constants used in the program */

char textdata[250][100];//read file into array
char data;
int datacountrow=0;
int datacountcol=0;

int textdatasize[250];

/* function prototype*/

void readtext(void);/*function that gets data from input.txt*/
int word_check_hor(int x,int y, char word[], int wordsize);/*function that control to array horizontal*/
int word_check_ver(int x,int y, char word[], int wordsize);/*function that control to array vertical*/
void check_word(int wordid);



int main(void)
{
    readtext();
check_word(1);
check_word(2);
check_word(3);
check_word(4);
check_word(5);

}

void readtext(void)
{
    FILE *readfile;
    readfile = fopen("input.txt", "r");

    int status=1;

  while(1)
    {
     status=fscanf(readfile, "%c",&data);
     if(status==EOF)
     {
        break;
     }
     
    if(data=='\n')
        {
            datacountrow++;
            datacountcol=0;
           
        }
        else
        {
        textdata[datacountrow][datacountcol]=data;
        datacountcol++;
        textdatasize[datacountrow]=datacountcol;
        
        }
    }
fclose(readfile);
}

int word_check_hor(int x,int y, char word[], int wordsize)
{
	int valid=0;
	for(int i=0;i<wordsize;i++)
	{
		if(textdata[x][y+i]==word[i])
		{
			valid++;
		}
		else
		{
			return 0;
		}
		
	}
	
	return valid;
	
}

int word_check_ver(int x,int y, char word[], int wordsize)
{
	int valid=0;
	for(int i=0;i<wordsize;i++)
	{
		if(textdata[x+i][y]==word[i])
		{
			valid++;
		}
		else
		{
			return 0;
		}
		
	}
	
	return valid;
	
}

void check_word(int wordid)
{
for(int i=0;i<=datacountrow;i++)
{
    for(int k=0;k<textdatasize[i];k++)
    {
		
		if(wordid==1)
		{
		if(word_check_hor(i,k,"Xanthos",7)){printf("Xanthos (%d,%d) Horizontal\n",i+1,k+1);}
		if(word_check_ver(i,k,"Xanthos",7)){printf("Xanthos (%d,%d) Vertical\n",i+1,k+1);}
		}
		if(wordid==2)
		{
		if(word_check_hor(i,k,"Patara",6)){printf("Patara (%d,%d) Horizontal\n",i+1,k+1);}
		if(word_check_ver(i,k,"Patara",6)){printf("Patara (%d,%d) Vertical\n",i+1,k+1);}
		}
		if(wordid==3)
		{
		if(word_check_hor(i,k,"Myra",4)){printf("Myra (%d,%d) Horizontal\n",i+1,k+1);}
		if(word_check_ver(i,k,"Myra",4)){printf("Myra (%d,%d) Vertical\n",i+1,k+1);}
		}
		if(wordid==4)
		{
		if(word_check_hor(i,k,"Arycanda",8)){printf("Arycanda (%d,%d) Horizontal\n",i+1,k+1);}
		if(word_check_ver(i,k,"Arycanda",8)){printf("Arycanda (%d,%d) Vertical\n",i+1,k+1);}
		}
		if(wordid==5)
		{
		if(word_check_hor(i,k,"Phaselis",8)){printf("Phaselis (%d,%d) Horizontal\n",i+1,k+1);}
		if(word_check_ver(i,k,"Phaselis",8)){printf("Phaselis (%d,%d) Vertical\n",i+1,k+1);}
		}
		
		
		
		
		
    }
	
}



}




