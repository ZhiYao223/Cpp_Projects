#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

//定义树
typedef struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
}TreeNode;

//定义链表节点
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(nullptr){}
};

//创建一个简单的二叉树
TreeNode* createSimpleTree(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

#if 0
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

class Solution{
public:
    bool isSymmetric(TreeNode* root){
        if(root == nullptr) return true;
        stack<TreeNode*> st;
        st.push(root->left);
        st.push(root->right);
        while(!st.empty()){
            TreeNode*  rightNode = st.top(); st.pop();
            TreeNode*  leftNode = st.top(); st.pop();
            if(!leftNode && !right) continue;
            if(!leftNode || !rightNode || (leftNode->val != rightNode->val)) return false;
            st.push(leftNode->left);
            st.push(rightNode->right);
            st.push(leftNode->right);
            st.push(rightNode->left);
        }
        return true;
    }
};

class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        queue<TreeNode*> que;
        if (root == nullptr && subRoot == nullptr) return true;
        que.push(root);
        que.push(subRoot);
        while(!que.empty()){
            TreeNode* rootNode = que.front(); que.pop();
            TreeNode* subNode = que.front(); que.pop();


        }
    }
};


//序列化二叉树(前序遍历)
class Solution{
public:
    void serializeTree(TreeNode* root, std::string& result){
        if(!root){
            result += "#"; //#表示空节点
            return ;
        }
        result += "#" + std::to_string(root->val) + "#";
        serializeTree(root->left, result);
        serializeTree(root->right, result);
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot){
        if (!subRoot) return true;
        if (!root) return false;
        //序列化root和subRoot
        std::string rootStr, subRootStr;
        serializeTree(root,rootStr);
        serializeTree(subRoot,subRootStr);
        return rootStr.find(subRootStr) != std::string::npos;
    }
};

class Solution{
public:
    // 计算树的高度
    int getdepth(TreeNode* node){
        if(node == nullptr) return 0;
        int depth = max(getdepth(node->left), getdepth(node->right)) + 1;
        return depth;
    }
    int maxDepth(TreeNode* root){
        return  getdepth(root);
    }
};

class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {val = _val;}
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Solution {
public:
    int maxDepth(Node* root) {
        if(root == nullptr) return 0;
        queue<Node*> que;
        que.push(root);
        int maxDepth = 0;
        while(!que.empty()){
            int size = que.size();
            vector<int> vec;
            for(int i = 0; i < size; i++){
                Node* node = que.front();
                que.pop();
                vec.push_back(node->val);
                for(auto child : node->children){
                    que.push(child);
                }
            }
            maxDepth++;
        }
        return  maxDepth;
    }
};

class Solution{
public:
    int maxDepth(Node* root){
        if(root == 0) return  0;
        int depth = 0; 
        for(int i = 0; i < root->children.size(); i++){
            depth = max(depth, maxDepth(root->children[i]));
        }
        return depth+1;
    }
};

class Solution{
public:
    int minDepth(TreeNode* root){
        if(root == nullptr) return 0;
        if(root->left == nullptr && root->right != nullptr){
            return  1 + minDepth(root->right);
        }
        if(root->left != nullptr && root->right == nullptr){
            return  1 + minDepth(root->left);
        }
        return 1+min(minDepth(root->left),minDepth(root->right));
    }
};

class Solution{
public:
    int minDepth(TreeNode* root){
        if(root == nullptr) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int depth = 0;
        while(!que.empty()){
            int size = que.size();
            for(int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
                if(!node->left && !node->right){
                    return depth + 1;  
                }
                depth++;
            }
        }
        return depth;
    }
};

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int count = 0;
        while(!que.empty()){
            int size = que.size();
            for(int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            count += size;
        }
        return  count;
    }
};

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftnum = countNodes(root->left);
        int rightnum = countNodes(root->right);
        int count = leftnum + rightnum + 1;
        return count;
    }
};

class Solution {
public:
    int getHeight(TreeNode* node){
        if(node == nullptr) return 0;
        int leftHeight = getHeight(node->left);
        if(leftHeight == -1) return -1;
        int rightHeight = getHeight(node->right);
        if(rightHeight == -1) return -1;
        return abs(leftHeight-rightHeight) > 1 ? -1 : 1+max(leftHeight, rightHeight);
    }
    bool isBalanced(TreeNode* root) {
        return getHeight(root) == -1 ? false : true; 
    }
};

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        
    }
    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result){
        if(cur->left == nullptr && cur->right == nullptr){
            
        }
    }
};


class Solution {
public:
    int divisorSubstrings(int num, int k) {
        vector<int> vec;
        string numStr = to_string(num);
        for(size_t i = 0; i <= numStr.size() - k; i++){
            int subNum = stoi(numStr.substr(i,k));
            vec.push_back(subNum);
        }
        int beautifulCount = 0;
        for(auto subnum : vec){
            if(subnum != 0 && num % subnum == 0){
                ++beautifulCount;
            }
        }
        return beautifulCount;
    }
};

