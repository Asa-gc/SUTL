#include <iostream>
#include "gtest/gtest.h"
#include <vector>
using namespace std;

void test_assertions (){
    vector<int>x,y;
    ASSERT_EQ(x.size(),y.size())<<"Vectors x and y are of unequal length";
    for (int i = 0; i < 10; ++i) {
        x.push_back(i);
        y.push_back(i);
    }
    y[4]=58;
    for (int i = 0; i < x.size(); ++i) {
      EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    }
}

int main()
{
    test_assertions();
    cout << "Hello World!" << endl;
    return 0;
}
