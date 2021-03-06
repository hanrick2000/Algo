// Segment Tree solution, time O(NlogN)
class Solution {
private:
    struct SegmentTreeNode {
        int m_start;
        int m_end;
        int m_sum;
        SegmentTreeNode *m_left;
        SegmentTreeNode *m_right;
        SegmentTreeNode() = default;
        SegmentTreeNode(int start, int end, int sum) :
            m_start(start), m_end(end), m_sum(sum),
            m_left(nullptr), m_right(nullptr) {}
    };

    SegmentTreeNode* m_root;

    SegmentTreeNode * build(int start, int end, const vector<int>& A) {
        if(start > end) return nullptr;

        SegmentTreeNode * root = new SegmentTreeNode(start, end, A[start]);
        if(start == end) return root;

        int mid = (start + end) / 2;
        root->m_sum = 0;
        root->m_left = build(start, mid, A);
        root->m_right = build(mid + 1, end, A);
        if(root->m_left != nullptr) root->m_sum += root->m_left->m_sum;
        if(root->m_right != nullptr) root->m_sum += root->m_right->m_sum;
        return root;
    }

    int querySum(int start, int end, SegmentTreeNode* root) {
        if(root == nullptr || start > end) return 0;
        if(start <= root->m_start && end >= root->m_end) {
            return root->m_sum;
        }

        int leftSum = 0;
        int rightSum = 0;
        int mid = (root->m_start + root->m_end) / 2;
        if(start <= mid) {
            if(end <= mid) {
                leftSum = querySum(start, end, root->m_left);
            } else {
                leftSum = querySum(start, mid, root->m_left);
            }
        }
        if(end > mid){
            if(start > mid) {
                rightSum = querySum(start, end, root->m_right);
            } else {
                rightSum = querySum(mid + 1, end, root->m_right);
            }
        }

        return leftSum + rightSum;
    }

    void increaseValue(int index, SegmentTreeNode* root) {
        if(root == nullptr) return;

        if(index == root->m_start && index == root->m_end) {
            ++root->m_sum;
            return;
        }

        int mid = (root->m_start + root->m_end) / 2;
        if(index <= mid) {
            increaseValue(index, root->m_left);
        } else {
            increaseValue(index, root->m_right);
        }
        root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
    }
public:
    /**
     * @param nums: a list of integers
     * @return: return a list of integers
     */
    vector<int> countSmaller(vector<int> &nums) {
        int len = nums.size();
        if(len == 0) return {};

        int maxNum = INT_MIN;
        int minNum = INT_MAX;
        for(auto i : nums) {
            maxNum = std::max(maxNum, i);
            minNum = std::min(minNum, i);
        }

        vector<int> A(maxNum - minNum + 1, 0);
        int offsetMax = maxNum - minNum;
        m_root = build(0, offsetMax, A);

        vector<int> result(len, 0);
        for(int i = len - 1; i >= 0; --i) {
            increaseValue(nums[i] - minNum, m_root);
            if(nums[i] - minNum == 0) {
                result[i] = 0;
                continue;
            }
            result[i] = querySum(0, nums[i] - minNum - 1, m_root);
        }
        return result;
    }
};


// Binary indexed tree solution time O(NlogN)
class Solution {
private:
    vector<int> m_biTree;
    int m_size;

    int lowBit(int x) {
        return x & (-x);
    }

    void descretization(vector<int>& nums) {
        vector<int> sortedNums(nums);
        sort(sortedNums.begin(), sortedNums.end());
        int len = nums.size();
        for(int i = 0; i < len; ++i) {
            nums[i] = binarySearch(sortedNums, nums[i]) + 1;
        }
    }

    int binarySearch(const vector<int>& sortedNums, int target) {
        int start = 0;
        int end = sortedNums.size() - 1;
        while(start + 1 < end) {
            int mid = (start + end) / 2;
            if(sortedNums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }

        if(sortedNums[start] == target) return start;
        if(sortedNums[end] == target) return end;
        return sortedNums.size();
    }

    void add(int pos, int val) {
        ++pos;
        for(int i = pos; i < m_size + 1; i += lowBit(i)) {
            m_biTree[i] += val;
        }
    }

    int sum(int pos) {
        int sum = 0;
        ++pos;
        for(int i = pos; i > 0; i -= lowBit(i)) {
            sum += m_biTree[i];
        }
        return sum;
    }
public:
    /**
     * @param nums: a list of integers
     * @return: return a list of integers
     */
    vector<int> countSmaller(vector<int> &nums) {
        int len = nums.size();
        if(len == 0) return {};

        m_size = len;
        m_biTree.resize(len + 1);
        descretization(nums);

        vector<int> result(len, 0);
        for(int i = len - 1; i >= 0; --i) {
            add(nums[i], 1);
            result[i] = sum(nums[i]-1);
        }
        return result;
    }
};