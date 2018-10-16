    1- Initialize game objects from xml document
    2- Get user input
    3- Map input to a Command object
    4- Check if triggers override a command
    5- If not execute the command
    6- else execute the trigger
    7- Go to 2




Initialization:
- [ ] Create a GameWorld object
- [ ] GameWorld object will have all GameObjects in the game
- [ ] Rooms should be a map from room name to Room object to facilitate lookup
- [ ] Creatures should be a map from item name to Item Object to facilitate lookup
- [ ] Containers should be a map from item name to Item Object to facilitate lookup


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
    -

Condition Object:


Creature:
- [x] Has a vector of vulnerabilities
- [x] Has an Attack **similar to a trigger**

Container:
- [ ] Vector of item names stored in the container
- [ ] Vector of accept names storing items that can be accepted by the container


Player:
- [ ] Player will have a room
- [ ] Player will have inventory


InputHandler:
- [ ] Handle all commands described in hpp



