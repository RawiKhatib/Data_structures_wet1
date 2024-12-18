#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>


template <class T> class Node {
public:
    T value;
    Node *parent;
    Node *right;
    Node *left;
    int height;
    
public:
    Node(const T &value)
	: value(value), parent(nullptr), right(nullptr), left(nullptr),
	  height(0) {}
    
    ~Node() = default;
    
    T &getValue() { return this->value; }
    void setValue(const T &val) {
	if (this == nullptr) {
	    return;
	}
	this->value = val;
    }
    void setLeft(Node *left) {
	if (this == nullptr) {
	  return;
	}
	this->left = left;
    }

    Node *getLeft() const {
	if (this == nullptr) {
	    return nullptr;
	}
	return this->left;
    }

    void setRight(Node *right) {
	if (this == nullptr) {
	  return;
	}
	this->right = right;
    }

    Node *getRight() const {
	if (this == nullptr) {
	    return nullptr;
	}
	return this->right;
    }

    void setParent(Node *parent) {
	if (this == nullptr)
	  return;
	this->parent = parent;
    }

  Node *getParent() const {
    if (this == nullptr) {
      return nullptr;
    }
    return this->parent;
  }
  void setHeight(const int height) {
      if (this == nullptr) {
	  return;
      }
      this->height = height;
      return;
  }
  int getHeight() const {
    if (this == nullptr)
      return -1;
    return this->height;
  }
};
template<class T>
int getHeight(Node<T>* t) {
    if(t == nullptr)
	return -1;
    return t->height;
}
template<class T>
void setParent(Node<T>* t,Node<T>* parent) {
    if(t == nullptr)
	return;
    t->parent = parent;
}

template<class T,class K>//herdId and horseId
K defaultKeyFn(const T& value) {
	return value;
}

template <class T,class K>
class AVLTree {
public:
    Node<T> *root;
    // returns a key to compare values by
    // K must implement < and ==
    K (*keyfn)(const T&);
    int size;
    void insertNode(Node<T> *root, Node<T> *added_Node);
    Node<T> *vertexWithMinVal(Node<T> *vertex) const;
    Node<T> *vertexWithMinVal() const;
    Node<T> *vertexWithMaxVal() const;
    Node<T> *deleteNode(Node<T> *root, const K &key);
    void deleteAllNodes(Node<T> *node);
    int getBalanceFactor(const Node<T> *root) const;
    Node<T> *rotateLeft(Node<T> *root);
    Node<T> *rotateRight(Node<T> *root);

    static int getMax(int a, int b);


public:

    AVLTree(): root(nullptr),size(0)
    {}
    AVLTree(K (*keyf)(const T&)) : root(nullptr),keyfn(keyf),size(0)
    {}
    ~AVLTree();
    // NOTE(Salim): does not modify the root
    AVLTree(const AVLTree &) = default;
    AVLTree &operator=(const AVLTree &) = default;

    bool insert(const T &value);
    Node<T> *getRoot() const;
    Node<T> *find(Node<T> *root, const K &key);
    Node<T> *find(const K &key);
    
    bool deleteValue(const K &key);

    int getSize() const;
#ifndef NDEBUG
    void print() const {
        if (!root) {
            std::cout << "Tree is empty.\n";
            return;
        }
        printTree(root, 0);
    }
    void printTree(Node<T> *node, int space) const {
        if (!node)
            return;

        const int COUNT = 5;
        space += COUNT;

        printTree(node->right, space);

        std::cout << std::endl;
        for (int i = COUNT; i < space; ++i)
	    {
		std::cout << " ";
	    }
        std::cout << node->value << "\n";

        printTree(node->left, space);
    }
#endif // NDEBUG
    
};
template<class T,class K>
void printTree2(const AVLTree<T,K> &tree) {
    tree.print();
}
template <class T,class K>
int AVLTree<T,K>::getSize() const {
  if (this == nullptr || root == nullptr)
    return 0;
  return size;
}

