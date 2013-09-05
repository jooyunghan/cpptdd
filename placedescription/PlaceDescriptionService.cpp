#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(Http * http) 
	: http_(http) {
}

string PlaceDescriptionService::getAddressFrom(const string& latitude, const string& longitude) const {
	string jsonResponse = http_->get(makeRequest(latitude, longitude));
  Address address = AddressExtractor().extractFrom(jsonResponse);	
	return address.summary();
}

string PlaceDescriptionService::makeRequest(const string& latitude, const string& longitude) const {
	const string& start = "http://open.mapquestapi.com/nominatim/v1/reverse.php?format=json&";
	return start + "lat=" + latitude + "&lon=" + longitude;
}

