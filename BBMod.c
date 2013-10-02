//
//  BBMod.c
//  Brogue
//
//  Created by Brenton Bade on 9/29/13.
//
//

#include <stdio.h>
#include "BBMod.h"

// function defs
int printMultipleChoiceBox(char* title, brogueButton* buttons, int nButtons);

// vars
static CharacterClass selectedClass;
static const int MAX_CLASS_ITEMS = 5;


//code
void setupSelectedClass() {
  item *items[MAX_CLASS_ITEMS];
  memset(items, 0, MAX_CLASS_ITEMS * sizeof(item*));
  selectedClass.getItems(items);
  
  for (int i = 0; i < MAX_CLASS_ITEMS && items[i] != 0; i++) {
    item *theItem = items[i];
    identify(theItem);
    items[0] ->flags &= ~(ITEM_CURSED | ITEM_RUNIC);
    addItemToPack(theItem);
  }
}

void arcanist(item **items) {
  items[1] = generateItem(SCROLL, SCROLL_IDENTIFY);
  items[2] = generateItem(SCROLL, SCROLL_NEGATION);
}

void theif(item **items) {
  items[0] = generateItem(RING, RING_STEALTH);
  items[0] ->enchant1 = 1;
}

void warrior(item **items) {
  items[0] = generateItem(WEAPON, SWORD);
  items[0] ->enchant1 = 0;
  // maybe a potion of strenght?
}

void healer(item **items) {
  items[0] = generateItem(CHARM, CHARM_HEALTH);
  items[0] ->enchant1 = 1;
}

void pyro(item **items) {
  items[0] = generateItem(WEAPON, INCENDIARY_DART);
  items[0] ->quantity = 5;
  items[1] = generateItem(POTION, POTION_INCINERATION);
}

void enchanter(item **items) {
  items[0] = generateItem(SCROLL, SCROLL_ENCHANTING);
  items[1] = generateItem(SCROLL, SCROLL_ENCHANTING);
}

void miner(item **items) {
  items[0] = generateItem(STAFF, STAFF_TUNNELING);
  items[0] ->enchant1 = 1;
  items[1] = generateItem(POTION, POTION_DESCENT);
}

void explorer(item **items) {
  items[0] = generateItem(FOOD, RATION);
  items[1] = generateItem(RING, RING_LIGHT);
  items[1] ->enchant1 = 2;
}

void skrimisher(item **items) {
  items[0] = generateItem(WEAPON, DART);
  items[0] ->enchant1 = 1;
  items[0] ->quantity = 5;
  items[1] = generateItem(WEAPON, JAVELIN);
  items[1]->quantity = 10;
}

void noClass(item **items){
  //do nothing
}

// The second field will be prefixed by "Starts with "
const CharacterClass CLASSES [] = {
  {"Arcanist",   "Scroll of Identify and Scroll of Remove Curse", .getItems = arcanist},
  {"Thief",      "Ring of stealth", .getItems = theif},
  {"Warrior",    "A trusty sword", .getItems = warrior},
  {"Healer",     "A healing charm", .getItems = healer},
  {"Pyro",       "Incindiary darts and potion of fire", .getItems = pyro},
  {"Enchanter",  "Two scrolls of enchantment", .getItems = enchanter},
  {"Miner",      "A staff of digging and a potion of descent", .getItems = miner},
  {"Explorer",   "Extra food and a ring of light", .getItems = explorer},
  {"Skrimisher", "Five +1 Darts, 10 Javlins", .getItems = skrimisher},
  {"No Class",   "Play a standard game", .getItems = noClass}
};




void selectClass() {
  // We want a button array
  brogueButton buttons [NUM_CLASSES];
  
  // Create a button for each class
  for (int i = 0; i < NUM_CLASSES; i++) {
    const CharacterClass *cClass = CLASSES + i;
    initializeButton(buttons + i);
    strncpy(buttons[i].text, cClass->className, COLS);
    buttons[i].hotkey[0] = 'a' + i;
    buttons[i].hotkey[1] = 'A' + i;
    buttons[i].x = 2;
    buttons[i].y = i + 2;
  }
  
  // display a dialog box
  int option = printMultipleChoiceBox("Choose your class", buttons, NUM_CLASSES);

  // get the class that was selected
  printf("Selected dialog index %d, which is class %s", option, CLASSES[option].className);

  //configure global state or something
  selectedClass = CLASSES[option];
}


int printMultipleChoiceBox(char* title, brogueButton* buttons, int nButtons) {
  const int height = ROWS / 2;
  const int width = COLS / 2;
  const int winX = COLS *.25;
  const int winY = ROWS * .25;
  const int hPadding = 2;
  const int vPadding = 1;
  const int titleRow = winY + vPadding;
  const int firstButtonRow = winY + 2 * vPadding;
  
  // align the buttons
  for (int i = 0; i < nButtons; i++) {
    buttons[i].x = winX + hPadding;
    buttons[i].y = firstButtonRow + i;
  }
  
  color *dialogColor = &interfaceBoxColor;
  cellDisplayBuffer dbuf[COLS][ROWS], rbuf[COLS][ROWS];
  clearDisplayBuffer(dbuf);
  printString(title, winX + hPadding, titleRow,  &itemMessageColor, dialogColor, dbuf);
  rectangularShading(winX, winY, width + 1, height + 1, dialogColor, INTERFACE_OPACITY, dbuf);
  overlayDisplayBuffer(dbuf, NULL);
  return buttonInputLoop(buttons, nButtons, winX, winY, width, height, NULL);
}