template <class T,class S>
int AVLTree<T,S>::getMax(int a, int b) {
  return (a >= b) ? a : b;
}

template <class T,class S>
Node<T> *AVLTree<T,S>::vertexWithMinVal(Node<T> *vertex) const {
  Node<T> *current = vertex;
  while (current->left != nullptr)
    current = current->left;
  return current;
}
template<class T,class S>
Node<T> *AVLTree<T,S>::vertexWithMinVal() const {
    return vertexWithMinVal(root);
}
template <class T,class S>
Node<T> *AVLTree<T,S>::vertexWithMaxVal() const {
    if(root == nullptr)
	return nullptr;

    Node<T> *current = root;
    while(current->right != nullptr)
	current = current->right;
    return current;
}

template <class T,class S>
Node<T> *AVLTree<T,S>::deleteNode(Node<T> *root, const S& key) {

  if (root == nullptr)
    return root;
  if(key < keyfn(root->value)) {
    root->left = deleteNode(root->left, key);
    setParent(root->left,root);
  } else if (keyfn(root->value) < key) {
      root->right = deleteNode(root->right, key);
      setParent(root->right,root);
  }
  // this is the vertex to be deleted
  else {
      // case 1: v has 0 or 1 child
      if ((root->left == nullptr) || (root->right == nullptr)) {
	  Node<T> *tmp = root->left != nullptr ? root->left : root->right;
	  // no kids
	  if (tmp == nullptr) {
	      tmp = root;
	      root = nullptr;
	      delete tmp;
	  } else {
	      // 1 child
	      // tmp->setParent(root->getParent());
	      tmp->parent = root->parent;
	      if (root == this->root) {
		  this->root = tmp;
	      }
	      delete root;
	      root = tmp;
	  }
      } else {
	  // 2 or more children
	  Node<T> *tmp = vertexWithMinVal(root->right);
	  T root_val = root->getValue();
	  root->setValue(tmp->getValue());
	  tmp->setValue(root_val);
	  root->setRight(deleteNode(root->right, keyfn(root_val)));
      }
  }
  if (root == nullptr)
    return root;
  root->setHeight(getMax(getHeight(root->left), getHeight(root->right)) + 1);
  // AVL balancing algorithm
  int balance = getBalanceFactor(root);
  if (balance > 1) { // left tree unbalanced
    if (getBalanceFactor(root->left) < 0) // right child of left tree is the cause
      root->setLeft(rotateLeft(root->left)); // double rotation required
    return rotateRight(root);
  } else if (balance < -1) { // right tree unbalanced
    if (getBalanceFactor(root->right) > 0) // left child of right tree is the cause
	root->setRight(rotateRight(root->right));
    return rotateLeft(root);
  }
  return root;
}

template <class T,class S>
bool AVLTree<T,S>::deleteValue(const S &key) {
  if (find(root, key) == nullptr)
      return false;

  this->root = deleteNode(root, key);

  size--;
  return true;
}

template <class T,class S>
AVLTree<T,S>::~AVLTree() {
  if (root != nullptr) {
    deleteAllNodes(root);
  }
  root = nullptr;
}

template <class T,class S>
void AVLTree<T,S>::deleteAllNodes(Node<T> *node) {
  if (node) {
    deleteAllNodes(node->left);
    deleteAllNodes(node->right);
    delete node;
  }
}

template <class T,class S>
bool AVLTree<T,S>::insert(const T &value) {
  if (this->find(root, keyfn(value)) != nullptr) {
	return false;
    }
    Node<T> *new_node = new Node<T>(value);
    new_node->setHeight(0);
    if (!new_node) {
	delete new_node;
	return false;
    }
    if (this->root == nullptr) {
	root = new_node;
    } else {
	insertNode(root, new_node);
     }
    size++;
    return true;
}

