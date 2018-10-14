#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "rapidxml.hpp"



int main(void) {
    //Find the xml file in the directory

    using namespace rapidxml;
    using namespace std;

   xml_document <> doc;
   ifstream file ("sample.txt.xml");

   stringstream buffer ;
   buffer << file.rdbuf();
   file.close();
   string content(buffer.str());

   doc.parse<0>(&content[0]);
   xml_node<> *root_node = doc.first_node();
    // Find our root node
    root_node = doc.first_node("MyBeerJournal");
    // Iterate over the brewerys

    for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
    {
        printf("I have visited %s in %s. ",
               brewery_node->first_attribute("name")->value(),
               brewery_node->first_attribute("location")->value());
        // Interate over the beers
        for(xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
        {
            printf("On %s, I tried their %s which is a %s. ",
                   beer_node->first_attribute("dateSampled")->value(),
                   beer_node->first_attribute("name")->value(),
                   beer_node->first_attribute("description")->value());
            printf("I gave it the following review: %s", beer_node->value());
        }
        cout << endl;
    }



}
