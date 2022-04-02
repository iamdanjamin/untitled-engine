#include <core/logger.hpp>
#include <core/asserts.hpp>

#include <platform.hpp>

int main() {
    const char* message = "A test message: %f";
    UFATAL(message, 3.14f);
    UERROR(message, 3.14f);
    UWARN(message, 3.14f);
    UINFO(message, 3.14f);
    UDEBUG(message, 3.14f);
    UTRACE(message, 3.14f);

    platform_state state;
    if (platform_startup(&state, "Untitled Engine Testbed", 100, 100, 1280, 720)) {
        while (true) {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}