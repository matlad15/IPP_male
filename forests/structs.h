#ifndef STRUCTS_H
#define STRUCTS_H

//deklaracja struktury String
//p to wskaznik to pamieci zaalokowanej do etykiety stringa
//length to dlugosc stringa
struct String
{
	unsigned char *p;
	int length;
};

typedef struct String String;

//deklaracja struktury Node
//height to najdluzsza wysokosc poddrzewa
//length to dlugosc etykiety wierzcholka
//name to wskaznik do etykiety wierzcholka
//root to wskaznik do struktury trzymajacej wszystkie elementy swiata w danym wierzcholku
//left to wskaznik do lewego poddrzewa
//right to wskaznik do prawego poddrzewa
struct Node;

typedef struct Node Node;

struct Node
{
	int height;
	int length;
	unsigned char *name;
	Node *root, *left, *right;
};

#endif /* STRUCTS_H */