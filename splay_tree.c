#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct splay_node{
    int key;
    struct splay_node *left, *right;
}splay_node;

/*helpler function that allocate a new node with the given key 
and NULL left the right nodes*/
struct splay_node* newNode(int key)
{
    struct splay_node* node = (struct splay_node*)malloc(sizeof(struct splay_node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

/*A utility function to right rotate subtree roted with y*/
struct splay_node* rightRotate(struct splay_node *x)
{
    struct splay_node* y = x->left;
    struct splay_node* tmp = y->right;
    y->right = x;
    x->left = tmp; 
    return y;
}

/*A utility function to left rotate subtree roted with x*/
struct splay_node* leftRotate(struct splay_node *x)
{
    struct splay_node* y = x->right;
    struct splay_node* tmp = y->left;
    y->left = x;
    x->right = tmp;
    return y;
}

/*This function brings the key at root if key is present in tree.
If key is not present, then it brings the latest accessed item at
root. This function modifies the tree and returns the new root.
*/

struct splay_node* splay(struct splay_node *root, int key)
{
    if(root == NULL || key == root->key)
        return root;
    //the key is on the left
    if(root->key > key){
        //key not in the tree, we are done.
        if(root->left == NULL) return root;
        //left-left
        else{
            //right rotate first
            splay_node* rt_tmp = rightRotate(root);
            return splay(rt_tmp, key);
        }
    }
    //the key is on the right
    else{
        if(root->right == NULL) return root;
        else{
            splay_node *rt_tmp = leftRotate(root);
            return splay(rt_tmp, key);
        }
    }
}

/*A utility function to print preorder traversal of the tree.
The function also prints height of every node*/
void preOrder(splay_node *root)
{
    if(root != NULL){
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


int main(int argc, char ** argv){
    //put the test here.
    splay_node *root = newNode(100);
    root->left = newNode(50);
    root->right = newNode(200);
    root->left->left = newNode(40);
    root->left->left->left = newNode(30);
    root->left->left->left->left = newNode(20);
    preOrder(root);
    root = splay(root, 200);
    root = splay(root, 100);
    printf("\n/********results shown below*********\n");

    preOrder(root);
    return 0;
}