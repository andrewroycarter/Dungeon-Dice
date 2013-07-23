#ifndef _dice_h
#define _dice_h

typedef enum {
	Dice_Type_D4 = 0,
	Dice_Type_D6,
	Dice_Type_D8,
	Dice_Type_D10,
	Dice_Type_D12,
	Dice_Type_D20,
}	Dice_Type;

typedef void (*DiceSelectionChange)(Dice_Type);

// init and push dice window to stack
void display_dice(Dice_Type dice_type, DiceSelectionChange dice_selection_change);

#endif