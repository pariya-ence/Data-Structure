#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
/* Create a new node */
TreeNode *createNode(int value) {
    TreeNode *newNode;
    newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/* Insert a node into BST */
TreeNode *insertNode(TreeNode *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else {
        root->right = insertNode(root->right, value);
    }
    return root;
}
/* Search for a value in BST */
TreeNode *searchNode(TreeNode *root, int key) {
    TreeNode *current = root;
    while (current != NULL) {
        if (key == current->data) {
            return current;
        }
        if (key < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}
/* Inorder  : Left -> Root -> Right */
void inorder(TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
/* Preorder : Root -> Left -> Right */
void preorder(TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
/* Postorder : Left -> Right -> Root */
void postorder(TreeNode *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
TreeNode *Min(TreeNode *root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
TreeNode *Max(TreeNode *root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode *current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}
TreeNode *deleteNode(TreeNode *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        else {
            TreeNode *temp;
            temp = Min(root->right);
            root->data = temp->data;
            root->right =
                deleteNode(root->right, temp->data);
        }
    }
    return root;
}
int main() {

    TreeNode *root = NULL;
    TreeNode *result;
    int choice;
    int value;
    int key;
    TreeNode *min;
    TreeNode *max;
    printf("\n     Binary Search Tree");
    printf("\n1. Insert Node");
    printf("\n2. Search Node");
    printf("\n3. Delete Node");
    printf("\n4. Traversal");
    printf("\n5. Find MIN/MAX");
    printf("\n6. Exit");
    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            root = insertNode(root, value);
            printf("%d inserted into BST.\n", value);
            break;
       case 2:
            if (root == NULL) {
                printf("BST is empty.\n");
                break;
            }
            printf("Enter value to search: ");
            scanf("%d", &key);
            result = searchNode(root, key);
            if (result != NULL) {
                printf("%d is found in BST.\n", key);
            }
            else {
                printf("%d is not found in BST.\n", key);
            }
            break;
        case 3:
          printf("Enter value to delete: ");
            scanf("%d", &value);
            result = searchNode(root, value);
            if (result == NULL) {
                printf("%d not found in BST.\n", value);
            }
            else {
                root = deleteNode(root, value);
                printf("%d deleted from BST.\n", value);
            }
            break;
        case 4:
            if (root == NULL) {
                printf("BST is empty.\n");
            }
            else {
                printf("\nInorder   : ");
                inorder(root);
                printf("\nPreorder  : ");
                preorder(root);
                printf("\nPostorder : ");
                postorder(root);
                printf("\n");
            }
            break;
         case 5:
            if (root == NULL) {
                printf("BST is empty.\n");
            }
            else {
                min = Min(root);
                max = Max(root);
                printf("\nMin value : %d", min->data);
                printf("\nMax value : %d\n", max->data);
            }

            break;   
        case 6:
            printf("Exit program.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 6);
    return 0;

}
