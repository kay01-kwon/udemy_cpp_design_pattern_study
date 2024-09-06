#include <iostream>
#include <vector>
#include <string>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;

template <typename T>
struct Node
{
    Node(T data): data_(data) {}

    Node(T data, Node<T> *left, Node<T> *right)
    : data_(data), left_(left), right_(right)
    {
        left_->parent_ = right_->parent_ = this;
    }

    // ~Node()
    // {
    //     if(left_)
    //         delete left_;
    //     if(right_)
    //         delete right_;
    // }

    void preorder_traversal(vector<Node<T>*> &result)
    {
        // preorder_traversal_impl(this, result);
        result.push_back(this);
        if(left_)
            left_->preorder_traversal(result);
        if(right_)
            right_->preorder_traversal(result);
    }

    // void preorder_traversal_impl(Node<T> *current, 
    // vector<Node<T>*>& result)
    // {
    //     result.push_back(current);
    //     if(current->left_)
    //         preorder_traversal_impl(current->left_, result);
    //     if(current->right_)
    //         preorder_traversal_impl(current->right_, result);
    // }

    T data_;
    Node<T> *left_{nullptr};
    Node<T> *right_{nullptr};
    Node<T> *parent_{nullptr};

};

int main()
{
    Node<char> c{'c'};
    Node<char> d{'d'};
    Node<char> e{'e'};
    Node<char> b{'b', &c, &d};
    Node<char> a{'a', &b, &e};

    vector<Node<char>*> result;
    a.preorder_traversal(result);

    for(auto node: result)
    {
        cout << node->data_ << endl;
    }


    return 0;
}