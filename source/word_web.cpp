#include <algorithm>
#include <cstddef>
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
                web_[word] = absl::flat_hash_set<std::string>();
            }
        }
        // fill web
        for (auto it1 = req_lexicon.begin(); it1 != req_lexicon.end(); it1++) {
            auto word1 = std::string(*it1);
            auto it2 = it1;
            for (it2++; it2 != req_lexicon.end(); it2++) {
                auto word2 = std::string(*it2);
                if (is_hamming_dist_1(word1, word2)) {
                    add_edge(word1, word2);
                }
            }
        }
    }

    // assumes both strings are of the same length
    auto word_web::is_hamming_dist_1(const std::string& str1, const std::string& str2) -> bool {
        if (str1 == str2) {
            return false;
        }
        auto mismatch_pair = std::mismatch(str1.begin(), str1.end(), str2.begin());
        return std::mismatch(++mismatch_pair.first, str1.end(), ++mismatch_pair.second).first == str1.end();
    }

    void word_web::add_edge(const std::string& str1, const std::string& str2) {
        web_[str1].insert(str2);
        web_[str2].insert(str1);
    }

    auto word_web::shortest_ladders(const std::string& from, const std::string& to)
        -> std::vector<std::vector<std::string>> {
        std::size_t min = 0;
        std::vector<std::vector<std::string>> ladders;
        std::queue<std::vector<std::string>> q;
        std::vector<std::string> path;
        std::size_t prev_ladder_len = 0;
        // words visited in all paths of len <= curr_path.size()
        absl::flat_hash_set<std::string> visited_prev_ladder_lens;
        // new words visited
        absl::flat_hash_set<std::string> visited_curr_ladder_len;

        path.push_back(from);
        visited_curr_ladder_len.insert(from);
        q.push(path);
        while (!q.empty()) {
            path = q.front();
            q.pop();
            // if path length increased
            // should be an increase by 1
            if (path.size() != prev_ladder_len) {
                visited_prev_ladder_lens.insert(visited_curr_ladder_len.begin(), visited_curr_ladder_len.end());
                visited_curr_ladder_len.clear();
                prev_ladder_len++;
            }
            const auto& curr = path.back();
            // path is a ladder
            if (curr == to) {
                // if first ladder to be added
                if (ladders.empty()) {
                    min = path.size();
                }
                // else if path is shorter than min
                else if (path.size() < min) {
                    min = path.size();
                    // purge ladders
                    ladders.clear();
                }
                // only add ladders of the shortest length
                if (path.size() == min) {
                    ladders.push_back(path);
                }
            }
            // keep traversing web
            else {
                // only if uncompleted path is shorter than shortest ladder
                if (!ladders.empty() && path.size() >= min) {
                    continue;
                }
                for (const auto& next : web_[curr]) {
                    // check next word isn't one that we've already visited
                    if (!visited_prev_ladder_lens.contains(next)) {
                        auto new_path(path);
                        new_path.push_back(next);
                        visited_curr_ladder_len.insert(next);
                        q.push(new_path);
                    }
                }
            }
        }
        /*
        // remove non shortest ladders
        ladders.erase(std::remove_if(ladders.begin(), ladders.end(), [&min](const std::vector<std::string>& ladder) {
            return ladder.size() > min;
        }), ladders.end());
        */
        return ladders;
    }

    auto word_web::shortest_ladders_sorted(const std::string &from, const std::string &to)
        -> std::vector<std::vector<std::string>> {
        auto ladders = shortest_ladders(from, to);
        // sort shortest ladders
        std::sort(ladders.begin(), ladders.end(),
            [](std::vector<std::string>& ladder1, std::vector<std::string>& ladder2) {
            auto mismatch_pair = std::mismatch(ladder1.begin(), ladder1.end(), ladder2.begin());
            if (mismatch_pair.first == ladder1.end()) {
                return false;
            }
            return std::string(*mismatch_pair.first) < std::string(*mismatch_pair.second);
        });
        return ladders;
    }
}  // namespace word_ladder
