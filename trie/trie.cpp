#include <unordered_map>
#include <iostream>
#include <string>
#include <iterator>
#include <cctype>

using namespace std;

class trie {
	int count;
	unordered_map<char, trie> children;

	int& get(const char* s) {
		if (*s == '\0') {
			return count;
		} else {
			return children[*s].get(s+1);
		}
	}
public:
	int& operator[](const string& s) {
		return get(s.c_str());
	}
};

string normalize(string s) {
	auto out = ::begin(s);
	for (auto c : s) {
		if (::isalpha(c)) 
			*out++ = ::tolower(c);
	}
	return string(begin(s), out);
}

int main() {
	trie root;
	for (istream_iterator<string> word(cin), end; word != end; word++) {
		auto w = normalize(*word);
		if (w.size() > 0) {
			root[w]++;
		}
	}
	cout <<  root["steve"] << endl;
	return 0;
}

