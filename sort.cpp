#include <iostream>
#include <stdlib.h>
#include <vector>

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
int main()
{
    int i = 0, in = 0;
    Sort *s;

    /* Bubble Sort */
    BubbleSort bs(9);
    s = &bs;
    s->getArray();
    s->sortArray();
    s->display();
    /* Bubble Sort */

    return 0;
}
