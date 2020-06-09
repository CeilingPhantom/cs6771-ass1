/*
    'web' / graph of all words that are same length as input words
*/

#include <cstddef>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

namespace word_ladder {
    class word_web {

            const std::size_t& word_len_;
            // web stored as adjacency list
            absl::flat_hash_map<std::string, absl::flat_hash_set<std::string>> web_;

            void init_web(const absl::flat_hash_set<std::string>& lexicon);
            static auto one_char_diff(const std::string& str1, const std::string& str2) -> bool;
            void add_edge(const std::string& str1, const std::string& str2);

            auto shortest_ladders(const std::string& from, const std::string& to)
                -> std::vector<std::vector<std::string>>;

        public:
            word_web(const std::size_t& word_len, const absl::flat_hash_set<std::string>& lexicon)
                : word_len_(word_len) {
                init_web(lexicon);
            }
            auto shortest_ladders_sorted(const std::string& from, const std::string& to)
                -> std::vector<std::vector<std::string>>;

    };
}  // namespace word_ladder