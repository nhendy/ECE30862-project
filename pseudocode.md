# URGENT!
- [ ] Model turn on as if it's a trigger in item.hpp
- [ ] Model attack as if it's a trigger in Creature.hpp
- [ ] Error check all input commands and all actions
  
  
  
  
  
# General program flow 
  
1- Initialize game objects from xml document
2- Get user input
3- ~~Map input to a Command object~~
4- Check if triggers override a command
5- If not execute the command
6- else execute the trigger
7- Go to 2




Initialization:
- [x] Create a GameWorld object
- [x] GameWorld object will have all GameObjects in the game
- [x] Rooms should be a map from room name to Room object to facilitate lookup
- [x] Creatures should be a map from item name to Item Object to facilitate lookup
- [x] Containers should be a map from item name to Item Object to facilitate lookup










# Objects Description


GameWorld Object:
- [x] rooms should map room names to room objects
- [x] items should map items names to items objects
- [x] containers should map container names to container objects
- [x] creatures  should map creature names to creature objects
- [x] current room pointer should point to current Room object
- [x] Inventory should be a map from name to item objects


Room Object:
- [x] name variable
- [x] type variable can be exit, entrance or regular. regular by default.
- [x] borders will have a direction and name should map direction to room name
- [x] containers should be a list of container names
- [x] items should be a list of item names
- [x] creatures should be a list of creature names

Item Object:

Command Object:

Trigger Object:


Condition Object:


Creature:
- [x] Has a vector of vulnerabilities
- [x] Has an Attack **similar to a trigger**
