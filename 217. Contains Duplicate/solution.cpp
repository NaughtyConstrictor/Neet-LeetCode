#include <vector>
#include <unordered_set>
#include <algorithm>

//sol2
class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::vector<int> sorted_nums = std::vector(nums);
        std::sort(sorted_nums.begin(), sorted_nums.end());
        for (int i = 1; i < sorted_nums.size(); ++i)
        {
            if (sorted_nums[i] == sorted_nums[i - 1])
                return true;
        }
        return false;
    }
};


// sol1
class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::unordered_set<int> seen;
        for (int num: nums)
        {
            if (seen.count(num))
                return true;
            seen.insert(num);
        }
        return false;   
    }
};
