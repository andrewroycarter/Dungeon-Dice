#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "dice.h"

Window dice_window;
TextLayer dice_number_text_layer;
static char display_text[32];

int max_dice_number = 0;

void dice_window_load(Window *window);
void dice_window_unload(Window *window);
void setup_dice_window();
int roll_dice(int max);

void dice_window_load(Window *window) {

  Layer *root_layer = window_get_root_layer(&dice_window);

  GRect root_layer_bounds = layer_get_bounds(root_layer);

  text_layer_init(&dice_number_text_layer, GRect(0, 50, root_layer_bounds.size.w, 45));

  int roll = roll_dice(max_dice_number);
  snprintf(display_text, sizeof(display_text), "%d", roll);
  text_layer_set_text(&dice_number_text_layer, display_text);
  
  text_layer_set_text_alignment(&dice_number_text_layer, GTextAlignmentCenter);
  text_layer_set_font(&dice_number_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
  layer_add_child(root_layer, (Layer *)&dice_number_text_layer);
}

int roll_dice(int max) {

  srand(time(NULL));
  int roll = (rand() % max_dice_number) + 1;
  vibes_short_pulse();
  return roll;
}

void dice_window_unload(Window *window) {

	// This function isn't in SDK yet? 
	// text_layer_deinit(&dice_number_text_layer);

}

void display_dice(int max_dice_number_)
{
	max_dice_number = max_dice_number_;
	setup_dice_window();
	window_stack_push(&dice_window, true);
}


void setup_dice_window() {

  window_init(&dice_window, "Dice");
  window_set_window_handlers(&dice_window, (WindowHandlers){
    .load = dice_window_load,
    .unload = dice_window_unload,
  });

}