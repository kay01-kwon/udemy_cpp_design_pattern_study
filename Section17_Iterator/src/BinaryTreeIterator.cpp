#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;

//    A
//  /  \
// B   C

template <typename T>
struct BinaryTree;

template <typename T>
struct Node
{
    explicit Node(T data): data_(data) {}

    Node(T data, Node<T> *left, Node<T> *right)
    : data_(data), left_(left), right_(right) 
    {
        left_->tree_ = right_->tree_ = tree_;
        left_->parent_ = right_->parent_ = this;
    }

    void setTree(BinaryTree<T> *tree)
    {
        tree_ = tree;
        if(left_)
            left_->setTree(tree);
        if(right_)
            right_->setTree(tree);
    }

    ~Node()
    {
        if(left_)
            delete left_;
        if(right_)
            delete right_;
    }

    T data_ = T();
    Node<T> *left_ = nullptr;
    Node<T> *right_ = nullptr;
    Node<T> *parent_ = nullptr;
    BinaryTree<T> *tree_ = nullptr;
};

template <typename T>
struct BinaryTree
{
    Node<T> *root_ = nullptr;

    BinaryTree(Node<T> *root)
    : root_(root), pre_order(*this)
    {
        root_->setTree(this);
    }

    ~BinaryTree()
    {
        if(root_)
            delete root_;
    }

    template <typename U>
    struct PreOrderIterator
    {
        Node<U> *current_;

        PreOrderIterator(Node<U> *current)
        : current_(current) {}

        bool operator!=(const PreOrderIterator<U> &other)
        {
            return current_ != other.current_;
        }

        PreOrderIterator<U> &operator++()
        {
            if(current_->right_)
            {
                current_ = current_->right_;
                while(current_->left_)
                    current_ = current_->left_;
            }
            else
            {
                Node<T> *p = current_->parent_;
                while(p && current_ == p->right_)
                {
                    current_ = p;
                    p = p->parent_;
                }
                current_ = p;
            }
            return *this;
        }

        Node<U> &operator*() { return *current_;}

        Node<U> *operator->() { return current_;}
    };  // PreOrderIterator

    typedef PreOrderIterator<T> iterator;

    iterator begin()
    {
        Node<T> *n = root_;
        if(n)
            while(n->left_)
                n = n->left_;
        return iterator{n};
    }

    iterator end()
    {
        return iterator{nullptr};
    }

    class PreOrderTraversal
    {
        public:
            PreOrderTraversal(BinaryTree<T> &tree)
            : tree_(tree) {}

            iterator begin() { return tree_.begin();}
            iterator end() { return tree_.end();}
        
        private:
            BinaryTree<T> &tree_;
    } pre_order;
};

int main()
{
    //      me
    //     /  \
    //  mother father
    //    /  \
    //  m'm   m'f

    BinaryTree<string> family{
        new Node<string>("me",
            new Node<string>("mother",
                new Node<string>("mother's mother"),
                new Node<string>("mother's father")),
            new Node<string>("father"))
    };

    // for(auto it = family.begin(); it != family.end(); ++it)
    // {
    //     cout << it->data_ << endl;
    // }

    for(const auto& it: family.pre_order)
    {
        cout << it.data_ << endl;
    }

    return 0;
}