#include "Dictionary.h"
#include "Errors.h"

Dictionary::Dictionary(std::istream& stream) {
    std::string input;
    while (std::getline(stream, input)) {
        bool valid = true;
        for (size_t i = 0; i < input.length(); i++) {
            if (!isalpha(input[i]) || !islower(input[i])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            Word* word = new Word {input};
            size_t word_length = input.length();
            if (word_length >= MAX_LENGTH) {
                exit(5); // indicates that max length is not long enough
            }
            if (word_length > real_max_length) {
                real_max_length = word_length;
            }
            for (size_t i = 0; i < word_length; i++) {
                std::string template_string = input;
                template_string[i] = 'A';
                word->templates.push_back(template_string);
                templates_map[word_length][template_string].push_back(word);
            }
            lengths[word_length].emplace(input, word);
        }
    }
    for (size_t curr_length = 1; curr_length <= real_max_length; curr_length++) {
        for (auto curr_word = lengths[curr_length].begin(); curr_word != lengths[curr_length].end(); curr_word++) {
            for (size_t i = 0; i < curr_length; i++) {
                std::vector<Word*>* adj_ptrs = &templates_map[curr_length][curr_word->second->templates[i]];
                for (size_t j = 0; j < adj_ptrs->size(); j++) {
                    curr_word->second->adjs.push_front(adj_ptrs->at(j));
                }
            }
        }
    }
}

Dictionary* Dictionary::create(std::istream& stream) {
    return new Dictionary(stream);
}

Dictionary::~Dictionary() {
    for (size_t curr_length = 1; curr_length <= real_max_length; curr_length++) {
        for (auto curr_word = lengths[curr_length].begin(); curr_word != lengths[curr_length].end(); curr_word++) {
            delete curr_word->second;
        }
    }
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
    if (from.length() >= MAX_LENGTH || to.length() >= MAX_LENGTH) {
        exit(5); // indicates that max length is not long enough
    }
    try {
        lengths[from.length()].at(from);
    }
    catch (std::out_of_range) {
        throw InvalidWord(from);
    }
    try {
        lengths[to.length()].at(to);
    }
    catch (std::out_of_range) {
        throw InvalidWord(to);
    }
    if (from.length() != to.length()) {
        throw NoChain();
    }
    std::vector<std::string> path;
    if (from == to) {
        path.push_back(from);
        return path;
    }
    // bfs goes here!!
    if (path.size() == 0) {
        throw NoChain();
    }
}
