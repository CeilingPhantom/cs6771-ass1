/*
    Program assumes:
        - source and destination words exist in the lexicon
        - source and destination words are of the same length

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

		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "fork", "form", "foam", "flam", "flay", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "perk", "peak", "pean", "plan", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "perk", "peak", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "perk", "pert", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "porn", "pirn", "pian", "plan", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "port", "pert", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "word", "wood", "pood", "plod", "ploy", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "worm", "form", "foam", "flam", "flay", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "worn", "porn", "pirn", "pian", "plan", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "wort", "bort", "boat", "blat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "wort", "port", "pert", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "wort", "wert", "pert", "peat", "plat", "play"})));
	}

	SECTION("awake -> sleep") {
		const auto ladders = word_ladder::generate("awake", "sleep", english_lexicon);

		CHECK(ranges::size(ladders) != 0);
		CHECK(ranges::is_sorted(ladders));

		CHECK(ranges::any_of(
		   ladders,
		   testing::contain(
		      {"awake", "aware", "sware", "share", "sharn", "shawn", "shewn", "sheen", "sheep", "sleep"})));
		CHECK(ranges::any_of(
		   ladders,
		   testing::contain(
		      {"awake", "aware", "sware", "share", "shire", "shirr", "shier", "sheer", "sheep", "sleep"})));
	}

	SECTION("airplane -> tricycle") {
		const auto ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);

		CHECK(ranges::size(ladders) == 0);
	}
}

// [2]

TEST_CASE("[2]: custom small lexicon") {
	const auto lexicon = word_ladder::read_lexicon("./lex0");

	SECTION("[2.1]: ladders are shortest possible, sorted and have correct contents") {
		SECTION("a -> i") {
			const auto ladders = word_ladder::generate("a", "i", lexicon);

			CHECK(ranges::size(ladders) == 1);

			CHECK(ranges::any_of(ladders, testing::contain({"a", "i"})));
		}

		SECTION("ah -> no") {
			const auto ladders = word_ladder::generate("ah", "no", lexicon);

			CHECK(ranges::size(ladders) == 2);
			CHECK(ranges::is_sorted(ladders));

			CHECK(ranges::any_of(ladders, testing::contain({"ah", "aa", "na", "no"})));
			CHECK(ranges::any_of(ladders, testing::contain({"ah", "oh", "oo", "no"})));
		}

		SECTION("dog -> hex") {
			const auto ladders = word_ladder::generate("dog", "hex", lexicon);

			CHECK(ranges::size(ladders) == 2);
			CHECK(ranges::is_sorted(ladders));

			CHECK(ranges::any_of(ladders,
			                     testing::contain({"dog", "fog", "foe", "toe", "tox", "hox", "hex"})));
			CHECK(ranges::any_of(ladders,
			                     testing::contain({"dog", "fog", "foe", "woe", "wee", "wex", "hex"})));
		}

		SECTION("fall -> tilt") {
			const auto ladders = word_ladder::generate("fall", "tilt", lexicon);

			CHECK(ranges::size(ladders) == 1);

			CHECK(ranges::any_of(ladders, testing::contain({"fall", "wall", "will", "till", "tilt"})));
		}

		SECTION("yep -> nop") {
			const auto ladders = word_ladder::generate("yep", "nop", lexicon);

			CHECK(ranges::size(ladders) == 3);

			CHECK(ranges::any_of(ladders, testing::contain({"yep", "yap", "nap", "nop"})));
			CHECK(ranges::any_of(ladders, testing::contain({"yep", "pep", "pop", "nop"})));
			CHECK(ranges::any_of(ladders, testing::contain({"yep", "hep", "hop", "nop"})));
		}

		SECTION("aa -> oo") {
			const auto ladders = word_ladder::generate("aa", "oo", lexicon);

			CHECK(ranges::size(ladders) == 8);
			CHECK(ranges::is_sorted(ladders));

			CHECK(ranges::any_of(ladders, testing::contain({"aa", "ah", "oh", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "am", "om", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "an", "on", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "as", "os", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "ga", "go", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "ha", "ho", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "na", "no", "oo"})));
			CHECK(ranges::any_of(ladders, testing::contain({"aa", "ta", "to", "oo"})));
		}

		SECTION("avernus -> avernus") {
			const auto ladders = word_ladder::generate("avernus", "avernus", lexicon);

			CHECK(ranges::size(ladders) == 1);

			CHECK(ranges::any_of(ladders, testing::contain({"avernus"})));
		}
	}

	SECTION("[2.2]: [2.1] but reversed source and destination") {
		SECTION("i -> a") {
			const auto ladders = word_ladder::generate("i", "a", lexicon);

			CHECK(ranges::size(ladders) == 1);

			CHECK(ranges::any_of(ladders, testing::contain({"i", "a"})));
		}

		SECTION("ah -> no") {
			const auto ladders = word_ladder::generate("no", "ah", lexicon);

			CHECK(ranges::size(ladders) == 2);
			CHECK(ranges::is_sorted(ladders));

			CHECK(ranges::any_of(ladders, testing::contain({"no", "na", "aa", "ah"})));
			CHECK(ranges::any_of(ladders, testing::contain({"no", "oo", "oh", "ah"})));
		}

		SECTION("hex -> dog") {
			const auto ladders = word_ladder::generate("hex", "dog", lexicon);

			CHECK(ranges::size(ladders) == 2);
			CHECK(ranges::is_sorted(ladders));

			CHECK(ranges::any_of(ladders,
			                     testing::contain({"hex", "hox", "tox", "toe", "foe", "fog", "dog"})));
			CHECK(ranges::any_of(ladders,
			                     testing::contain({"hex", "wex", "wee", "woe", "foe", "fog", "dog"})));
		}

		SECTION("tilt -> fall") {
			const auto ladders = word_ladder::generate("tilt", "fall", lexicon);

			CHECK(ranges::size(ladders) == 1);

			CHECK(ranges::any_of(ladders, testing::contain({"tilt", "till", "will", "wall", "fall"})));
		}

		SECTION("nop -> yep") {
			const auto ladders = word_ladder::generate("nop", "yep", lexicon);

			CHECK(ranges::size(ladders) == 3);

			CHECK(ranges::any_of(ladders, testing::contain({"nop", "nap", "yap", "yep"})));
			CHECK(ranges::any_of(ladders, testing::contain({"nop", "pop", "pep", "yep"})));
			CHECK(ranges::any_of(ladders, testing::contain({"nop", "hop", "hep", "yep"})));
		}

		SECTION("oo -> aa") {
			const auto ladders = word_ladder::generate("oo", "aa", lexicon);

			CHECK(ranges::size(ladders) == 8);
			CHECK(ranges::is_sorted(ladders));

			CHECK(ranges::any_of(ladders, testing::contain({"oo", "oh", "ah", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "om", "am", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "on", "an", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "os", "as", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "go", "ga", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "ho", "ha", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "no", "na", "aa"})));
			CHECK(ranges::any_of(ladders, testing::contain({"oo", "to", "ta", "aa"})));
		}
	}

	SECTION("[2.3]: no possible ladders") {
		SECTION("harm -> heal") {
			const auto ladders = word_ladder::generate("harm", "heal", lexicon);
			CHECK(ranges::size(ladders) == 0);
		}

		SECTION("lord -> life") {
			const auto ladders = word_ladder::generate("lord", "life", lexicon);
			CHECK(ranges::size(ladders) == 0);
		}

		SECTION("war -> end") {
			const auto ladders = word_ladder::generate("war", "end", lexicon);
			CHECK(ranges::size(ladders) == 0);
		}
	}
}
