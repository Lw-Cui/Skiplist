#include "Skiplist.h"
#include "gtest/gtest.h"
#include <algorithm>
using namespace std;

class SkiplistTest: public ::testing::Test {
protected:
	static const int LEN = 100000;
	Skiplist p;
	int data[LEN];
	int end;
};

TEST_F(SkiplistTest, insertAndFind) {
	srand(time(NULL));
	for (auto &value: data)
		value = rand();
	sort(data, data + LEN);
	end = unique(data, data + LEN) - data;
	for (auto value: data)
		ASSERT_TRUE(p.insert(value) && p.find(value));
}

TEST_F(SkiplistTest, delAndFind) {
	for (int i = 0; i < end / 2; i++)
		ASSERT_TRUE(p.del(data[i]) && !p.find(data[i]));

	for (int i = end / 2; i < end; i++)
		ASSERT_TRUE(p.find(data[i]));
}