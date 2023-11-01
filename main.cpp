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
	    if (searchKey > -1)
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

    return 0;
}
