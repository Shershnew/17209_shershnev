#include <gtest/gtest.h>
#include "flat_map.h"

using namespace Fmap;

TEST(Fmaptest, insert_erase_at) {
	Value v1(1), v2(2), v3(3), v4(4);
	Flat_map map1;
	EXPECT_EQ(map1.size(), 0);
	EXPECT_TRUE(map1.empty());
	map1.insert("el1", v1);
	map1.insert("el3", v3); /// std copy , copy backword
	map1.insert("el2", v2);
	map1.insert("el4", v4);
	EXPECT_EQ(v4.age, map1.at("el4").age);
	EXPECT_EQ(v1.age, map1.at("el1").age);
	EXPECT_EQ(v2.age, map1.at("el2").age);
	EXPECT_EQ(v3.age, map1.at("el3").age);
	EXPECT_ANY_THROW(map1.at("el7777"));
	map1.erase("el4");
	map1.erase("el1");
	map1.erase("el3");
	EXPECT_ANY_THROW(map1.at("el1"));
	EXPECT_ANY_THROW(map1.at("el3"));
	EXPECT_ANY_THROW(map1.at("el4"));
	EXPECT_EQ(v2.age, map1.at("el2").age);
}

TEST(Fmaptest, size_contains_empty_clear) {
	Value v1(1), v2(2), v3(3), v4(4);
	Flat_map map1;
	EXPECT_EQ(0, map1.size());
	EXPECT_TRUE(map1.empty());
	map1.insert("el1", v1);
	map1.insert("el3", v3);
	map1.insert("el2", v2);
	map1.insert("el4", v4);
	EXPECT_TRUE(map1.contains("el1"));
	EXPECT_TRUE(map1.contains("el2"));
	EXPECT_TRUE(map1.contains("el3"));
	EXPECT_TRUE(map1.contains("el4"));
	EXPECT_FALSE(map1.contains("el5"));
	EXPECT_FALSE(map1.empty());
	EXPECT_EQ(4, map1.size());
	map1.clear();
	EXPECT_TRUE(map1.empty());
	EXPECT_EQ(map1.size(), 0);
}

TEST(Fmaptest, brackets) {
	Value v1(1), v2(2), v3(3), v4(4);
	Flat_map map1;
	map1["el1"] = v1;
	map1["el3"] = v2;
	map1["el2"] = v3;
	map1["el4"] = v4;
	EXPECT_EQ(map1.at("el1").age, map1["el1"].age);
	EXPECT_EQ(map1.at("el2").age, map1["el2"].age);
	EXPECT_EQ(map1.at("el3").age, map1["el3"].age);
	EXPECT_EQ(map1.at("el4").age, map1["el4"].age);
}

TEST(Fmaptest, equality_constructor) {
	Value v1(1), v2(2), v3(3), v4(4);
	Flat_map map1;
	map1["el1"] = v1;
	map1["el3"] = v2;
	map1["el2"] = v3;
	map1["el4"] = v4;
	Flat_map map2 = map1;
	EXPECT_TRUE(map1 == map2);
	EXPECT_TRUE(map2 == map1);
	EXPECT_FALSE(map1 != map2);
	EXPECT_FALSE(map2 != map1);
	map1.erase("el2");
	EXPECT_FALSE(map1 == map2);
	EXPECT_FALSE(map2 == map1);
	EXPECT_TRUE(map1 != map2);
	EXPECT_TRUE(map2 != map1);
}

TEST(Fmaptest, swap_assignment) {
	Value v1(1), v2(2), v3(3), v4(4);
	Flat_map map1;
	map1["el1"] = v1;
	map1["el3"] = v2;
	map1["el2"] = v3;
	map1["el4"] = v4;
	Flat_map map2;
	map2 = map1 = map1;
	EXPECT_TRUE(map2 == map1);
	map1.erase("el1");
	EXPECT_TRUE(map2 != map1);
	map1.swap(map2);
	map2.swap(map1);
	map2.swap(map1);
	EXPECT_TRUE(map1.contains("el1"));
	EXPECT_FALSE(map2.contains("el1"));
}

int main(int argc, char ** argv){
	testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}