#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "range/v3/numeric.hpp"
#include "range/v3/view.hpp"
#include "word_web.hpp"

namespace word_ladder {
    void word_web::init_web(const std::size_t& word_len, const absl::flat_hash_set<std::string>& lexicon) {
        absl::flat_hash_set<std::string> req_lexicon;
        for (auto& word : lexicon) {
            if (word.length() == word_len) {
                req_lexicon.insert(word);
                web_[word] = absl::flat_hash_map<std::string, unsigned int>();
            }
        }
        // fill web
        for (auto it1 = req_lexicon.begin(); it1 != req_lexicon.end(); it1++) {
            auto word1 = std::string(*it1);
            auto it2 = it1;
            for (it2++; it2 != req_lexicon.end(); it2++) {
                auto word2 = std::string(*it2);
                auto d = hamming_dist(word1, word2);
                if (d < word_len) {
                    add_edge(word1, word2, d);
                }
            }
        }
    }

    // assumes both strings are of the same length
    auto word_web::hamming_dist(const std::string& str1, const std::string& str2) -> unsigned int {
        if (str1 == str2) {
            return 0;
        }
        auto d = ranges::views::zip_with(ranges::not_equal_to{}, str1, str2);
        // should be fine since it will always be >0
        return static_cast<unsigned int>(ranges::accumulate(d, 0));
    }

    void word_web::add_edge(const std::string& str1, const std::string& str2, const unsigned int& weight) {
        web_[str1][str2] = weight;
        web_[str2][str1] = weight;
        //std::cout << str1 << " - " << str2 << std::endl;
    }

    auto word_web::ladder_len(std::vector<std::string>& ladder) -> unsigned int {
        unsigned int len = 0;
        auto it1 = ladder.begin();
        auto it2 = it1 + 1;
        while (it2 != ladder.end()) {
            len += web_[*it1][*it2];
            it1++;
            it2++;
        }
        return len;
    }

    // check to see if two words can connect 1 letter at a time in the web
    auto word_web::validate_edge(std::string& curr_word, std::string& next_word) -> bool {
        if (web_by_weight_[curr_word][1].contains(next_word)) {
            return true;
        }
        for
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
                    if (std::find(path.begin(), path.end(), next.first) == path.end()) {
                        auto new_path(path);
                        new_path.push_back(next.first);
                        q.push(new_path);
                    }
                }
            }
        }
        // remove non shortest ladders
        ladders.erase(std::remove_if(ladders.begin(), ladders.end(), [&min](const std::vector<std::string>& ladder) {
            return ladder.size() > min;
        }), ladders.end());
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
