#include "Person.h"

Person::Person() {
  this->personMother = nullptr;
  this->personFather = nullptr;
  this->personChildren = {};
  this->personGrandparents = {};
  this->personParents = {};
  this->personGrandmothers = {};
  this->personGrandfathers = {};
}
// Person Member Functions
void Person::setName(const std::string& newname) {
  this->personName = newname;
}
void Person::setGender(const std::string& genderstring) {
  if (0 == genderstring.compare("male")) {
    this->personGender = Gender::MALE;
  } else if (0 == genderstring.compare("female")) {
    this->personGender = Gender::FEMALE;
  } else {
    this->personGender = Gender::ANY;
  }
}
void Person::setChild(Person* newname) {
  this->personChildren.insert(newname);
}
void Person::setFather(Person* newname) {
  this->personFather = newname;
  newname->setChild(this);
}
void Person::setMother(Person* newname) {
  this->personMother = newname;
  newname->setChild(this);
}
const std::string& Person::name() const {
  return this->personName;
}
Gender Person::gender() const {
  return this->personGender;
}
Person* Person::mother() {
  return this->personMother;
}
Person* Person::father() {
  return this->personFather;
}
std::set<Person*> Person::descendants() {
  std::set<Person *> personDescendents = {};
  for (std::set<Person *>::iterator it = this->personChildren.begin();
       it != this->personChildren.end(); ++it) {
    personDescendents.insert(*it);
    for (std::set<Person *>::iterator jt = (*it)->personChildren.begin();
         jt != (*it)->personChildren.end(); ++jt) {
      personDescendents.insert(*jt);
    }
  }
  return personDescendents;
}
std::set<Person*> Person::children() {
  return personChildren;
}
std::set<Person*> Person::grandchildren() {
  std::set<Person *> personGrandchildren = {};
  for (std::set<Person *>::iterator it = this->personChildren.begin();
       it != this->personChildren.end(); ++it) {
    for (std::set<Person *>::iterator jt = (*it)->personChildren.begin();
         jt != (*it)->personChildren.end(); ++jt) {
      personGrandchildren.insert(*jt);
    }
  }
  return personGrandchildren;
}
std::set<Person*> Person::granddaughters() {
  std::set<Person *> personGranddaughters = {};
  for (std::set<Person *>::iterator it = this->personChildren.begin();
       it != this->personChildren.end(); ++it) {
    for (std::set<Person *>::iterator jt = (*it)->personChildren.begin();
         jt != (*it)->personChildren.end(); ++jt) {
      if (Gender::FEMALE == (*jt)->gender()) {
        personGranddaughters.insert(*jt);
      }
    }
  }
  return personGranddaughters;
}
std::set<Person*> Person::grandsons() {
  std::set<Person *> personGrandsons = {};
  for (std::set<Person *>::iterator it = this->personChildren.begin();
       it != this->personChildren.end(); ++it) {
    for (std::set<Person *>::iterator jt = (*it)->personChildren.begin();
         jt != (*it)->personChildren.end(); ++jt) {
      if (Gender::MALE == (*jt)->gender()) {
        personGrandsons.insert(*jt);
      }
    }
  }
  return personGrandsons;
}
std::set<Person*> Person::sons() {
  std::set<Person *> personSons = {};
  return personSons;
}
std::set<Person*> Person::daughters() {
  std::set<Person *> personDaughters = {};
  return personDaughters;
}
std::set<Person*> Person::grandfathers(PMod pmod) {
  std::set<Person *> myParents = this->parents();
  std::set<Person *> myGPs;
  for (std::set<Person *>::iterator it = myParents.begin();
       it != myParents.end(); ++it) {
    myGPs = (*it)->parents();
    for (std::set<Person *>::iterator jt = myGPs.begin();
         jt != myGPs.end(); ++jt) {
      if (nullptr == *jt) continue;
      if (Gender::MALE == (*jt)->gender()) {
        this->personGrandfathers.insert(*jt);
      }
    }
  }
  return this->personGrandfathers;
}
std::set<Person*> Person::grandmothers(PMod pmod) {
  std::set<Person *> myParents = this->parents();
  std::set<Person *> myGPs;
  for (std::set<Person *>::iterator it = myParents.begin();
       it != myParents.end(); ++it) {
    myGPs = (*it)->parents();
    for (std::set<Person *>::iterator jt = myGPs.begin();
         jt != myGPs.end(); ++jt) {
      if (nullptr == *jt) continue;
      if (Gender::FEMALE == (*jt)->gender()) {
        this->personGrandmothers.insert(*jt);
      }
    }
  }
  return this->personGrandmothers;
}
std::set<Person*> Person::parents(PMod pmod) {
  this->personParents = {this->personMother, this->personFather};
  return this->personParents;
}
std::set<Person*> Person::grandparents(PMod pmod) {
  std::set<Person *> myGPs = this->grandmothers();
  for (std::set<Person *>::iterator jt = myGPs.begin();
       jt != myGPs.end(); ++jt) {
    this->personGrandparents.insert(*jt);
  }
  myGPs = this->grandfathers();
  for (std::set<Person *>::iterator jt = myGPs.begin();
       jt != myGPs.end(); ++jt) {
    this->personGrandparents.insert(*jt);
  }
  return this->personGrandparents;
}
std::set<Person*> Person::ancestors(PMod pmod) {
  std::set<Person *> personGrandparents = {};
  return personGrandparents;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
  std::set<Person *> personCousins = {};
  return personCousins;
}
