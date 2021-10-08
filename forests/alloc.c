#include <stdlib.h>
#include "structs.h" //Node, String
#include "alloc.h"

//alokowanie pamieci pod strukture Node
Node *alloc_node()
{
	Node *alloc = (Node*)malloc(sizeof(Node));
	return alloc;
}

//alokowanie pamieci na strukture String o wielkosci takiej jak str
unsigned char *alloc_name(String str)
{
	unsigned char *alloc = (unsigned char*)malloc(sizeof(unsigned char) * (str.length + 2));
	return alloc;
}

//funkcja zwalniajaca pamiec trzymajaca etykiety w stringach
void free_str(String *in_str)
{
	if (in_str[0].p != NULL)
		free(in_str[0].p);
	if (in_str[1].p != NULL)
		free(in_str[1].p);
	if (in_str[2].p != NULL)
		free(in_str[2].p);
	if (in_str[3].p != NULL)
		free(in_str[3].p);
}

//funkcja free_all() zwalnia pamiec przechowujaca rozne struktury drzewiaste
//najpierw zwalnia pamiec przechowujaca wszystkie swiaty z lewego i prawego poddrzewa
//na koniec zwalnia pamiec przechowujaca swiat reprezentowany przez dany wierzcholek
void free_all(Node *node)
{
	Node *l = (*node).left;
	Node *r = (*node).right;

	if (l != NULL)
		free_all(l);

	if (r != NULL)
		free_all(r);

	if ((*node).root != NULL)
		free_all((*node).root);

	free((*node).name);
	free(node);
}