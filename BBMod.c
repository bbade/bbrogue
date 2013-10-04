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


//public
void setupSelectedClass() {
  if (selectedClass.classId == CLS_NONE) {
    return;
  }
  
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


boolean selectedClassHasArmor() {
  return selectedClass.classId != CLS_RUNNER ||
    selectedClass.classId != CLS_ARCMAGE;
}
boolean selectedClassHasDarts() {
  return selectedClass.classId != CLS_ARCMAGE;
}

// private

void arcanist(item **items) {
  items[1] = generateItem(SCROLL, SCROLL_IDENTIFY);
}

void theif(item **items) {
  items[0] = generateItem(RING, RING_STEALTH);
  items[0] ->enchant1 = 1;
}

void warrior(item **items) {
  items[0] = generateItem(WEAPON, SWORD);
  items[0] ->enchant1 = 0;
  // maybe a potion of strenght or a scroll of acid protection?
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
  items[1] = generateItem(RING, RING_LIGHT);
  items[1] ->enchant1 = 1;
}

void runner(item **items) {
  items[0] = generateItem(CHARM, CHARM_HASTE);
  items[0] -> enchant1 = 3;
}

void noClass(item **items){
  //do nothing
}

void arcmage(item **items) {
  items[0] = generateItem(STAFF, STAFF_FIRE);
  items[0] ->enchant1 = 1;
  items[1] = generateItem(STAFF, STAFF_LIGHTNING);
  items[1] ->enchant1 = 1;
  items[2] = generateItem(RING, RING_WISDOM);
  items[2] -> enchant1 = 1;
  
  // Give player 3 darts so that they can still solve puzzles
  items[3] = generateItem(WEAPON, DART);
  items[3] -> quantity = 3;
}


// The second field will be prefixed by "Starts with "
const CharacterClass CLASSES [] = {
  {CLS_NONE,      "No Class",   "Play a standard game", .getItems = noClass},
  {CLS_ARCANIST,  "Arcanist",   "Scroll of Identify", .getItems = arcanist},
  {CLS_THEIF,     "Thief",      "Ring of stealth", .getItems = theif},
  {CLS_WARRIOR,   "Warrior",    "A trusty sword", .getItems = warrior}, // maybe make it acid proof?
  {CLS_HEALER,    "Healer",     "A healing charm", .getItems = healer},
  {CLS_PYRO,      "Pyro",       "Incindiary darts and potion of fire", .getItems = pyro},
  {CLS_ENCHANTER, "Enchanter",  "Two scrolls of enchantment", .getItems = enchanter},
  {CLS_MINER,     "Miner",      "A staff of digging and a a ring of light", .getItems = miner},
  {CLS_RUNNER,    "Runner", "No armor. Haste charm and potion of descent", .getItems = runner},
  {CLS_ARCMAGE,   "Arcmage", "No Armor, 3 Darts. Staffs of lightning and Fire", .getItems = arcmage},
}; 


void selectClass() {
  // We want a button array
  brogueButton buttons [NUM_CLASSES];
  
  // Create a button for each class
  for (int i = 0; i < NUM_CLASSES; i++) {
    const CharacterClass *cClass = CLASSES + i;
    initializeButton(buttons + i);
    buttons[i].text[0] = 'a' + i;
    buttons[i].text[1] = ')';
    buttons[i].text[2] = ' ';
    strncpy(buttons[i].text+3, cClass->className, COLS-3);
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
  cellDisplayBuffer dbuf[COLS][ROWS];//, rbuf[COLS][ROWS];
  clearDisplayBuffer(dbuf);
  printString(title, winX + hPadding, titleRow,  &itemMessageColor, dialogColor, dbuf);
  rectangularShading(winX, winY, width + 1, height + 1, dialogColor, INTERFACE_OPACITY, dbuf);
  overlayDisplayBuffer(dbuf, NULL);
  return buttonInputLoop(buttons, nButtons, winX, winY, width, height, NULL);
}


