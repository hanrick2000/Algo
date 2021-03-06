class Solution {
public:
    /**
     * @param friends: people's friends
     * @param user: the user's id
     * @return: the person who most likely to know
     */
    int recommendFriends(vector<vector<int>> &friends, int user) {
        unordered_map<int, unordered_set<int>> friendShip;

        int len = friends.size();
        for(int i = 0; i < len; ++i) {
            friendShip[i].insert(friends[i].begin(), friends[i].end());
        }

        unordered_set<int> candidates;
        for(int i = 0; i < len; ++i) {
            if(i != user) candidates.insert(i);
        }

        for(auto friendId : friendShip[user]) {
            candidates.erase(friendId);
        }


        int maxCount = 0;
        int mostProbably = -1;
        for(auto candidate : candidates) {
            unordered_set<int> intersection;
            for (auto i = friendShip[candidate].begin(); i != friendShip[candidate].end(); i++) {
                if (friendShip[user].find(*i) != friendShip[user].end()) intersection.insert(*i);
            }
            if(intersection.size() == 0) continue;
            if(intersection.size() > maxCount) {
                maxCount = intersection.size();
                mostProbably = candidate;
            } else if (intersection.size() == maxCount) {
                if(candidate < mostProbably) mostProbably = candidate;
            }
        }

        return mostProbably;
    }
};

// Time O(N^2)
class Solution {
public:
    /**
     * @param friends: people's friends
     * @param user: the user's id
     * @return: the person who most likely to know
     */
    int recommendFriends(vector<vector<int>> &friends, int user) {
        unordered_set<int> userFriends;

        for(auto friendId : friends[user]) {
            userFriends.insert(friendId);
        }
        int len = friends.size();
        int mx = -1;
        int ans = -1;
        for(int i = 0; i < len; i++) {
            if(i == user || userFriends.count(i) > 0) {
                continue;
            }
            int cnt = 0;
            for(auto friendId : friends[i]) {
                if(userFriends.count(friendId) > 0) {
                    cnt++;
                }
            }
            if(cnt == 0) {
                continue;
            }
            if(cnt > mx) {
                ans = i;
                mx = cnt;
            } else if(cnt == mx && ans > i) {
                ans = i;
            }
        }

        return ans;
    }
};