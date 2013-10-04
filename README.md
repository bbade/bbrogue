bbrogue
=======

a fork of brogue with some minor additions

1) Casts detect magic on potions when they are picked up so that you know if you're getting one that's harmful or helpful. 

2) Adds support for "classes".
These classes start the player off with one or two items that would typically be found in the first few
dungeon levels. The idea of the class is to give the player a tiny bit of control over the direction their 
character goes in, or to provide a little flavor. 


Here's the current class set
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
