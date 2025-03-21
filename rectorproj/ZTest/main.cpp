#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <ulimit.h>
#include <map>
#include <thread>
#include <atomic>
#include <memory>
#include <unordered_map>
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
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
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

//层序遍历
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

//中序遍历
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


class Solution {
public:
    TreeNode* traversal(vector<int>& inorder, vector<int>& postorder){
        if(inorder.size() == 0) return nullptr;
        int rootValue = postorder[postorder.size()-1];
        TreeNode* root = new TreeNode(rootValue);
        int pointPos = 0;
        for(pointPos = 0; pointPos < inorder.size(); pointPos++){
            if(inorder[pointPos] ==  rootValue) break;
        }

        vector<int> leftInorder(inorder.begin(), inorder.begin()+pointPos);
        vector<int> rightInorder(inorder.begin()+pointPos+1, inorder.end());

        //舍弃后序末尾元素
        postorder.resize(postorder.size()-1);

        vector<int>leftPostorder(postorder.begin(), postorder.begin()+leftInorder.size());
        vector<int>rightPostorder(postorder.begin()+leftInorder.size(), postorder.end());

        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder,rightPostorder); 

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0 ||postorder.size() == 0) return nullptr;
        return traversal(inorder, postorder);        
    }
};


class Solution1 {
public:
    int lengthOfLastWord(string s) {
        int result = 0;
        int len = s.size()-1;
        while( len >= 0 && s[len] == ' ' ){
            len--;
        }
        while (len >= 0 && s[len] != ' ' ){
            result++;
            len--;
        }
        return result;
    }
};



class Solution {
public:
    TreeNode* traversal(vector<int>& preorder,vector<int>& inorder){
        if(inorder.size() == 0) return nullptr;
        int rootValue = preorder.front();
        TreeNode* root = new TreeNode(rootValue);
        int pos = 0;
        for(; pos < inorder.size(); pos++){
            if(inorder[pos] == rootValue) break;
        }
        vector<int> leftInorder(inorder.begin(), inorder.begin()+pos);
        vector<int> rightInorder(inorder.begin()+pos+1,inorder.end());

        preorder.erase(preorder.begin());

        vector<int> leftPreorder(preorder.begin(), preorder.begin()+leftInorder.size());
        vector<int> rightPreorder(preorder.begin()+leftInorder.size(), preorder.end());

        root->left = traversal(leftPreorder, leftInorder);
        root->right = traversal(rightPreorder, rightInorder);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0) return nullptr;
        return traversal(preorder, inorder);
    }
};

//最大二叉树
// class Solution {
// public:
//     TreeNode* traversasl(vector<int>& nums){
//         if(nums.size() == 0) return nullptr;
//         int rootValue = nums[0];
//         vector<pair<int,int>> st;
//         for(int pos = 1; pos < nums.size(); pos++){
//             if(rootValue < nums[pos]){
//                 st.push_back(pair<int,int>(pos, nums[pos]));
//                 rootValue = st.back().second; 
//             }
//         }
//         int pos = st.back().first; //找到数组中的最大值下标
//         TreeNode* root = new TreeNode(rootValue); 
//         vector<int> leftNums(nums.begin(), nums.begin() + pos);
//         vector<int> rightNums(nums.begin()+pos+1, nums.end());

//         root->left = traversasl(leftNums);
//         root->right = traversasl(rightNums);

//         return root;
//     }
//     TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
//         if(nums.size() == 0) return nullptr;
//         return traversasl(nums);
//     }
// };

//485 最大连续1的个数
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int count = 0;
        int max = 0;
        for(int i = 0; i < nums.size(); i++){ 
            if(nums[i] == 1){
                count++;  
                if(i == nums.size()-1){
                    max = count > max ?  count : max;
                }
                continue;
            }
            max = count > max ?  count : max; 
            count = 0;
        }
        return max;
    }
};

//88. 合并2个有序数组
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i = m; i < m+n; i++){
            nums1[i] = nums2[i-m];
        }
        sort(nums1.begin(), nums1.end());
    }
};


//27. 移除元素
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int pos;
        vector<int> result;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != val){
                result.push_back(nums[i]);
            }
        }
        nums = result;
        return result.size();
    }
};

