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
  CLS_NONE = 0, // play a standard game

  CLS_ARCANIST, // scroll of identify
  CLS_THEIF,    // ring of stealth +1
  CLS_WARRIOR,  // +0 sword
  CLS_HEALER,   // +1 healing charm
  CLS_PYRO,     // pot of incineration, fire darts
  CLS_ENCHANTER, // 2 scroll of enchantment
  CLS_MINER,    //staff of dig + ring of light
  CLS_RUNNER,   // no armor, haste charm
  CLS_ARCMAGE,  // no armor, some staffs
  NUM_CLASSES
};

//  CLS_CLOWN ,
//  CLS_WIZZRD, // -1 dagger, no armor, lots of magical items
//  CLS_SCOUT,  // Ring of Awareness +1
//  CLS_RUNNER,   // no armor, no darts, +3 haste charm, scroll recharging

typedef void(*ClassInitFn)(item** classItems);


typedef struct CharacterClass {
  enum CharacterClassType classId;
  char* className;
  char* classDescription;
  // funciton pointer to the init function
  ClassInitFn getItems;
} CharacterClass;



/**
 * Adds items from the selected class to pack, does
 * any other fanciness.
 */
void setupSelectedClass(); //should be called when the player's items are assigned
boolean selectedClassHasArmor();
boolean selectedClassHasDarts();
void selectClass();  // prompts the user to select a class, then sets the info up


#endif
