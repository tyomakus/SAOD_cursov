#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <locale>

using namespace std;

struct record1
{
    char a[30];
    short int b;
    char c[22];
    char d[10];
};

// Structure for AVL tree node
struct Node
{
    record1 data;
    Node *left;
    Node *right;
    int height;
};
// Function to compare for quicksort
int compareRecords(const void *a, const void *b)
{
    const record1 *recordA = static_cast<const record1 *>(a);
    const record1 *recordB = static_cast<const record1 *>(b);

    if (recordA->b < recordB->b)
        return -1;
    else if (recordA->b > recordB->b)
        return 1;
    else
        return strcmp(recordA->a, recordB->a);
}

// Function to perform quicksort
void quickSort(record1 *array, int left, int right)
{
    if (left < right)
    {
        int pivot = left;
        int i = left;
        int j = right;

        while (i < j)
        {
            while (compareRecords(&array[i], &array[pivot]) <= 0 && i < right)
                i++;
            while (compareRecords(&array[j], &array[pivot]) > 0)
                j--;

            if (i < j)
                swap(array[i], array[j]);
        }

        swap(array[pivot], array[j]);

        quickSort(array, left, j - 1);
        quickSort(array, j + 1, right);
    }
}



// Function to print records 20 at a time
void printRecords(record1 *array, int size)
{
    cout<<"\t\t"<<"FIO"<<"\t\t"<<"  |N otdela"<<"     |Doljnost"<<"\t"<<"      |Date of birth    |"<<endl;
    cout<<"_________________________________________________________________________________________"<<endl;
    for (int j = 0; j < size; j++)
    {
        cout << array[j].a <<"\t  |\t "<< array[j].b <<"\t|"<< array[j].c <<"|   "<< array[j].d <<"     |"<<endl;
        if ((j + 1) % 20 == 0)
        {
            cout << "Press any key to continue...\n";
            cin.get();
        }
    }
}



// Function to search and display records with a specific key
void searchAndPrintByKey(record1 *array, int size, short int key)
{
    cout << "Records with key " << key << ":\n";
    for (int j = 0; j < size; j++)
    {
        if (array[j].b == key)
        {
            cout << array[j].a << "\t  |\t " << array[j].b << "\t|" << array[j].c << "|\t" << array[j].d << "     |\n";
        }
    }
}
// Function to compare for AVL tree based on a key different from short int b
int compareRecordsByKey(const record1 &recordA, const record1 &recordB)
{
    // Compare records based on the key you want (e.g., recordA.c, recordB.c)
    return strcmp(recordA.c, recordB.c);
}

// Function to get the height of a node
int getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(Node *node)
{
    if (node == nullptr)
        return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to perform a right rotation
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to balance a node and return the new root
Node *balanceNode(Node *node)
{
    int balance = getHeight(node->left) - getHeight(node->right);

    if (balance > 1)
    {
        if (compareRecordsByKey(node->data, node->left->data) > 0)
            return rightRotate(node);
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balance < -1)
    {
        if (compareRecordsByKey(node->data, node->right->data) < 0)
            return leftRotate(node);
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// Function to insert a record into the AVL tree
Node *insertNode(Node *root, record1 data)
{
    if (root == nullptr)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (compareRecordsByKey(data, root->data) < 0)
        root->left = insertNode(root->left, data);
    else if (compareRecordsByKey(data, root->data) > 0)
        root->right = insertNode(root->right, data);
    else
        return root; // Duplicate keys are not allowed

    updateHeight(root);
    return balanceNode(root);
}

// Function to search for a record in the AVL tree by the specified key
Node *searchByKey(Node *root, const char *key)
{
    if (root == nullptr || strcmp(key, root->data.c) == 0)
        return root;

    if (compareRecordsByKey(root->data, root->data) < 0)
        return searchByKey(root->left, key);

    return searchByKey(root->right, key);
}

// Function to display the contents of the AVL tree (inorder traversal)
void displayAVL(Node *root)
{
    if (root != nullptr)
    {
        displayAVL(root->left);
        cout << root->data.a << "\t  |\t " << root->data.b << "\t|" << root->data.c << "|\t" << root->data.d << "     |\n";
        displayAVL(root->right);
    }
}

int main()
{
    system("chcp 866>nul");
    //setlocale(LC_CTYPE, "Russian");
    FILE *fp;
    fp = fopen("testBase2.dat", "rb");
    record1 mas[4000] = {0};
    int i = 0, sum = 0;
    int ch[10];
    int sortornot;
    int viewdb;
    short int searchKey;
    i = fread((record1 *)mas, sizeof(record1), 4000, fp);
    cout<<"B(DataBase) - 2,\n C(Num otdel + FIO(Key - Num otdel)) - 1,\n S(Sort quicksort) - 2,\n D(tree - AVL) - 1,\n E(Shennon code) - 2\n";
	cout<<"sort? 1/0 \n";
	cin >> sortornot;
	cout<<"view DataBase? 1/0\n";
	cin>>viewdb;
	    // Prompt the user for the key to search


    if (sortornot != 0)
    {
        // Sorting the array using quicksort
        quickSort(mas, 0, i - 1);
    }
	if (viewdb < 1)
	{
    	cout << "Enter the key (short int b) to search: ";
    	cin >> searchKey;
	    // Print records or search by key
	    if (searchKey != 0)
		{
	        searchAndPrintByKey(mas, i, searchKey);
	    }
	    else
	    {
	        // Print all records
	        printRecords(mas, i);
	    }
	}
	if (viewdb > 0)
	{
		printRecords(mas, i);
	}


    // Create an empty AVL tree for a key different from short int b
    Node *root = nullptr;

    // Insert records into the AVL tree
    for (int j = 0; j < i; j++)
    {
        root = insertNode(root, mas[j]);
    }

    // Display the contents of the AVL tree (inorder traversal)
    cout << "Contents of the AVL Tree (based on a different key):\n";
    cout << "FIO" << "\t\t" << "  |N otdela" << "     |Doljnost" << "\t" << "      |Date of birth    |\n";
    cout << "_________________________________________________________________________________________\n";
    displayAVL(root);

    // Prompt the user for a key to search in the AVL tree
    char searchKey[22];
    cout << "Enter the key (e.g., 'Doljnost') to search in the AVL Tree: ";
    cin.ignore(); // Clear newline character
    cin.getline(searchKey, 22);

    // Search for a record by the specified key
    Node *foundNode = searchByKey(root, searchKey);

    if (foundNode != nullptr)
    {
        cout << "Record found: " << foundNode->data.a << "\t  |\t " << foundNode->data.b << "\t|" << foundNode->data.c << "|\t" << foundNode->data.d << "     |\n";
    }
    else
    {
        cout << "Record not found for the specified key.\n";
    }

    cout << sizeof(record1) << endl;

    return 0;
}
