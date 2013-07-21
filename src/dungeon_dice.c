#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "dice_menu.h"

#define MY_UUID { 0xF8, 0x82, 0x91, 0x21, 0xDC, 0x82, 0x49, 0xE3, 0xBE, 0x75, 0xC3, 0x77, 0x19, 0xB2, 0xE4, 0xFC }
PBL_APP_INFO(MY_UUID,
             "Dungeon Dice", "Pinch Studios",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

void handle_init(AppContextRef ctx) {

  // First screen is dice selection
  display_dice_menu();

}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
