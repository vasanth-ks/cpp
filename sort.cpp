#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>

using namespace std;

/* Abstract class */
class Sort
{
    protected:
        size_t size;
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

/* Insertion sort */
class InsertionSort : public Sort
{
    public:
        InsertionSort(int n) : Sort(n)
        {
            cout << "Initializing the array size in Insertion sort constructor\n";
        }
        void sortArray();
        ~InsertionSort()
        {
            cout << "Insertion sort destructor\n";
        }
};

void InsertionSort::sortArray()
{
    int i = 0, j = 0, k = 0, currElement, tmp;
    
    cout << "Insertion sort...\n";
    for (i = 1; i < size; ++i) {
        currElement = array[i];
        j = i - 1;
        while ((currElement < array[j]) && (j >= 0)) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = currElement;
    }
    return;
}
/* Merge Sort */
class MergeSort : public Sort
{
    public:
        MergeSort(int n) : Sort(n)
        {
            cout << "Initializing array size in Merge sort constructor\n";
        }
        void sortArray();
        ~MergeSort()
        {
            cout << "Merge sort destructor\n";
        }
    private:
        void mergeSort(vector <int> &arr);
        void mergeArray(vector <int> left, vector <int> right, vector <int>
        &arr);
};

void MergeSort::sortArray()
{
    cout << "Merge sort...\n";
    mergeSort(array);
}

void MergeSort::mergeSort(vector <int> &arr)
{
    size_t mid = 0;
    unsigned int i = 0;
    vector <int> left;
    vector <int> right;

    mid = arr.size() / 2;

    if (arr.size() <= 1) {
        return;
    }

    for (i = 0; i < mid; ++i) {
        left.push_back(arr[i]);
    }
    for (i = mid; i < arr.size(); ++i) {
        right.push_back(arr[i]);
    }

    mergeSort(left);
    mergeSort(right);

    mergeArray(left, right, arr);

    return;
}
void MergeSort::mergeArray(vector <int> left, vector <int> right, vector <int> &arr)
{
    unsigned int i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k] = left[i++];
        } else {
            arr[k] = right[j++];
        }
        k++;
    }

    while (i < left.size()) {
        arr[k++] = left[i++];
    }
    while (j < right.size()) {
        arr[k++] = right[j++];
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
    cout << "3. Insertion Sort\n";
    cout << "4. Merge Sort\n";
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
        cout << "Object type: " << typeid(bs).name() << endl;
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
    case 3: 
        /* Insertion Sort */
    {
        InsertionSort Is(7);
        s = &Is;
        s->getArray();
        s->sortArray();
        s->display();
        break;
    }
    case 4: 
        /* Merge Sort */
    {
        MergeSort m(8);
        s = &m;
        s->getArray();
        s->sortArray();
        s->display();
        break;
    }
    default:
        cout << "Invalid option\n";
        break;
    }
    
    return 0;
}
