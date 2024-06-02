#include <iostream>
#include <queue>
using namespace std;

struct node
{
    int val;

    node* nodes[2];

    node(int v, node* r = NULL, node* l = NULL)
    {
        val = v;
        nodes[0] = r;
        nodes[1] = l;
    }
};

int HEIGTH(node*, int);

struct tree
{
    node* root;

    tree();
    void add(int);
    bool find(int, node**&);
    void del(int);
    void preorder(node*);
    void preorder();
    void inorder(node*);
    void inorder();
    void posorder(node*);
    void posorder();
    void heigth();
    void levels();

};


int main()
{
    tree tree;

    tree.add(50);
    tree.add(30);
    tree.add(70);
    tree.add(90);
    tree.add(20);
    tree.add(10);

    tree.heigth();

    cout << "\nINORDER: ";
    tree.inorder();
    cout << "\nPOSORDER: ";
    tree.posorder();
    cout << "\nPREORDER: ";
    tree.preorder();
    cout << "\nLEVELS: ";
    tree.levels();

    tree.del(10);
    cout << "\nINORDER: ";
    tree.inorder();

    tree.del(70);
    cout << "\nINORDER: ";
    tree.inorder();

    tree.del(50);
    cout << "\nINORDER: ";
    tree.inorder();

    tree.del(20);
    cout << "\nINORDER: ";
    tree.inorder();
}

tree::tree() 
{
    root = NULL;
}

bool tree::find(int v, node** &location)
{
    while ((*location))
    {
        if ((*location)->val > v) 
        {
            location = &((*location)->nodes[0]);
        }
        else if ((*location)->val < v) 
        {
            location = &((*location)->nodes[1]);
        }
        else
        {
            return true;
        }
    }
    return false;
}

void tree::add(int v)
{
    if (!root) root = new node(v);
    node** location = &root;

    if (!find(v, location))
    {
        (*location) = new node(v);
    }
}

void tree::inorder(node* node)
{
    if (!node)return;


    inorder(node->nodes[0]);
    cout << node->val << " ";
    inorder(node->nodes[1]);

}

void tree::inorder()
{
    inorder(root);
}

void tree::posorder(node* node)
{
    if (!node)return;


    posorder(node->nodes[0]);
    posorder(node->nodes[1]);
    cout << node->val << " ";

}

void tree::posorder()
{
    posorder(root);
}

void tree::preorder(node* node)
{
    if (!node)return;

    cout << node->val << " ";
    preorder(node->nodes[0]);
    preorder(node->nodes[1]);

}

void tree::preorder()
{
    preorder(root);
}

void tree::del(int v)
{
    node** location = &root;
    if (!find(v, location))return;

    if (!((*location)->nodes[0] || (*location)->nodes[1]))
    {
        delete* location;
        *location = NULL;
    }
    else if((*location)->nodes[0] && (*location)->nodes[1])
    {
        node** pos = location;
        location = &(*location)->nodes[0];
        while ((*location)->nodes[1])
        {
            location = &((*location)->nodes[1]);
        }
        node* tmp = *location;
        node* tmp2 = *pos;
        (*pos)->nodes[0] = ((*location)->nodes[0]);
        tmp->nodes[1] = (*pos)->nodes[1];
        tmp->nodes[0] = (*pos)->nodes[0];


        if (root == *pos)root = tmp;

        delete tmp2;
    }
    else 
    {
        node* tmp = *location;
        *location = tmp->nodes[!tmp->nodes[0]];
        delete tmp;
    }
}

int HEIGTH(node* node, int a = 0)
{
    if (!node)return 0;

    int r = HEIGTH(node->nodes[0]);
    int l = HEIGTH(node->nodes[1]);
    if (r > l)return r + 1;
    return l + 1;
}

void tree::heigth()
{
    cout << "\nALTURA: " << HEIGTH(root);
}

void tree::levels()
{
    queue<node*> cola;
    node* tmp;
    cola.push(root);

    while (!cola.empty())
    {
        tmp = cola.front();
        cola.pop();

        cout << tmp->val << " ";

        if(tmp->nodes[0])cola.push(tmp->nodes[0]);
        if (tmp->nodes[1])cola.push(tmp->nodes[1]);
    }

    
}
