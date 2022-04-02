#include "application.hpp"

#include "logger.hpp"
#include "platform.hpp"

typedef struct application_state {
    b8 is_running;
    b8 is_suspended;
    platform_state* platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = false;
static application_state app_state;

UAPI b8 application_create(application_config* config) {
    if (initialized) {
        UERROR("application_create called more than once.");
        return false;
    }

    initialize_logging();

    const char* message = "A test message: %f";
    UFATAL(message, 3.14f);
    UERROR(message, 3.14f);
    UWARN(message, 3.14f);
    UINFO(message, 3.14f);
    UDEBUG(message, 3.14f);
    UTRACE(message, 3.14f);
}

UAPI b8 application_run() {

}