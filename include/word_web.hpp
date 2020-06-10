/*
    'web' / graph of all words that are same length as input words
*/

#include <cstddef>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

namespace word_ladder {
    class word_web {

            // web stored as adjacency list
            absl::flat_hash_map<std::string, absl::flat_hash_map<std::string, unsigned int>> web_;
            absl::flat_hash_map<std::string, absl::flat_hash_map<unsigned int, std::vector<std::string>>> web_by_weight_;

            void init_web(const std::size_t& word_len, const absl::flat_hash_set<std::string>& lexicon);
            static auto hamming_dist(const std::string& str1, const std::string& str2) -> unsigned int;
            void add_edge(const std::string& str1, const std::string& str2, const unsigned int& weight);

            auto ladder_len(std::vector<std::string>& ladder) -> unsigned int;
            auto validate_edge(std::string curr_word, std::string& next_word) -> bool;
            auto shortest_ladders(const std::string& from, const std::string& to)
                -> std::vector<std::vector<std::string>>;

        public:
            word_web(const std::size_t& word_len, const absl::flat_hash_set<std::string>& lexicon) {
                init_web(word_len, lexicon);
            }
            auto shortest_ladders_sorted(const std::string& from, const std::string& to)
                -> std::vector<std::vector<std::string>>;

    };
}  // namespace word_ladder