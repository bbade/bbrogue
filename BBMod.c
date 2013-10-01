//
//  BBMod.c
//  Brogue
//
//  Created by Brenton Bade on 9/29/13.
//
//

#include <stdio.h>
#include "BBMod.h"

typedef void(*ClassInitFn)();

typedef struct CharacterClass {
  char* className;
  char* classDescription;
  // funciton pointer to the init function
  ClassInitFn setMeUp;
} CharacterClass;

//even index is name, odd index is description. TODO: relearn C
const char *ClassNamesAndDescriptions [] = {
  "Arcanist",   "Scroll of Identify and Scroll of Remove Curse"
  "Thief",      "Ring of stealth",
  "Warrior",    "A trusty sword",
  "Healer",     "A healing charm",
  "Pyro",       "A staff and potion of fire",
  "Enchanter",  "Two scrolls of enchantment",
  "Miner",      "A staff of digging and a scroll of shattering",
  "Explorer",   "Extra food and a ring of light",
  "Skrimisher", "10 extra Darts and Javlins",
//  "Clown",      "3 Potions of hallucination, a scroll of summon monster, and a Mango"
//  "Wizard",     "No armor, a -1 Dagger, Healing Charm, Staff of Lightning, Staff of Fire, Wand of Negation",
  "No Class",   "Play a standard game"
};


void selectClass() {
  
}


const CharacterClass CLASSES [] = {
  {.className = "a", .classDescription = "b", .setMeUp= selectClass}
};



void showDialog() {
  cellDisplayBuffer rbuf[COLS][ROWS];
  
	brogueButton OKButton;
	initializeButton(&OKButton);
	strcpy(OKButton.text, "     OK     ");
	OKButton.hotkey[0] = RETURN_KEY;
	OKButton.hotkey[1] = ENTER_KEY;
	OKButton.hotkey[2] = ACKNOWLEDGE_KEY;
	short option = printTextBox(message, COLS/3, ROWS/3, COLS/3, &white, &interfaceBoxColor, rbuf, &OKButton, 1);
  overlayDisplayBuffer(rbuf, NULL);
  
  
}
