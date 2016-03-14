#include "Skiplist.h"
#include "gtest/gtest.h"
const int LEN = 100000;

class SkiplistTest: public ::testing::Test {
protected:
	Skiplist p;
	int data[LEN];
	int end;
};

TEST_F(SkiplistTest, insertAndFind) {
	srand(time(NULL));
	for (int i = 0; i < LEN; i++)
		data[i] = rand();
	std::sort(data, data + LEN);
	end = std::unique(data, data + LEN) - data;
	for (int i = 0; i < end; i++)
		ASSERT_TRUE(p.insert(data[i]) && p.find(data[i]));
}

TEST_F(SkiplistTest, delAndFind) {
	for (int i = 0; i < end / 2; i++)
		ASSERT_TRUE(p.del(data[i]) && !p.find(data[i]));

	for (int i = end / 2; i < end; i++)
		ASSERT_TRUE(p.find(data[i]));
}