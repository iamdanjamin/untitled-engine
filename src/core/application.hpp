#pragma once

#include "defines.hpp"

typedef struct application_config {
    /** @brief Window starting position x axis, if applicable. */
    i16 start_pos_x;

    /** @brief Window starting position y axis, if applicable. */
    i16 start_pos_y;

    /** @brief Window starting width, if applicable. */
    i16 start_width;

    /** @brief Window starting height, if applicable. */
    i16 start_height;

    /** @brief The application name used in windowing, if applicable. */
    char* name;
} application_config;

UAPI b8 application_create(application_config* config);

UAPI b8 application_run();