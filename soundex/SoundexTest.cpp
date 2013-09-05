#include <gmock/gmock.h>
#include <string>
using namespace std;

/* TODO
 * case ignore
 */

string removeCharsIn(string chars, string word);
string replaceWithDigits(string consonants);
string first(string word) { return word.substr(0, 1); }
string rest(string word) { return word.substr(1); }
char digitFor(char c);
bool oneof(char ch, string chars);

string encodeWithDigits(string word) {
	string result {digitFor(word.front())};
	for (auto c : rest(word)) {
		auto digit = digitFor(c);
		if (result.back() != digit && !oneof(c, "hw")) {
			result.push_back(digit);
		}
	}
	return result;
}

string trim(string word) {
	string cut = word.substr(0, 4);
	return cut + string(4 - cut.size(), '0');
}

string encode(string word) {
	string encoded = first(word) + rest(encodeWithDigits(word));
	return trim(removeCharsIn("*", encoded));
}

bool oneof(char ch, string chars) {
	return chars.find(tolower(ch)) != string::npos;
}

string removeCharsIn(string chars, string word) {
	string result;
	for (auto c : word) {
		if (!oneof(c, chars)) {
			result.push_back(c);
		}
	}
	return result;
}

char digitFor(char c) {
	if (oneof(c, "bfpv")) {
		return '1';
	} else if (oneof(c, "cgjkqsxz")) {
		return '2';
	} else if (oneof(c, "dt")) {
		return '3';
	} else if (oneof(c, "l")) {
		return '4';
	} else if (oneof(c, "mn")) {
		return '5';
	} else if (oneof(c, "r")) {
		return '6';
	} else {
		return '*'; // special char for unmatching 
	}
}

TEST(Soundex, RemoveCharsIn) {
	ASSERT_EQ("", removeCharsIn("*", ""));
	ASSERT_EQ("", removeCharsIn("aeiouwhy", "aeiouwh"));
	ASSERT_EQ("bcdfgjklmnpqrstvxz", removeCharsIn("aeiouwhy", "abcdefghijklmnopqrstuvwxyz"));
}

TEST(Soundex, RetainFirstLetterAndDropsAll_AEIOUYHW) {
	ASSERT_EQ("A600", encode("Air"));
	ASSERT_EQ("H400", encode("Hello"));
}

TEST(Soundex, ReplaceConsonantsWithDigitsAfterFirstLetter_bfpv) {
	ASSERT_EQ("B000", encode("Bb"));
	ASSERT_EQ("B000", encode("Bf"));
	ASSERT_EQ("B000", encode("Bp"));
	ASSERT_EQ("B000", encode("Bv"));
	ASSERT_EQ("B000", encode("Bbb"));
	ASSERT_EQ("B000", encode("Bfv"));
}

TEST(Soundex, ReplaceConsonantsWithDigitsAfterFirstLetter_cgjkqsxz) {
	ASSERT_EQ("B200", encode("Bc"));
	ASSERT_EQ("B200", encode("Bg"));
	ASSERT_EQ("B200", encode("Bj"));
	ASSERT_EQ("B200", encode("Bk"));
	ASSERT_EQ("B200", encode("Bq"));
	ASSERT_EQ("B200", encode("Bs"));
	ASSERT_EQ("B200", encode("Bx"));
	ASSERT_EQ("B200", encode("Bz"));
	ASSERT_EQ("B200", encode("Bzz"));
	ASSERT_EQ("B200", encode("Bzc"));
}

TEST(Soundex, ReplaceConsonantsWithDigitsAfterFirstLetter_dt_l_mn_r) {
	ASSERT_EQ("B300", encode("Bd"));
	ASSERT_EQ("B300", encode("Bt"));
	ASSERT_EQ("B300", encode("Bdt"));
	ASSERT_EQ("B340", encode("Bdl"));
	ASSERT_EQ("B345", encode("Bdlmrn"));
}

TEST(Soundex, TwoOrMoreLettersWithSameNumberAreAdjacent_ThenOnlyRetainFirst) {
	ASSERT_EQ("B000", encode("Bbbb")); // this rule applies before rule # 1(retain first letter)
	ASSERT_EQ("B000", encode("Bpp"));
	ASSERT_EQ("B410", encode("Blpp"));
}

TEST(Soundex, SameNumberSeparatedBy_H_W_ThenCodedAsSingleNumber) {
	ASSERT_EQ("B000", encode("BHbHbb")); 
	ASSERT_EQ("B000", encode("BHpp"));
	ASSERT_EQ("B410", encode("BlpHp"));
}

TEST(Soundex, SameNumberSeparatedByVowels_ThenCodedAsSeparateNumbers) {
	ASSERT_EQ("B100", encode("BHbAbb")); 
	ASSERT_EQ("B100", encode("BHpAp"));
}

TEST(Soundex, ResultsInMax4LettersWithPaddingZeros) {
	ASSERT_EQ("R163", encode("Robert"));
	ASSERT_EQ("R163", encode("Rupert"));
	ASSERT_EQ("R150", encode("Rubin"));
	ASSERT_EQ("A261", encode("Ashcroft"));
}
