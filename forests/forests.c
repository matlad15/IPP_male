#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h" //Node, String
#include "input_output.h" //read(), input(), error(), yes(), no(), ok()
#include "iter.h" //take_p(), check(), check1(), iter()
#include "nodes.h" //height(), make(), bal(), add(), min_el(), del_min(), merge(), del()
#include "alloc.h" //alloc_node(), alloc_name(), free_str(), free_all()
#include "tests.h" //correct_str(), test(), compare(), min(), max()

int main()
{
	int last = '*'; //ostatni znak wczytywanych wierszy

	Node *main_root = NULL; //wskaznik do korzenia glownej struktury

	while (last != EOF)
	{
		String in_str[4]; //tablica stringow wejsciowych

		//deklaracja pol w strukturze stringow wejsciowych
		in_str[0].p = in_str[1].p = in_str[2].p = in_str[3].p = NULL;
		in_str[0].length = in_str[1].length = in_str[2].length = in_str[3].length = 0;

		bool com = 0; //zmienna przyjmujaca 1, gdy pierwszy znak w wierszu to '#' i 0 w.p.p.

		//wczytywanie wiersza
		int count = input(in_str, &com, &last); //count trzyma ilosc stringow w wierszu

		//sprawdzenie poprawnosci alokowania pamieci na stringi wejsciowe
		//jezeli wystapil blad w alokowaniu pamieci, zwalniana jest cala pamiec i zamykany jest program
		if (count >= 1 && in_str[0].p == NULL)
		{
			free_str(in_str);
			if (main_root != NULL)
				free_all(main_root);
			exit(1);
		}
		if (count >= 2 && in_str[1].p == NULL)
		{
			free_str(in_str);
			if (main_root != NULL)
				free_all(main_root);
			exit(1);
		}
		if (count >= 3 && in_str[2].p == NULL)
		{
			free_str(in_str);
			if (main_root != NULL)
				free_all(main_root);
			exit(1);
		}
		if (count >= 4 && in_str[3].p == NULL)
		{
			free_str(in_str);
			if (main_root != NULL)
				free_all(main_root);
			exit(1);
		}

		//pusty wiersz
		if (count == 0)
			continue;

		//jezeli pierwszy znak w wierszu to '#', zwalniamy pamiec trzymajaca wejsciowe stringi ignorujemy reszte dzialan dla tego wiersza
		if (com == 1)
		{
			free_str(in_str);
			continue;
		}

		//brak znaku nowej linii na koncu wiersza
		if (last != '\n')
		{
			free_str(in_str);
			error();
			continue;
		}

		//sprawdzenie poprawnosci stringow wejsciowych
		if (count >= 1 && correct_str(in_str[0]) == false)
		{
			error();
			free_str(in_str);
			continue;
		}
		if (count >= 2 && correct_str(in_str[1]) == false)
		{
			error();
			free_str(in_str);
			continue;
		}
		if (count >= 3 && correct_str(in_str[2]) == false)
		{
			error();
			free_str(in_str);
			continue;
		}
		if (count >= 4 && correct_str(in_str[3]) == false)
		{
			error();
			free_str(in_str);
			continue;
		}


		//dzialania w przypadku gdy pierwszy string ma 3 znaki
		if (in_str[0].length == 2)
		{
			//dodawanie elementow do swiata
			if ((in_str[0].p)[0] == 'A' && (in_str[0].p)[1] == 'D' && (in_str[0].p)[2] == 'D')
			{
				if (count < 2 || count > 4) //bledne wejscie
					error();
				else
				{
					if (count >= 2) //dodawanie lasow
					{
						if (check(main_root, in_str[1]) == false)
						{
							Node *n_node = alloc_node();
							unsigned char *n_name = alloc_name(in_str[1]);
							if (n_node == NULL || n_name == NULL)
							{
								if (main_root != NULL)
									free_all(main_root);
								free_str(in_str);
								exit(1);
							}
							main_root = add(main_root, in_str[1], n_node, n_name);
						}
					}

					if (count >= 3) //dodawanie drzew
					{
						Node *forest = take_p(main_root, in_str[1]);
						if (check((*forest).root, in_str[2]) == false)
						{
							Node *n_node = alloc_node();
							unsigned char *n_name = alloc_name(in_str[2]);
							if (n_node == NULL || n_name == NULL)
							{
								if (main_root != NULL)
									free_all(main_root);
								free_str(in_str);
								exit(1);
							}
							(*forest).root = add((*forest).root, in_str[2], n_node, n_name);
						}
					}

					if (count >= 4) //dodawanie zwierat
					{
						Node *forest = take_p(main_root, in_str[1]);
						Node *tree = take_p((*forest).root, in_str[2]);
						if (check((*tree).root, in_str[3]) == false)
						{
							Node *n_node = alloc_node();
							unsigned char *n_name = alloc_name(in_str[3]);
							if (n_node == NULL || n_name == NULL)
							{
								if (main_root != NULL)
									free_all(main_root);
								free_str(in_str);
								exit(1);
							}
							(*tree).root = add((*tree).root, in_str[3], n_node, n_name);
						}
					}

					ok();
				}
			}
			//usuwanie elementow ze swiata
			else if ((in_str[0].p)[0] == 'D' && (in_str[0].p)[1] == 'E' && (in_str[0].p)[2] == 'L')
			{
				if (count > 4) //bledne wejscie
					error();
				else
				{
					if (count == 1) //usuwanie calego swiata
					{
						if (main_root != NULL)
							free_all(main_root);
						main_root = NULL;
					}
					else if (count == 2) //usuwanie lasow
					{
						if (check(main_root, in_str[1]))
							main_root = del(main_root, in_str[1]);
					}
					else if (count == 3) //usuwanie drzew z lasow
					{
						if (check(main_root, in_str[1]))
						{
							Node *forest = take_p(main_root, in_str[1]);
							if (check((*forest).root, in_str[2]))
								(*forest).root = del((*forest).root, in_str[2]);
						}
					}
					else if (count == 4) //usuwanie zwierzat z drzew w danych lasach
					{
						if (check(main_root, in_str[1]))
						{
							Node *forest = take_p(main_root, in_str[1]);
							if (check((*forest).root, in_str[2]))
							{
								Node *tree = take_p((*forest).root, in_str[2]);
								if (check((*tree).root, in_str[3]))
									(*tree).root = del((*tree).root, in_str[3]);
							}
						}
					}
					ok();
				}
			}
			else error();
		}
		//dzialania w przypadku gdy pierwszy string ma 5 znakow
		else if (in_str[0].length == 4)
		{
			//wypisywanie elementow na stdout
			if ((in_str[0].p)[0] == 'P' && (in_str[0].p)[1] == 'R' && (in_str[0].p)[2] == 'I' && (in_str[0].p)[3] == 'N' && (in_str[0].p)[4] == 'T')
			{
				if (count > 3) //bledne wejscie
					error();
				else
				{
					if (count == 1) //wypisywanie lasow
					{
						if (main_root != NULL)
							iter(main_root);
					}
					else if (count == 2) //wypisywanie drzew z lasow
					{
						if (check(main_root, in_str[1]))
						{
							Node *forest = take_p(main_root, in_str[1]);
							if ((*forest).root != NULL)
								iter((*forest).root);
						}
					}
					else if (count == 3) //wypisywanie zwierzat z drzew w danym lesie
					{
						if (check(main_root, in_str[1]))
						{
							Node *forest = take_p(main_root, in_str[1]);
							if (check((*forest).root, in_str[2]))
							{
								Node *tree = take_p((*forest).root, in_str[2]);
								if ((*tree).root != NULL)
									iter((*tree).root);
							}
						}
					}
				}
			}
			//sprawdzanie istnienia danych elementow
			else if ((in_str[0].p)[0] == 'C' && (in_str[0].p)[1] == 'H' && (in_str[0].p)[2] == 'E' && (in_str[0].p)[3] == 'C' && (in_str[0].p)[4] == 'K')
			{
				bool ans = 0; //zmienna przetrzymujaca 1, gdy dany element istnieje, 0 gdy nie istnieje oraz 2 gdy dane wejsciowe sa niepoprawne ('*' jako ostatni argument)

				if (count >= 2 && count <= 4) //sprawdzanie poprawnosci wejscia
				{
					if (count == 2 && in_str[1].length == 0 && (in_str[1].p)[0] == '*') //sprawdzanie poprawnosci wejscia
						error();
					else if (count == 3 && in_str[2].length == 0 && (in_str[2].p)[0] == '*') //sprawdzanie poprawnosci wejscia
						error();
					else if (count == 4 && in_str[3].length == 0 && (in_str[3].p)[0] == '*') //sprawdzanie poprawnosci wejscia
						error();
					else
					{
						check1(main_root, in_str, 1, count - 1, &ans); //sprawdzanie istnienia danego elementu
						if (ans == false)
							no();
						else if (ans == true)
							yes();
					}
				}
				else error();
			}
			else error();
		}
		else error();

		//zwalnianie pamieci przetrzymujacej wejsciowe stringi
		free_str(in_str);
	}

	//zwalnianie pamieci przetrzymujacej caly swiat
	if (main_root != NULL)
		free_all(main_root);

	exit(0);
}