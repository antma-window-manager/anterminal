#pragma once

#include <stdio.h>

// Opacity level
double opacity = 0.8;

// Background 
char* BACKGROUND = "#000000";

// Foreground 
char* FOREGROUND = "#ffffff";

// Colors
char* BLACK = "#000000";
char* RED = "#cd0000";
char* GREEN = "#00cd00";
char* YELLOW = "#cdcd00";
char* BLUE = "#0000ee";
char* MAGENTA = "#cd00cd";
char* CYAN = "#00cdcd";
char* WHITE = "#e5e5e5";
char* LIGHT_BLACK = "#7f7f7f";
char* LIGHT_RED = "#ff0000";
char* LIGHT_GREEN = "#00ff00";
char* LIGHT_YELLOW = "#ffff00";
char* LIGHT_BLUE = "#5c5cff";
char* LIGHT_MAGENTA = "#ff00ff";
char* LIGHT_CYAN = "#00ffff";
char* LIGHT_WHITE = "#ffffff";

// Font name
char* FONT = "monospace";
// Font size 
int FONT_SIZE = 12;

// Cursor shape {BLOCK, BEAM, UNDERLINE}
char *CURSOR_SHAPE = "BLOCK";

// Cursor blinking {TRUE / FALSE}
#define CURSOR_BLINKING TRUE

void initconfig()
{
    
}