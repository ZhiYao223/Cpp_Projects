#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
}TreeNode;

class Solution{
public:
    void traversal(TreeNode* cur, vector<int>& vec){
        if (cur == nullptr) return ;
        vec.push_back(cur->val);
        traversal(cur->left, vec);
        traversal(cur->right, vec);
    }
    vector<int> preorderTraversal(TreeNode* root){
        vector<int> result;
        traversal(root,result);
        return result;
    }
};

class Solution
{
public:
    vector<int> preorderTraversal(TreeNode* root){
        stack<TreeNode*> st;
        vector<int> result;
        if(root == nullptr) return result;
        st.push(root);
        while(!st.empty()){
            TreeNode* node = st.top();
            if(node != NULL)
            {
                st.pop();
                result.push_back(node->val);
                if(node->right) st.push(node->right);
                if(node->left) st.push(node->left);
                st.push(node);
                st.push(NULL);
            }else
            {

            }
        }
    }
};

class Solution{
public:
    vector<vector<int>> levelOrder(TreeNode* root){
        queue<TreeNode*> que;
        if(root != nullptr) que.push(root);
        vector<vector<int>> result;
        while(!que.empty()){
            int size = que.size();
            vector<int> vec;
            for(int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(vec);
        }
        return result;
    }  
};

class Solution {
    public:
        vector<vector<int>> levelOrderBottom(TreeNode* root) {
            queue<TreeNode*> que;
            if (root != nullptr) que.push(root);
            vector<vector<int>> result;
            while(!que.empty()){
                int size = que.size();
                vector<int> vec;
                for(int i = 0; i < size; i++){
                    TreeNode* node = que.front();
                    que.pop();
                    vec.push_back(node->val);
                    if(node->left) que.push(node->left);
                    if(node->right) que.push(node->right);
                } 
                result.push_back(vec);
            } 
            reverse(result.begin(),result.end());
            return result;
        }
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> que;
        vector<int> vec;
        if (root != nullptr) que.push(root);
        while(!que.empty()){
            int size = que.size();
            for(int i = 0; i < size; i++){
                TreeNode*  node = que.front();
                que.pop();
                if(i == size-1) vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return vec;
    }
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        vector<double> result;
        while(!que.empty()){
            int size = que.size();
            double value = 0;
            for (int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                value += node->val;
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(value/size);
        }
        return result;
    }
};

class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*> que;
        if (root != nullptr) que.push(root);
        vector<vector<int>> result;
        while(!que.empty()){
            int size = que.size();
            vector<int> vec;
            for(int i = 0; i < size; i++){
                Node* node = que.front();
                que.pop();
                vec.push_back(node->val);
                for(int i = 0; i < node->children.size(); i++){
                    if (node->children[i]){
                        que.push(node->children[i]);
                    }
                }
            }
            result.push_back(vec);
        }
        return result;
    }
};

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
       queue<TreeNode*> que;
       if (root != nullptr) que.push(root);
       vector<int> result;
       while(!que.empty()){
            int size = que.size();
            int max = INT8_MIN;
            for (int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                max = node->val > max ? node->val : max;
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(max);
       }
       return result; 
    }
};

