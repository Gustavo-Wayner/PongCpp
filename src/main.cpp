#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Objects.h"
#include "Rooms.h"

int main()
{
    SetWindowState(FLAG_VSYNC_HINT);
    InitWindow(900, 600, "Pong");
    SetTargetFPS(60);

    global::manager.SwitchTo<Game>();
    SetExitKey(KEY_F12);
    while (!WindowShouldClose())
    {
        global::manager.Update();
    }

    CloseWindow();
    return 0;
}