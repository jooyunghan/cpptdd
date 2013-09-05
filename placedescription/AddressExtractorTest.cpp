#include <gmock/gmock.h>
#include "AddressExtractor.h"
using namespace testing;

TEST(AddressExtractor, parsesJsonAddressFormat) {
	AddressExtractor extractor;
	Address address = extractor.extractFrom("{\"place_id\":\"38440067\",\"licence\":\"Data \u00a9 OpenStreetMap contributors, ODbL 1.0. http:\\/\\/www.openstreetmap.org\\/copyright\",\"osm_type\":\"way\",\"osm_id\":\"26996903\",\"lat\":\"51.5217972792865\",\"lon\":\"-0.162823605843687\",\"display_name\":\"The Landmark, Melcombe Place, Marylebone, City of Westminster, \ub7f0\ub358, Greater London, England, NW1 6JJ, \uc601\uad6d\",\"address\":{\"hotel\":\"The Landmark\",\"road\":\"Melcombe Place\",\"suburb\":\"Marylebone\",\"city\":\"City of Westminster\",\"county\":\"\ub7f0\ub358\",\"state_district\":\"Greater London\",\"state\":\"England\",\"postcode\":\"NW1 6JJ\",\"country\":\"\uc601\uad6d\",\"country_code\":\"gb\"}}");

	ASSERT_THAT(address.road, Eq("Melcombe Place"));
	ASSERT_THAT(address.city, Eq("City of Westminster"));
	ASSERT_THAT(address.state, Eq("England"));
	ASSERT_THAT(address.country, Eq("\uc601\uad6d"));
}

TEST(Address, summary) {
	ASSERT_THAT(Address("road", "city", "state", "country").summary(), Eq("road, city, state, country"));
}

