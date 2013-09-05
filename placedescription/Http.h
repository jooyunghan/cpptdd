#pragma once
#include <string>
class Http {
	public:
		virtual ~Http() {}
		virtual std::string get(const std::string& url) = 0;
};
