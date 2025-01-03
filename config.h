#pragma once

#include <stdio.h>
#include <libconfig.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Default values
double opacity = 0.8;
char BACKGROUND[] = "#000000";
char FOREGROUND[] = "#ffffff";
char BLACK[] = "#000000";
char RED[] = "#cd0000";
char GREEN[] = "#00cd00";
char YELLOW[] = "#cdcd00";
char BLUE[] = "#0000ee";
char MAGENTA[] = "#cd00cd";
char CYAN[] = "#00cdcd";
char WHITE[] = "#e5e5e5";
char LIGHT_BLACK[] = "#7f7f7f";
char LIGHT_RED[] = "#ff0000";
char LIGHT_GREEN[] = "#00ff00";
char LIGHT_YELLOW[] = "#ffff00";
char LIGHT_BLUE[] = "#5c5cff";
char LIGHT_MAGENTA[] = "#ff00ff";
char LIGHT_CYAN[] = "#00ffff";
char LIGHT_WHITE[] = "#ffffff";
char FONT[] = "monospace";
int FONT_SIZE = 12;
const char *CURSOR_SHAPE = "BLOCK";
#define CURSOR_BLINKING 1

config_t cfg;

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void initconfig()
{
    char *CONFIGFILEPATH = concat(getenv("HOME"), "/.config/anterminal.conf");
    if (access(CONFIGFILEPATH, F_OK) == 0)
    {
        config_init(&cfg);
        if (!config_read_file(&cfg, CONFIGFILEPATH))
        {
            fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                    config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
            free(CONFIGFILEPATH);
            exit(EXIT_FAILURE);
        }

        // Load configuration values
        config_lookup_float(&cfg, "OPACITY", &opacity);
        
        const char *temp;
        
        if (config_lookup_string(&cfg, "BACKGROUND", &temp)) {
            strncpy(BACKGROUND, temp, sizeof(BACKGROUND) - 1);
            BACKGROUND[sizeof(BACKGROUND) - 1] = '\0';
        }
        
        if (config_lookup_string(&cfg, "FOREGROUND", &temp)) {
            strncpy(FOREGROUND, temp, sizeof(FOREGROUND) - 1);
            FOREGROUND[sizeof(FOREGROUND) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "BLACK", &temp)) {
            strncpy(BLACK, temp, sizeof(BLACK) - 1);
            BLACK[sizeof(BLACK) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "RED", &temp)) {
            strncpy(RED, temp, sizeof(RED) - 1);
            RED[sizeof(RED) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "GREEN", &temp)) {
            strncpy(GREEN, temp, sizeof(GREEN) - 1);
            GREEN[sizeof(GREEN) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "YELLOW", &temp)) {
            strncpy(YELLOW, temp, sizeof(YELLOW) - 1);
            YELLOW[sizeof(YELLOW) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "BLUE", &temp)) {
            strncpy(BLUE, temp, sizeof(BLUE) - 1);
            BLUE[sizeof(BLUE) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "MAGENTA", &temp)) {
            strncpy(MAGENTA, temp, sizeof(MAGENTA) - 1);
            MAGENTA[sizeof(MAGENTA) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "CYAN", &temp)) {
            strncpy(CYAN, temp, sizeof(CYAN) - 1);
            CYAN[sizeof(CYAN) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "WHITE", &temp)) {
            strncpy(WHITE, temp, sizeof(WHITE) - 1);
            WHITE[sizeof(WHITE) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_BLACK", &temp)) {
            strncpy(LIGHT_BLACK, temp, sizeof(LIGHT_BLACK) - 1);
            LIGHT_BLACK[sizeof(LIGHT_BLACK) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_RED", &temp)) {
            strncpy(LIGHT_RED, temp, sizeof(LIGHT_RED) - 1);
            LIGHT_RED[sizeof(LIGHT_RED) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_GREEN", &temp)) {
            strncpy(LIGHT_GREEN, temp, sizeof(LIGHT_GREEN) - 1);
            LIGHT_GREEN[sizeof(LIGHT_GREEN) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_YELLOW", &temp)) {
            strncpy(LIGHT_YELLOW, temp, sizeof(LIGHT_YELLOW) - 1);
            LIGHT_YELLOW[sizeof(LIGHT_YELLOW) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_BLUE", &temp)) {
            strncpy(LIGHT_BLUE, temp, sizeof(LIGHT_BLUE) - 1);
            LIGHT_BLUE[sizeof(LIGHT_BLUE) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_MAGENTA", &temp)) {
            strncpy(LIGHT_MAGENTA, temp, sizeof(LIGHT_MAGENTA) - 1);
            LIGHT_MAGENTA[sizeof(LIGHT_MAGENTA) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_CYAN", &temp)) {
            strncpy(LIGHT_CYAN, temp, sizeof(LIGHT_CYAN) - 1);
            LIGHT_CYAN[sizeof(LIGHT_CYAN) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "LIGHT_WHITE", &temp)) {
            strncpy(LIGHT_WHITE, temp, sizeof(LIGHT_WHITE) - 1);
            LIGHT_WHITE[sizeof(LIGHT_WHITE) - 1] = '\0';
        }

        if (config_lookup_string(&cfg, "FONT", &temp)) {
            strncpy(FONT, temp, sizeof(FONT) - 1);
            FONT[sizeof(FONT) - 1] = '\0';
        }

        config_lookup_int(&cfg, "FONT_SIZE", &FONT_SIZE);
    }
}
