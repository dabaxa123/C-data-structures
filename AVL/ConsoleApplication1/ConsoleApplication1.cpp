#include <iostream>
#include <algorithm>

class AVL {
    // AVL ხის კვანძი
    class Node {
    public:
        int key;        // კვანძის მნიშვნელობა
        Node* right;    // მარჯვენა შვილი
        Node* left;     // მარცხენა შვილი
        int height;     // კვანძის სიმაღლე

        Node(int val) {
            key = val;
            right = left = nullptr;
            height = 1; // ახალი კვანძის სიმაღლე არის 1
        }
    };

    Node* root; // ხის ფესვი

    // აბრუნებს კვანძის სიმაღლეს
    int Height(Node* node) {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    // აბრუნებს ბალანსის ფაქტორს
    // balance = მარცხენა სიმაღლე - მარჯვენა სიმაღლე
    int get_factor(Node* root) {
        if (root == nullptr)
            return 0;

        return Height(root->left) - Height(root->right);
    }

    // მარჯვნივ როტაცია
    Node* rotate_right(Node* root) {
        Node* newroot = root->left;
        Node* temp = newroot->right;

        // როტაცია
        newroot->right = root;
        root->left = temp;

        // სიმაღლეების განახლება
        root->height = std::max(Height(root->left), Height(root->right)) + 1;
        newroot->height = std::max(Height(newroot->left), Height(newroot->right)) + 1;

        return newroot;
    }

    // მარცხნივ როტაცია
    Node* rotate_left(Node* root) {
        Node* newRoot = root->right;
        Node* temp = newRoot->left;

        // როტაცია
        newRoot->left = root;
        root->right = temp;

        // სიმაღლეების განახლება
        root->height = std::max(Height(root->left), Height(root->right)) + 1;
        newRoot->height = std::max(Height(newRoot->left), Height(newRoot->right)) + 1;

        return newRoot;
    }

    // ახალი ელემენტის დამატება AVL ხეში
    Node* insertNode(Node* node, int key) {
        // თუ ადგილი ცარიელია, ვქმნით ახალ კვანძს
        if (node == nullptr)
            return new Node(key);

        // თუ key ნაკლებია, მივდივართ მარცხნივ
        if (key < node->key)
            node->left = insertNode(node->left, key);

        // თუ key მეტია, მივდივართ მარჯვნივ
        else if (key > node->key)
            node->right = insertNode(node->right, key);

        // თუ იგივე key უკვე არსებობს, აღარ ვამატებთ
        else
            return node;

        // სიმაღლის განახლება
        node->height = 1 + std::max(Height(node->left), Height(node->right));

        // ბალანსის ფაქტორის გამოთვლა
        int balance = get_factor(node);

        // Left Left შემთხვევა
        if (balance > 1 && key < node->left->key) {
            return rotate_right(node);
        }

        // Left Right შემთხვევა
        if (balance > 1 && key > node->left->key) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        // Right Left შემთხვევა
        if (balance < -1 && key < node->right->key) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        // Right Right შემთხვევა
        if (balance < -1 && key > node->right->key) {
            return rotate_left(node);
        }

        return node;
    }

    // პოულობს მინიმალურ კვანძს მოცემულ ქვეხეში
    Node* minimum(Node* node) {
        Node* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    // კვანძის წაშლა AVL ხიდან
    Node* deletenode(Node* node, int key) {
        // თუ ხე ცარიელია
        if (node == nullptr)
            return node;

        // თუ წასაშლელი key ნაკლებია, ვეძებთ მარცხენა ქვეხეში
        if (key < node->key) {
            node->left = deletenode(node->left, key);
        }

        // თუ წასაშლელი key მეტია, ვეძებთ მარჯვენა ქვეხეში
        else if (key > node->key) {
            node->right = deletenode(node->right, key);
        }

        // თუ ვიპოვეთ წასაშლელი კვანძი
        else {
            // შემთხვევა 1: კვანძს არ ჰყავს შვილი ან ჰყავს მხოლოდ ერთი შვილი
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                // თუ შვილი არ ჰყავს
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }

                // თუ ერთი შვილი ჰყავს
                else {
                    *node = *temp;
                }

                delete temp;
            }

            // შემთხვევა 2: კვანძს ჰყავს ორი შვილი
            else {
                // მარჯვენა ქვეხეში ვპოულობთ მინიმალურ ელემენტს
                Node* temp = minimum(node->right);

                // მიმდინარე კვანძში გადმოგვაქვს მინიმალური მნიშვნელობა
                node->key = temp->key;

                // შემდეგ იმ მინიმალურ კვანძს ვშლით
                node->right = deletenode(node->right, temp->key);
            }
        }

        // თუ წაშლის შემდეგ კვანძი nullptr გახდა
        if (node == nullptr)
            return node;

        // სიმაღლის განახლება
        node->height = 1 + std::max(Height(node->left), Height(node->right));

        // ბალანსის ფაქტორი
        int balanceFactor = get_factor(node);

        // Left Left შემთხვევა
        if (balanceFactor > 1 && get_factor(node->left) >= 0) {
            return rotate_right(node);
        }

        // Left Right შემთხვევა
        if (balanceFactor > 1 && get_factor(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        // Right Right შემთხვევა
        if (balanceFactor < -1 && get_factor(node->right) <= 0) {
            return rotate_left(node);
        }

        // Right Left შემთხვევა
        if (balanceFactor < -1 && get_factor(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        return node;
    }

    // Inorder traversal
    // ანუ ჯერ მარცხენა, შემდეგ root, შემდეგ მარჯვენა
    // ამიტომ შედეგი იბეჭდება ზრდადობით
    void print_tree(Node* root) {
        if (root != nullptr) {
            print_tree(root->left);
            std::cout << root->key << " ";
            print_tree(root->right);
        }
    }

    // ხის მეხსიერებიდან გასუფთავება
    void clear(Node* node) {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

public:
    // კონსტრუქტორი
    AVL() {
        root = nullptr;
    }

    // დესტრუქტორი — პროგრამის ბოლოს მეხსიერებას ასუფთავებს
    ~AVL() {
        clear(root);
    }

    // ელემენტის დამატება
    void insert(int val) {
        root = insertNode(root, val);
    }

    // ელემენტის წაშლა
    void remove(int val) {
        root = deletenode(root, val);
    }

    // ხის დაბეჭდვა
    void display() {
        print_tree(root);
        std::cout << std::endl;
    }
};

int main()
{
    AVL a1;

    // ელემენტების დამატება
    a1.insert(33);
    a1.insert(13);
    a1.insert(53);
    a1.insert(9);
    a1.insert(21);
    a1.insert(61);
    a1.insert(8);
    a1.insert(12);

    std::cout << "AVL tree inorder: ";
    a1.display();

    // წაშლის შემოწმება
    a1.remove(13);

    std::cout << "After deleting 13: ";
    a1.display();

    return 0;
}