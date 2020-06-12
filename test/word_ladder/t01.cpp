#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/is_sorted.hpp"
#include "range/v3/range/primitives.hpp"

TEST_CASE("work -> play") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	CHECK(ranges::size(ladders) == 12);
	CHECK(ranges::is_sorted(ladders));

	CHECK(ranges::any_of(ladders, testing::contain({"work", "fork", "form", "foam", "flam", "flay", "play"})));

	std::cout << ":" << ladders.size() << std::endl;
}
