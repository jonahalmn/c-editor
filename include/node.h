#pragma once
#include "commons.h"

typedef struct node Node;

struct node
{
    char letter;
    Node * next;
};

Node * node_create(char c);