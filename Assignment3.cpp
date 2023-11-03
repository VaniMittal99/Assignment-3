#include <iostream>
#include <cassert>
#include <stdexcept>

class InvalidChoiceException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid choice. Please select a valid option.";
    }
};

template <typename T>
class QuartenarySearchTree {
private:
    struct Node {
        T key;
        Node* children[4];
        Node(T k) : key(k) {
            for (int i = 0; i < 4; i++) {
                children[i] = nullptr;
            }
        }
    };

    Node* root;

public:
    QuartenarySearchTree() : root(nullptr) {}

    QuartenarySearchTree(const T* objects, int numObjects) : root(nullptr) {
        for (int i = 0; i < numObjects; i++) {
            insert(objects[i]);
        }
    }

    void insert(const T& key) {
        root = insertRecursive(root, key);
    }

    void insertAdditionalElements(const T* elements, int numElements) {
        for (int i = 0; i < numElements; i++) {
            insert(elements[i]);
        }
    }

    void deleteElement(const T& key) {
        root = deleteElementRecursive(root, key);
    }

    void printPreorder() {
        printPreorder(root);
        std::cout << std::endl;
    }

    void printInorder() {
        printInorder(root);
        std::cout << std::endl;
    }

    void printPostorder() {
        printPostorder(root);
        std::cout << std::endl;
    }

private:
    Node* insertRecursive(Node* node, const T& key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->children[0] = insertRecursive(node->children[0], key);
        } else if (key < node->key * 0.5) {
            node->children[1] = insertRecursive(node->children[1], key);
        } else if (key < node->key * 2.0) {
            node->children[2] = insertRecursive(node->children[2], key);
        } else {
            node->children[3] = insertRecursive(node->children[3], key);
        }

        return node;
    }

    Node* deleteElementRecursive(Node* node, const T& key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->children[0] = deleteElementRecursive(node->children[0], key);
        } else if (key < node->key * 0.5) {
            node->children[1] = deleteElementRecursive(node->children[1], key);
        } else if (key < node->key * 2.0) {
            node->children[2] = deleteElementRecursive(node->children[2], key);
        } else {
            node->children[3] = deleteElementRecursive(node->children[3], key);
        }

        if (key == node->key) {
            if (node->children[0] == nullptr && node->children[1] == nullptr && node->children[2] == nullptr && node->children[3] == nullptr) {
                delete node;
                return nullptr;
            } else {
                // Element found, but not leaf node; replace with the minimum value from the right subtree
                if (node->children[3]) {
                    Node* minNode = findMin(node->children[3]);
                    node->key = minNode->key;
                    node->children[3] = deleteElementRecursive(node->children[3], minNode->key);
                } else if (node->children[2]) {
                    Node* minNode = findMin(node->children[2]);
                    node->key = minNode->key;
                    node->children[2] = deleteElementRecursive(node->children[2], minNode->key);
                } else if (node->children[1]) {
                    Node* minNode = findMin(node->children[1]);
                    node->key = minNode->key;
                    node->children[1] = deleteElementRecursive(node->children[1], minNode->key);
                } else {
                    Node* minNode = findMin(node->children[0]);
                    node->key = minNode->key;
                    node->children[0] = deleteElementRecursive(node->children[0], minNode->key);
                }
            }
        }

        return node;
    }

    Node* findMin(Node* node) {
        if (node->children[0] == nullptr) {
            return node;
        }
        return findMin(node->children[0]);
    }

    void printPreorder(Node* node) {
        if (node) {
            std::cout << node->key << ' ';
            for (int i = 0; i < 4; i++) {
                printPreorder(node->children[i]);
            }
        }
    }

    void printInorder(Node* node) {
        if (node) {
            printInorder(node->children[0]);
            std::cout << node->key << ' ';
            printInorder(node->children[1]);
            printInorder(node->children[2]);
            printInorder(node->children[3]);
        }
    }

    void printPostorder(Node* node) {
        if (node) {
            for (int i = 0; i < 4; i++) {
                printPostorder(node->children[i]);
            }
            std::cout << node->key << ' ';
        }
    }
};

int main() {
    QuartenarySearchTree<int> qst;

    int* elements = nullptr;
    int* additionalElements = nullptr;

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Insert elements" << std::endl;
        std::cout << "2. Insert additional elements" << std::endl;
        std::cout << "3. Delete element" << std::endl;
        std::cout << "4. Print Preorder" << std::endl;
        std::cout << "5. Print Inorder" << std::endl;
        std::cout << "6. Print Postorder" << std::endl;
        std::cout << "7. Exit" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1:
                    int numElements;
                    std::cout << "Enter the number of elements to insert: ";
                    std::cin >> numElements;

                    if (numElements <= 0) {
                        throw std::runtime_error("Invalid number of elements.");
                    }

                    elements = new int[numElements];
                    for (int i = 0; i < numElements; i++) {
                        std::cout << "Enter element " << i + 1 << ": ";
                        std::cin >> elements[i];
                    }
                    qst.insertAdditionalElements(elements, numElements);
                    delete[] elements;
                    break;
                case 2:
                    int numAdditionalElements;
                    std::cout << "Enter the number of additional elements to insert: ";
                    std::cin >> numAdditionalElements;

                    if (numAdditionalElements <= 0) {
                        throw std::runtime_error("Invalid number of additional elements.");
                    }

                    additionalElements = new int[numAdditionalElements];
                    for (int i = 0; i < numAdditionalElements; i++) {
                        std::cout << "Enter additional element " << i + 1 << ": ";
                        std::cin >> additionalElements[i];
                    }
                    qst.insertAdditionalElements(additionalElements, numAdditionalElements);
                    delete[] additionalElements;
                    break;
                case 3:
                    int keyToDelete;
                    std::cout << "Enter the key of the element to delete: ";
                    std::cin >> keyToDelete;
                    qst.deleteElement(keyToDelete);
                    break;
                case 4:
                    qst.printPreorder();
                    break;
                case 5:
                    qst.printInorder();
                    break;
                case 6:
                    qst.printPostorder();
                    break;
                case 7:
                    delete[] elements;
                    delete[] additionalElements;
                    return 0;
                default:
                    throw InvalidChoiceException();
            }
        } catch (const InvalidChoiceException& e) {
            std::cerr << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
