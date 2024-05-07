//
// Created by Shira Meiri on 07/05/2024.
//

#include "LeetcodeStorage.h"

int Solution::gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void Solution::merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

int Solution::removeElement(vector<int> &nums, int val) {
    int n = nums.size();
    int i = 0;
    while (i < n) {
        if (nums[i] == val) {
            nums[i] = nums[n - 1];
            n--;
        } else {
            i++;
        }
    }
    return n;
}

int Solution::removeDuplicates(vector<int> &nums) {
    if (nums.empty()) return 0;
    int i = 0;
    for (int j = 1; j < nums.size(); j++) {
        if (nums[j] != nums[i]) {
            i++;
            nums[i] = nums[j];
        }
    }
    nums.resize(i + 1);
    return i + 1;
}

int Solution::removeDuplicates2(vector<int> &nums) {
    if (nums.empty()) return 0;
    int i = 0;
    int rep = 1;
    for (int j = 1; j < nums.size(); j++) {
        if (nums[j] != nums[i]) {
            i++;
            nums[i] = nums[j];
            rep = 1;
        } else if (rep < 2) {
            i++;
            nums[i] = nums[j];
            rep++;
        }
    }
    nums.resize(i + 1);
    return i + 1;
}

int Solution::majorityElement(vector<int> &nums) {
    int count = 0;
    int candidate = 0;
    for (int num: nums) {
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }
    return candidate;

}

void Solution::rotate(vector<int> &nums, int k) {
    int n = nums.size();
    k = k % n;
    int count = 0; // count for the number of elements visited
    for (int start = 0; count < n; start++) {
        int current = start;
        int prev = nums[start];
        do {
            int next = (current + k) % n;
            int temp = nums[next]; // save the value at the target position
            nums[next] = prev; // update the value at the target position
            prev = temp;
            current = next;
            count++;
        } while (start != current); // end the loop if we've returned to the start
    }
}

void Solution::rotate3(vector<int> &nums, int k) {
    //idea: move by k to i%k, when finished a cycle, go to the next one. works perfectly fine due to algebra being awesome
    int n = nums.size();
    k = k % n;
    int sets = gcd(k, n);
    for (int i = 0; i < sets; i++) {
        int temp = nums[i];
        int j = i;
        while (true) {
            int d = (j + k) % n;
            if (d == i)
                break;
            nums[j] = nums[d];
            j = d;
        }
        nums[j] = temp;
    }
}

void Solution::rotate2(vector<int> &nums, int k) {
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

int Solution::maxProfit2(vector<int> &prices) {
    //sliding window
    int n = int(prices.size());
    int MIN_PRICE = INT_MAX;
    int maxProfit = 0;
    for (int i = 0; i < n; i++) {
        if (prices[i] < MIN_PRICE) {
            MIN_PRICE = prices[i];
        } else {
            maxProfit = max(maxProfit, prices[i] - MIN_PRICE);
        }
    }
    return maxProfit;

}

int Solution::maxProfit(vector<int> &prices) {
    int n = prices.size();
    int maxProfit = 0;
    for (int i = 1; i < n; i++) {
        if (prices[i] > prices[i - 1]) {
            maxProfit += prices[i] - prices[i - 1];
        }
    }
    return maxProfit;
}

bool Solution::canJump1(vector<int> &nums) {
    if (nums.empty()) {
        return true;
    }
    int jump_dist = nums[0];
    int n = int(nums.size());
    int i = 0;
    while (i < n) {
        if (nums[i] > jump_dist) {
            jump_dist = nums[i];
        } else if (jump_dist <= 0 && i < n - 1) {
            return false;
        }
        jump_dist--;
        i++;
    }
    return true;
}

int Solution::jump(vector<int> &nums) {
    int n = nums.size();
    int jumps = 0, curEnd = 0, curFarthest = 0;
    for (int i = 0; i < n - 1; i++) {
        curFarthest = max(curFarthest, i + nums[i]);
        if (i == curEnd) {
            jumps++;
            curEnd = curFarthest;
        }
    }
    return jumps;

}

int Solution::hIndex(vector<int> &citations) {
    int n = int(citations.size());
    //counting sort
    vector<int> count(n + 1, 0);
    for (int c: citations) {
        count[min(c, n)]++;
    }
    int k = n;
    for (int s = count[n]; s < k; s += count[k]) {
        k--;
    }
    return k;
}

vector<int> Solution::productExceptSelf(vector<int> &nums) {
    int n = nums.size();

    vector<int> output(n, 1);
    int left = 1;
    for (int i = 0; i < n; i++) {
        output[i] = left;
        left *= nums[i];
    }
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
        output[i] *= right;
        right *= nums[i];
    }
    return output;
}

