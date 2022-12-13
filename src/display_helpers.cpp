#include <mbed.h>
//this file has all the functions for interacting
//with the screen
#include "drivers/LCD_DISCO_F429ZI.h"
#define BACKGROUND 1
#define FOREGROUND 0
#define GRAPH_PADDING 5


//LCD_DISCO_F429ZI lcd;
//buffer for holding displayed text strings
char display_buf[4][60];
// uint32_t graph_width=lcd.GetXSize()-2*GRAPH_PADDING;
// uint32_t graph_height=graph_width;

//sets the background layer 
//to be visible, transparent, and
//resets its colors to all black
void setup_background_layer(LCD_DISCO_F429ZI& lcd){
  lcd.SelectLayer(BACKGROUND);
  lcd.Clear(LCD_COLOR_BLACK);
  lcd.SetBackColor(LCD_COLOR_BLACK);
  lcd.SetTextColor(LCD_COLOR_GREEN);
  lcd.SetLayerVisible(BACKGROUND,ENABLE);
  lcd.SetTransparency(BACKGROUND,0x7Fu);
}

//resets the foreground layer to
//all black
void setup_foreground_layer(LCD_DISCO_F429ZI& lcd){
    lcd.SelectLayer(FOREGROUND);
    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_LIGHTGREEN);
}

void clear_display(LCD_DISCO_F429ZI& lcd){
  setup_background_layer(lcd);
  setup_foreground_layer(lcd);
}
//draws a rectangle with horizontal tick marks
//on the background layer. The spacing between tick
//marks in pixels is taken as a parameter
// void draw_graph_window(uint32_t horiz_tick_spacing){
//   lcd.SelectLayer(BACKGROUND);
  
//   lcd.DrawRect(GRAPH_PADDING,GRAPH_PADDING,graph_width,graph_width);
//   //draw the x-axis tick marks
//   for (int32_t i = 0 ; i < graph_width;i+=horiz_tick_spacing){
//     lcd.DrawVLine(GRAPH_PADDING+i,graph_height,GRAPH_PADDING);
//   }
// }

//maps inputY in the range minVal to maxVal, to a y-axis value pixel in the range
//minPixelY to MaxPixelY
// uint16_t mapPixelY(float inputY,float minVal, float maxVal, int32_t minPixelY, int32_t maxPixelY){
//   const float mapped_pixel_y=(float)maxPixelY-(inputY)/(maxVal-minVal)*((float)maxPixelY-(float)minPixelY);
//   return mapped_pixel_y;
// }

void display_warning(LCD_DISCO_F429ZI& lcd) {
  setup_background_layer(lcd);

  setup_foreground_layer(lcd);

  //creates c-strings in the display buffers, in preparation
  //for displaying them on the screen
  snprintf(display_buf[0],60,"WARNING",lcd.GetXSize());
  snprintf(display_buf[1],60,"Your baby might",lcd.GetYSize());
  snprintf(display_buf[2],60,"stop breathing!",lcd.GetYSize());
  //snprintf(display_buf[2],60,"detecting your baby's breath!",lcd.GetYSize());
  lcd.SelectLayer(FOREGROUND);
  //display the buffered string on the screen
  lcd.SetTextColor(LCD_COLOR_RED);
  lcd.SetFont(&Font24);
  lcd.DisplayStringAt(0, LINE(6), (uint8_t *)display_buf[0], CENTER_MODE);

  lcd.SetTextColor(LCD_COLOR_WHITE);
  lcd.SetFont(&Font16);
  lcd.DisplayStringAt(0, LINE(12), (uint8_t *)display_buf[1], CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(13), (uint8_t *)display_buf[2], CENTER_MODE);
  //lcd.DisplayStringAt(0, LINE(14), (uint8_t *)display_buf[3], CENTER_MODE);
  //draw the graph window on the background layer
  // with x-axis tick marks every 10 pixels
  // draw_graph_window(10);


  lcd.SelectLayer(FOREGROUND); 
}

