#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}


struct Node* insert(struct Node* root, int data) {

    if (root == NULL) {
        return newNode(data);
    }

   
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

   
    return root;
}


struct Node* search(struct Node* root, int key) {

    if (root == NULL || root->data == key) {
        return root;
    }

   
    if (root->data < key) {
        return search(root->right, key);
    }

    
    return search(root->left, key);
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}


void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}


struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


struct Node* deleteNode(struct Node* root, int key) {
    
    if (root == NULL) {
        return root;
    }

   
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

    
        struct Node* temp = minValueNode(root->right);

       
        root->data = temp->data;

        
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n--- Binary Search Tree Operations ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. In-order Traversal\n");
        printf("4. Pre-order Traversal\n");
        printf("5. Post-order Traversal\n");
        printf("6. Delete\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Node %d inserted.\n", value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value) != NULL) {
                    printf("Node %d found in the BST.\n", value);
                } else {
                    printf("Node %d not found in the BST.\n", value);
                }
                break;

            case 3:
                printf("In-order traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Pre-order traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Post-order traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 6:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node %d deleted (if it existed).\n", value);
                break;

            case 7:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

