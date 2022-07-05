#include "avl.h"

AVL* initAVL() {
    AVL* tempAVL = (AVL*)malloc(sizeof(AVL));
    tempAVL->left = NULL;
    tempAVL->right = NULL;
    return tempAVL;
}

int height(AVL* current) {
    if (current == NULL) return 0;
    else return current->height;
}

int getBalance(AVL* current) {
    if (current == NULL) return 0;
    else return height(current->left) - height(current->right);
}

AVL* rotateRight(AVL* current) {
    AVL* targetRotate = current->left;
    AVL* targetRotateChildrenRight = targetRotate->right;
    targetRotate->right = current;
    current->left = targetRotateChildrenRight;
    current->height = 1 + max(height(current->left), height(current->right));
    targetRotate->height = 1 + max(height(targetRotate->left), height(targetRotate->right));
    return targetRotate;
}

AVL* rotateLeft(AVL* current) {
    AVL* targetRotate = current->right;
    AVL* targetRotateChildrenLeft = targetRotate->left;
    targetRotate->left = current;
    current->right = targetRotateChildrenLeft;
    current->height = 1 + max(height(current->left), height(current->right));
    targetRotate->height = 1 + max(height(targetRotate->left), height(targetRotate->right));
    return targetRotate;
}

AVL* createNewAVL(image_t* img) {
    AVL* newAVL
        = (AVL*)malloc(sizeof(AVL));
    newAVL->elements = img;
    newAVL->left = NULL;
    newAVL->right = NULL;
    return newAVL;
}

AVL* insert(AVL* current, image_t* img) {
    if (current == NULL) {
        return createNewAVL(img);
    }

    else if (img->contrast > current->elements->contrast) {
        current->right = insert(current->right, img);
    }

    else if (img->contrast < current->elements->contrast) {
        current->left = insert(current->left, img);
    }

    else {
        return current;
    }

    current->height = 1 + max(height(current->left), height(current->right));

    int balance = getBalance(current);

    if (balance > 1) {
        if (img->contrast < current->left->elements->contrast) {
            return rotateRight(current);
        }

        else if (img->contrast > current->left->elements->contrast) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
    }

    else if (balance < -1) {
        if (img->contrast > current->right->elements->contrast) {
            return rotateLeft(current);
        }

        else if (img->contrast < current->right->elements->contrast) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
    }
    return current;
}

AVL* avl_init() {
    AVL* newAVL
        = (AVL*)malloc(sizeof(AVL));
    return newAVL;
}