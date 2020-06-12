#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/is_sorted.hpp"
#include "range/v3/range/primitives.hpp"

TEST_CASE("cat -> sea") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("cat", "sea", english_lexicon);

	CHECK(ranges::size(ladders) != 0);
	CHECK(ranges::is_sorted(ladders));

	CHECK(ranges::any_of(ladders, testing::contain({"cat", "sat", "set", "sea"})));

	std::cout << ":" << ladders.size() << std::endl;
}

TEST_CASE("sea -> cat") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("sea", "cat", english_lexicon);

	CHECK(ranges::size(ladders) != 0);
	CHECK(ranges::is_sorted(ladders));

	CHECK(ranges::any_of(ladders, testing::contain({"sea", "set", "sat", "cat"})));

	std::cout << ":" << ladders.size() << std::endl;
}
