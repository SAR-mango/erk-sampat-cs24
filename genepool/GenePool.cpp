#include "GenePool.h"

// GenePool Member Functions

GenePool::GenePool(std::istream& stream) {
}

GenePool::~GenePool() {
}

std::set<Person*> GenePool::everyone() const {
    return everyone;
}

Person* GenePool::find(const std::string& name) const {
}

/*class GenePool {
  // Member Variables
  std::map<std::string, Person*> everyone;
  std::set<Person*> everyone_set;

  // Helper Functions

public:
  // Build a database of people from a TSV file.
  GenePool(std::istream& stream);

  // Clean it up.
  ~GenePool();

  // List all the people in the database.
  std::set<Person*> everyone() const;

  // Find a person in the database by name.
  // Return nullptr if there is no such person.
  Person* find(const std::string& name) const;
};*/
