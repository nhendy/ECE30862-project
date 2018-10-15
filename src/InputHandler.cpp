#include "../inc/InputHandler.hpp"



InputHandler::InputHandler(GameWorld & gameWorld): gameworld_(gameWorld) {}
InputHandler::~InputHandler() {}

bool InputHandler::change_room(string) {}
bool InputHandler::show_inventory() {}
bool InputHandler::take(string) {}
bool InputHandler::open(string) {}
bool InputHandler::read(string) {}
bool InputHandler::drop(string) {}
bool InputHandler::turnon(string) {}
bool InputHandler::attack(string) {}
bool InputHandler::put(string) {}



