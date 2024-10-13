//{ Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};


Node *buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N')
        return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;)
        ip.push_back(str);

    // Create the root of the tree
    Node *root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current Node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current Node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size())
            break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current Node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


// } Driver Code Ends
//User function Template for C++

/*
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/
class Solution {
  public:
    int minTime(Node* root, int target) 
    {
        // Your code goes here
        map<Node*,vector<Node*>>adj;
        Node *x;
        function<void(Node*)>f=[&](Node* root)->void{
         if(root==NULL)
         return;
         
            if(root->left)
            {
                adj[root].push_back(root->left);
                adj[root->left].push_back(root);
            }
            
            if(root->right)
            {
                adj[root].push_back(root->right);
                adj[root->right].push_back(root);
            }
            if(root->data==target)
            x=root;
            f(root->left);
            f(root->right);
        };
        f(root);
        
        queue<pair<Node*,int>>q;
        q.push({x,0});
        set<Node*>vis;
        int res=0;
        while(!q.empty())
        {
            auto it=q.front();
            q.pop();
            auto u=it.first;
            // cout<<u->data<<" "<<it.second<<endl;
            res=max(res,it.second);
            vis.insert(u);
            for(auto i:adj[u])
            {
                if(vis.find(i)==vis.end())
                {
                    vis.insert(i);
                    q.push({i,it.second+1});
                }
            }
        }
        
        return res;
    }
};

//{ Driver Code Starts.

int main() 
{
    int tc;
    scanf("%d ", &tc);
    while (tc--) 
    {    
        string treeString;
        getline(cin, treeString);
        // cout<<treeString<<"\n";
        int target;
        cin>>target;
        // cout<<target<<"\n";

        Node *root = buildTree(treeString);
        Solution obj;
        cout<<obj.minTime(root, target)<<"\n"; 

        cin.ignore();

    }


    return 0;
}

// } Driver Code Ends