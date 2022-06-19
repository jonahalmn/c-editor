#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include "stream.h"

void gui_init();
int gui_actualize_stream(Stream *stream);
void gui_header(Stream *stream);
int gui_tick(Stream *stream);
void gui_deinit();