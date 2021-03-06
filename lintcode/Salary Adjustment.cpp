// Two binary search approach
class Solution {
public:
    /**
     * @param a: the list of salary
     * @param target: the target of the sum
     * @return: the cap it should be
     */
    int getCap(vector<int> &a, int target) {
        int size = a.size();
        std::sort(a.begin(), a.end());
        int sum = std::accumulate(a.begin(), a.end(), 0);
        int cacheSum[size] = {0};
        cacheSum[0] = sum;
        for(int i = 1; i < size; ++i) {
            cacheSum[i] = cacheSum[i-1] - a[i-1];
        }
        
        int start = 0;
        int end = size - 1;
        int mid;
        while(start + 1 < end) {
            mid = start + (end - start) / 2;
            sum = a[mid] * (mid+1) + cacheSum[mid+1];
            if ( sum == target) return a[mid];
            else if(sum < target ) start = mid;
            else end = mid;
        }
        
        int left = a[start];
        int right = a[end];
        int m;
        while(left + 1 < right) {
            m = left + (right - left) / 2;
            sum = m * (start+1) + cacheSum[start+1];
            if(sum == target) return m;
            else if (sum < target) left = m;
            else right = m;
        }
        if(left * (start+1) + cacheSum[start+1] == target) return left;
        if(right * (start) + cacheSum[start] == target) return right;
            
    }
};

// single binary search-based solution but not necessarily faster
class Solution {
private:
    int getTotal(const std::vector<int>& a, int cap) {
        int total = 0;
        for(auto i : a) {
            total += std::max(i, cap);
        }
        return total;
    }
public:
    /**
     * @param a: the list of salary
     * @param target: the target of the sum
     * @return: the cap it should be
     */
    int getCap(vector<int> &a, int target) {
        int size = a.size();
        // Assume cannot be empty
        std::sort(a.begin(), a.end());
        
        int left = a[0];
        int right = a[size - 1];
        int cap;
        while(left + 1 < right) {
            cap = left + (right - left) / 2;
            int total = getTotal(a, cap);
            if( total > target) right = cap;
            else if(total < target) left = cap;
            else return cap;
        }
        if(getTotal(a, left) == target) return left;
        if(getTotal(a, right) == target) return right;
        return -1;
    }
};