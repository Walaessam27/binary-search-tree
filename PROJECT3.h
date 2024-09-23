#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;

class NODE 
{
public:
    NODE()//constructor
    {
        left = NULL;
        right = NULL;
        height = 1;
        data = -1;
        bf = -1;
    }
    NODE(int d)//constructor
    {
        left = NULL;
        right = NULL;
        height = 1;
        data = d;
        bf = 0;
    }
    int data;
    int bf;
	NODE* left;
	NODE* right;
    int height;
    ~NODE(){}//destructor
};

class MyAVL
{
public:
	NODE* root;
    MyAVL()//constructer
    {
       this->root = NULL;
    }
    friend istream& operator>> (istream& in, NODE& a)
    {
        const int size = 10;
            int tree[size];
            for (int i = 0;i <= size;i++)
            {
                while (!in.eof())
                {
                    in >> a.data;
                    tree[i] = a.data;
                }
            }
    }

	MyAVL(int Mytree[], int size)//constructor
    {   
        cout << "input size of tree" << endl;
        cin >> size;
        Mytree[size];
        printf("\n input elements of tree ");
        for (int i = 0; i < size;i++)
        {
            cin >> Mytree[i];
            this->root = NULL;
        }
        return;
    }

    int getHeight(NODE* p)
    {
        if (p->left && p->right) 
        {
            if (p->left->bf < p->right->bf)
                return p->right->bf + 1;
            else return  p->left->bf + 1;
        }

        else if (p->left && p->right == NULL)
        {
            return p->left->bf + 1;
        }

        else if (p->left == NULL && p->right)
        {
            return p->right->bf + 1;
        }
        return 0;
    }
   
    int bf(NODE* p)
    {
        if (p->left && p->right)
        {
            return p->left->height - p->right->height;
        }

        else if (p->left && p->right == NULL)
        {
            return p->left->height;
        }

        else if (p->left == NULL && p->right) 
        {
            return -p->right->height;
        }
    }
    
    NODE* leftleft(NODE* a) 
    {
        NODE* p;
        NODE* p1;
        p = a;
        p1 = p->left;

        a->left = p1->right;
        p1->right = a;

        return p1;
    }

    NODE* rightright(NODE* a) 
    {
        NODE* p;
        NODE* p1;
        p = a;
        p1 = p->right;

        p->right = p1->left;
        p1->left = p;

        return p1;
    }

    NODE* rightleft(NODE* a) 
    {
        NODE* p;
        NODE* p1;
        NODE* p2;
        p = a;
        p1 = p->right;
        p2 = p->right->left;

        p->right = p2->left;
        p1->left = p2->right;
        p2->left = p;
        p2->right = p1;

        return p2;
    }

    NODE* leftright(NODE* a)
    {
        NODE* p;
        NODE* p1;
        NODE* p2;
        p = a;
        p1 = p->left;
        p2 = p->left->right;

        p->left = p2->right;
        p1->right = p2->left;
        p2->right = p;
        p2->left = p1;

        return p2;
    }

    NODE* insertData(NODE* p, int d)
    {
        if (p == NULL) 
        {
            NODE* n;
            n = new NODE;
            n->data = d;
            p = n;
            p->left = p->right = NULL;
            p->height = 1;
            return p;
        }

        else
        {
            if (d < p->data)
                p->left = insertData(p->left, d);
            else
               p->right = insertData(p->right, d);
        }

        p->height = getHeight(p);

        if (bf(p) == 2 && bf(p->left) == 1)
        {
            p = leftleft(p);
        }

        else if (bf(p) == -2 && bf(p->right) == -1) 
        {
            p = rightright(p);
        }

        else if (bf(p) == -2 && bf(p->right) == 1)
        {
            p = rightleft(p);
        }

        else if (bf(p) == 2 && bf(p->left) == -1) 
        {
            p = leftright(p);
        }
        return p;
    }

    NODE* maxright(NODE* p)
    {
        while (p->right != NULL)
            p = p->right;
        return p;
    }

    NODE* maxleft(NODE* p)
    {
        while (p->left != NULL)
            p = p->left;

        return p;
    }

    NODE* deleteData(NODE* p, int d)
    {
        if (p->left == NULL && p->right == NULL)
            {
                if (p == this->root)
                    this->root = NULL;
                   delete p;
                return NULL;
            }
        NODE* w;
        NODE* t;
          
            if (p->data < d)
            {
                p->right = deleteData(p->right, d);
            }
            else if (p->data > d)
            {
                p->left = deleteData(p->left, d);
            }
            else
            {
                if (p->left != NULL)
                {
                    w = maxright(p->left);
                    p->data = w->data;
                    p->left = deleteData(p->left, w->data);
                }
                else
                {
                    w = maxleft(p->right);
                    p->data = p->data;
                    p->right = deleteData(p->right, w->data);
                }
            }

            if (bf(p) == 2 && bf(p->left) == 1)
            {
                p = leftleft(p);
            }
            else if (bf(p) == 2 && bf(p->left) == -1)
            {
                p = leftright(p);
            }
            else if (bf(p) == 2 && bf(p->left) == 0)
            {
                p = leftleft(p);
            }
            else if (bf(p) == -2 && bf(p->right) == -1)
            {
                p = rightright(p);
            }
            else if (bf(p) == -2 && bf(p->right) == 1)
            {
                p = rightleft(p);
            }
            else if (bf(p) == -2 && bf(p->right) == 0)
            {
                p = leftleft(p);
            }
            return p;
       
    }

    void printInOrder(NODE* p)
    {
        ofstream outputtree("Avltree.txt", ios::out);
        if (root != NULL)
        {
            outputtree << p->data << "," << endl;
            printInOrder(p->left);
            printInOrder(p->right);
        }
    }

    ~MyAVL() {}//destructor
};