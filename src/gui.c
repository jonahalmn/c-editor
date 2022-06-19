#include "commons.h"
#include "gui.h"

static struct termios oldt, newt;


void gui_init() {
    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
}

int gui_actualize_stream(Stream *stream) {
    int keycode = getchar();
      if(keycode == '\033') {
        getchar(); // discard [
        switch (getchar())
        {
        case '\n':
          break;
        case 65:
          /* code */
          break;
        case 66:
          /* code */
          break;
        case 67: // right
          stream_move_cursor_right(stream);
          break;
        case 68: // left
          stream_move_cursor_left(stream);
          break;
        default:
          //stream_write(stream, keycode);
          break;
        }
      } else {
        switch (keycode)
        {
        case 11:
            return 0;
            break;
        case 127:
          stream_del(stream);
          break;
        
        default:
          stream_write(stream, keycode);
          break;
        }
    }

    return keycode;
}

void gui_header(Stream *stream) {
    int pos =  stream_get_cursor_line_position(stream);
    printf("\x1b[2J\x1b[H");
    printf("\x1b[1;31;47m");
    printf(" JOEDIT V1.0 | Stream Size : %d | Cursor : %d:%d | Lines : %d \n", 
        stream->size, 
        pos,
        stream->cursor->line,
        stream->lines
        );
    printf("\x1b[1;0m");
}

int gui_tick(Stream *stream) {
    int code = gui_actualize_stream(stream);
    gui_header(stream);
    stream_print_editor(*stream);
    int pos =  stream_get_cursor_line_position(stream);
    printf("\ncode : %d", code);
    printf("\x1b[H\x1b[%d;%dH", stream->cursor->line + 1, pos + 1);
    return code;
}

void gui_deinit() {
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}