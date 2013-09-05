#pragma once
#include <string>
class Http;
class PlaceDescriptionService {
	Http * http_;
	public:
		PlaceDescriptionService(Http * http);
		std::string getAddressFrom(const std::string& latitude, const std::string& longitude) const;
	private:
		std::string makeRequest(const std::string& latitude, const std::string& longitude) const;
};
