#include <iostream>
#include <vector>
#include <limits.h>
#include <string>

using namespace std;

inline int max (long int a, long int b)
{
    return ((a > b) ? a : b);
}

void findMaxSubArray (vector <int> &in, int &contSum, int &nonContSum)
{
    int i = 0, j = 0;
    vector <int> contSumArray;
    vector <int> nonContSumArray;
    contSumArray.push_back(in[i]);
    nonContSumArray.push_back(in[i]);
    contSum = in[i];
    nonContSum = in[i];

    for (i = 1; i < in.size(); ++i) {
        contSumArray.push_back(max((contSumArray[i-1] + in[i]), in[i]));
        contSum = max(contSumArray[i], contSum);

        nonContSumArray.push_back(max(nonContSumArray[i-1], in[i]));
        nonContSum = max((nonContSum + in[i]), nonContSumArray[i]);
        nonContSumArray[i] = nonContSum;
    }

    return;
}


int main()
{
    vector <int> input;
    int n_elements, value;
    int contiguousSum = INT_MIN, nonContiguousSum = INT_MIN;
    unsigned int n_tests, i, j;

    cin >> n_tests;
    for (i = 0; i < n_tests; ++i) {
        cin >> n_elements;
        for (j = 0; j < n_elements; ++j) {
            cin >> value;
            input.push_back(value);
        }
        findMaxSubArray(input, contiguousSum, nonContiguousSum);
        cout << contiguousSum << " " << nonContiguousSum << endl;
        input.clear();
        contiguousSum = INT_MIN;
        nonContiguousSum = INT_MIN;
    }

    return 0;
}
