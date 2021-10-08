#include <stdlib.h>
#include <stdbool.h>
#include "structs.h" //Node, String
#include "nodes.h"
#include "alloc.h" //alloc_node(), alloc_str(), free_str(), free_all()
#include "tests.h" //correct_str(), test(), compare(), min(), max()

//funkcja zwracajaca najwieksza dlugosc poddrzewa danego wierzcholka
int height_f(Node *node)
{
	if (node == NULL)
		return 0;
	else return (*node).height;
}

//funkcja tworzaca nowy wierzcholek pod adresm node_m
//node_l i node_m to adresy kolejno lewego i prawego poddrzewa
//zwraca utworzony wierzcholek
Node *make(Node *node_l, Node *node_m, Node *node_r)
{
	Node *node;
	node = node_m;
	(*node).left = node_l;
	(*node).right = node_r;
	(*node).height = max(height_f(node_l), height_f(node_r)) + 1;
	return node;
}

//funkcja balansujaca drzewo w danym wierzcholku
//najpierw sprawdza czy roznica wysokosci lewego i prawego poddrzewa nie jest za duza
//w przypadku gdy ta roznica jest za duza zbiera dane z prawego i lewego poddrzewa i wywoluje funkcje make()
//zwraca zbalansowane drzewo
Node *bal(Node *node)
{
	Node *l = (*node).left;
	Node *r = (*node).right;
	int hl = height_f(l);
	int hr = height_f(r);
	if (hl > hr + 1)
	{
		Node *ll = (*l).left;
		Node *lr = (*l).right;
		int hll = height_f(ll);
		int hlr = height_f(lr);
		if (hll >= hlr)
			node = make(ll, l, make(lr, node, r));
		else
		{
			Node *lrl = (*lr).left;
			Node *lrr = (*lr).right;
			node = make(make(ll, l, lrl), lr, make(lrr, node, r));
		}
	}
	else if (hr > hl + 1)
	{
		Node *rl = (*r).left;
		Node *rr = (*r).right;
		int hrl = height_f(rl);
		int hrr = height_f(rr);
		if (hrr >= hrl)
			node = make(make(l, node, rl), r, rr);
		else
		{
			Node *rll = (*rl).left;
			Node *rlr = (*rl).right;
			node = make(make(l, node, rll), rl, make(rlr, r, rr));
		}
	}
	else (*node).height = max(hl, hr) + 1;
	return node;
}

//funkcja add() dodaje do drzewa nowy wierzcholek (w miejscu o adresie alloc) o etykiecie takiej jak str
//etykieta nowego wierzcholka zapisana jest pod adresem n_str
//po dodaniu wierzcholka przebudowuje drzewo i na koniec zwraca wierzcholek bedacy jego korzeniem
//do porownywania stringow korzysta z funkcji compare()
//uzywa funkcji bal() do balansowania zmienionego drzewa
//jezeli juz istnieje wierzcholek o danej etykiecie, nie dodaje zadnego nowego
Node *add(Node *node, String str, Node *alloc, unsigned char *n_str)
{
	if (node == NULL)
	{
		(*alloc).height = 1;
		(*alloc).length = str.length;
		for(int i = 0; i <= str.length; i++)
			n_str[i] = (str.p)[i];
		(*alloc).name = n_str;
		(*alloc).root = (*alloc).left = (*alloc).right = NULL;
		return alloc;
	}
	int cmp = compare(str.p, str.length, (*node).name, (*node).length);
	if (cmp == 1)
	{
		(*node).left = add((*node).left, str, alloc, n_str);
		node = bal(node);
	}
	else if (cmp == -1)
	{
		(*node).right = add((*node).right, str, alloc, n_str);
		node = bal(node);
	}
	return node;
}

//funkcja take_p() zwraca wierzcholek majacy najmniejsza pod wzgledem porzadku leksykograficznego etykiete w drzewie o korzeniu w wierzcholku node
//schodzi w dol po lewych poddrzewach az znajdzie szukany wierzcholek
Node *min_el(Node *node)
{
	if ((*node).left == NULL)
		return node;
	else return min_el((*node).left);
}

//funkcja usuwajaca z drzewa wierzcholek o minimalnej pod wzgledem porzadku leksykograficznego atykiecie
//balansuje zmienione drzewo i na koncu je zwraca
//korzysta z funkcji min_el() i bal() do modyfukowania drzewa
Node *del_min(Node *node)
{
	if ((*node).left == NULL)
		return (*node).right;
	else 
	{
		(*node).left = del_min((*node).left);
		node = bal(node);
		return node;
	}
}

//funkcja tworzaca drzewo skladajace sie z lewego i prawego poddrzewa danego wierzcholka
//zwraca to drzewo
//zwalnia pamiec przetrzymujaca dany wierzcholek oraz jego etykiete
//do tworzenia nowego poddrzewa w przypadku gdy lewe i prawe poddrzewo sa niepuste uzywa make(), bal(), del_min() oraz min_el()
Node *merge(Node *node)
{
	Node *l = (*node).left;
	Node *r = (*node).right;

	free((*node).name);
	free(node);

	if (l == NULL)
		return r;
	else if (r == NULL)
		return l;
	else 
	{
		Node *node_m = min_el(r);
		return bal(make(l, node_m, del_min(r)));
	}
}

//funkcja usuwajaca wierzcholek o etykiecie takiej jak ta w str
//jezeli takiej nie ma, nic nie usuwa
//gdy taki znajdzie, uzywa merge() do usuniecia oraz free_all() do zwolnienia pamieci trzymajacej swiat reprezentowany przez dany wierzcholek
//uzywa bal() do balansowania zmienionego drzewa
Node *del(Node *node, String str)
{
	if (node == NULL)
		return NULL;

	int cmp = compare(str.p, str.length, (*node).name, (*node).length);

	if (cmp == 1)
	{
		(*node).left = del((*node).left, str);
		node = bal(node);
	}
	else if (cmp == 0)
	{
		if ((*node).root != NULL)
			free_all((*node).root);
		node = merge(node);
	}
	else
	{
		(*node).right = del((*node).right, str);
		node = bal(node);
	}
	return node;
}