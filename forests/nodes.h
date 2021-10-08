#ifndef NODES_H
#define NODES_H

int height_f(Node *node);

Node *make(Node *node_l, Node *node_m, Node *node_r);

Node *bal(Node *node);

Node *add(Node *node, String str, Node *alloc, unsigned char *n_str);

Node *min_el(Node *node);

Node *del_min(Node *node);

Node *merge(Node *node);

Node *del(Node *node, String str);

#endif /* NODES_H */