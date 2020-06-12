/*
    [1]
    Testing with the given lexicon against the examples given in the spec
    (with the exception of sea <-> cat)

    [2]
    Testing with a significantly smaller lexicon for correctness in that:
            [2.1]
            - ladders produced are the shortest
            - contents of the ladders are correct
            - ladders are sorted
            [2.2]
            - reversing the source and destination words should produce the
              same ladders but in reverse (and conform to req in [2.0])
            [2.3]
            - no ladders are produced if there are no possible ladders
*/

#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/is_sorted.hpp"
#include "range/v3/range/primitives.hpp"


// [1]

TEST_CASE("[1]: given lexicon, spec examples") {
	const auto english_lexicon = word_ladder::read_lexicon("./english.txt");

	SECTION("cat -> sea") {
	    const auto ladders = word_ladder::generate("cat", "sea", english_lexicon);

    	CHECK(ranges::size(ladders) != 0);
    	CHECK(ranges::is_sorted(ladders));

    	CHECK(ranges::any_of(ladders, testing::contain({"cat", "sat", "set", "sea"})));
    }

    SECTION("sea -> cat") {
        const auto ladders = word_ladder::generate("sea", "cat", english_lexicon);

    	CHECK(ranges::size(ladders) != 0);
    	CHECK(ranges::is_sorted(ladders));

    	CHECK(ranges::any_of(ladders, testing::contain({"sea", "set", "sat", "cat"})));
    }

    SECTION("work -> play") {
        const auto ladders = word_ladder::generate("work", "play", english_lexicon);

    	CHECK(ranges::size(ladders) == 12);
    	CHECK(ranges::is_sorted(ladders));

    	CHECK(ranges::any_of(ladders, testing::contain({"work", "fork", "form", "foam", "flam", "flay", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "pork", "perk", "peak", "pean", "plan", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "pork", "perk", "peak", "peat", "plat", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "pork", "perk", "pert", "peat", "plat", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "pork", "porn", "pirn", "pian", "plan", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "pork", "port", "pert", "peat", "plat", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "word", "wood", "pood", "plod", "ploy", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "worm", "form", "foam", "flam", "flay", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "worn", "porn", "pirn", "pian", "plan", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "wort", "bort", "boat", "blat", "plat", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "wort", "port", "pert", "peat", "plat", "play"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"work", "wort", "wert", "pert", "peat", "plat", "play"})));
    }

    SECTION("awake -> sleep") {
        const auto ladders = word_ladder::generate("awake", "sleep", english_lexicon);

    	CHECK(ranges::size(ladders) != 0);
    	CHECK(ranges::is_sorted(ladders));

    	CHECK(ranges::any_of(ladders, testing::contain({"awake","aware","sware","share","sharn","shawn","shewn","sheen","sheep","sleep"})));
    	CHECK(ranges::any_of(ladders, testing::contain({"awake","aware","sware","share","shire","shirr","shier","sheer","sheep","sleep"})));
    }

    SECTION("airplane -> tricycle") {
        const auto ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);

        CHECK(ranges::size(ladders) == 0);
    }
}


// [2]

TEST_CASE("[2]: custom small lexicon") {
    const auto lexicon = word_ladder::read_lexicon("./lex0");

    SECTION("[2.1]: ladders are shortest possible, sorted and have correct contents") {}
}
