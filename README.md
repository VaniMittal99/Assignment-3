# Assignment-3
Quatenary Search Tree 
Clone the repository to your local machine.

Compile the code using a C++ compiler. You can use a command like this:
g++ Assignment3.cpp -o outputA3
Run the compiled program:
./outputA3
The program will display a menu with several options. Choose from the following options:

Insert elements: Add a set of elements to the QST.
Insert additional elements: Add more elements to the QST.
Delete element: Remove an element from the QST.
Print Preorder: Display the elements of the tree in preorder traversal.
Print Inorder: Display the elements of the tree in inorder traversal.
Print Postorder: Display the elements of the tree in postorder traversal.
Exit: Quit the program.
Follow the prompts to enter your choice and the required input data, such as element values.
The program will perform the requested action and provide feedback on the result.

You can continue to interact with the program by selecting options from the menu until you choose to exit.
Exception Handling
The program includes error handling to deal with potential issues. It catches and reports two types of exceptions:

InvalidChoiceException: This exception is thrown when the user selects an invalid choice from the menu.

std::runtime_error: This exception is used to handle cases like providing an invalid number of elements for insertion.
