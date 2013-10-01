//
//  BBMod.h
//  Brogue
//
//  Created by Brenton Bade on 9/29/13.
//
//

#ifndef Brogue_BBMod_h
#define Brogue_BBMod_h

#include "Rogue.h"
#include "IncludeGlobals.h"

enum CharacterClassType {
  CLS_ARCANIST, // starts with scroll of identify, scroll of remove curse
  CLS_THEIF,    // starts with ring of stealth +1
  CLS_WARRIOR,  // Starts with +0 sword
  CLS_HEALER,   // S/W +1 healing charm
  CLS_PYRO,     // S/W pot of incineration, staff fire
  CLS_ENCHANTER, // S/W 2 scroll of enchantment
  CLS_MINER,    //SW Scroll of Shattering, Staff of digging
  CLS_EXPLORER, // ring of light & extra ration
  CLS_SKRIMISHER, //darts and javlins
//  CLS_CLOWN ,
//  CLS_WIZZRD, // -1 dagger, no armor, lots of magical items
//  CLS_SCOUT,  // Ring of Awareness +1
  CLS_RUNNER,   // no armor, no darts, +2 haste charm
  CLS_NONE, // play a standard game
  NUM_CLASSES
};


// prompts the user to select a class, then sets the info up, or something
void selectClass();

#endif
