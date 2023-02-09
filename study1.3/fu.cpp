//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//struct ListNode 
//{
//    int val;
//    struct ListNode* next;
//};
//
//ListNode* reverseBetween(ListNode* head, int m, int n)
//{
//    if (m == n)
//    {
//        return head;
//    }
//
//    ListNode* n1 = head;
//    int a = 1;
//    if (m == 1)
//    {
//        n1 = (struct ListNode*)malloc(sizeof(struct ListNode));
//        n1->next = head;
//        --a;
//    }
//
//    ListNode* cur = n1;
//    while ((a + 1) != m)
//    {
//        cur = cur->next;
//        ++a;
//    }
//    ListNode* begin1 = cur;
//    ListNode* begin2 = cur->next;
//
//    cur = head;
//    a = 1;
//    while (a != n)
//    {
//        cur = cur->next;
//        ++a;
//    }
//    ListNode* end1 = cur;
//    ListNode* end2;
//    if (cur->next == nullptr)
//    {
//        end2 = nullptr;
//    }
//    else
//    {
//        end2 = cur->next;
//    }
//
//    ListNode* prve = nullptr;
//    ListNode* curr = begin2;
//    while (curr != end2)
//    {
//
//        ListNode* next = curr->next;
//        curr->next = prve;
//        prve = curr;
//        curr = next;
//    }
//    
//    begin1->next = end1;
//    begin2->next = end2;
//    if (m == 1)
//    {
//        return end1;
//    }
//
//    return head;
//};
//
//
//ListNode* removeZeroSumSublists(ListNode* head)
//{
//    if (head == nullptr || head->next == nullptr)
//    {
//        return head;
//    }
//
//    int n = 0;
//    vector<int> v;
//    ListNode* cur = head;
//    while (cur != nullptr)
//    {
//        v.push_back(cur->val + n);
//        n += cur->val;
//        cur = cur->next;
//    }
//    int begin = 0;
//    int end = 0;
//    int t = 0;
//    for (int i = 0; i < v.size(); ++i)
//    {
//        int s = v[i];
//        for (int j = i + 1; j < v.size(); ++j)
//        {
//            if (s == v[j])
//            {
//                begin = i;
//                end = j;
//                t = 1;
//            }
//        }
//        if (t == 1)
//        {
//            break;
//        }
//    }
//    cur = head;
//    while (begin--)
//    {
//        cur = cur->next;
//    }
//    ListNode* n1 = cur;
//    cur = head;
//    while (end--)
//    {
//        cur = cur->next;
//    }
//    ListNode* n2 = cur;
//    n1->next = n2->next;
//    return head;
//}
//
//int main()
//{
//    struct ListNode* n1 = (struct ListNode*)malloc(sizeof(struct ListNode));
//    struct ListNode* n2 = (struct ListNode*)malloc(sizeof(struct ListNode));
//    struct ListNode* n3 = (struct ListNode*)malloc(sizeof(struct ListNode));
//    struct ListNode* n4 = (struct ListNode*)malloc(sizeof(struct ListNode));
//    struct ListNode* n5 = (struct ListNode*)malloc(sizeof(struct ListNode));
//
//    n1->val = 1;
//    n2->val = 2;
//    n3->val = -3;
//    n4->val = 3;
//    n5->val = 1;
//
//    n1->next = n2;
//    n2->next = n3;
//    n3->next = n4;
//    n4->next = n5;
//    n5->next = nullptr;
//
//    //reverseBetween(n1, 1, 5);
//    removeZeroSumSublists(n1);
//    return 0;
//}