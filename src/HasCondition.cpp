//
// Created by Noureldin Hendy on 9/24/18.
//

#include "../inc/HasCondition.hpp"
#include "../inc/Condition.hpp"

HasCondition::~HasCondition() {}
HasCondition::HasCondition(rapidxml::xml_node<> * condition_node) {

}
bool HasCondition::isConditionSatisfied(GameWorld *) {}