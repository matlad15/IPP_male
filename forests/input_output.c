#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h" //Node, String
#include "input_output.h"
#include "tests.h" //correct_str(), test(), compare(), min(), max()


//funkcja read() tworzy etykiete dla stringa o adresie str
//oprocz wskaznika na stringa funkcja read przyjmuje pierwszy znak nowej etykiety stringa
//funkcja wczytuje znak po znaku i przerywa wczytywanie po wczytaniu znaku bialego lub "\n" lub EOF
//gdy nie ma zaalokowanej wystarczajacej ilosci pamieci alokuje nowa, 2 razy wieksza pamiec
//funkja ta konczy program i zwalnia cala zaalokowana w programie pamiec w momencie bledu w alokacji pamieci
//zwraca ostatni wczytany znak
int read(String *str, int c)
{
	int size = 1;
	(*str).p = (unsigned char*)malloc(sizeof(unsigned char) * 2);

	if ((*str).p != NULL)
		((*str).p)[0] = c;

	while (test(c = getchar()) && c != '\n' && c != EOF)
	{
		(*str).length++;

		if ((*str).length >= size)
		{
			size *=2;
			unsigned char *n_str = NULL;
			if ((*str).p != NULL)
				n_str = (unsigned char*)realloc((*str).p, sizeof(unsigned char) * (size + 1));
			(*str).p = n_str;
		}

		if ((*str).p != NULL)
			((*str).p)[(*str).length] = c;
	}

	return c;
}

//funkcja input() wczytuje caly wiersz wejscia
//przyjmuje jako argumenty:
	//wskaznik do tablicy stringow
	//adres zmiennej com, ktora przyjmuje 1 gdy pierwszym znakiem wiersza jest '#' i 0 w.p.p.
	//adres znaku last przechowujacego ostatni znak wiersza
//gdy napotka znak nie bedacy znakiem bialym wywoluje funkcje read()
//zlicza ilosc stworzonych stringow i zwraca ja
//jezeli w wierszu napotka jeden znak i bedzie to EOF, zwraca -1
int input(String *str_a, bool *com, int *last)
{
	int nr = 0;
	int c;
	int count = 0;

	while ((c = getchar()) != '\n' && c != EOF)
	{
		nr++;
		if (nr == 1 && c == '#')
			*com = 1;

		*last = c;

		if (test(c))
		{
			count++;
			if (count <= 4)
			{
				c = read(&str_a[count - 1], c);
				unsigned char *n_str = NULL;
				if (str_a[count - 1].p != NULL)
					n_str = (unsigned char*)realloc(str_a[count - 1].p, sizeof(unsigned char) * (str_a[count - 1].length + 2));
				str_a[count - 1].p = n_str;
			}

			*last = c;
			if (c == '\n' || c == EOF)
				break;
		}
	}

	*last = c;
	return count;
}

//funkcja error() wypisuje "ERROR" na stderr
void error(void)
{
	fprintf(stderr, "ERROR\n");
}

//funkcja yes() wypisuje "YES" na stdout
void yes()
{
	printf("YES\n");
}

//funkcja no() wypisuje "NO" na stdout
void no()
{
	printf("NO\n");
}

//funkcja ok() wypisuje "OK" na stdout
void ok()
{
	printf("OK\n");
}