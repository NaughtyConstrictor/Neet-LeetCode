/**
 * @param {number[]} nums
 * @return {boolean}
 */


// sol2
var containsDuplicate = function(nums) {
    // `.toSorted` method is supported in node 20 and higher
    const sorted_nums = [...nums].sort()
    //const sorted_nums = nums.slice().sort()
    for (let i = 1; i < sorted_nums.length; ++i) {
        if (sorted_nums[i] === sorted_nums[i - 1])
            return true
    }
    return false;
};

// sol1
var containsDuplicate = function(nums) {
    let seen = new Set()
    for (const num of nums) {
        if (seen.has(num))
            return true;
        seen.add(num)
    }
    return false
};