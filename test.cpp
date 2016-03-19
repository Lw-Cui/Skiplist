#include "interface.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
using namespace std;

class SkiplistTest: public ::testing::Test {
protected:
	SkiplistTest():p(Baselist::make_Skiplist()) {}
	virtual void SetUp() {
		srand(time(NULL));
		for (auto &value: data)
			value = rand();
		sort(data, data + LEN);
		end = unique(data, data + LEN) - data;
	}

	static const int LEN = 10000;
	shared_ptr<Baselist> p;
	int data[LEN];
	int end;
};

TEST_F(SkiplistTest, insertAndFind) {
	for (int i = 0; i < end; i++) {
		ASSERT_TRUE(p->insert(data[i]));
		ASSERT_TRUE(p->find(data[i]));
	}
}

TEST_F(SkiplistTest, delAndFind) {
	for (int i = 0; i < end; i++) {
		ASSERT_TRUE(p->insert(data[i]));
		ASSERT_TRUE(p->del(data[i]));
		ASSERT_TRUE(!p->find(data[i]));
	}
}