int Solution::canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();
    int total_tank = 0;
    int curr_tank = 0;
    int starting_station = 0;
    for (int i = 0; i < n; i++) {
        total_tank += gas[i] - cost[i];
        curr_tank += gas[i] - cost[i];
        if (curr_tank < 0) {
            starting_station = i + 1;
            curr_tank = 0;
        }
    }
    return total_tank >= 0 ? starting_station : -1;
}

int Solution::candy(vector<int> &ratings) {
    int n = ratings.size();

    vector<int> candies(n, 1);
    //left to right
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1] && candies[i] <= candies[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }
    //right to left
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {
            candies[i] = candies[i + 1] + 1;
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += candies[i];
    }
    return sum;
}

int Solution::trap(vector<int> &height) {
    int n = height.size();
    if (n == 0) return 0;

    int left = 0, right = n - 1;
    int maxLeft = height[left], maxRight = height[right];
    int water = 0;

    while (left < right) {
        if (height[left] <= height[right]) {
            left++;
            maxLeft = max(maxLeft, height[left]);
            water += maxLeft - height[left];
        } else {
            right--;
            maxRight = max(maxRight, height[right]);
            water += maxRight - height[right];
        }
    }

    return water;

}

int Solution::romanToInt(string s) {
    unordered_map<char, int> romanToInt = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
    };
    int n = s.size();
    int result = romanToInt[s[n - 1]];
    for (int i = n - 2; i >= 0; i--) {
        if (romanToInt[s[i]] < romanToInt[s[i + 1]]) {
            result -= romanToInt[s[i]];
        } else {
            result += romanToInt[s[i]];
        }
    }
    return result;
}

string Solution::intToRoman(int num) {
    unordered_map<int, char> intToRoman = {
            {1,    'I'},
            {5,    'V'},
            {10,   'X'},
            {50,   'L'},
            {100,  'C'},
            {500,  'D'},
            {1000, 'M'}
    };
    string result;
    int divisor = 1000;
    while (num > 0) {
        int digit = num / divisor;
        if (digit > 0) {
            if (digit == 9) {
                result += intToRoman[divisor];
                result += intToRoman[divisor * 10];
            } else if (digit >= 5) {
                result += intToRoman[divisor * 5];
                result += string(digit - 5, intToRoman[divisor]);
            } else if (digit == 4) {
                result += intToRoman[divisor];
                result += intToRoman[divisor * 5];
            } else {
                result += string(digit, intToRoman[divisor]);
            }
        }
        num %= divisor;
        divisor /= 10;
    }
    return result;
}

int Solution::lengthOfLastWord(string s) {
    int n = s.size();
    int length = 0;
    int i = n - 1;
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }
    return length;
}

string Solution::longestCommonPrefix(vector<string> &strs) {
    string prefix = "";
    if (strs.empty()) return prefix;
    int n = strs[0].size();
    for (int i = 0; i < n; i++) {
        char c = strs[0][i];
        for (const string &str: strs) {
            if (str[i] != c || str[i] == '\0') {
                return prefix;
            }
        }
        prefix += c;
    }
    return prefix;
}

string Solution::reverseWords(string s) {
    reverse(s.begin(), s.end());
    int n = s.size();
    int index = 0;
    for (int start = 0; start < n; start++) {
        if (s[start] != ' ') {
            if (index != 0) s[index++] = ' ';
            int end = start;
            while (end < n && s[end] != ' ') s[index++] = s[end++];
            reverse(s.begin() + index - (end - start), s.begin() + index);
            start = end;
        }
    }
    s.erase(s.begin() + index, s.end());
    return s;
}

string Solution::addBinary(string a, string b) {
    string result;
    int i = a.size() - 1, j = b.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 2;
        result += to_string(sum % 2);
    }
    if (carry) result += to_string(carry);
    reverse(result.begin(), result.end());
    return result;

}

uint32_t Solution::reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

vector<int> Solution::twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (map.find(complement) != map.end()) {
            return {map[complement], i};
        }
        map[nums[i]] = i;
    }
    return {};
}
