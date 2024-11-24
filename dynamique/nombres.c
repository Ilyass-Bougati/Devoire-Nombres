#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <uchar.h>


char *get_string(char *prompt);
bool check_string_entier(char *string);
bool check_string_reel(char *string);
void read(char *string, int n);
void entier_to_text(char *entier);
char **read_numbers(char *file_path);
void reel_to_text(char *string);
bool is_real(char *string);

char *units[] = {
	"cent",
	"mille",
	"million",
	"milliard"
};

char **nombres;
bool negative;

int main()
{
	nombres = read_numbers("nombres.txt");
	char *input;
	int choix;

	do {
		input = get_string("Entrer un nombre : ");
	} while (check_string_reel(input));

	bool is_reel = is_real(input);
	printf("%s est un %s\n", input, is_reel ? "reel" : "entier");

	if (is_real)
	{
		reel_to_text(input);
	} else
	{
		entier_to_text(input);
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
		// check if the comma is the first character
		if (i == 1 + negative)
		{
			printf("zéro");
		}

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
				printf("zéro ");
			} else {
				printf("%s ", nombres[zeros]);
				printf("zéros ");
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
	
	// take into account the minus sign
	if (string[0] == '-')
	{
		negative = true;
		string++;
	}

	// checking for comma in as the first or last element of the number
	if (string[strlen(string) - 1] == '.')
	{
		string[strlen(string) - 1] = '\0';
	}

	int i, vigrule_counte = 0;

	if (strlen(string) > 12)
	{
		printf("la taille maximale est 12\n");
		return true;
	}

	// checking for non numerique characters and 2+ commas
	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] == '.')
		{
			vigrule_counte += 1;
			continue;
		} 
		if ((string[i] > '9' || string[i] < '0') || vigrule_counte > 1)
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
		negative = true;
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

// n <= 3
// n <= 3
void read(char *string, int n)
{
	n = n == 0 ? 3 : n;
	char buffer[4];
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

char **read_numbers(char *file_path)
{
	FILE *fptr = fopen(file_path, "r");
	char **nombres = NULL;
	char *line = NULL; 
	char character;
	int i = 0, j = 0;

	if (fptr == NULL)
	{
		printf("File couldn't be opened");
		exit(1);
	}

	while ((character = fgetc(fptr)) != EOF) {
		if (character == '\n')
		{
			// adding the null character at the end of the line
			line = (char *) realloc(line, (j + 1) * sizeof(char));
			line[j] = '\0';

			// getting to the next line
			nombres = (char **) realloc(nombres, (i + 1) * sizeof(char*));
			nombres[i++] = line;

			// creating a new line
			line = NULL;
			j = 0;
		} else {
			// adding a character to the line
			line = (char *) realloc(line, (j + 1) * sizeof(char));
			line[j++] = character;
		}
    }

	return nombres;
}

bool is_real(char *string)
{
	// checking for comma
	bool found_comma = false;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == '.')
		{
			found_comma = true;
			continue;
		}
		if (string[i] != '0' & found_comma)
		{
			// if the program reaches this point then the number is real
			return true;
		}
	}

	return false;
}
