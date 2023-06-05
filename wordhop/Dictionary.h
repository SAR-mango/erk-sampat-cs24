#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_map>
#include <forward_list>

class Dictionary {
  // Member Variables
  struct Word {
    std::string word = "";
    std::forward_list<Word*> adjs;
    std::vector<std::string> templates;
  };
  std::unordered_map<std::string, Word*> lengths[40];
  std::unordered_map<std::string, std::vector<Word*>> templates_map[40];

  // Helper Functions
  Dictionary(std::istream& stream);

public:
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif
