#include <mbed.h>
//this file has all the functions for interacting
//with the screen
#include "drivers/LCD_DISCO_F429ZI.h"


// display a preset warning message on the screen.
void display_warning(LCD_DISCO_F429ZI& lcd);

// clear all the output on the display. Must be run before putting anything new on the display
void clear_display(LCD_DISCO_F429ZI& lcd); 
