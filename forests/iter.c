#include <stdio.h>
#include <stdbool.h>
#include "structs.h" //Node, String
#include "iter.h"
#include "tests.h" //correct_str(), test(), compare(), min(), max()


//funkcja zwracajaca wierzcholek o identycznej etykiecie jak ta w str
//jezeli nie ma takiego wierzcholka, zwraca NULL
//do porownywania stringow uzywa compare()
Node *take_p(Node *node, String str)
{
	if (node == NULL)
		return NULL;

	int cmp = compare(str.p, str.length, (*node).name, (*node).length);

	if (cmp == 1)
		return take_p((*node).left, str);
	else if (cmp == 0)
		return node;
	else
		return take_p((*node).right, str);
}

//funkcja zwracajaca true jezeli w danym drzewie znajduje sie wierzcholek o etykiecei takiej samej jak str
//zwraca false jezeli takiego nie znajdzie
//do porownywania stringow uzywa funkcji compare()
bool check(Node *node, String str)
{
	if (node == NULL)
		return false;

	int cmp = compare(str.p, str.length, (*node).name, (*node).length);

	if (cmp == 1)
		return check((*node).left, str);
	else if (cmp == 0)
		return true;
	else
		return check((*node).right, str);
}

//funkcja sprawdzajaca czy w danym swiecie wystepuje byt reprezentowany przez tablice stringow pod adresem str
//jezeli funkcja znajdzie jeden z szukanych bytow, zaczyna szukac nastepnego w swiecie reprezentowanym przez znaleziony byt
//w zmiennej pod adresen ans trzyma true jezeli znajdzie wszystkie byty albo false jezeli nie znajdzie
void check1(Node *node, String *str, int cnt, int limit, bool *ans)
{
	if (node == NULL)
		return;

	if (cnt < limit)
	{
		if (str[cnt].length == 0 && (str[cnt].p)[0] == '*')
		{
			check1((*node).left, str, cnt, limit, ans);
			check1((*node).right, str, cnt, limit, ans);
			check1((*node).root, str, cnt + 1, limit, ans);
		}
		else if (check(node, str[cnt]))
		{
			Node *n_node = take_p(node, str[cnt]);
			check1((*n_node).root, str, cnt + 1, limit, ans);
		}
	}
	else if (cnt == limit)
		*ans = max(*ans, check(node, str[cnt]));
}

//funkcja iterujaca sie po drzewie i wypisujaca etykiety w jego wierzcholkach w kolejnosci leksykograficznej
void iter(Node *node)
{
	Node *l = (*node).left;
	Node *r = (*node).right;

	if (l != NULL)
		iter(l);

	unsigned char *str = (*node).name;
	for (int i = 0; i <= (*node).length; i++)
		printf("%c", str[i]);
	printf("\n");
	
	if (r != NULL)
		iter(r);
}