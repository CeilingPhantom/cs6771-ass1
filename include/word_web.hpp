/*
    'web' / graph of all words that are same length as input words
*/

#include <cstddef>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

namespace word_ladder {
    class WordWeb {

            const std::size_t& word_len;
            // web stored as adjacency list
            absl::flat_hash_map<std::string, absl::flat_hash_set<std::string>> web;
            absl::flat_hash_map<std::string, absl::flat_hash_map<char, int>> words_char_count;

            auto init_web(const absl::flat_hash_set<std::string>& lexicon) -> bool;
            auto one_char_diff(const std::string& str1, const std::string& str2) -> bool;
            void add_edge(const std::string& str1, const std::string& str2);

            auto all_ladders(const std::string& from, const std::string& to)
                -> std::vector<std::vector<std::string>>;

        public:
            WordWeb(const std::size_t& word_len, const absl::flat_hash_set<std::string>& lexicon)
                : word_len(word_len) {
                init_web(lexicon);
            }
            auto optimal_ladders_sorted(const std::string& from, const std::string& to)
                -> std::vector<std::vector<std::string>>;

    };
}  // namespace word_ladder