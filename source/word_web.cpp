#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "word_web.hpp"

namespace word_ladder {
    void word_web::init_web(const absl::flat_hash_set<std::string>& lexicon) {
        absl::flat_hash_set<std::string> req_lexicon;
        for (auto& word : lexicon) {
            if (word.length() == word_len_) {
                req_lexicon.insert(word);
                web_[word] = absl::flat_hash_set<std::string>();
            }
        }
        // fill web
        for (auto it1 = req_lexicon.begin(); it1 != req_lexicon.end(); it1++) {
            auto word1 = std::string(*it1);
            for (auto it2 = it1++; it2 != req_lexicon.end(); it2++) {
                auto word2 = std::string(*it2);
                if (one_char_diff(word1, word2)) {
                    add_edge(word1, word2);
                }
            }
        }
    }

    auto word_web::one_char_diff(const std::string& str1, const std::string& str2) -> bool {
        if (str1 == str2) {
            return false;
        }
        auto mismatch_pair = std::mismatch(str1.begin(), str1.end(), str2.begin());
        return std::mismatch(++mismatch_pair.first, str1.end(), ++mismatch_pair.second).first == str1.end();
    }

    void word_web::add_edge(const std::string& str1, const std::string& str2) {
        web_[str1].insert(str2);
        web_[str2].insert(str1);
        std::cout << str1 << " - " << str2 << std::endl;
    }

    auto word_web::shortest_ladders(const std::string& from, const std::string& to)
        -> std::vector<std::vector<std::string>> {
        std::size_t min = 0;
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
                // if first ladder to be added
                if (ladders.empty()) {
                    min = path.size();
                }
                // if path is shorter than min
                if (path.size() < min) {
                    min = path.size();
                    // purge ladders
                    ladders.clear();
                }
                ladders.push_back(path);
            }
            // keep traversing web
            else {
                // only if uncompleted path is shorter than shortest ladder
                if (!ladders.empty() && path.size() >= min) {
                    continue;
                }
                for (const auto& next : web_[curr]) {
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

    auto word_web::shortest_ladders_sorted(const std::string &from, const std::string &to)
        -> std::vector<std::vector<std::string>> {
        auto ladders = shortest_ladders(from, to);
        std::cout << std::endl;
        for (auto& ladder : ladders) {
            for (auto& word : ladder) {
                std::cout << word << " ";
            }
            std::cout << std::endl;
        }
        // sort shortest ladders
        std::sort(ladders.begin(), ladders.end(),
            [](std::vector<std::string>& ladder1, std::vector<std::string>& ladder2) {
            auto mismatch_pair = std::mismatch(ladder1.begin(), ladder1.end(), ladder2.begin());
            return std::string(*mismatch_pair.first) < std::string(*mismatch_pair.second);
        });
        return ladders;
    }
}  // namespace word_ladder
