#include "../Core/Game.h"

// IMPORTANTE: Cambiar a SDL_main si usas SDL2main.lib
int SDL_main(int argc, char* argv[]) {
    Game game; // Usamos stack en vez de heap, más limpio y seguro

    if (!game.Init("Hot And Cold", 100, 100, 800, 600, false)) {
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
