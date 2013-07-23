#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "dice_menu.h"
#include "dice.h"

static Window dice_select_window;
static SimpleMenuLayer dice_menu_layer;
static SimpleMenuSection dice_menu_sections[1];
static SimpleMenuItem dice_menu_section0_items[6];

void dice_window_load(Window *window);
void dice_window_unload(Window *window);
void setup_dice_select_window();
void dice_menu_layer_select_callback(int index, void *context);
void setup_datasource();

void dice_select_window_load(Window *window) {
    
    Layer *root_layer = window_get_root_layer(&dice_select_window);
    simple_menu_layer_init(&dice_menu_layer,
                           layer_get_bounds(root_layer),
                           &dice_select_window,
                           dice_menu_sections,
                           sizeof(dice_menu_sections) / sizeof(dice_menu_sections[0]),
                           NULL);
    layer_add_child(root_layer, &dice_menu_layer.menu.scroll_layer.layer);
    
}

void dice_select_window_unload(Window *window) {


}

void display_dice_menu() {
    
	setup_datasource();
	setup_dice_select_window();
	window_stack_push(&dice_select_window, true);
    
}

void dice_selection_changed(Dice_Type dice_type) {

  simple_menu_layer_set_selected_index(&dice_menu_layer, (int)dice_type, true);

}

void dice_menu_layer_select_callback(int index, void *context)
{
    display_dice((Dice_Type)index, dice_selection_changed);
}

void setup_datasource() {
    
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
    
}

void setup_dice_select_window() {
    
    window_init(&dice_select_window, "Select Dice");
    window_set_window_handlers(&dice_select_window, (WindowHandlers){
        .load = dice_select_window_load,
        .unload = dice_select_window_unload,
    });
    
}