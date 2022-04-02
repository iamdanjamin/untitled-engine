#pragma once

#include "core/application.hpp"
#include "core/logger.hpp"
#include "game_types.hpp"

extern b8 create_game(game* out_game);

int main(void) {
    // Request the game instance from the application.
    game game_inst;

    if (!create_game(&game_inst)) {
        UFATAL("Could not create game!");
        return -1;
    }

    // Ensure the function pointers exist.
    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize) {
        UFATAL("The game's function pointers must be assigned!");
        return -2;
    }

    // Initialization.
    if (!application_create(&game_inst)) {
        UFATAL("Application failed to create!.");
        return 1;
    }

    // Begin the game loop.
    if (!application_run()) {
        UINFO("Application did not shutdown gracefully.");
        return 2;
    }

    if (!application_create(&game_inst)) {
        UINFO("Application failed to create!");
        return 1;
    }
    if (!application_run()) {
        UINFO("Application did not shutdown as expected.");
        return 2;
    }

    return 0;
}