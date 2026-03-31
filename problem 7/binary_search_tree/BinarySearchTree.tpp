#include "BinarySearchTree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = nullptr;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& tree_to_copy)
{
    root = nullptr;
    Node<KeyType, ItemType>** this_tree_root = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.node_to_copy = tree_to_copy.root;
    rootvar.this_node_address = this_tree_root;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_node_to_copy = currentvar.node_to_copy;
        Node<KeyType, ItemType>** curr_this_node_address = currentvar.this_node_address;

        if (curr_node_to_copy == nullptr)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_node_to_copy->key;
        temp->data = curr_node_to_copy->data;
        temp->left = nullptr;
        temp->right = nullptr;
        *curr_this_node_address = temp; // assigns value using this node address

        // push left subtree
        stackvar<KeyType, ItemType> left_subtree_root;
        left_subtree_root.node_to_copy = curr_node_to_copy->left;
        left_subtree_root.this_node_address = &((*curr_this_node_address)->left); 
        s.push(left_subtree_root);

        // push right subtree
        stackvar<KeyType, ItemType> right_subtree_root;
        right_subtree_root.node_to_copy = curr_node_to_copy->right;
        right_subtree_root.this_node_address = &((*curr_this_node_address)->right);
        s.push(right_subtree_root);
    }
}


template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> tree_to_copy)
{
    swap(tree_to_copy);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType>& tree_to_swap)
{
    std::swap(root, tree_to_swap.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}


template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != nullptr) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = nullptr;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    // TODO 
    //Current node pointer
    Node<KeyType, ItemType>* curr = nullptr;

    //current node parent
    Node<KeyType, ItemType>* curr_parent = nullptr;

    //search for key
    bool found = search(key, curr, curr_parent);
    //duplicate key
    if (found) return false;

    //new node pointer
    Node<KeyType, ItemType>* new_node = new Node<KeyType, ItemType>;
    new_node->key = key;
    new_node->data = item;
    new_node->left = nullptr;
    new_node->right = nullptr;

    //check if empty tree
    if (root == nullptr) {
        root = new_node;
    }
    //insert as left child attach at curr
    else if (key< curr->key){
        curr->left = new_node;
    }
    //insert as right child attach at curr
    else {
        curr->right = new_node;
    }

    //return succesful
    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == nullptr);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    bool found = search(key, curr, curr_parent);

    if (found) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree

    // TODO
    //current node pointer
    Node<KeyType, ItemType>* curr = nullptr;
    //current node parent pointer
    Node<KeyType, ItemType>* parent = nullptr;

    //search for key
    bool found = search(key, curr, parent);

    //return false if not found
    if (!found) return false;
    // case one thing in the tree
    if (curr == root && curr->left == nullptr && curr->right == nullptr) {
        delete root;
        root = nullptr;
        return true;
    }

    // case, found deleted item at leaf
    if (curr->left == nullptr && curr->right == nullptr) {
        if (parent->left == curr)
            parent->left = nullptr;
        else
            parent->right = nullptr;

        delete curr;
        return true;
    }
    // case, item to delete has only a right child
    if (curr->left == nullptr && curr->right != nullptr) {
        if (curr == root)
            root = curr->right;
        else if (parent->left == curr)
            parent->left = curr->right;
        else 
            parent->right = curr->right;

        delete curr;
        return true;
    }

    // case, item to delete has only a left child
    if (curr->left != nullptr && curr->right == nullptr) {
        if (curr == root)
            root = curr->left;
        else if (parent->left == curr)
            parent->left = curr->left;
        else 
            parent->right = curr->left;

        delete curr;
        return true;
    }

    // case, item to delete has two children
    //two new node poiinters for succ and succ_parrent
    Node<KeyType, ItemType>* succ = nullptr;
    Node<KeyType, ItemType>* succ_parent = nullptr;

    inorder_successor(curr, succ, succ_parent);

    curr->key = succ->key;
    curr->data = succ->data;

    if (succ_parent->left == succ)
        succ_parent->left = succ->right;
    else 
        succ_parent->right = succ->right;

    delete succ;
    return true;
}


template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int arr_size) {
    // BONUS TODO: check for duplicate items in the input array

    // BONUS TODO: use the tree to sort the array items

    // BONUS TODO: overwrite input array values with sorted values
}


template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder_successor(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& inorder, Node<KeyType, ItemType>*& inorder_parent)
{
    inorder_parent = curr;
    inorder = curr->right;
    while (inorder != nullptr && inorder->left != nullptr) {
        inorder_parent = inorder;
        inorder = inorder->left;
    }
    
    // inorder points to the inorder successor at the end of this loop

}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& curr_parent)
{
    curr = root;
    curr_parent = nullptr;

    if (isEmpty())
        return false;
    
    while (true) {
        if (key == curr->key) {
            // found
            return true;
        } 
        if (key < curr->key) {
            // search left
            if (curr->left != nullptr) {
                curr_parent = curr;
                curr = curr->left;
            } else {
                // nowhere further to search
                return false;
            }
        } else {
            // search right
            if (curr->right != nullptr) {
                curr_parent = curr;
                curr = curr->right;
            } else {
                // nowhere further to search
                return false;
            }
        }
    }
}

