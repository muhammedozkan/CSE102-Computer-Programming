/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h>

char dataarr[100];
int datacount = 0;

void readtext(void);
void printtree(int, int);

int main(void)
{
	readtext();

	printtree(0, 0);
}

void readtext(void)
{
	FILE *readfile;
	readfile = fopen("input.txt", "r");

	int status = 1;
	char data;
	while (1)
	{
		status = fscanf(readfile, "%c", &data);
		if (status == EOF)
		{
			break;
		}
		else
		{
			dataarr[datacount] = data;
			datacount++;
		}
	}

	fclose(readfile);
}

void printtree(int _level, int _first)
{

	if (dataarr[_first] == '(')
	{
		_level++;
		_first++;
	}
	else if (dataarr[_first] == ')')
	{
		_level--;
		_first++;
	}
	else if (dataarr[_first] == ',')
	{
		_first++;
	}
	else
	{
		for (int i = 0; i < _level; i++)
		{
			printf("-");
		}
		printf("%c\n", dataarr[_first]);
		_first++;
	}
	if (_first != datacount)
	{
		printtree(_level, _first);
	}
}