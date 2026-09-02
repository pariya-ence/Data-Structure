//AVL TREE
#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int item;                 // ข้อมูลในทรี
    struct TreeNode *lChild;  // ลูกทางซ้าย
    struct TreeNode *rChild;  // ลูกทางขวา
    int balFactor;            // Balance Factor
};
int max(int a, int b)
{
    if (a > b) {
    return a;
    } else {    
    return b;
}
}
int height(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return 1 + max(height(node->lChild),height(node->rChild));
}
int getBalance(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return height(node->lChild) - height(node->rChild);
}
void updateBalance(struct TreeNode *node)
{
    if (node != NULL)
        node->balFactor = getBalance(node);
}
struct TreeNode *createNode(int newItem)
{
    struct TreeNode *newNode;

    newNode = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    newNode->item = newItem;
    newNode->lChild = NULL;
    newNode->rChild = NULL;
    newNode->balFactor = 0;
    return newNode;
}
 //  LL Rotation -> หมุนขวา 
struct TreeNode *singleRotateLChild(struct TreeNode *node)
{
    struct TreeNode *temp;
    temp = node->lChild;
    node->lChild = temp->rChild;
    temp->rChild = node;
    updateBalance(node);
    updateBalance(temp);
    return temp;
}
 //  RR Rotation -> หมุนซ้าย
struct TreeNode *singleRotateRChild(struct TreeNode *node)
{
    struct TreeNode *temp;
    temp = node->rChild;
    node->rChild = temp->lChild;
    temp->lChild = node;
    updateBalance(node);
    updateBalance(temp);
    return temp;
}
  // LR Rotation
struct TreeNode *doubleRotateLChild(struct TreeNode *node)
{
    node->lChild =singleRotateRChild(node->lChild);
    return singleRotateLChild(node);
}
  // RL Rotation
struct TreeNode *doubleRotateRChild(struct TreeNode *node)
{
    node->rChild = singleRotateLChild(node->rChild);
    return singleRotateRChild(node);
}
 //       INSERT AVL
struct TreeNode *insertAVL(struct TreeNode *node,int newItem)
{
    if (node == NULL)
        return createNode(newItem);
    if (newItem < node->item)
    {
        node->lChild = insertAVL(node->lChild, newItem);
    }
    else if (newItem > node->item)
    {
        node->rChild = insertAVL(node->rChild, newItem);
    }
    else
    {
        return node;
    }
    updateBalance(node);
    if (node->balFactor > 1 && newItem < node->lChild->item)
    {
        return singleRotateLChild(node);
    }
    if (node->balFactor > 1 && newItem > node->lChild->item)
    {
        return doubleRotateLChild(node);
    }
    if (node->balFactor < -1 && newItem > node->rChild->item)
    {
        return singleRotateRChild(node);
    }
    if (node->balFactor < -1 && newItem < node->rChild->item)
    {
        return doubleRotateRChild(node);
    }
    return node;
}
struct TreeNode *insertNodeAVL(struct TreeNode *root, int newItem)
{
    if (root == NULL)
        root = createNode(newItem);
    else
        root = insertAVL(root, newItem);

    return root;
}

struct TreeNode *findMin(struct TreeNode *node)
{
    struct TreeNode *current = node;

    while (current != NULL && current->lChild != NULL)
    {
        current = current->lChild;
    }
    return current;
}
struct TreeNode *deleteNodeAVL(struct TreeNode *subRoot,
                               int key)
{
    if (subRoot == NULL)
        return NULL;
    if (key < subRoot->item)
    {
        subRoot->lChild = deleteNodeAVL(subRoot->lChild, key);
    }
    else if (key > subRoot->item)
    {
        subRoot->rChild = deleteNodeAVL(subRoot->rChild, key);
    }
    else
    {
        if (subRoot->lChild == NULL || subRoot->rChild == NULL)
        {
            struct TreeNode *temp;
            if (subRoot->lChild != NULL)
                temp = subRoot->lChild;
            else
                temp = subRoot->rChild;
            if (temp == NULL)
            {
                free(subRoot);
                return NULL;
            }
            else
            {
                struct TreeNode *oldNode = subRoot;
                subRoot = temp;
                free(oldNode);
            }
        }
        else
        {
            struct TreeNode *temp;
           temp = findMin(subRoot->rChild);
            subRoot->item = temp->item;
            subRoot->rChild = deleteNodeAVL(subRoot->rChild, temp->item);
        }
    }
    if (subRoot == NULL)
        return NULL;
    updateBalance(subRoot);
    if (subRoot->balFactor > 1 && getBalance(subRoot->lChild) >= 0)
    {
        return singleRotateLChild(subRoot);
    }
    if (subRoot->balFactor > 1 && getBalance(subRoot->lChild) < 0)
    {
        return doubleRotateLChild(subRoot);
    }

    if (subRoot->balFactor < -1 && getBalance(subRoot->rChild) <= 0)
    {
        return singleRotateRChild(subRoot);
    }
    if (subRoot->balFactor < -1 && getBalance(subRoot->rChild) > 0)
    {
        return doubleRotateRChild(subRoot);
    }
    return subRoot;
}
void inorder(struct TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->lChild);

        printf("%d ", root->item);

        inorder(root->rChild);
    }
}
void preorder(struct TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->item);

        preorder(root->lChild);
        preorder(root->rChild);
    }
}

int main()
{
    struct TreeNode *root = NULL;
    root = insertNodeAVL(root, 30);
    root = insertNodeAVL(root, 20);
    root = insertNodeAVL(root, 40);
    root = insertNodeAVL(root, 10);
    root = insertNodeAVL(root, 25);
    root = insertNodeAVL(root, 35);
    root = insertNodeAVL(root, 50);
    printf("\nInorder : ");
    inorder(root);
    printf("\nPreorder: ");
    preorder(root);
    root = deleteNodeAVL(root, 20);
    printf("\n\nAfter delete 20");
    printf("\nInorder : ");
    inorder(root);
    printf("\nPreorder: ");
    preorder(root);
    return 0;
}