class Solution {
public:
    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result){
        if(cur != nullptr){
            path.push_back(cur->val);
        }
        if(cur->left)  {
            traversal(cur->left, path, result);
            path.pop_back();
        }
        if(cur->right) {
            traversal(cur->right, path, result);
            path.pop_back();
        }
        if(cur->left == nullptr && cur->right == nullptr){
            string sPath;
            for(int i = 0; i < path.size()-1; i++){
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() -1]);
            result.push_back(sPath); //收集一个路径
            return;
        }

    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<int> path; 
        vector<string> result;
        if(root == nullptr) return result;
        traversal(root, path, result);
        return result;
    }
};



//前序遍历
class Solution1{
public:
    vector<int> preorderTraversal(TreeNode* root){
        vector<int> result;
        stack<TreeNode*> st;
        if(root != nullptr) st.push(root);
        while(!st.empty()){
            TreeNode* node = st.top();
            if(node != nullptr){
                st.pop();
                if(node->right) st.push(node->right);
                if(node->left) st.push(node->left);
                st.push(node);
                st.push(nullptr);
            }else{
                st.pop();
                result.push_back(st.top()->val);
                st.pop();
            }
        }   
        return result;
    }
};

class Solution2{
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> result;
        stack<TreeNode*> st;
        if(root != nullptr) st.push(root);
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            if(node != nullptr){
                if(node->right) st.push(node->right);
                st.push(node);
                st.push(nullptr);
                if(node->left) st.push(node->left);
            }else{
                result.push_back(st.top()->val);
                st.pop();
            }
        }
        return result;
    }
};

class Solution3{
public:
    vector<int> postorderTraversal(TreeNode* root){
        vector<int> result;
        stack<TreeNode*> st;
        if(root != nullptr) st.push(root);
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            if(node != nullptr){
                st.push(node);
                st.push(nullptr);
                if(node->right) st.push(node->right);
                if(node->left) st.push(node->left);
            }else{
                result.push_back(st.top()->val);
                st.pop();
            }
        }
        return result;
    }
};

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftnum = countNodes(root->left);
        int rightnum = countNodes(root->right);
        int count = leftnum + rightnum + 1;
        return count;
    }
};



class Solution{
public:
    bool isSameTree(TreeNode* p, TreeNode* q){
    if(p == nullptr && q == nullptr) return true;
    if(p == nullptr || q == nullptr) return false;
    if(p->val != q->val) return false;
    return isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
    }
    
    bool isSubtree(TreeNode* root,TreeNode* subRoot){
        if(root == nullptr) return false;
        if(isSameTree(root, subRoot)) return true;
        return isSubtree(root->left,subRoot) || isSubtree(root->right, subRoot);
    }
};


class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        stack<TreeNode*> st;
        if(root == nullptr) return 0;
        st.push(root);
        int result = 0;
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            if(node->left != nullptr && node->left->left == nullptr && node->left->right == nullptr){
                result += node->left->val; 
            }
            if(node->right) st.push(node->right);
            if(node->left) st.push(node->left);
        }
        return result;
    }
};

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int result = 0;
        while(!que.empty()){
            int size = que.size();
            for(int i = 0; i < size; i++){
                TreeNode* node =que.front();
                que.pop();
                if(i == 0) result = node->val;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        return result;
    }
};

class Solution{
public:
    int maxDepth = INT8_MIN;
    int result;
    void traversal(TreeNode* root, int depth){
        if(root->left == nullptr && root->right == nullptr){
            if(depth > maxDepth){
                maxDepth = depth;
                result = root->val;
            }
        }
        if(root->left) {
            depth++;
            traversal(root->left, depth);
            depth--;
        }
        if(root->right){
            depth++;
            traversal(root->right,depth);
            depth--;
        }
        return ;
    }
    int findBottomLeftValue(TreeNode* root){
        traversal(root,0);
        return result;
    }  
};


class Solution {
private:   
    bool traversal(TreeNode* cur, int count)
    {
        if(!cur->left && !cur->right && count == 0) return true;
        if(!cur->left && !cur->right) return false;
        if(cur->left){
            count -= cur->left->val;
            if(traversal(cur->left, count)) return true;
            count += cur->left->val;
        }
        if(cur->right){
            count -= cur->right->val;
            if(traversal(cur->right,count)) return true;
            count += cur->right->val;
        }
        return false;
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return 0;
        return traversal(root,targetSum - root->val);
    }
};
#endif

class Solution{
public:
    bool hasPathSum(TreeNode* root, int sum){
        if(root == nullptr) return false;
        stack<pair<TreeNode*,int>> st;
        st.push(pair<TreeNode*, int>(root, root->val));
        while(!st.empty()){
            pair<TreeNode*,int> node = st.top();
            st.pop();
            if(!node.first->left && !node.first->right && sum == node.second) return true;
            if(node.first->right){
                st.push(pair<TreeNode*, int>(node.first->right,node.second + node.first->right->val));
            }
            if(node.first->left){
                st.push(pair<TreeNode*,int>(node.first->left, node.second + node.first->left->val));
            }
        }   
        return false;     
    } 
};

