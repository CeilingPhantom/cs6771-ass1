/*
    'web' / graph of all words that are same length as input words
*/

#include <cstddef>
#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

namespace word_ladder {
    class word_web {

            enum edge_valid_state {
                none,
                invalid,
                valid,
            };

            // web stored as adjacency list
            // pair -> hamming dist, edge can be travelled via 1 weight hops
            absl::flat_hash_map<std::string, absl::flat_hash_map<std::string, std::pair<unsigned int, edge_valid_state>>> web_;
            //absl::flat_hash_map<std::string, absl::flat_hash_map<unsigned int, absl::flat_hash_set<std::string>>> web_by_weight_;

            void init_web(const std::size_t& word_len, const absl::flat_hash_set<std::string>& lexicon);
            static auto hamming_dist(const std::string& str1, const std::string& str2) -> unsigned int;
            void add_edge(const std::string& str1, const std::string& str2, const unsigned int& weight);

            auto ladder_len(const std::vector<std::string>& ladder) -> unsigned int;
            auto validate_edge(const std::string& curr, const std::string& dest, unsigned int iter) -> edge_valid_state;
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