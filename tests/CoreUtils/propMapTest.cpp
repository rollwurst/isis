/*
* propertyTest.cpp
*
*  Created on: Sep 23, 2009
*      Author: proeger
*/

// The BOOST_TEST_MODULE is similar to a unit test suite.
#define BOOST_TEST_MODULE PropMapTests
#include <boost/test/included/unit_test.hpp>
#include <CoreUtils/propmap.hpp>
#include <CoreUtils/vector.hpp>
#include <string>

namespace isis{namespace test{
	
	BOOST_AUTO_TEST_CASE(propMap_init_test)
	{
		ENABLE_LOG(util::CoreDebug,util::DefaultMsgPrint,util::warning);
		ENABLE_LOG(util::CoreLog,util::DefaultMsgPrint,util::warning);
		
		util::PropMap map1;
		map1["Test1"]=6.4;
		map1["Test2"]=5;
		map1["Test3"]=util::fvector4(1,1,1,1);
		map1["Test4"]=std::string("Hallo");
		
		BOOST_CHECK_EQUAL(map1["Test1"],6.4);
		BOOST_CHECK_EQUAL(map1["Test2"],5);
		BOOST_CHECK_EQUAL(map1["Test3"],util::fvector4(1,1,1,1));
		BOOST_CHECK_EQUAL(map1["Test4"],std::string("Hallo"));
		BOOST_CHECK(map1["Test5"].empty());
	}

	BOOST_AUTO_TEST_CASE(propMap_join_test)
	{
		util::PropMap map1,map2,result,org;
		map1["Test1"]=6.4;
		map1["Test3"]=util::fvector4(1,1,1,1);
		map1["Test4"]=std::string("Hallo");
		util::PropMap::key_list rej;

		//create empty Property "Test5" through accessing it
		BOOST_CHECK(map1["Test5"].empty());

		map2["Test2"]=5;
		map2["Test3"]=util::fvector4(1,1,1,1);
		map2["Test4"]=std::string("Hallo Welt");
		map2["Test5"]=std::string("nix leer");

		//First check not overwriting join
		result=map1;
		rej=result.join(map2);

		// Test2 should be inserted because its in map1
		// Test5 should be inserted because its empty in map1
		org = map1;
		org["Test2"]=map2["Test2"];
		org["Test5"]=map2["Test5"];
		BOOST_CHECK_EQUAL(org,result);
		
		// There should be one rejected key in reject, namely Test4 (its allready set in map1)
		BOOST_CHECK_EQUAL(rej.size(),1);
		BOOST_CHECK_EQUAL(*rej.begin(), "Test4");

		//now check with overwriting
		result=map1;
		rej=result.join(map2,true);
		
		//Test4 should be overwritten, and therefore be set to  "Hallo Welt"
		org["Test4"]=std::string("Hallo Welt");
		BOOST_CHECK_EQUAL(org,result);

		// nothing should be rejected
		BOOST_CHECK(rej.empty());
	}

	BOOST_AUTO_TEST_CASE(propMap_diff_test)
	{
		util::PropMap map1,map2;
		map1["Test1"]=6.4;
		map1["Test3"]=util::fvector4(1,1,1,1);
		map1["Test4"]=std::string("Hallo");
		util::PropMap::key_list rej;

		//create empty Property "Test5" through accessing it
		BOOST_CHECK(map1["Test5"].empty());

		map2["Test2"]=5;
		map2["Test3"]=util::fvector4(1,1,1,1);
		map2["Test4"]=std::string("Hallo Welt");
		map2["Test5"]=std::string("nix leer");

		util::PropMap::diff_map result=map1.diff(map2),org;

		//Test1 must be pair of map1["Test1"] and |empty|
		BOOST_CHECK_EQUAL(result["Test1"].first,map1["Test1"]);
		BOOST_CHECK(result["Test1"].second.empty());
		
		//Test2 must be pair of |empty| and map2["Test2"]
		BOOST_CHECK(result["Test2"].first.empty());
		BOOST_CHECK_EQUAL(result["Test2"].second,map2["Test2"]);

		//Test2 must be pair of map1["Test4"] and map2["Test4"]
		BOOST_CHECK_EQUAL(result["Test4"],std::make_pair(map1["Test4"],map2["Test4"]));

		//Test5 must be pair of |empty| and map2["Test5"]
		BOOST_CHECK(result["Test5"].first.empty());
		BOOST_CHECK_EQUAL(result["Test5"].second,map2["Test5"]);
		
	}
}}