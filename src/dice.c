#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "dice.h"

static Window dice_window;
static TextLayer dice_number_text_layer;
static TextLayer dice_type_text_layer;

int max_dice_number = 0;

void dice_window_load(Window *window);
void dice_window_unload(Window *window);
void setup_dice_window();
void roll_dice(int max);
void dice_config_provider(ClickConfig **config, Window *window);
void dice_select_single_click_handler(ClickRecognizerRef recognizer, Window *window);
void set_dice_type_text_layer_text(int max);


void dice_config_provider(ClickConfig **config, Window *window) {

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) dice_select_single_click_handler;

}

void dice_select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {

  roll_dice(max_dice_number);

}

void dice_window_load(Window *window) {

  Layer *root_layer = window_get_root_layer(&dice_window);

  GRect root_layer_bounds = layer_get_bounds(root_layer);

  text_layer_init(&dice_number_text_layer, GRect(0, 50, root_layer_bounds.size.w, 45));  
  text_layer_set_text_alignment(&dice_number_text_layer, GTextAlignmentCenter);
  text_layer_set_font(&dice_number_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
  layer_add_child(root_layer, (Layer *)&dice_number_text_layer);

  text_layer_init(&dice_type_text_layer, GRect(0, 0, root_layer_bounds.size.w, 25));  
  text_layer_set_text_alignment(&dice_type_text_layer, GTextAlignmentCenter);
  text_layer_set_font(&dice_type_text_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  set_dice_type_text_layer_text(max_dice_number);
  layer_add_child(root_layer, (Layer *)&dice_type_text_layer);

  roll_dice(max_dice_number);
}

void set_dice_type_text_layer_text(int max) {
  
  static char dice_type_text[32];
  snprintf(dice_type_text, sizeof(dice_type_text), "d%d", max);
  text_layer_set_text(&dice_type_text_layer, dice_type_text);

}

void roll_dice(int max) {

  srand(time(NULL));
  int roll = (rand() % max_dice_number) + 1;
  static char display_text[32];
  snprintf(display_text, sizeof(display_text), "%d", roll);
  text_layer_set_text(&dice_number_text_layer, display_text);
  vibes_short_pulse();

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

  window_set_click_config_provider(&dice_window, (ClickConfigProvider) dice_config_provider);


}