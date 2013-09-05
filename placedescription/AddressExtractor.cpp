#include <stdexcept>
#include <json/value.h>
#include <json/reader.h>
#include "AddressExtractor.h"
using namespace std;

Address::Address(const string& ro, const string& ci, const string& st, const string& co) 
	: road(ro), city(ci), state(st), country(co) {
}

string Address::summary() const {
	return road + ", " + city + ", " + state + ", " + country;
}

Address AddressExtractor::extractFrom(const string& json) const {
	Json::Value value;
	parseJson(json, value);
  return makeAddress(value["address"]);	
}

Address AddressExtractor::makeAddress(const Json::Value& address) const {
	string road = address["road"].asString();
	string city = address["city"].asString();
	string state = address["state"].asString();
	string country = address["country"].asString();
	return Address(road, city, state, country);
}	

void AddressExtractor::parseJson(const string& json, Json::Value& value) const {
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json, value);
	if (!parsingSuccessful) {
		throw runtime_error("parse failed");
	}
}	

