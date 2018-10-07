class Solution {
public:
    /**
     * @param nums: an array of integers
     * @return: the number of unique integers
     */
    int deduplication(vector<int> &nums) {
        int len = nums.size();
        if(len == 0) return 0;
        std::sort(nums.begin(), nums.end());
        int left = 0;
        int right = 0;
        int duplicates = 0;
        while(right < len) {
            if(nums[left] != nums[right]) {
                ++left;
                nums[left] = nums[right];
            } else {
                ++duplicates;
            }
            ++right;
        }
        return left + 1;
    }
};