//645最大二叉树
class Solution {
    public:
        TreeNode* constructNode(vector<int>& nums,int left,int right){
            if(left > right) return nullptr;
            int max_val = INT16_MIN;
            int index;
            for(int i = left; i <= right; i++){
                if(nums[i] > max_val){
                    max_val  = nums[i];
                    index = i;
                }
            }
            TreeNode* root = new TreeNode(max_val);
            root->left = constructNode(nums, left, index-1);
            root->right = constructNode(nums, index+1, right);
            return root;
        }
        TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
            return constructNode(nums, 0, nums.size()-1);
        }
};


//645最大二叉树
class Solution {
    public:
        TreeNode* traversasl(vector<int>& nums){
            int rootValue = INT16_MIN;
            int pos = 0;
            for(int i = 0; i < nums.size(); i++){
                if(nums[i] > rootValue){
                    rootValue = nums[i];
                    pos = i; 
                }
            }    
            TreeNode* root = new TreeNode(rootValue);
            if(pos > 0){
                vector<int> leftNums(nums.begin(), nums.begin() + pos);
                root->left = traversasl(leftNums);
            }
            if(pos < (nums.size() - 1)){
                vector<int> rightNums(nums.begin()+pos+1, nums.end());
                root->right = traversasl(rightNums);
            }
            return root;
        }
        TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
            if(nums.size() == 0) return nullptr;
            return traversasl(nums);
        }
};

//617.合并二叉树
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2) return root1;
        if(root1 == nullptr) return root2;
        if(root2 == nullptr) return root1;
        TreeNode* root = new TreeNode(root1->val);
        root->val = root1->val + root2->val;
        root->left = mergeTrees(root1->left,root2->left);
        root->right = mergeTrees(root1->right,root2->right);
        return root;
    }
};

class Solution{
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2){
        if(!root1 && !root2) return root1;
        if(root1 == nullptr) return root2;
        if(root2 == nullptr) return root1;
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left,root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};

//617 合并二叉树-中序遍历
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr) return root2;
        if(root2 == nullptr) return root1;
        root1->left = mergeTrees(root1->left,root2->left);
        root1->val += root2->val;
        root1->right = mergeTrees(root1->right,root2->right);
        return root1;
    }
};

//700. 二叉搜索树中的搜索-层序遍历
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
         if(root == nullptr) return nullptr;
         queue<TreeNode*> que;
         que.push(root);
         while (!que.empty()){
            int size = que.size();
            for(int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                if(node->val ==  val) return node;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
         }
         return nullptr;
    }
}; 
//700.二叉搜索树中的搜索-递归
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr || root->val == val) return root;
        TreeNode* rootLeft = searchBST(root->left,val);
        TreeNode* rootRight = searchBST(root->right,val);
        return rootRight ? rootRight : rootLeft;
    }
};
//700.二叉搜索树中的搜索-递归
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr || root->val == val) return root;
        TreeNode* node = nullptr;
        if(root->val < val) node = searchBST(root->right, val);
        if(root->val > val) node = searchBST(root->left, val);
        return node;
    }
};
    
//98.验证二叉搜索树
class Solution {
public:
    bool isValidBST(TreeNode* root, long minVal = __LONG_MAX__, long maxVal = __LONG_MAX__) {
        if(root == nullptr) return true;
        if(root->val <= minVal || root->val >= maxVal);
            return false;
        bool rootLeft = isValidBST(root->left, minVal, root->val);
        bool rootRight = isValidBST(root->right,root->val, maxVal);
        return rootLeft && rootRight;
    }
};

//98.验证二叉搜索树
class Solution {
public:
    void inorderTraversal(TreeNode* root, vector<int>& vec){
        if(root == nullptr) return ;
        inorderTraversal(root->left, vec);
        vec.push_back(root->val);
        inorderTraversal(root->right,vec);
    }
    bool isValidBST(TreeNode* root) {
        vector<int> result;
        inorderTraversal(root, result);
        for(int i = 1; i+1 < result.size(); i++){
            cout << result[i-1] << " ";
            if(result[i] <= result[i-1])
                return false;
        }
        return true;
    }
};

//530. 二叉搜索树的最小绝对差
class Solution {
public:
    vector<int> vec;
    void inorderTraversal(TreeNode* root){
        if(root == nullptr) return ;
        inorderTraversal(root->left);
        vec.push_back(root->val);
        inorderTraversal(root->right);
    }
    int getMinimumDifference(TreeNode* root) {
        if(root == nullptr) return 0;
        inorderTraversal(root);
        int result = INT16_MAX;
        for(int i = 1; i < vec.size(); i++){
            result = min(result, vec[i] - vec[i-1]);            
        }
        return result;
    }    
};

