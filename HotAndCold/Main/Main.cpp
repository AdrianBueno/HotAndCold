#include "../Core/Game.h"
#include "../Core/Config.h"

int SDL_main(int argc, char* argv[]) {
    Game game;

    if (!game.Init("Hot And Cold",
        Config::WINDOW_POS_X,
        Config::WINDOW_POS_Y,
        Config::WINDOW_WIDTH,
        Config::WINDOW_HEIGHT,
        Config::FULLSCREEN)) {
        return -1;
    }

    while (game.Running()) {
        game.HandleEvents();
        game.Update();
        game.Render();
    }

    game.Clean();

    return 0;
}