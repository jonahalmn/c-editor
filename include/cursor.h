#pragma once
#include "commons.h"
#include "node.h"

typedef struct 
{
    Node * prev;
    Node * next;
    int position;
    int line;
} Cursor;

Cursor *cursor_create();