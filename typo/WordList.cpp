#include "WordList.h"

WordList::WordList(std::istream& stream) {
    std::string input;
    while (std::getline(stream, input)) {
        for (size_t i = 0; i < input.length(); i++) {
            if (!std::isalpha(input[i]) || !std::islower(input[i])) {
                continue;
            }
        }
        mWords.push_back(input);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
}

/*class WordList {
    std::vector<std::string> mWords;

public:
    WordList(std::istream& stream);

    Heap correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const;
};*/