//501.二叉搜索树中的众数
class Solution {
public:
    void traversal(TreeNode* root, unordered_map<int,int>& map){
        if(root == nullptr) return ;
        map[root->val]++;
        traversal(root->left, map);
        traversal(root->right,map);
        return ;
    }
    bool static compare(const pair<int,int>& a,const pair<int,int>& b){
        return a.second > b.second;
    }
    vector<int> findMode(TreeNode* root) {
        unordered_map<int,int> map;
        vector<int> result;
        if(root == nullptr) return result;
        traversal(root, map);
        vector<pair<int,int>>vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), compare);    
        result.push_back(vec[0].first);
        for(int i = 1; i < vec.size(); i++){
            if(vec[i].second == vec[0].second){
                result.push_back(vec[i].first);
            }else{
                break;
            }
        }
        return result;
    }
};

//501.二叉搜索树中的众数
class Solution {
public:
    void countFrequency(TreeNode* root, unordered_map<int,int>& freq_map){
        if(root == nullptr) return ;
        freq_map[root->val]++;
        countFrequency(root->left,freq_map);
        countFrequency(root->right, freq_map);
    }
    vector<int> findMode(TreeNode* root) {
        if(root == nullptr) return {};
        unordered_map<int,int>freq_map;
        countFrequency(root,freq_map);
        vector<pair<int,int>> vec(freq_map.begin(),freq_map.end());
        int max_freq = 0;
        vector<int> result;
        for(const auto& it : freq_map){
            if(it.second > max_freq){
                max_freq = it.second;
                result.clear();
                result.push_back(it.first);
            }else if(it.second == max_freq){
                result.push_back(it.first);
            }
        }
        return result;
    }
};

class Person{
public:
    int value;
    Person(){}
    Person(string name, string id, int age,int height){
        this->name_ = name;
        this->id_ = id;
        this->age_ = age;
        this->height_ = height;
    }
    virtual void infoShow(){
        std::cout << "姓名\t："<< name_
                  << "ID\t:" << id_ 
                  << "年龄\t："<< age_
                  << "身高\t："<< height_
                  << std::endl;
    }
protected:
    string name_;
    string id_;
    int age_;
    int height_;
};

class Student : public Person{
public:
    Student(){};
    Student(string name, string id, int age,int height)
    : Person(name,id,age,height){} //调用父类的构造函数
    void infoShow() override{
        std::cout << "姓名\t："<< name_ << endl
                  << "ID \t：" << id_ << endl
                  << "年龄\t："<< age_<< endl
                  << "身高\t："<< height_<<endl
                  << std::endl;        
    }

    int getAge(){
        return age_;
    }
};

class Teacher : public Person{
public:
    Teacher(){}
    Teacher(string name, string id, string course,int age)
    : Person(name,id,age,0){
        this->course_ = course;
    }
    void infoShow() override{
        std::cout << "姓名\t："<< name_ << endl
                  << "ID \t：" << id_ << endl
                  << "课程\t："<< course_<< endl
                  << "年龄\t："<< age_<<endl
                  << std::endl;        
    }
    int getAge(){
        return age_;
    }
private:
    string course_;
};


int main()
{

    Student stu("小刘","123",18, 170);
    Teacher tea("张老师","001","语文",30);
    Person* stu1 = new Student("小刘","123",18, 170);
    Person* tea1 = new Teacher("张老师","001","语文",30);
    stu.infoShow();
    tea.infoShow();

    stu1->infoShow();
    tea1->infoShow();
    delete stu1;
    delete tea1;
    return 0;
}


class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int RMaxnum = 0;
        int LMaxnum = 0;
        int n = nums.size();
        RMaxnum = nums[n-1]*nums[n-2]*nums[n-3];
        LMaxnum = nums[0]*nums[1]*nums[n-1];

        return RMaxnum > LMaxnum ? RMaxnum : LMaxnum;
    }
};
#endif

class Solution{
public: 
    TreeNode* searchBST(TreeNode* root, int val){
        if(root == nullptr) return root;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()){
            int size = que.size();
            TreeNode* node = que.front();
            que.pop();
            if(node->val == val) return node;
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }
        return nullptr;
    }
};

TreeNode* createBST(){
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    return root;
}

// 释放二叉树内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}




