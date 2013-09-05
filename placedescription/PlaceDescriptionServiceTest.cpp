#include <gmock/gmock.h>
#include <string>
#include <stdexcept>
#include "PlaceDescriptionService.h"
#include "Http.h"

using namespace std;
using namespace ::testing;

class HttpStub : public Http {
	public:
		virtual string get(const string& url) {
			verify(url);
			return ("{\"place_id\":\"38440067\",\"licence\":\"Data \u00a9 OpenStreetMap contributors, ODbL 1.0. http:\\/\\/www.openstreetmap.org\\/copyright\",\"osm_type\":\"way\",\"osm_id\":\"26996903\",\"lat\":\"51.5217972792865\",\"lon\":\"-0.162823605843687\",\"display_name\":\"The Landmark, Melcombe Place, Marylebone, City of Westminster, \ub7f0\ub358, Greater London, England, NW1 6JJ, \uc601\uad6d\",\"address\":{\"hotel\":\"The Landmark\",\"road\":\"Melcombe Place\",\"suburb\":\"Marylebone\",\"city\":\"City of Westminster\",\"county\":\"\ub7f0\ub358\",\"state_district\":\"Greater London\",\"state\":\"England\",\"postcode\":\"NW1 6JJ\",\"country\":\"United Kingdom\",\"country_code\":\"gb\"}}");
		}
		void verify(const string& url) const {
			ASSERT_THAT(url, Eq("http://open.mapquestapi.com/nominatim/v1/reverse.php?format=json&lat=51.521435&lon=-0.162714"));
		}
};

TEST(APlaceDescriptionService, ReturnsValidAddressWithValidLocation) {
	HttpStub http;
	PlaceDescriptionService service(&http);
	string address = service.getAddressFrom("51.521435", "-0.162714");
	ASSERT_THAT(address, Eq("Melcombe Place, City of Westminster, England, United Kingdom"));
}

extern "C" {
#include <curl/curl.h>
}

class NetHttp : public Http {
	string body;
	public:
		virtual string get(const string& url) {
			CURL *curl;
			CURLcode res;
			curl = curl_easy_init();
			if (curl) {
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
				curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NetHttp::write);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
				curl_easy_perform(curl);
				curl_easy_cleanup(curl);
				return body;
			}
			throw runtime_error("can't initialize curl");
		}
		void append(void *ptr, size_t size, size_t nmemb) {
			body.append((const char*)ptr, size * nmemb);
		}
		static size_t write(void* ptr, size_t size, size_t nmemb, void* self) {
			((NetHttp*)self)->append(ptr, size, nmemb);
			return size * nmemb;
		}
};

TEST(APlaceDescriptionService, ReturnsValidAddressWithValidLocation_Real) {
	NetHttp http;
	PlaceDescriptionService service(&http);
	string address = service.getAddressFrom("51.521435", "-0.162714");
	ASSERT_THAT(address, Eq("Melcombe Place, City of Westminster, England, United Kingdom"));
}
