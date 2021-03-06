// Time O(logN + K)
class Solution {
private:
    int findFirstGTE(const vector<int> &A, int target) {
        int l = 0;
        int r = A.size() - 1;
        while(l + 1 < r) {
            int mid = l + (r - l) / 2;
            if(A[mid] < target) l = mid;
            else r = mid;
        }

        if(A[l] >= target) return l;
        if(A[r] >= target) return r;

        return A.size();
    }
public:
    /**
     * @param A: an integer array
     * @param target: An integer
     * @param k: An integer
     * @return: an integer array
     */
    vector<int> kClosestNumbers(vector<int> &A, int target, int k) {

        int len = A.size();
        if(len == 0 || k == 0) return {};

        int pos = findFirstGTE(A, target);
        int lower = 0;
        int higher = pos;
        int loopCount = k;
        vector<int> result;
        if(pos == 0){
            lower = -1;
        } else if(pos == len) {
            lower = len - 1;
        } else {
            if(A[pos] == target) {
                result.push_back(target);
                --loopCount;
                lower = pos - 1;
                higher = pos + 1;
            } else {
                lower = pos - 1;
                higher = pos;
            }
        }

        while(loopCount-- > 0) {
            if(lower > -1 && higher < len) {
                if(target - A[lower] <= A[higher] - target) {
                    result.push_back(A[lower--]);
                } else {
                    result.push_back(A[higher++]);
                }
            } else {
                if(lower < 0 && higher < len) {result.push_back(A[higher++]);}
                else if(lower > -1 && higher >= len) {result.push_back(A[lower--]);}
                else {break;}
            }
        }
        return result;
    }
};


// Time O(logN + K)
class Solution {
public:
    /**
     * @param A: an integer array
     * @param target: An integer
     * @param k: An integer
     * @return: an integer array
     */
    vector<int> kClosestNumbers(vector<int> &A, int target, int k) {
        std::vector<int> result;
        if(k == 0) return result;
        int size = A.size();
        int mid;
        int start = 0;
        int end = size - 1;
        while(start < end) {
            mid = (start + end) / 2;
            if(A[mid] == target) break;
            else if(A[mid] < target) start = mid + 1;
            else end = mid - 1;
        }
        //std::cout << "start: " << start << ", end " << end << ", mid: " << mid << "\n";
        int left;
        int right;
        if(A[mid] == target) {
            result.push_back(target);
            --k;
            left = mid - 1;
            right = mid + 1;
        } else if(target < A[start]) {
            left = start - 1;
            right = start;
        } else {
            left = start;
            right = start + 1;
        }
        //std::cout << "left: " << left << ", right: " << right << "\n";
        //std::cout << "k: " << k << "\n";
        while(k > 0) {
            int leftVal = -10001;
            int rightVal = 10000;
            if(left > -1) leftVal = A[left];
            if(right < size) rightVal = A[right];
            //std::cout << "leftVal: " << leftVal << ", rightVal: " << rightVal << "\n";
            if(target - leftVal <= rightVal - target) {
               //std::cout << "pushing " << leftVal << "\n";
                result.push_back(leftVal);
                --left;
                --k;
            }
            if(k == 0) break;
            if(target - leftVal >= rightVal - target) {
                //std::cout << "pushing " << rightVal << "\n";
                result.push_back(rightVal);
                ++right;
                --k;
            }
        }
        return result;
    }
};