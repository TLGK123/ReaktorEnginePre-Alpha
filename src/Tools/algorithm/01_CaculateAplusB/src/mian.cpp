#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> res;
    int count = nums.size();
    for(int index = 0; index < count; ++index)
    {
        for (int j = index +1 ; j < count; ++j) {
            if(nums.at(index) + nums.at(j) == target)
            {
                
                res.push_back(index);
                res.push_back(j);
                return res;
            }
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    vector<int> valList = { 2,7,11,15};
    auto c =twoSum(valList,9);
	return 0;
}
