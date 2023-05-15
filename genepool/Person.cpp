#include "Person.h"

Person::Person() {
  this->personMother = nullptr;
  this->personFather = nullptr;
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
  return personDescendents;
}
std::set<Person*> Person::children() {
  return personChildren;
}
std::set<Person*> Person::grandchildren() {
  std::set<Person *> personGrandchildren = {};
  return personGrandchildren;
}
std::set<Person*> Person::granddaughters() {
  std::set<Person *> personGranddaughters = {};
  return personGranddaughters;
}
std::set<Person*> Person::grandsons() {
  std::set<Person *> personGrandsons = {};
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
  std::set<Person *> personGrandfathers = {};
  return personGrandfathers;
}
std::set<Person*> Person::grandmothers(PMod pmod) {
  std::set<Person *> personGrandmothers = {};
  return personGrandmothers;
}
std::set<Person*> Person::parents(PMod pmod) {
  return {this->personMother, this->personFather};
}
std::set<Person*> Person::grandparents(PMod pmod) {
  std::set<Person *> personGrandparents = {};
  return personGrandparents;
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
