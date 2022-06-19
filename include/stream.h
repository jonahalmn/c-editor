#pragma once
#include "commons.h"
#include "node.h"
#include "cursor.h"

typedef struct
{
    Node *head;
    Node *last;
    int size;
    int lines;
    Cursor *cursor;
} Stream;


Stream * stream_create();
void stream_insert_string(Stream * stream, char *str);
void stream_append(Stream * stream, char c);
void stream_print(Stream stream);
void _stream_print_revrec(Node * node);
void stream_print_rev(Stream *stream);

void stream_print_editor(Stream stream);
void stream_print_to_cursor(Stream stream);
void stream_print_from_cursor(Stream stream);
void stream_write(Stream * stream, char c);
Node * get_prev(Stream *stream, Node *node);

int stream_size(Stream *stream);
void stream_move_cursor_left(Stream * stream);
void stream_move_cursor_right(Stream * stream);
void stream_del(Stream * stream);

int stream_get_cursor_line_position(Stream *stream);