void display_adjust_needed(LCD_DISCO_F429ZI& lcd) {
  setup_background_layer(lcd);

  setup_foreground_layer(lcd);

  //creates c-strings in the display buffers, in preparation
  //for displaying them on the screen
  snprintf(display_buf[0],60,"ATTENTION",lcd.GetXSize());
  snprintf(display_buf[1],60,"Please adjust",lcd.GetYSize());
  snprintf(display_buf[2],60,"the fitting!",lcd.GetYSize());
  lcd.SelectLayer(FOREGROUND);
  //display the buffered string on the screen
  lcd.SetTextColor(LCD_COLOR_YELLOW);
  lcd.SetFont(&Font24);
  lcd.DisplayStringAt(0, LINE(6), (uint8_t *)display_buf[0], CENTER_MODE);

  lcd.SetTextColor(LCD_COLOR_WHITE);
  lcd.SetFont(&Font16);
  lcd.DisplayStringAt(0, LINE(12), (uint8_t *)display_buf[1], CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(13), (uint8_t *)display_buf[2], CENTER_MODE);


  lcd.SelectLayer(FOREGROUND); 
}

void display_breathing_msg1(LCD_DISCO_F429ZI& lcd) {
    clear_display(lcd);
    char display_buf[4][60];
    snprintf(display_buf[0],60,"Monitoring", lcd.GetXSize());
    lcd.SelectLayer(0);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    lcd.SetFont(&Font24);
    lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
}

void display_breathing_msg2(LCD_DISCO_F429ZI& lcd) {
    clear_display(lcd);
    char display_buf[4][60];
    snprintf(display_buf[0],60,"Breathing", lcd.GetXSize());
    lcd.SelectLayer(0);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    lcd.SetFont(&Font16);
    lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
}

void display_breathing_effect(LCD_DISCO_F429ZI& lcd) {
    char display_buf[4][60];
    snprintf(display_buf[0],60,"Breathing", lcd.GetXSize());
    lcd.SelectLayer(0);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    while (1) {
      lcd.SetFont(&Font24);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(800);

      lcd.SetFont(&Font20);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[1], CENTER_MODE);
      thread_sleep_for(1000);
      
      lcd.SetFont(&Font16);
      clear_display(lcd);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(1000);

      lcd.SetFont(&Font12);
      clear_display(lcd);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(1000);
      
      lcd.SetFont(&Font8);
      clear_display(lcd);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(1000);

      lcd.SetFont(&Font12);
      clear_display(lcd);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(1000);
      
      lcd.SetFont(&Font16);
      clear_display(lcd);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(1000);
      
      
      lcd.SetFont(&Font20);
      clear_display(lcd);
      lcd.DisplayStringAt(0, lcd.GetYSize()/2, (uint8_t *)display_buf[0], CENTER_MODE);
      thread_sleep_for(1000);
    }
}

void display_starting_msg(LCD_DISCO_F429ZI& lcd) {
    setup_background_layer(lcd);
    setup_foreground_layer(lcd);

    //creates c-strings in the display buffers, in preparation
    //for displaying them on the screen
    // snprintf(display_buf[0],60,"WARNING",lcd.GetXSize());
    snprintf(display_buf[1],60,"Push Blue Button",lcd.GetYSize());
    snprintf(display_buf[2],60,"to Start!",lcd.GetYSize());
    //snprintf(display_buf[2],60,"detecting your baby's breath!",lcd.GetYSize());
    lcd.SelectLayer(FOREGROUND);
    //display the buffered string on the screen
    // lcd.SetTextColor(LCD_COLOR_RED);
    // lcd.SetFont(&Font24);
    // lcd.DisplayStringAt(0, LINE(6), (uint8_t *)display_buf[0], CENTER_MODE);

    lcd.SetTextColor(LCD_COLOR_WHITE);
    lcd.SetFont(&Font16);
    lcd.DisplayStringAt(0, LINE(12), (uint8_t *)display_buf[1], CENTER_MODE);
    lcd.DisplayStringAt(0, LINE(13), (uint8_t *)display_buf[2], CENTER_MODE);
    //lcd.DisplayStringAt(0, LINE(14), (uint8_t *)display_buf[3], CENTER_MODE);
    //draw the graph window on the background layer
    // with x-axis tick marks every 10 pixels
    // draw_graph_window(10);


    lcd.SelectLayer(FOREGROUND); 
}