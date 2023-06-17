#include "Person.h"

// Person Member Functions

Person::Person(std::string name_str, std::string gender_str, Person* mother_ptr, Person* father_ptr) {
    p_name = name_str;
    if (gender_str == "male") {
        p_gender = Gender::MALE;
    }
    else {
        p_gender = Gender::FEMALE;
    }
    p_mother = mother_ptr;
    p_father = father_ptr;
}

const std::string& Person::name() const {
    return p_name;
}

Gender Person::gender() const {
    return p_gender;
}

Person* Person::mother() {
    return p_mother;
}

Person* Person::father() {
    return p_father;
}

std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> ancestors_set;
    return ancestors_set;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> aunts_set;
    return aunts_set;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
}

std::set<Person*> Person::children() {
    std::set<Person*> children_set;
    for (Person* person : p_children) {
        children_set.insert(person);
    }
    return children_set;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> cousins_set;
    return cousins_set;
}

std::set<Person*> Person::daughters() {
    std::set<Person*> daughters_set;
    for (Person* person : p_children) {
        if (person->gender() == Gender::FEMALE) {
            daughters_set.insert(person);
        }
    }
    return daughters_set;
}

std::set<Person*> Person::descendants() {
    std::set<Person*> descendants_set;
    return descendants_set;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> grandchildren_set;
    for (Person* kid : p_children) {
        std::set<Person*> ch_children = kid.children();
        grandchildren_set.merge(ch_children);
    }
    return grandchildren_set;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> granddaughters_set;
    for (Person* kid : p_children) {
        std::set<Person*> ch_daughters = kid.daughters();
        granddaughters_set.merge(ch_daughters);
    }
    return granddaughters_set;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> grandfathers_set;
    return grandfathers_set;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> grandmothers_set;
    return grandmothers_set;
}

std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> grandparents_set;
    return grandparents_set;
}

std::set<Person*> Person::grandsons() {
    std::set<Person*> grandsons_set;
    for (Person* kid : p_children) {
        std::set<Person*> ch_sons = kid.sons();
        grandsons_set.merge(ch_sons);
    }
    return grandsons_set;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> nephews_set;
    return nephews_set;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> nieces_set;
    return nieces_set;
}

std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> parents_set;
    return parents_set;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> siblings_set;
    return siblings_set;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> sisters_set;
    return sisters_set;
}

std::set<Person*> Person::sons() {
    std::set<Person*> sons_set;
    for (Person* person : p_children) {
        if (person->gender() == Gender::MALE) {
            sons_set.insert(person);
        }
    }
    return sons_set;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> uncles_set;
    return uncles_set;
}

void Person::addChild(Person* child) {
    p_children.push_back(child);
}
