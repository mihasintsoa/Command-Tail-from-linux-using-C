#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liat.h"


int countLine(FILE *f)
{
	int count = 0;
	char word[100];
	while ( (fgets(word,100,f) != 0) )
	{
		count++;
	}
	rewind(f);
	return (count);
}
int countCharact(FILE* f)
{
	int count = 0;
	char a;
	while ( !(feof(f)) )
	{
		a = fgetc(f);
		count++;
	}
	rewind(f);
	//printf("%d\n",count);
	return (count - 1);

}

FILE* f (char* argv,char* mode)
{
	FILE* a = NULL;
	a = fopen(argv,mode);
	if (a==NULL)
    {
        printf("Erreur ouverture");
        exit(1);
    }
    return a;
}

void option(int arg, char* argv[])
{
	int i, line, lineC;
	
	FILE *f = NULL;
	f = fopen(argv[arg - 1],"r");
	if ((f == NULL))
	{
		printf("ERROR WHEN LOADING THE FILE");
		exit(1);
	}
	if (arg == 2)
	{
		displayN(f,countLine(f),10);
	}
	else if (arg == 1)
	{
		displayHelp();
	}
	else
	{
		for ( i = 1; i <arg - 1;i++)
		{
			if ( (strcmp(argv[i],"-v")) == 0 && (strcmp(argv[i],"--verbose")) == 0)
			{
				printf("THE file name is :%s\n",argv[arg - 1]);
			}
			if ( (strcmp(argv[i],"-n")) == 0 && (strcmp(argv[i],"--lines")) == 0)
			{
				line = atoi(argv[i+1]);
				displayN(f,countLine(f),line);
			}
			if ( (strcmp(argv[i],"-c")) == 0 || (strcmp(argv[i],"--byte")) == 0 )
			{
				lineC = atoi(argv[i + 1]);
				displayC(f,countCharact(f),lineC);
			}
			if ( (strcmp(argv[i],"--help")) == 0 )
			{
				displayHelp();
			}
			if ( (strcmp(argv[i],"--version")) == 0 )
			{
				printf("Version 1.0.24 \n");
			}
			if ( (strcmp(argv[i],"-f")) == 0 )
			{
				FILE* file = NULL;
				file = fopen(argv[arg - 1],"r");
				int number = countLine(file);
				int num = number;
				num = atoi(argv[i + 1]);
				displayN(file,0,0);
				while(1)
				{
					int actualNumber = countLine(file);
					displayN(file,0,0);
					if (actualNumber != num)
					{
						displayN(file,actualNumber,0);
						number = actualNumber;
						system("sleep 2;clear");
					}
					fclose(file);
					file = fopen(argv[arg - 1], "r");
				}
			}
		}
	}
	
	fclose(f);
}

void displayN(FILE *f, int count,int line)
{
	int i = 0;
	char word[100];
	while ( !feof(f) )
	{
		fgets(word,100,f);
		if (i >= count - line)
		{
			printf("%s",word);
		}
		i++;
	}
}
void displayC(FILE* f, int countCharact, int value)
{
	char a;
	int i = 1;
	while (1)
	{
		a = fgetc(f);
		if (feof(f)) break;
		if (i >= (countCharact - value) )
		{
			printf("%c",a);
		}
		i++;
	}
}

void displayHelp()
{
    printf("Utilisation : executable [OPTION]... [FICHIER]...\n");
    printf("Afficher les 10 dernieres lignes de chaque FICHIER sur la sortie standard.\n");
    printf("Sans FICHIER ou quand FICHIER est -, afficher une demande.\n\n");
    printf("Les arguments disponible :\n");
    printf("-c, --bytes=[+]N ,-b        afficher les N derniers octets ; -c +N peut aussi\n");
    printf("                            être utilise pour afficher les octets a partir du\n");
    printf("                            Nieme de chaque fichier\n");
    printf(" -f, --follow[={name|descriptor}]\n");
    printf("                         afficher les donnees ajoutees au fur et a mesure\n");
    printf("                             que le fichier grandit ; sans argument, c’est\n");
    printf("                             equivalent a 'descriptor'\n");
    printf(" -n, --lines=[+]N         afficher les N dernieres lignes, au lieu des 10\n");

    printf("                             dernieres, -n +N pour afficher a partir de la Nieme\n");
    printf(" -v, --verbose            afficher toujours les en-têtes des noms de fichier\n");
    printf("     --help     afficher l'aide et quitter\n");
    printf("--version  afficher des informations de version et quitter\n\n");
    printf("FROM THE LINUX COMMAND TAIL write using the C Language\n\n");
    printf("WARNING: my -f option is not perfect. YOU WILL NOT BE ABLE TO USE CTRL + C TO STOP THE PROGRAMM\n ");
}
