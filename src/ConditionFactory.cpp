//
// Created 9/24/18.
//


#include "../inc/ConditionFactory.hpp"
#include "../inc/HasCondition.hpp"
#include "../inc/StatusCondition.hpp"


Condition* ConditionFactory::createCondition(rapidxml::xml_node<> * condition_node) {

    rapidxml::xml_node<> * child_has_node = condition_node -> first_node("has");
    rapidxml::xml_node<> * child_status_node = condition_node -> first_node("status");

    if(child_has_node)
    {
        return new HasCondition(condition_node);
    }

    else if(child_status_node)
    {
        return new StatusCondition(condition_node);
    }
}
