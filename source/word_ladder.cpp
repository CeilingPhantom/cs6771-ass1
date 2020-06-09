#include "comp6771/word_ladder.hpp"
#include "word_web.hpp"

namespace word_ladder {
    // Write your implementation here
    auto generate(const std::string& from,
                  const std::string& to,
                  const absl::flat_hash_set<std::string>& lexicon)
                  -> std::vector<std::vector<std::string>> {
        word_web web(from.length(), lexicon);
        return web.shortest_ladders_sorted(from, to);
    }
}  // namespace word_ladder
