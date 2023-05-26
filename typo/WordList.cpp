#include "WordList.h"
#include <cmath>
//#include <iostream>
//#include <cstddef>

WordList::WordList(std::istream& stream) {
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
            mWords.push_back(input);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    size_t word_length = points.size();
    std::vector<std::string> possible_words;
    Heap heap(maxcount);
    for (size_t i = 0; i < mWords.size(); i++) {
        if (mWords.at(i).length() == word_length) {
            possible_words.push_back(mWords.at(i));
        }
    }
    for (size_t i = 0; i < possible_words.size(); i++) {
        std::string word = possible_words.at(i);
        float mean_score = 0.0;
        for (size_t j = 0; j < word_length; j++) {
            size_t index = word[j] - 97;
            Point touch_pt = points.at(j);
            Point actual_pt = QWERTY[index];
            float dist = sqrt(pow(touch_pt.x - actual_pt.x, 2) + pow(touch_pt.y - actual_pt.y, 2));
            mean_score += 1.0 / (10.0 * pow(dist, 2) + 1.0);
        }
        mean_score /= float(word_length);
        if (mean_score >= cutoff) {
            heap.push(word, mean_score);
        }
    }
    return heap;
}

/*class WordList {
    std::vector<std::string> mWords;

public:
    WordList(std::istream& stream);

    Heap correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const;
};*/
