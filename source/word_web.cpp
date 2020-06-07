#include <algorithm>
#include <cstddef>
#include <queue>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "word_web.hpp"

namespace word_ladder {
    auto WordWeb::init_web(const absl::flat_hash_set<std::string>& lexicon) -> bool {
        absl::flat_hash_set<std::string> req_lexicon;
        for (auto& word : lexicon) {
            if (word.length() == word_len) {
                req_lexicon.insert(word);
                web[word] = absl::flat_hash_set<std::string>();
                absl::flat_hash_map<char, int> char_count;
                for (const char& c : word) {
                    char_count[c]++;
                }
                words_char_count[word] = char_count;
            }
        }
        // fill web
        for (auto& word1 : req_lexicon) {
            for (auto& word2 : req_lexicon) {
                if (one_char_diff(word1, word2)) {
                    add_edge(word1, word2);
                }
            }
        }
        return false;
    }

    auto WordWeb::one_char_diff(const std::string& str1, const std::string& str2) -> bool {
        if (str1 == str2) {
            return false;
        }
        bool diff = false;
        for (char c = 'a'; c != 'z'; c++) {
            const int d = abs(words_char_count[str1][c] - words_char_count[str2][c]);
            if (d > 1) {
                return false;
            }
            if (d == 1) {
                if (diff) {
                    return false;
                }
                diff = true;
            }
        }
        return true;
    }

    void WordWeb::add_edge(const std::string& str1, const std::string& str2) {
        web[str1].insert(str2);
    }

    auto WordWeb::all_ladders(const std::string& from, const std::string& to)
        -> std::vector<std::vector<std::string>> {
        std::vector<std::vector<std::string>> ladders;
        std::queue<std::vector<std::string>> q;
        std::vector<std::string> path;
        path.push_back(from);
        q.push(path);
        while (!q.empty()) {
            path = q.front();
            q.pop();
            const auto& curr = path.back();
            // path is a ladder
            if (curr == to) {
                ladders.push_back(path);
            }
            // keep traversing web
            else {
                for (const auto& next : web[curr]) {
                    if (std::find(path.begin(), path.end(), next) == path.end()) {
                        auto new_path(path);
                        new_path.push_back(next);
                        q.push(new_path);
                    }
                }
            }
        }
        return ladders;
    }

    auto WordWeb::optimal_ladders_sorted(const std::string& from, const std::string& to)
        -> std::vector<std::vector<std::string>> {
        auto ladders = all_ladders(from, to);
        // find the length of the shortest ladder
        std::size_t min;
        for (const auto& ladder : ladders) {
            if (ladder == *ladders.begin() || ladder.size() < min) {
                min = ladder.size();
            }
        }
        // retrieve shortest ladders
        std::vector<std::vector<std::string>> shortest_ladders;
        for (const auto& ladder : ladders) {
            if (ladder.size() == min) {
                shortest_ladders.push_back(ladder);
            }
        }
        // sort shortest ladders
        std::sort(shortest_ladders.begin(), shortest_ladders.end(),
            [](std::vector<std::string>& ladder1, std::vector<std::string>& ladder2) {
            auto mismatch_pair = std::mismatch(ladder1.begin(), ladder1.end(), ladder2.begin());
            return std::string(*mismatch_pair.first) < std::string(*mismatch_pair.second);
        });
        return shortest_ladders;
    }
}  // namespace word_ladder
