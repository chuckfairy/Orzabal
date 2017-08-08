/**
 * Jack port register should happen upon starting audio server
 */
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "Orzabal/JSON/json_test"

#include <boost/test/unit_test.hpp>

#include <json/json.hpp>

#include <iostream>

using nlohmann::json;

/**
 * Main port register
 */

BOOST_AUTO_TEST_CASE( json_test ) {

    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

    std::cout << j["happy"];

};
