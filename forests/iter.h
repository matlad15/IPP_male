#ifndef ITER_H
#define ITER_H

Node *take_p(Node *node, String str);

bool check(Node *node, String str);

void check1(Node *node, String *str, int cnt, int limit, bool *ans);

void iter(Node *node);

#endif /* ITER_H */