#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <uchar.h>

#include "include/chiffres.h"

char *get_string(char *prompt);
bool check_string_entier(char *string);
bool check_string_reel(char *string);
bool check_strlen(char *string);
void read(char *string, int n);
void entier_to_text(char *entier);
void reel_to_text(char *string);
char **read_numbers(char *file_path);

char *units[] = {
	"cent",
	"mille",
	"million",
	"milliard"
};

int main()
{
	char *input;
	int choix;

	printf("Choisi si tu veux saisir un entier ou un reel :\n");
	printf("	1 - Entier\n");
	printf("	2 - Reel\n");
	do {
		printf("> ");
		scanf("%d", &choix);
		getchar();
	} while (choix != 1 && choix != 2);
	

	if (choix == 1)
	{
		do {
			input = get_string("Entrer un Entier : ");
		} while (check_string_entier(input) || check_strlen(input));
		entier_to_text(input);
	} else if (choix == 2)
	{
		do {
			input = get_string("Entrer un Reel : ");
		} while (check_string_reel(input) || check_strlen(input));
		reel_to_text(input);
	}
	printf("\n");
}


void reel_to_text(char *string)
{
	char character, *partie_fract, *partie_entiere;
	int i = 0, j = 0;
	
	// afficher la partie entier
	partie_entiere = (char *) malloc(sizeof(char));
	while ((character = string[i]) != '.' && character != '\0')
    {
        partie_entiere[i++] = character;
        partie_entiere = (char *) realloc(partie_entiere, (i + 1) * sizeof(char));
    }
	partie_entiere[i++] = '\0';
	entier_to_text(partie_entiere);

	// afficher la partie fractionnaire
	if (character == '.')
	{
		printf(" virgule ");
		// le nombre de zeros avant le virgule
		int zeros = 0;
		while (string[i] == '0')
		{
			zeros++;
			i++;
		}

		if (zeros != 0)
		{
			if (zeros == 1)
			{
				printf("z\x82ro ");
			} else {
				printf("%s ", nombres[zeros]);
				printf("z\x82ros ");
			}
		}

		partie_fract = (char *) malloc(sizeof(char));
		while ((character = string[i]) != '\0')
		{
			partie_fract[j++] = character;
			partie_fract = (char *) realloc(partie_fract, (j + 1) * sizeof(char));
			i++;
		}
		partie_fract[j] = '\0';
		
		entier_to_text(partie_fract);
	}
}


// convertir les chiffres au mots
void entier_to_text(char *entier)
{
	// Le cas special de 0
	if (!strcmp(entier, "0"))
	{
		printf("%s", nombres[0]);
		return;
	}

	// afficher "moins" si le premier charactere est '-'
	if (entier[0] == '-')
	{
		printf("moins ");
		entier++;
	}

	int i = 0; 
	int len = strlen(entier);
	int j = (len - 1)/ 3;
	while (i < len && j >= 0)
	{
		read(entier + i, (len - i) % 3);
		if (j != 0)
		{
			printf(" %s ", units[j--]);
		}
		i += (len - i) % 3 ? (len - i) % 3 : 3;
	}
}

// saisir une chaine de characters
char *get_string(char *prompt)
{
	printf("%s", prompt);
	char *chaine, character;
    int i = 0;
    chaine = (char *) malloc(sizeof(char));
    while ((character = getchar()) != '\n')
    {
        chaine[i++] = character;
        chaine = (char *) realloc(chaine, (i + 1) * sizeof(char));
    }
    chaine[i] = '\0';

    return chaine;
}

// verifer qu'une chaine de characters peut etre convertir a un reel
bool check_string_reel(char *string)
{
	int i, vigrule_counte = 0;
	if (string[0] == '-')
	{
		string++;
	}

	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] == '.')
		{
			vigrule_counte += 1;
		} 
		if (string[i] > '9' || string[i] < '0' || vigrule_counte > 1)
		{
			printf("Reel non valide\n");
			return true;
		}
	}
	return false;
}

bool check_string_entier(char *string)
{
	int i;
	if (string[0] == '-')
	{
		string++;
	}

	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] > '9' || string[i] < '0')
		{
			printf("Entier non valide\n");
			return true;
		}
	}
	return false;
}

// verifier que la taille de entier est inferieur a 13
bool check_strlen(char *string)
{
	if (strlen(string) > 12)
	{
		printf("la taille maximale est 12\n");
		return true;
	}
	return false;
}

// n <= 3
void read(char *string, int n)
{
	n = n == 0 ? 3 : n;
	char buffer[3];
	int i;
	for (i = 0; i < n; i++)
	{
		buffer[i] = string[i];
	}
	buffer[i] = '\0';

	int entier = atoi(buffer);
	if (entier != 0)
	{
		printf("%s", nombres[entier]);
	}	
}
