#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>

using namespace std;

 struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode * t1 ,* t2 ,* t3 ,* t4 ,* t5;
    t4 = new ListNode(0);
    t1 = l1 , t2 =l2;
    t5 = t4;
    do
    {
        int v1 = t1 ==NULL ?0:t1->val;
        int v2 = t2 ==NULL ?0:t2->val;
        
        t4->val += v1+v2;
        if(t4->val>=10)
        {
            t4->val %=10;
            t4->next = new ListNode(1);
        }else
        {
      
            t4->next =new ListNode(0);
        }
        t3 =t4;
        t4= t4->next;
        
        if(t1 !=NULL)
        {
            //cout<<t1->val<<endl;
            t1= t1->next;
        };
        if(t2 !=NULL)
        {
            t2= t2->next;
        };
        ;
    }while ( t1!=NULL||t2!=NULL) ;
    
    if ( t4->val ==0) {
        t3->next =NULL;
    }
    return t5;
}

int main(int argc, char const *argv[])
{
    ListNode * l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next =  new ListNode(5);
    
    ListNode * l2 = new ListNode(5);
    l2->next = new ListNode(4);
    l2->next->next =  new ListNode(6);
    
    auto v =addTwoNumbers(l1,l2);
	return 0;
}


