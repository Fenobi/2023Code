#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;


//string makeGood(string s)
//{
//    int t = 1;
//    
//    while (t)
//    {
//        int n = s.size();
//        int i = 0;
//        string str;
//        t = 0;
//        while (i < n)
//        {
//            
//            while (i < n && (s[i] == (s[i + 1] + 'A' - 'a') || s[i] == (s[i + 1] - 'A' + 'a')))
//            {
//                i += 2;
//                t = 1;
//            }
//            str += s[i];
//            ++i;
//        }
//        s = str;
//    }
//    return s;
//}

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    //*TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
};



int a[1000] = { 0 };
class Solution {
public:

    void Color(TreeNode* root)
    {
        if (root == NULL)
        {
            return;
        }
        a[root->val] = 1;
        Color(root->left);
        Color(root->right);
    }

    int numColor(TreeNode* root)
    {
        int sum = 0;
        Color(root);
        for (int i = 0; i < 1000; ++i)
        {
            if (a[i] == 1)
            {
                ++sum;
            }
        }
        return sum;
    }
};


//int main()
//{
//    string s("leEeetcode");
//    s = makeGood(s);
//    //s.resize(s.size());
//
//    /*string str;
//    for (int i = 0; i < s.size(); ++i)
//    {
//        str += s[i];
//    }*/
//    cout << s << '\n';
//    return 0;
//}