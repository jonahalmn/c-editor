
#include "commons.h"
#include "stream.h"
#include "gui.h"

int main() {
    printf("EDITOR V1.0\n");
    printf("Press key to start edit.\n");

    // signal(SIGINT, intHandler);

    Stream * stream = stream_create();

    gui_init();
    while(gui_tick(stream)); 
    gui_deinit();
    return 0;
}
