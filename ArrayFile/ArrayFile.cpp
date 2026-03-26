 // ArrayFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <ios>
#include <vector>

#include <time.h>

using namespace std;

typedef double* pDouble;
/*
*   ConsoleInputArrayDouble
*   
*/
int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0; 
    do {
        cout << " Input size Array ( 0< 1 < " << sizeMax << " ) ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
        for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> A[i];
    }
    return size;
}

/*
*   RndInputArrayDouble
*
*/
int RndInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1=0, r2=0;
    srand(size);

    for (int i = 0; i < size; i++) {
        r1 = rand();
        r2 = rand();
        A[i] = 100.0 * r1;
        A[i] = A[i] / (1.0 + r2);
        cout << A[i] << "   ";
    }
    return size;
}

int ConsoleInputDynamicArrayNew(int sizeMax, pDouble &pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = new double[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, pDouble& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

void ConsoleInputVector(int sizeMax, vector<double> &A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    double d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return ;
}


/*
*  WriteArrayTextFile 
*
*/

void WriteArrayTextFile(int n, double *arr, const char *fileName )
{
    ofstream fout(fileName);
    if (fout.fail()) return;
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close(); //
}
/*
*  ReadArrayTextFile
*
*/


int ReadArrayTextFile(int n, double* arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) return 0;
    fin >> size;
    if (size <= 0) return 0;
    if (size > n) size = n;   
    for (int i = 0; i < n; i++)
       fin>> arr[i];
    fin.close();
    return size;
    
}


void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;
    bfout.write((const char*)&n, sizeof(int));
    std::streamsize  cn = static_cast<std::streamsize>(n) *sizeof(double);
    bfout.write((const char*)arr, cn);
    bfout.close();
}

int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
    int size=0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;
    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;
    bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
    bfin.close();
    // ssdhs
    return size;
}

void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
  }

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2 \n";
    cout << "    3.  Task 3 \n"; 
    cout << "    4.  Exit \n";
}

void MenuInput()
{
    cout << "     Menu Input   \n";
    cout << "    1.  Console all \n";
    cout << "    2.  Console - size, array - random \n";
    cout << "    3.  File 1.txt \n";
    cout << "    4.  bb    \n";
    cout << "    5.  Exit \n";
}


/*
* Задано одновимірний масив А розміру 2N. 
* Побудувати два масиви В і С розміру N, 
* включивши  у масив В елементи масиву А з парними індексами,
* а у С - з непарними.
*****************
*  A - in 
*  B, C - out 
*/
void  TestVariant(int N, double* A, double* B, double* C) {
    for (int i = 0; i < N; i++) {
        B[i] = A[2 * i];
        C[i] = A[2 * i + 1];
    }
}
//Завдання 3.1, 1 варіант
int ArrayTask3_1(int n, double* A, double* B)
{
    int sizeB = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] > 0) {
            B[sizeB] = A[i];
            sizeB++;
        }
    }
    return sizeB;
}

void Task3_1()
{
    const int MAX_SIZE = 560;
    double A[MAX_SIZE], B[MAX_SIZE];
    int n, sizeB;

    cout << "\n--- Task 1: Positive elements ---\n";

    // Ввод масива
    n = ConsoleInputArray(MAX_SIZE, A);

    // Формування B
    sizeB = ArrayTask3_1(n, A, B);

    // Запис в файл
    WriteArrayTextFile(n, A, "A.txt");
    WriteArrayTextFile(sizeB, B, "B.txt");

    // Вивід
    cout << "\nArray A:\n";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";

    cout << "\n\nArray B:\n";
    for (int i = 0; i < sizeB; i++)
        cout << B[i] << " ";

    cout << "\n\nPress Enter...";
    cin.ignore();
    cin.get();
}

//Завдання 3.2, варіант 1

int FindLastMaxPositiveAfterT(int n, int* A, int T)
{
    int startIndex = -1;

    // Шукаємо перший елемент > T
    for (int i = 0; i < n; i++) {
        if (A[i] > T) {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1) return -1; 

    int max = -2147483648; 
    int index = -1;

    int* p = A + startIndex;

    for (int i = startIndex; i < n; i++, p++) {
        if (*p > 0) { 
            if (*p >= max) { 
                max = *p;
                index = i;
            }
        }
    }

    return index;
}

int RndInputArrayInt(int sizeMax, int* A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        A[i] = rand() % 100 - 50;
        cout << A[i] << " ";
    }

    return size;
}

void WriteArrayBinFileInt(int n, int* arr, const char* fileName)
{
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;

    bfout.write((const char*)&n, sizeof(int));
    bfout.write((const char*)arr, n * sizeof(int));

    bfout.close();
}