template <class T,class S>
void AVLTree<T,S>::insertNode(Node<T> *root, Node<T> *added_Node) {
    if (keyfn(added_Node->value) < keyfn(root->value)) {
	if (root->left)
	    insertNode(root->left, added_Node);
	else {
	    root->setLeft(added_Node);
	    added_Node->setParent(root);
	}
    } else {
	if (root->right != nullptr)
	    insertNode(root->right, added_Node);
	else {
	    root->setRight(added_Node);
	    added_Node->setParent(root);
	}
    }
    int updated_height = getMax(root->left->getHeight(), root->right->getHeight()) + 1;
    root->setHeight(updated_height);
  // NOTE(Salim): start balancing
  int balance = getBalanceFactor(root);
  if (balance > 1) { // left tree unbalanced
      // right child of left tree is the cause
      if (getBalanceFactor(root->left) < 0)
	  rotateLeft(root->left); // double rotation required
      rotateRight(root);
  } else if (balance < -1) {
      // right tree unbalanced
      // left child of right tree is the cause
      if (getBalanceFactor(root->right) > 0)
	  rotateRight(root->right);
      rotateLeft(root);
  }
}

template <class T,class S>
Node<T> *AVLTree<T,S>::find(Node<T> *root, const S &key) {
  if (root != nullptr) {
      if (keyfn(root->value) == key)
	  return root;
      else if (key < keyfn(root->value))
	  return find(root->left, key);
      else
	  return find(root->right, key);
  }
  return nullptr;
}
template <class T,class S>
Node<T> *AVLTree<T,S>::find(const S &key) {
    return find(root,key);
}
template <class T,class S>
int AVLTree<T,S>::getBalanceFactor(const Node<T> *root) const {
  int balance = 0;
  if (root != nullptr) {
    balance = (root->left)->getHeight() - (root->right)->getHeight();
  }
  return balance;
}

template <class T,class S>
Node<T> *AVLTree<T,S>::rotateLeft(Node<T> *z) {
  Node<T> *y = z->right;
  z->setRight(y->left);
  z->setHeight(getMax((z->left)->getHeight(), (z->right)->getHeight()) + 1);
  y->setLeft(z);
  y->setHeight(getMax(y->left->getHeight(), y->right->getHeight()) + 1);
  setParent(z->right,z);

  // if (z->getParent() == nullptr) {
  if(z->parent == nullptr) {
    y->setParent(nullptr);
    z->setParent(y);
    this->root = y;
    return y;
  // } else if (z->getParent()->left == z) {
  } else if(z->parent->left == z) {
    // z->getParent()->setLeft(y);
      z->parent->left = y;
  } else {
    // z->getParent()->setRight(y);
      z->parent->right = y;
  }
  z->getParent()->setHeight(getMax((z->getParent()->left)->getHeight(),
				   z->getParent()->right->getHeight()) +
			    1);
  y->setParent(z->getParent());
  z->setParent(y);
  return y;
}

template <class T,class S>
Node<T> *AVLTree<T,S>::rotateRight(Node<T> *z) {

  Node<T> *y = z->left;
  z->setLeft(y->right);
  z->setHeight(getMax((z->left)->getHeight(), (z->right)->getHeight()) + 1);
  y->setRight(z);
  y->setHeight(getMax((y->left)->getHeight(), (y->right)->getHeight()) + 1);

  z->left->setParent(z);
  if (z->getParent() == nullptr) {
    y->setParent(nullptr);
    z->setParent(y);
    this->root = y;
    return y;
  } else if (z->getParent()->left == z) {
    z->getParent()->setLeft(y);
  } else {
    z->getParent()->setRight(y);
  }
  z->getParent()->setHeight(getMax((z->getParent()->left)->getHeight(),
				   (z->getParent()->left)->getHeight()) +
			    1);
  y->setParent(z->getParent());
  z->setParent(y);
  return y;
}

template <class T,class S>
Node<T> *AVLTree<T,S>::getRoot() const {
    return root;
}

#endif
