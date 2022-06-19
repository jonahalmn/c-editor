#include "cursor.h"
#include "stream.h"

Cursor *cursor_create() {
    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->prev = NULL;
    cursor->next = NULL;
    cursor->position = 0;
    cursor->line = 1;
    return cursor;
}