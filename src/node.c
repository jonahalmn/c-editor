#include "node.h"

Node * node_create(char c) {
    Node *node = malloc(sizeof(Node));
    node->letter = c;
    node->next = NULL;
    return node;
}