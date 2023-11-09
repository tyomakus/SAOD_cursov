//Добавь меню, которое позволит листать по 20 записей, сортировать базу данных, искать по ключу (все эти функции уже есть, необходимо сделать только меню)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <conio.h>

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
    char keypressed;
    cout<<"\t\t"<<"FIO"<<"\t\t"<<"  |N otdela"<<"     |Doljnost"<<"\t"<<"      |Date of birth    |"<<endl;
    cout<<"_________________________________________________________________________________________"<<endl;
    for (int j = 0; j < size; j++)
    {
        cout << array[j].a <<"\t  |\t "<< array[j].b <<"\t|"<< array[j].c <<"|   "<< array[j].d <<"     |"<<endl;
        if ((j + 1) % 20 == 0)
        {
            cout << "Press any key to continue...\n";
            cin.get();
            //cout<<"_________________________________________________________________________________________\n"<<endl;
            //cout<<"1. back <\t\t\t\t\t 2. next >\n 3. sort '\t\t\t\t 4. find by a key 'fbk'"<<endl;
            //cin>>keypressed;
            //cout<<keypressed<<endl;
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

// int main()
// {
//     system("chcp 866>nul");
//     //setlocale(LC_CTYPE, "Russian");
//     FILE *fp;

//     fp = fopen("testBase2.dat", "rb");
//     record1 mas[4000] = {0};
//     int i = 0, sum = 0;
//     int ch[10];
//     int sortornot;
//     int viewdb;
//     short int searchKey;
//     i = fread((record1 *)mas, sizeof(record1), 4000, fp);

//     int pageSize = 20; // Размер страницы (20 записей)
//     int currentPage = 0; // Текущая страница

//     cout << "B(DataBase) - 2,\n C(Num otdel + FIO(Key - Num otdel)) - 1,\n S(Sort quicksort) - 2,\n D(tree - AVL) - 1,\n E(Shennon code) - 2\n";

//     int choice;
//     do {
//         cout << "Choise action:\n";
//         cout << "1.Show records (20 rec)\n";
//         cout << "2. Sortх\n";
//         cout << "3. Find by a key\n";
//         cout << "4. Leave\n";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 // Вывод записей с учетом текущей страницы
//                 for (int j = currentPage * pageSize; j < (currentPage + 1) * pageSize && j < i; j++) {
//                     cout << mas[j].a << "\t  |\t " << mas[j].b << "\t|" << mas[j].c << "|\t" << mas[j].d << "     |\n";
//                 }

//                 if (i > (currentPage + 1) * pageSize) {
//                     cout << "Press Enter to next page";
//                     cin.ignore();
//                     cin.get();
//                     currentPage++;
//                 } else {
//                     cout << "DB end.\n";
//                 }
//                 break;

//             case 2:
//                 // Ваш код для сортировки базы данных
//                 break;

//             case 3:
//                 cout << "Searck Key: ";
//                 cin >> searchKey;
//                 // Ваш код для поиска и отображения записей по ключу
//                 break;

//             case 4:
//                 cout << "Left.\n";
//                 break;

//             default:
//                 cout << "Uncorrect key. Again pls.\n";
//                 break;
//         }
//     } while (choice != 4);

//     return 0;
// }

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

    int pageSize = 20; // Размер страницы (20 записей)
    int currentPage = 0; // Текущая страница
    int choice;


    do {
        // Очистим экран
        system("cls");
        // Выводим записи с учетом текущей страницы
        for (int j = currentPage * pageSize; j < (currentPage + 1) * pageSize && j < i; j++) {
            cout << mas[j].a << "\t  |\t " << mas[j].b << "\t|" << mas[j].c << "|\t" << mas[j].d << "     |\n";
        }

        cout << "Vverh vniz listat, Esc menushka...";

        // Ожидаем нажатия клавиши
        int key = _getch();

        switch (key) {
            case 27: // Esc - показать меню
            cout << "Choise action:\n";
            cout << "1.Show records (20 rec)\n";
            cout << "2. Sortх\n";
            cout << "3. Find by a key\n";
            cout << "4. Leave\n";
                // Обработка выбора из меню
                cin>>choice;
                    if (choice = 1)
                    {
                        // Вывод записей с учетом текущей страницы
                        for (int j = currentPage * pageSize; j < (currentPage + 1) * pageSize && j < i; j++) {
                            cout << mas[j].a << "\t  |\t " << mas[j].b << "\t|" << mas[j].c << "|\t" << mas[j].d << "     |\n";
                        }
                    

                        if (i > (currentPage + 1) * pageSize) {
                            //cout << "Press Enter to next page";
                            cin.ignore();
                            cin.get();
                            currentPage++;
                        } else {
                            cout << "DB end.\n";
                        }
                        break;
                    };
                    if (choice = 2)
                    {
                        // Ваш код для сортировки базы данных
                        // Sorting the array using quicksort
                    quickSort(mas, 0, i - 1);
                        break;
                    };
                    if (choice = 3)
                    {
                        cout << "Searck Key: ";
                        cin >> searchKey;
                        // Ваш код для поиска и отображения записей по ключу
                        searchAndPrintByKey(mas, i, searchKey);
                        break;
                    };
                    if (choice = 4)
                    {
                        cout << "Left.\n";
                        break;
                    };
                    if (choice > 4) 
                    {
                        //cout << "Uncorrect key. Again pls.\n";
                        //break;
                    };

            case 224: // Специальный код для стрелок
                key = _getch();
                if (key == 80) { // Стрелка вниз
                    if (i > (currentPage + 1) * pageSize) {
                        currentPage++;
                    }
                } else if (key == 72) { // Стрелка вверх
                    if (currentPage > 0) {
                        currentPage--;
                    }
                }
                break;

            default:
                // Обработка других клавиш
                break;
        //     cin >> choice;
        //    
        //     switch (choice) {
        //         case 1:
        //             // Вывод записей с учетом текущей страницы
        //             for (int j = currentPage * pageSize; j < (currentPage + 1) * pageSize && j < i; j++) {
        //                 cout << mas[j].a << "\t  |\t " << mas[j].b << "\t|" << mas[j].c << "|\t" << mas[j].d << "     |\n";
        //             }

        //             if (i > (currentPage + 1) * pageSize) {
        //                 cout << "Press Enter to next page";
        //                 cin.ignore();
        //                 cin.get();
        //                 currentPage++;
        //             } else {
        //                 cout << "DB end.\n";
        //             }
        //             break;

        //         case 2:
        //             // Ваш код для сортировки базы данных
        //             break;

        //         case 3:
        //             cout << "Searck Key: ";
        //             cin >> searchKey;
        //             // Ваш код для поиска и отображения записей по ключу
        //             break;

        //         case 4:
        //             cout << "Left.\n";
        //             break;

        //         default:
        //             cout << "Uncorrect key. Again pls.\n";
        //             break;
        // }
        }
    } 
    while (choice != 4);
    return 0;
}

