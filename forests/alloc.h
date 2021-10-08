#ifndef ALLOC_H
#define ALLOC_H

Node *alloc_node();

unsigned char *alloc_name(String str);

void free_str(String *in_str);

void free_all(Node *node);

#endif /* ALLOC_H */