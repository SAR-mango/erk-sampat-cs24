#include "GenePool.h"
#include <iostream>
using namespace std;

// GenePool Member Functions
GenePool::GenePool(std::istream& stream) {
  std::string line;
  std::string Name;
  // size_t lineNum = 0;
  Person *pPerson;
  while (std::getline(stream, line)) {
    // lineNum++;
    // cout << "Line number " << lineNum << "\n";
    // cout << line << "\n";
    if (0 == line.size()) continue;
    if (('#' == line[0]) || ('\n' == line[0]) || ('\r' == line[0])) {
      continue;
    }
    // We're now past comments and new lines, so parse
    size_t pos = 0, newPos = 0;
    newPos = line.find('\t');
    std::string temp = line.substr(pos, newPos - pos);
    pPerson = new Person;
    this->Everyone.insert(pPerson);
    pos = newPos + 1;
    // cout << "Name: " << temp << "\n";
    pPerson->setName(temp);
  
    newPos = line.find('\t', pos);
    temp = line.substr(pos, newPos - pos);
    pos = newPos + 1;
    // cout << "Gender: " << temp << "\n";
    pPerson->setGender(temp);

    newPos = line.find('\t', pos);
    temp = line.substr(pos, newPos - pos);
    pos = newPos + 1;
    // cout << "Mother: " << temp << "\n";
    for (std::set<Person *>::iterator it = Everyone.begin();
         it != Everyone.end(); ++it) {
      if (0 == (*it)->name().compare(temp)) {
        pPerson->setMother(*it);
      }
    }

    temp = line.substr(pos);
    // cout << "Father: " << temp << "\n";
    for (std::set<Person *>::iterator it = Everyone.begin();
         it != Everyone.end(); ++it) {
      if (0 == (*it)->name().compare(temp)) {
        pPerson->setFather(*it);
      }
    }
  };
}

// Clean it up.
GenePool::~GenePool() {
    for (std::set<Person *>::iterator it = Everyone.begin();
         it != Everyone.end(); ++it) {
      delete *it;
      Everyone.erase(it);
    }
}
// List all the people in the database.
std::set<Person*> GenePool::everyone() const {
  return this->Everyone;
}

// Find a person in the database by name.
// Return nullptr if there is no such person.
Person* GenePool::find(const std::string& name) const {
    for (std::set<Person *>::iterator it = Everyone.begin();
         it != Everyone.end(); ++it) {
      if (0 == (*it)->name().compare(name)) {
        return *it;
      }
    }
    return nullptr;
}
