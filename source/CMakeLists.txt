cxx_library(
	TARGET word_web
	FILENAME word_web.cpp
	LINK
		absl::flat_hash_map
		absl::flat_hash_set
)

cxx_library(
	TARGET word_ladder
	FILENAME word_ladder.cpp
	LINK range-v3 absl::flat_hash_set word_web
)

cxx_library(
	TARGET lexicon
	FILENAME lexicon.cpp
	LINK
	#     absl::flat_hash_map    # Uncomment if you use absl::flat_hash_map
	     absl::flat_hash_set
	#     absl::strings          # Uncomment if you use absl::StrCat
	#     fmt::fmt-header-only   # Uncomment if you use fmt::format
	#     gsl::gsl-lite-v1       # Uncomment if you use gsl_lite::narrow_cast
	     range-v3
)
