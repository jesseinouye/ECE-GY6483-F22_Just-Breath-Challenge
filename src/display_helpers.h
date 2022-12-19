#include <mbed.h>
//this file has all the functions for interacting
//with the screen
#include "drivers/LCD_DISCO_F429ZI.h"


// display a preset warning message on the screen.
void display_warning(LCD_DISCO_F429ZI& lcd);

// display a preset message to tell the user to adjust the fitting.
void display_adjust_needed(LCD_DISCO_F429ZI& lcd);

// display a breathing effect of the word "breathing" when there is no abnormality
void display_breathing_effect(LCD_DISCO_F429ZI& lcd);

// clear all the output on the display. Must be run before putting anything new on the display
void clear_display(LCD_DISCO_F429ZI& lcd); 

// display a starting instruction before the button is pressed
void display_starting_msg(LCD_DISCO_F429ZI& lcd); 

// display a breathing message, indicating that everything is fine
void display_breathing_msg1(LCD_DISCO_F429ZI& lcd); 

void display_breathing_msg2(LCD_DISCO_F429ZI& lcd); 