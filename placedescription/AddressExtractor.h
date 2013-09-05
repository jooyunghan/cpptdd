#pragma once
#include <string>
#include <json/forwards.h>

class Address {
	public:
		std::string road;
		std::string city;
		std::string state;
		std::string country;

		Address(const std::string& ro, const std::string& ci, const std::string& st, const std::string& co);
		std::string summary() const;
};

class AddressExtractor {
	public:
		Address extractFrom(const std::string& json) const;
	private:
		void parseJson(const std::string& json, Json::Value& value) const;
		Address makeAddress(const Json::Value& address) const;
};