void Task3_2()
{
    const int MAX_SIZE = 500;
    int* A = new int[MAX_SIZE];

    int n = RndInputArrayInt(MAX_SIZE, A);

    int T;
    cout << "\nEnter T: ";
    cin >> T;

    int index = FindLastMaxPositiveAfterT(n, A, T);

    if (index == -1)
        cout << "\nNot found\n";
    else
        cout << "\nIndex = " << index << " Value = " << A[index] << endl;

    WriteArrayBinFileInt(n, (int*)A, "A.bin");

    delete[] A;
}

//Завдання 3.3, варіант 1
void ArrayTask3_3(int n, double* X, double a, double b,
    double& sumLessA,
    double& prodGreaterB,
    double& maxAB,
    double& minAB,
    bool& hasAB)
{
    sumLessA = 0;
    prodGreaterB = 1;
    hasAB = false;

    for (int i = 0; i < n; i++)
    {
        if (X[i] < a)
            sumLessA += X[i];

        if (X[i] > b)
            prodGreaterB *= X[i];

        if (X[i] >= a && X[i] <= b)
        {
            if (!hasAB)
            {
                maxAB = minAB = X[i];
                hasAB = true;
            }
            else
            {
                if (X[i] > maxAB) maxAB = X[i];
                if (X[i] < minAB) minAB = X[i];
            }
        }
    }
}

void Task3_3()
{
    const int MAX_SIZE = 200;
    double* X = new double[MAX_SIZE];

    double a, b;
    cout << "Enter a and b (a < b): ";
    cin >> a >> b;

    int n = ReadArrayTextFile(MAX_SIZE, X, "input.txt");

    double sumLessA, prodGreaterB, maxAB, minAB;
    bool hasAB;

    ArrayTask3_3(n, X, a, b,
        sumLessA,
        prodGreaterB,
        maxAB,
        minAB,
        hasAB);

    // Вивід у консоль
    cout << "\nSum X(i) < a: " << sumLessA << endl;
    cout << "Product X(i) > b: " << prodGreaterB << endl;

    if (hasAB)
    {
        cout << "Max in [a,b]: " << maxAB << endl;
        cout << "Min in [a,b]: " << minAB << endl;
    }
    else
    {
        cout << "No elements in [a,b]\n";
    }

    // Запис у файл
    ofstream fout("output.txt");
    fout << sumLessA << endl;
    fout << prodGreaterB << endl;

    if (hasAB)
        fout << maxAB << " " << minAB << endl;
    else
        fout << "No elements in [a,b]\n";

    fout.close();

    delete[] X;
}

void TaskV()
{
    char ch = '5',t;
    do {
        system("cls");
        MenuTask();
        ch = getchar();
        t=getchar();
            switch (ch) {
             case '1': Task3_1(); break;
             case '2': Task3_2(); break;
             case '3': Task3_3(); break;
            //
            case '4': return;
            }
        cout << " Press any key and enter\n";
        ch = getchar();
        } while (ch != 27);
    
}

void ArrayLocal()
{
    double A[1000], B[500], C[500];
    int n;
    char ch = '5',t;
    do {
        system("cls");
        MenuTask();
        ch = getchar();
        t = getchar();
        switch (ch) {
        case '1': cout << " 1 "; break;
        case '2': cout << " 2 "; break;
        case '5': return;
        }
        cout << " Press any key and enter\n";
        ch = getchar();
    } while (ch != 27);

}


int main()
{ 
    
    
    
    const int MAX_SIZE = 560;
    std::cout << "Hello World!\n";
    ShowMainMenu();
    /*
    double A[MAX_SIZE], B[MAX_SIZE],C[MAX_SIZE];
    int n,m;
    n = RndInputArray(MAX_SIZE, A);
    WriteArrayTextFile(n, A, "1.txt");
    m = ReadArrayTextFile(MAX_SIZE, B, "1.txt");
    cout << " \n m= " << m << endl;
    for (int i = 0; i < m; i++)
        cout << B[i] << "   ";
    WriteArrayBinFile(n, A, "1.bin");
    m = ReadArrayBinFile(MAX_SIZE, C, "1.bin");
    cout << " \n m= " << m << endl;
    for (int i = 0; i < m; i++)
        cout << C[i] << "   ";
    cout << "\n  Vector \n";
    vector<double> vA;
    ConsoleInputVector(MAX_SIZE, vA);
    for (auto v : vA) {
        cout << v << "   ";
    }
*/
    TaskV();
    return 1;

}

