#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "dice.h"

static Window dice_window;
static TextLayer dice_number_text_layer;
static TextLayer dice_type_text_layer;
static Dice_Type current_dice_type;
static int dice_type_to_dice_number[] = {4, 8, 10, 12, 20};

typedef enum {

  Dice_Select_Direction_Up,
  Dice_Select_Direction_Down,

} Dice_Select_Direction;

void dice_window_load(Window *window);
void dice_window_unload(Window *window);
void setup_dice_window();
void roll_dice(Dice_Type dice_type);
void dice_config_provider(ClickConfig **config, Window *window);
void dice_select_single_click_handler(ClickRecognizerRef recognizer, Window *window);
void dice_down_single_click_handler(ClickRecognizerRef recognizer, Window *window);
void dice_up_single_click_handler(ClickRecognizerRef recognizer, Window *window);
void set_dice_type_text_layer_text(Dice_Type dice_type);
void select_dice(Dice_Select_Direction direction);


void dice_config_provider(ClickConfig **config, Window *window) {

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) dice_select_single_click_handler;
  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) dice_down_single_click_handler;
  config[BUTTON_ID_UP]->click.handler = (ClickHandler) dice_up_single_click_handler;

}

void dice_up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {

  select_dice(Dice_Select_Direction_Up);

}

void dice_down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {

  select_dice(Dice_Select_Direction_Down);

}

void select_dice(Dice_Select_Direction direction) {

  int index = (int)current_dice_type;

  switch (direction)
  {
    case Dice_Select_Direction_Down:
    {
      index += 1;
      if (index > (uint)sizeof(dice_type_to_dice_number) / dice_type_to_dice_number[0]) {
        index = 0;
      }
    }
    break;

    case Dice_Select_Direction_Up:

    break;

    default:
    break;
  }

  current_dice_type = (Dice_Type)index;
  set_dice_type_text_layer_text(current_dice_type);
  roll_dice(current_dice_type);

}

void dice_select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {

  roll_dice(current_dice_type);

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
  set_dice_type_text_layer_text(current_dice_type);
  layer_add_child(root_layer, (Layer *)&dice_type_text_layer);

  roll_dice(current_dice_type);
}

void set_dice_type_text_layer_text(Dice_Type dice_type) {
  
  static char dice_type_text[32];
  snprintf(dice_type_text, sizeof(dice_type_text), "d%d", dice_type_to_dice_number[dice_type]);
  text_layer_set_text(&dice_type_text_layer, dice_type_text);

}

void roll_dice(Dice_Type dice_type) {

  srand(time(NULL));
  int roll = (rand() % dice_type_to_dice_number[dice_type]) + 1;
  static char display_text[32];
  snprintf(display_text, sizeof(display_text), "%d", roll);
  text_layer_set_text(&dice_number_text_layer, display_text);
  vibes_short_pulse();

}

void dice_window_unload(Window *window) {

	// This function isn't in SDK yet? 
	// text_layer_deinit(&dice_number_text_layer);

}

void display_dice(Dice_Type dice_type)
{
	current_dice_type = dice_type;
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