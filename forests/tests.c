#include <stdbool.h>
#include "structs.h" //Node, String
#include "tests.h"


//funkcja corect_str() sprawdza czy dany string ma etykiete skladajaca sie ze znakow o kodach ASCII od 33 do 255
//jezeli string jest poprawny zwraca true
//jezeli nie zwraca false
bool correct_str(String str)
{
	for (int i = 0; i <= str.length; i++)
	{
		if ((str.p)[i] < 33)
			return false;
	}
	return true;
}

//funkcja test() sprawdza czy dany znak nie jest znakiem bialym
//zwraca false w przypadku gdy dany znak jest bialy i true w.p.p.
bool test(int c)
{
	if (c != ' ' && c != '\t' && c != '\v' && c != '\f' && c != '\r')
		return true;
	else return false;
}

//funkcja porownujaca leksykograficznie 2 stringi
//zwraca 1 jezele 1. jest < niz 2.
//zwraca 0 jezeli oba stringi sa identyczne
//zwraca -1 jezeli 1. jest > niz 2.
int compare(unsigned char *str1, int size1, unsigned char *str2, int size2)
{
	for (int i = 0; i <= min(size1, size2); i++)
	{
		if (str1[i] < str2[i])
			return 1;
		else if (str1[i] > str2[i])
			return -1;
	}
	
	if (size1 < size2)
		return 1;
	else if (size1 == size2)
		return 0;
	else return -1;
}

//funkcja zwracajaca minimum 2 liczb
int min(int a, int b)
{
	if (a <= b) 
		return a;
	else return b;
}

//funkcja zwracajaca maximum 2 liczb
int max(int a, int b)
{
	if (a >= b)
		return a;
	else return b;
}