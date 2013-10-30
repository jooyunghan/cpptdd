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
	template <typename F>
	void foreach(F f) {
		foreach("", f);
	}
	template <typename F>
	void foreach(string prefix, F f) {
		if (count > 0) f(prefix, count);
		for_each(begin(children), end(children), [&](pair<char, trie> p) {
			p.second.foreach(prefix + p.first, f);
		});
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

typedef istream_iterator<string> isit;

int main() {
	trie root;
	for_each(isit(cin), isit(), [&](const string &w) {
		auto n = normalize(w);
		if (n.size() > 1) {
			root[n]++;
		}
	});
	cout <<  root["steve"] << endl;
	root.foreach([](string s, int count){ cout << s << ":" << count << endl; });
	return 0;
}

