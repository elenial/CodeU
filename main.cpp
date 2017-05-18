#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>
#include <struct.h>
using namespace std;

char s1[100], s2[100];
int counts1[26], counts2[26];

struct node {
    int val;
    node *nxt;
};

void findkthtolast() {
    //Read list elements
    
    int n;
    printf("Enter list size\n");
    scanf("%d",&n); //length of list
    node *root = new(node);
    
    printf("Enter list elements\n");
    
    //Inserting elements into list
    node *prev = new(node);
    
    for (int i = 0; i < n; i++) {
        
        //create new node
        node *tmp = new(node);
        tmp->nxt = NULL;
        scanf("%d",&tmp->val);
        
        //have previous node point to it
        if (i != 0) {
            prev->nxt = tmp;
        } else {
            root = tmp;
        }
        prev = tmp;
    }
    
    int k;
    printf("Enter k\n");
    scanf("%d",&k);
    
    //Finding kth to last
    int pos = 0;
    node *curr = root;
    
    while (pos != n - k - 1) {
        curr = curr->nxt;
        pos++;
    }
    
    printf("%d\n",curr->val);
    
}

void isPermutation() {
    //Read input
    
    printf("Enter the 2 strings separated by a newline\n");

    scanf("%s", s1);
    scanf("\n");
    scanf("%s",s2);
    
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    
    //Input validation
    
    if (l1 == 0 || l2 == 0) 
        throw "Can't use empty string";
    
    //Solution
    
    for (int i = 0; i < l1; i++) { 
        if ((s1[i] < 'a' && s1[i] > 'Z') || s1[i] > 'z' || s1[i] < 'A' || (s1[i] > 'Z' && s1[i] < 'a')) 
            throw "Not valid character";
        
        counts1[tolower(s1[i]) - 'a']++;
    }
    
    for (int i = 0; i < l2; i++) {
        if ((s2[i] < 'a' && s2[i] > 'Z') || s2[i] > 'z' || s2[i] < 'A' || (s2[i] > 'Z' && s2[i] < 'a')) 
            throw "Not valid character";
        counts2[tolower(s2[i]) - 'a']++;
    }
    
    bool perm = true;
    
    
    for (int i = 0; i < 26; i++) {
        if (counts1[i] != counts2[i]) { 
            perm = false;
            break;
        }
    }
    
    if (perm) 
        printf("True\n");
    else 
        printf("False\n");
}

int main()
{
    isPermutation();
    findkthtolast();
   
    return 0;
}

