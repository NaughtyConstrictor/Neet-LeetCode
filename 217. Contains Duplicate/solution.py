from collections import Counter

class Solution:
    # sol3
    def containsDuplicate(self, nums: List[int]) -> bool:
        seen = set()
        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        return False
    # sol2
    def containsDuplicate(self, nums: List[int]) -> bool:
        return  len(set(nums)) != len(nums)

    # sol1
    def containsDuplicate(self, nums: List[int]) -> bool:
        counts = Counter(nums)
        return any(count > 1 for _, count in counts.items())