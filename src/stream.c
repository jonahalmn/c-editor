#include "stream.h"

Stream * stream_create() {
    Stream *stream = malloc(sizeof(Stream));

    stream->head = NULL;
    stream->last = NULL;
    stream->size = 0;
    stream->lines = 1;
    stream->cursor = cursor_create();
    return stream;
}

void stream_insert_string(Stream * stream, char *str) {
    while (*str != '\0')
    {
        stream_write(stream, *str);
        str++;
    }
}

void stream_append(Stream * stream, char c) {
    Node *node = node_create(c);
    if(stream->head == NULL) stream->head = node;
    else stream->last->next = node;
    stream->last = node;
    stream->size++;
}

void stream_delete_element(Stream *stream, Node *to_delete) {
    Node *current = stream->head;
    Node *prev = current;

    while (current && current != to_delete)
    {
        prev = current;
        current = current->next;
    }

    if(current == stream->head) {
        stream->head = stream->head->next;
        free(to_delete);
        stream->size--;
        return;
    }

    if(current == stream->last) {
        stream->last = prev;
        stream->last->next = NULL;
        free(to_delete);
        stream->size--;
        return;
    }
    
    prev->next = current->next;
    free(current);
    stream->size--;

}

void stream_del(Stream * stream) {
    if(stream->cursor->prev == NULL) return;

    stream->cursor->position--;
    if(stream->cursor->prev->letter == '\n') {
        stream->lines--;
        stream->cursor->line--;
    }
    if(stream->cursor->prev == stream->head) {
        stream_delete_element(stream, stream->cursor->prev);
        stream->cursor->prev = NULL;
        return;
    }

    Node *to_delete = stream->cursor->prev;
    stream->cursor->prev = get_prev(stream, stream->cursor->prev);
    stream_delete_element(stream, to_delete);

}

void stream_suppr(Stream * stream) {
    if(stream->cursor->next == NULL) return;

    if(stream->cursor->next == stream->last) {
        stream->cursor->prev = NULL;
        free(stream->head);
        stream->head = stream->cursor->next;    
    }
}

void stream_write(Stream * stream, char c) {
    Node *node = node_create(c);

    if(stream->head == NULL) {
        stream->head = node;
        stream->last = node;
    }

    if(stream->cursor->next == NULL) {
        stream->last = node; // cursor is at end
        node->next = NULL;
        stream->last = node;
    }

    if(stream->cursor->next != NULL)
        node->next = stream->cursor->next;

    if(stream->cursor->prev != NULL) 
        stream->cursor->prev->next = node;
    else {
        stream->head = node;
    }

    stream->cursor->prev = node;
    stream->cursor->next = node->next;
    stream->size++;
    stream->cursor->position++;
    if(c == '\n') {
        stream->lines++;
        stream->cursor->line++;
    };
}

void stream_move_cursor_left(Stream * stream) {
    if(stream->cursor->prev == NULL) return;
    if(stream->cursor->prev->letter == '\n') stream->cursor->line--;
    stream->cursor->next = stream->cursor->prev;
    stream->cursor->position--;
    if(stream->cursor->prev == stream->head) {
        stream->cursor->prev = NULL;
        return;
    }
    stream->cursor->prev = get_prev(stream, stream->cursor->prev);
    
}

int stream_get_cursor_line_position(Stream *stream) {
    int line = 1;
    int pos = 0;
    Node *current = stream->head;
    while (current && stream->cursor->line > line)
    {
        pos++;
        if(current->letter == '\n') line++;
        current = current->next;
    }
    
    return stream->cursor->position - pos;
}

void stream_move_cursor_right(Stream * stream) {
    if(stream->cursor->next == NULL) return;
    if(stream->cursor->next->letter == '\n') stream->cursor->line++;
    stream->cursor->prev = stream->cursor->next;
    stream->cursor->next = stream->cursor->next->next;
    stream->cursor->position++;
}


Node * get_prev(Stream *stream, Node *node) {
    Node *current = stream->head;

    while(current->next != node && current) {
        current = current->next;
    }

    return current;
}

void stream_print_editor(Stream stream) {
    stream_print_to_cursor(stream);
    printf("\x1b[s");
    //printf("|");
    stream_print_from_cursor(stream);
}

void stream_print_to_cursor(Stream stream) {
    if(stream.cursor->prev == NULL) return;
    Cursor *cursor = stream.cursor;
    Node *current = stream.head;
    while(cursor && current && current != cursor->prev && cursor->prev) {
        printf("%c", current->letter);
        current = current->next;
    }
    printf("%c", current->letter);
}

void stream_print_from_cursor(Stream stream) {
    Cursor *cursor = stream.cursor;
    if(!cursor) return;
    Node *current = cursor->next;
    while(cursor && current && current) {
        printf("%c", current->letter);
        current = current->next;
    }
}


void stream_print(Stream stream) {
    Node *current = stream.head;

    while(current) {
        printf("%c", current->letter);
        if(current)
        current = current->next;
    }
}

void stream_print_rev(Stream *stream) {
    _stream_print_revrec(stream->head);
}

void _stream_print_revrec(Node * node) {
    if(node->next != NULL) _stream_print_revrec(node->next);
    printf("%c", node->letter);
}

int stream_size(Stream *stream) {
    // In this ex I should ran across
    // the Node chain and count the Nodes
    // I prefer to use control structure
    // with metadata
    return stream->size;
}