#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xF8, 0x82, 0x91, 0x21, 0xDC, 0x82, 0x49, 0xE3, 0xBE, 0x75, 0xC3, 0x77, 0x19, 0xB2, 0xE4, 0xFC }
PBL_APP_INFO(MY_UUID,
             "Dungeon Dice", "Pinch Studios",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window dice_select_window;
SimpleMenuLayer dice_menu_layer;
SimpleMenuSection dice_menu_sections[1];
SimpleMenuItem dice_menu_section0_items[6];

void dice_window_load(Window *window);
void dice_window_unload(Window *window);
void setup_dice_select_window();


void handle_init(AppContextRef ctx) {

  setup_dice_select_window();
  window_stack_push(&dice_select_window, true);

}

void dice_window_load(Window *window) {

}

void dice_window_unload(Window *window) {

}

void dice_menu_layer_select_callback(int index, void *context)
{
   APP_LOG(APP_LOG_LEVEL_DEBUG, "Multi-Click: count:%u", index);
}

void setup_dice_select_window() {

  window_init(&dice_select_window, "Select Dice");
  window_set_window_handlers(&dice_select_window, (WindowHandlers){
    .load = dice_window_load,
    .unload = dice_window_unload,
  });

  Layer *root_layer = window_get_root_layer(&dice_select_window);

  dice_menu_section0_items[0] = (SimpleMenuItem) {
    .title = "d4",
    .callback = dice_menu_layer_select_callback,
  };

  dice_menu_section0_items[1] = (SimpleMenuItem) {
    .title = "d6",
    .callback = dice_menu_layer_select_callback,
  };

  dice_menu_section0_items[2] = (SimpleMenuItem) {
    .title = "d8",
    .callback = dice_menu_layer_select_callback,
  };

  dice_menu_section0_items[3] = (SimpleMenuItem) {
    .title = "d10",
    .callback = dice_menu_layer_select_callback,
  };

  dice_menu_section0_items[4] = (SimpleMenuItem) {
    .title = "d12",
    .callback = dice_menu_layer_select_callback,
  };

  dice_menu_section0_items[5] = (SimpleMenuItem) {
    .title = "d20",
    .callback = dice_menu_layer_select_callback,
  };

  dice_menu_sections[0] = (SimpleMenuSection) {
    .title = "Select a Dice",
    .items = dice_menu_section0_items,
    .num_items = sizeof(dice_menu_section0_items) / sizeof(dice_menu_section0_items[0])
  };

  simple_menu_layer_init(&dice_menu_layer,
                        layer_get_bounds(root_layer),
                        &dice_select_window,
                        dice_menu_sections,
                        sizeof(dice_menu_sections) / sizeof(dice_menu_sections[0]),
                        dice_menu_layer_select_callback);
  layer_add_child(root_layer, &dice_menu_layer.menu.scroll_layer.layer);

}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
