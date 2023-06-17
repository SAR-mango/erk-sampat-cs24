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
    if (pmod == PMod::MATERNAL) {
        if (p_mother == nullptr) {
            return ancestors_set;
        }
        ancestors_set.insert(p_mother);
        std::set<Person*> m_ancestors = p_mother->ancestors();
        ancestors_set.merge(m_ancestors);
        return ancestors_set;
    }
    else if (pmod == PMod::PATERNAL) {
        if (p_father == nullptr) {
            return ancestors_set;
        }
        ancestors_set.insert(p_father);
        std::set<Person*> f_ancestors = p_father->ancestors();
        ancestors_set.merge(f_ancestors);
        return ancestors_set;
    }
    else {
        if (p_mother != nullptr) {
            ancestors_set.insert(p_mother);
            std::set<Person*> m_ancestors = p_mother->ancestors();
            ancestors_set.merge(m_ancestors);
        }
        if (p_father != nullptr) {
            ancestors_set.insert(p_father);
            std::set<Person*> f_ancestors = p_father->ancestors();
            ancestors_set.merge(f_ancestors);
        }
        return ancestors_set;
    }
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> aunts_set;
    return aunts_set;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> brothers_set;
    return brothers_set;
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
        std::set<Person*> ch_children = kid->children();
        grandchildren_set.merge(ch_children);
    }
    return grandchildren_set;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> granddaughters_set;
    for (Person* kid : p_children) {
        std::set<Person*> ch_daughters = kid->daughters();
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
        std::set<Person*> ch_sons = kid->sons();
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
    if (pmod == PMod::MATERNAL) {
        if (p_mother == nullptr) {
            return siblings_set;
        }
        std::set<Person*> m_children = p_mother->children();
        m_children.erase(this);
        return m_children;
    }
    else if (pmod == PMod::PATERNAL) {
        if (p_father == nullptr) {
            return siblings_set;
        }
        std::set<Person*> f_children = p_father->children();
        f_children.erase(this);
        return f_children;
    }
    else if (smod == SMod::HALF) {
        std::set<Person*> m_children;
        std::set<Person*> f_children;
        if (p_mother != nullptr) {
            m_children = p_mother->children();
            m_children.erase(this);
            if (p_father != nullptr) {
                for (Person* m_child : m_children) {
                    if (m_child->father() == p_father) {
                        m_children.erase(m_child);
                    }
                }
            }
        }
        if (p_father != nullptr) {
            f_children = p_father->children();
            f_children.erase(this);
            if (p_mother != nullptr) {
                for (Person* f_child : f_children) {
                    if (f_child->mother() == p_mother) {
                        f_children.erase(f_child);
                    }
                }
            }
        }
        siblings_set.merge(m_children);
        siblings_set.merge(f_children);
        return siblings_set;
    }
    else if (smod == SMod::FULL) {
        std::set<Person*> m_children;
        std::set<Person*> f_children;
        if (p_mother != nullptr) {
            m_children = p_mother->children();
            m_children.erase(this);
            if (p_father != nullptr) {
                for (Person* m_child : m_children) {
                    if (m_child->father() != p_father) {
                        m_children.erase(m_child);
                    }
                }
            }
        }
        if (p_father != nullptr) {
            f_children = p_father->children();
            f_children.erase(this);
            if (p_mother != nullptr) {
                for (Person* f_child : f_children) {
                    if (f_child->mother() != p_mother) {
                        f_children.erase(f_child);
                    }
                }
            }
        }
        siblings_set.merge(m_children);
        siblings_set.merge(f_children);
        return siblings_set;
    }
    else {
        std::set<Person*> m_children;
        std::set<Person*> f_children;
        if (p_mother != nullptr) {
            m_children = p_mother->children();
            m_children.erase(this);
        }
        if (p_father != nullptr) {
            f_children = p_father->children();
            f_children.erase(this);
        }
        siblings_set.merge(m_children);
        siblings_set.merge(f_children);
        return siblings_set;
    }
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
