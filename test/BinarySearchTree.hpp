#include <iostream>
#include <fstream>
#include "BinarySearchTreeException.h"

using namespace std;

#ifndef BINARYSEARCHTREETEST_BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREETEST_BINARYSEARCHTREE_HPP

template<typename T>
struct BinaryTree {
    T data;
    BinaryTree *Right = NULL;
    BinaryTree *Left = NULL;
};

template<class T>
class BinarySearchTree {
public:
    BinarySearchTree();

    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree<T> &tmp);
    
    int get_size() const;

    bool Delete(BinaryTree<T> *&tmp, T value);

    BinaryTree<T> *Find(BinaryTree<T> *&tmp, T value);

    void Delete_tmp(BinaryTree<T> *&tmp);

    void ReadFromFile(string text);

    void WriteInFile(ostream &os);

    void Insert(BinaryTree<T> *&tmp, T value);

    void Print(BinaryTree<T> *tmp) const;

    void Copy(BinaryTree<T> *tmp);

    void PrintInFile(ostream &os, BinaryTree<T> *&tmp);

    template<class U>
    friend ostream &operator<<(ostream &os, const BinarySearchTree<U> &tmp);

    template<class U>
    friend fstream &operator<<(std::fstream &file, BinarySearchTree<U> &tmp);

    template<class U>
    friend fstream &operator>>(std::fstream &file, BinarySearchTree<U> &tmp);

private:


    BinaryTree<T> *head;
    int size;
};


template<class T>
BinarySearchTree<T>::BinarySearchTree()
        : head(NULL),
          size(0) { }

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &tmp) {
    size = tmp.size;
    Copy(tmp.head);
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    if (head != NULL) {
        for (int i = 0; i < size - 1; ++i) {
            Delete_tmp(head);
        }
        delete head;
    }
}

template<class T>
int BinarySearchTree<T>::get_size() const{
    return size;
}

template<class T>
BinaryTree<T> *BinarySearchTree<T>::Find(BinaryTree<T> *&tmp, T value) {
    if (tmp == NULL) {
        return NULL;
    }
    if (tmp->data == value) {
        return tmp;
    }
    if (tmp->data > value) {
        return Find(tmp->Left, value);
    } else {
        return Find(tmp->Right, value);
    }
}

template<class T>
void BinarySearchTree<T>::Insert(BinaryTree<T> *&tmp, T value) {
    if (tmp == NULL) {
        tmp = new BinaryTree<T>;
        tmp->data = value;
        size++;
        return;
    }
    if (tmp->data > value) {
        Insert(tmp->Left, value);
    }
    else {
        Insert(tmp->Right, value);
    }
}

template<class T>
bool BinarySearchTree<T>::Delete(BinaryTree<T> *&tmp, T value) {
    if (tmp == NULL) {
        return false;
    }
    if (tmp->data == value) {
        Delete_tmp(tmp);
        return true;
    }
    return Delete(tmp->data > value ? tmp->Left : tmp->Right, value);
}

template<class T>
void BinarySearchTree<T>::Delete_tmp(BinaryTree<T> *&tmp) {
    if (tmp->Left == NULL) {
        BinaryTree<T> *right = tmp->Right;
        delete tmp;
        tmp = right;
    } else if (tmp->Right == NULL) {
        BinaryTree<T> *left = tmp->Left;
        delete tmp;
        tmp = left;
    } else {
        BinaryTree<T> *minParent = tmp;
        BinaryTree<T> *min = tmp->Right;
        while (min->Left != NULL) {
            minParent = min;
            min = min->Left;
        }
        (minParent->Left == min ? minParent->Left : minParent->Right) = min->Right;
        tmp->data = min->data;
        delete min;
    }
}

template<class T>
void BinarySearchTree<T>::Print(BinaryTree<T> *tmp) const {
    try {
        if (tmp == NULL) {
            BinarySearchTreeExceptionIsEmpty tmp;
            throw tmp;
        }
        if (tmp->Left == NULL && tmp->Right == NULL) {
            cout << tmp->data;
            return;
        }
        if (tmp->Left != NULL) {
            Print(tmp->Left);

        }

        cout << tmp->data;

        if (tmp->Right != NULL) {
            Print(tmp->Right);
        }
    } catch (BinarySearchTreeExceptionIsEmpty tmp) {
        tmp.info();
    }

}

template<class T>
void BinarySearchTree<T>::Copy(BinaryTree<T> *tmp) {
    if (tmp == NULL) {
        return;
    }
    Copy(tmp->Left);
    Copy(tmp->Right);
    Insert(head, tmp->data);
}

template<class T>
void BinarySearchTree<T>::ReadFromFile(string text) {
    ifstream file(text);
    int value;
    int size;
    file >> size;
    for (int i = 0; i < size; ++i) {
        file >> value;
        Insert(head, value);
    }
    file.close();
}

template<class T>
void BinarySearchTree<T>::WriteInFile(ostream &os) {
    PrintInFile(os, head);
}

template<class T>
void BinarySearchTree<T>::PrintInFile(ostream &os, BinaryTree<T> *&tmp) {
    if (tmp->Left == NULL && tmp->Right == NULL) {
        os << tmp->data;
        return;
    }
    if (tmp->Left != NULL) {
        PrintInFile(os, tmp->Left);

    }

    os << tmp->data;

    if (tmp->Right != NULL) {
        PrintInFile(os, tmp->Right);
    }
}

template<class U>
ostream &operator<<(ostream &os, const BinarySearchTree<U> &tmp) {
    tmp.Print(tmp.head);
    return os;
}

template<class U>
fstream &operator<<(std::fstream &file, BinarySearchTree<U> &tmp) {
    file << tmp.size << endl;
    tmp.WriteInFile(file);
    return file;
}

template<class U>
fstream &operator>>(std::fstream &file, BinarySearchTree<U> &tmp) {
    int value;
    int size;
    file >> size;
    for (int i = 0; i < size; ++i) {
        file >> value;
        tmp.Insert(tmp.head, value);
    }
    return file;
}

#endif //BINARYSEARCHTREETEST_BINARYSEARCHTREE_HPP
