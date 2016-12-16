#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>

using namespace std;

/* Abstract class */
class Sort
{
    protected:
        int size;
        vector <int> array;
    public:
        Sort(size_t n);
        void getArray();
        virtual void sortArray() = 0;
        void display();
        ~Sort()
        {
            cout << "Abstract class destructor\n";
        }
};

Sort::Sort(size_t n)
{
    size = n;
    cout << "Initializing array size in abstract class constructor\n";
}

void Sort::getArray()
{
    int in = 0;
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < size; ++i) {
        cin >> in;
        array.push_back(in);
    }
    return;
}
void Sort::display()
{
    vector <int>::iterator it;

    for (it = array.begin(); it != array.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
    return;
}

/* Bubble sort */
class BubbleSort : public Sort
{
    public:
        BubbleSort(int n) : Sort(n)
        {
            cout << "Initializing array size in Bubble sort constructor\n";
        }
        void sortArray();
        ~BubbleSort()
        {
            cout << "Bubble sort destructor\n";
        }
};

void BubbleSort::sortArray()
{
    int i = 0, j = 0, tmp;
    
    cout << "Bubble sort ...\n";
    for (i = 0; i < size; ++i) {
        for (j = (size - 1); j > i; --j) {
            if (array[j] < array[j-1]) {
                tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
        }
    }
    return;
}

/* Selection sort */
class SelectionSort : public Sort
{
    public:
        SelectionSort(int n) : Sort(n)
        {
            cout << "Initializing the array size in Selection sort constructor\n";
        }
        void sortArray();
        ~SelectionSort()
        {
            cout << "Selection sort destructor\n";
        }
};
void SelectionSort::sortArray()
{
    int i = 0, j = 0, min = INT_MAX, tmp = 0, min_pos = -1;
    
    cout << "Selection Sort...\n";
    for (i = 0; i < size; ++i) {
        for (j = i; j < size; ++j) {
            if (array[j] < min) {
                min = array[j];
                min_pos = j;
            }
        }
        tmp = array[i];
        array[i] = min;
        array[min_pos] = tmp;
        min = INT_MAX;
        min_pos = -1;
    }
    return;
}

/* Main */
int main()
{
    int i = 0, in = 0, choice = -1;
    Sort *s;

    cout << "Choose the type of sorting algorithm:\n";
    cout << "****************************************\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "****************************************\n";
    cin >> choice;

    switch(choice) {
    case 1:
        /* Bubble Sort */
    {
        BubbleSort bs(8);
        s = &bs;
        s->getArray();
        s->sortArray();
        s->display();
        break;
    }
    case 2:
        /* Selection Sort */
    {
        SelectionSort ss(8);
        s = &ss;
        s->getArray();
        s->sortArray();
        s->display();
        break;
    }
    default:
        cout << "Invalid option\n";
        exit(-1);
    }
    
    return 0;
}
