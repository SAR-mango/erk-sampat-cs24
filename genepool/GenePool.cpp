#include "GenePool.h"

// GenePool Member Functions

GenePool::GenePool(std::istream& stream) {
    std::string name = "";
    std::string gender = "";
    std::string mother = "";
    std::string father = "";
    std::string input = "";
    everyone_map.emplace("???", nullptr);
    while (std::getline(stream, input)) {
        if (input[0] == '\n' || input[0] == '#') {
            continue;
        }
        else {
            size_t state = 0; // 0 name, 1 gender, 2 mother, 3 father
            for (size_t i = 0; i < input.length(); i++) {
                if (input[i] == '\t') {
                    state++;
                    continue;
                }
                if (state == 0) {
                    name += input[i];
                }
                else if (state == 1) {
                    gender += input[i];
                }
                else if (state == 2) {
                    mother += input[i];
                }
                else {
                    father += input[i];
                }
            }
            Person* person_ptr = new Person(name, gender, everyone_map[mother], everyone_map[father]);
            if (mother != "???") {
                everyone_map[mother]->addChild(person_ptr);
            }
            if (father != "???") {
                everyone_map[father]->addChild(person_ptr);
            }
            everyone_map.emplace(name, person_ptr);
            everyone_set.insert(person_ptr);
        }
    }
}

GenePool::~GenePool() {
    for (Person* person : everyone_set) {
        delete person;
    }
    everyone_map.clear();
    everyone_set.clear();
}

std::set<Person*> GenePool::everyone() const {
    return everyone_set;
}

Person* GenePool::find(const std::string& name) const {
    Person* person = nullptr;
    try {
        person = everyone_map.at(name);
    }
    catch () {
    }
    return person;
}
