/*
 * 解题思路：先固定第一个数字，在数组中寻找两个元素相加
 * 之和为第一个数字的相反数，第一个固定的数字可以从数组
 * 开始依次遍历，寻找其余的两个数字时可以通过先排序，然
 * 后使用双指针的方式优化，最后可以使用set降重，这样一来
 * 时间复杂度为O(n^2)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>


using namespace std;

// vector<vector<int>> solution2(vector<int>& nums)
// {
//     vector<vector<int>>ans;
//     unordered_map<vector<int>,bool>um;
//     for(int i=0;i<nums.size()-2;i++)
//     {
//         for(int j=i+1;j<nums.size()-1;j++)
//         {
//             for(int k = j+1;k<nums.size();k++)
//             {
//                 if(nums[i]+nums[j]+nums[k]==0)
//                 {
//                     vector<int>temp{nums[i],nums[j],nums[k]};
//                     sort(temp.begin(),temp.end());
//                     if(um[temp]==false)
//                     {
//                         ans.push_back(temp);
//                         um[temp]=true;
//                     }
//                 }
//             }
//         }
//     }
//     return ans;
// }
vector<vector<int>> solution(vector<int>& nums)
{
    vector<vector<int>>ans;
    sort(nums.begin(),nums.end());
    for(int i=0;i<nums.size()-2;i++)
    {
        int n = 0-nums[i];
        
        int j = i+1;
        int k = nums.size()-1;
        
        while(j<k)
        {
            int sum = nums[j]+nums[k];
            if(sum<n)
            {
                j++;
            }
            else if(sum>n)
            {
                k--;
            }
            else
            {
                ans.push_back(vector<int>{nums[i],nums[j],nums[k]});
                j++;
            }
        }
    }
    return ans;
    // unordered_map<int,bool>umap;
    // for(auto num:nums)
    // {
    //     umap[num]=true;
    // }
}



int main()
{
    vector<int>nums{-1,0,1,2,-1,-4};
    
    vector<vector<int>>ans = solution(nums);
    
    cout<<'[';
    for(auto v:ans)
    {
        cout<<'[';
        for(auto n:v)
        {
            cout<<n<<' ';
        }
        cout<<"],";
    }
    cout<<']';
    // solution2(nums);
}