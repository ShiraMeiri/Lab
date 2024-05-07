//
// Created by Shira Meiri on 07/05/2024.
//

#ifndef LAB_LEETCODESTORAGE_H
#define LAB_LEETCODESTORAGE_H

//
// Created by Shira Meiri on 24/04/2024.
//
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <random>
#include <cassert>
#include <map>

using namespace std;

class Solution {
private:
    int gcd(int a, int b);

public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n);

    int removeElement(vector<int> &nums, int val);

    int removeDuplicates(vector<int> &nums);

    int removeDuplicates2(vector<int> &nums);

    int majorityElement(vector<int> &nums);

    void rotate(vector<int> &nums, int k);

    void rotate3(vector<int> &nums, int k);

    void rotate2(vector<int> &nums, int k);

    int maxProfit2(vector<int> &prices);

    int maxProfit(vector<int> &prices);

    bool canJump1(vector<int> &nums);

    int jump(vector<int> &nums);

    int hIndex(vector<int> &citations);

    class RandomizedSet {
    private:
        vector<int> nums;
        unordered_map<int, int> valToIndex;

    public:
        RandomizedSet() {

        }

        bool insert(int val) {
            this->nums.push_back(val);
            try {
                this->valToIndex.at(val);
                return false;
            } catch (const out_of_range &oor) {
                this->valToIndex.insert(pair<int, int>(val, nums.size() - 1));
                return true;
            }

        }

        bool remove(int val) {
            try {
                int index = this->valToIndex.at(val);
                this->valToIndex.erase(val);
//                this->nums[index] = this->nums.back();
//                this->valToIndex[this->nums[index]] = this->nums.size()-1;
                this->nums.pop_back();
                return true;
            } catch (const out_of_range &oor) {
                return false;
            }
        }

        int getRandom() {
            return this->nums[random() % this->nums.size()];
        }
    };

    vector<int> productExceptSelf(vector<int> &nums);

    int canCompleteCircuit(vector<int> &gas, vector<int> &cost);

    int candy(vector<int> &ratings);

    int trap(vector<int> &height);

    int romanToInt(string s);

    string intToRoman(int num);

    int lengthOfLastWord(string s);

    string longestCommonPrefix(vector<string> &strs);

    string reverseWords(string s);

    string addBinary(string a, string b);

    uint32_t reverseBits(uint32_t n);

    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}

        ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *next) : val(x), next(next) {}

        ListNode *removeNodes(ListNode *head) {
            if (!head) return nullptr;
            //first step: reverse the list
            ListNode *prev = nullptr;
            ListNode *curr = head;
            ListNode *nextNode = nullptr;
            while (curr) {
                nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
            }
            //prev is the new head
            ListNode *newHead = prev;
            curr = newHead;
            prev = nullptr;

            //second step: do the removal
            int max = INT_MIN;
            while (curr) {
                if (curr->val > max) {
                    max = curr->val;
                    prev = curr;
                    curr = curr->next;
                } else if (curr->val == max) {
                    prev = curr;
                    curr = curr->next;
                } else {
                    if (!prev) { //not supposed to happen
                        cout << "error" << endl;
                        return nullptr;
                    }
                    prev->next = curr->next;
                    curr = curr->next;
                }
            }
            //third step: reverse the list again
            prev = nullptr;
            curr = newHead;
            nextNode = nullptr;
            while (curr) {
                nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
            }
            return prev;
        }

        ListNode *reverseList(ListNode *head) {
            ListNode *prev = nullptr;
            ListNode *curr = head;
            ListNode *nextNode = nullptr;
            while (curr) {
                nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
            }
            return prev;
        }

        ListNode *doubleIt(ListNode *head) {
            if (!head) return nullptr;
            //first step: reverse the list
            ListNode *newHead = reverseList(head);
            //prev is the new head
            ListNode *curr = newHead;
            int carry = 0;
            while (curr) {
                int sum = curr->val * 2 + carry;
                curr->val = sum % 10;
                carry = sum / 10;
                if (!curr->next && carry) {
                    curr->next = new ListNode(carry);
                    break;
                }
                curr = curr->next;
            }
            //third step: reverse the list again
            return reverseList(newHead);
        }
    };

    class FoodRatings {
    private:
        std::unordered_map<std::string, int> foodRatings;
        std::unordered_map<std::string, std::map<int, std::string, std::greater<int>>> cuisineFoods;

    public:
        FoodRatings(const std::vector<std::string> &foods, const std::vector<std::string> &cuisines,
                    const std::vector<int> &ratings) {
            for (int i = 0; i < foods.size(); ++i) {
                foodRatings[foods[i]] = ratings[i];
                cuisineFoods[cuisines[i]].insert({ratings[i], foods[i]});
            }
        }

        void changeRating(const std::string &food, int newRating) {
            int oldRating = foodRatings[food];
            for (auto &cuisine: cuisineFoods) {
                if (cuisine.second.count(oldRating) && cuisine.second[oldRating] == food) {
                    cuisine.second.erase(oldRating);
                    cuisine.second[newRating] = food;
                    break;
                }
            }
            foodRatings[food] = newRating;
        }

        std::string highestRated(const std::string &cuisine) {
            return cuisineFoods[cuisine].begin()->second;
        }
    };


    vector<int> twoSum(vector<int> &nums, int target);

};






#endif //LAB_LEETCODESTORAGE_H
