#include "application.hpp"
#include "game_types.hpp"

#include "logger.hpp"

#include "platform/platform.hpp"

typedef struct application_state {
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = false;
static application_state app_state;

b8 application_create(game* game_inst) {
    if (initialized) {
        UERROR("application_create called more than once.");
        return false;
    }

    app_state.game_inst = game_inst;

    // Initialize subsystems
    initialize_logging();

    // TODO: Remove this
    const char* message = "A test message: %f";
    UFATAL(message, 3.14f);
    UERROR(message, 3.14f);
    UWARN(message, 3.14f);
    UINFO(message, 3.14f);
    UDEBUG(message, 3.14f);
    UTRACE(message, 3.14f);

    app_state.is_running = true;
    app_state.is_suspended = false;

    if (!platform_startup(
        &app_state.platform,
        game_inst->app_config.name,
        game_inst->app_config.start_pos_x,
        game_inst->app_config.start_pos_y,
        game_inst->app_config.start_width,
        game_inst->app_config.start_height)) {
        return false;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        UFATAL("Game failed to initialize.");
        return false;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = true;

    return true;
}

b8 application_run() {
    while (app_state.is_running) {
        if (!platform_pump_messages(&app_state.platform)) {
            app_state.is_running = false;
        }

        if (!app_state.is_suspended) {
            if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
                UFATAL("Game update failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
                UFATAL("Game render failed, shutting down.");
                app_state.is_running = false;
                break;
            }
        }
    }

    app_state.is_running = false;

    platform_shutdown(&app_state.platform);

    return true;
}