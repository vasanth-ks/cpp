#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long mergeAndCountInv (const vector <int> &lHalf, const vector <int> &rHalf,
                             vector <int> &mHalves)
{
    long left = 0, right = 0, mHalvesInv = 0, i = 0, j = 0, k = 0;

    left = lHalf.size();
    right = rHalf.size();

    while ((i < left) && (j < right)) {
        if (lHalf[i] > rHalf[j]) {
            /* Increment split inversion */
            mHalvesInv += (left - i);
            mHalves[k++] = rHalf[j++];
        } else {
            mHalves[k++] = lHalf[i++];
        }
    }
    while (i < left) {
        mHalves[k++] = lHalf[i++];
    }
    while (j < right) {
        mHalves[k++] = rHalf[j++];
    }
    
    return mHalvesInv;
}

long countInversions (vector <int> &a)
{
    vector <int> leftHalf;
    vector <int> rightHalf;
    vector <int> mergedHalves(a.size());
    size_t mid = 0;
    long leftHalfInv = 0, rightHalfInv = 0, mergedHalvesInv = 0;

    /* Base case */
    if (a.size() == 1) {
        /* 
         * Since there is only one element in the array, return the number of
         * inversions as 0.
         */
         return 0;
    }

    mid = (a.size() / 2);
   
    /* Copy first half of the array to left half */
    for (long i = 0; i < mid; ++i) {
        leftHalf.push_back(a[i]);
    }

    /* Copy rest of the original array to right half */
    for (long i = mid; i < a.size(); ++i) {
        rightHalf.push_back(a[i]);
    }

    /* Count inversions in left half of the array */
    leftHalfInv = countInversions(leftHalf);
    /* Count inversions in right half of the array */
    rightHalfInv = countInversions(rightHalf);
    /* Count split inversions */
    mergedHalvesInv = mergeAndCountInv(leftHalf, rightHalf, mergedHalves);
    a = mergedHalves;
    
    /* Count all the inversions */
    mergedHalvesInv = (leftHalfInv + rightHalfInv + mergedHalvesInv);

    return mergedHalvesInv;
}

int main()
{
    size_t in_size = 0, i = 0;
    vector <int> input;
    int in = 0;
    unsigned int resCountInv = 0;

    scanf("%lu", &in_size);

    for (i = 0; i < in_size; ++i) {
        scanf("%d", &in);
        input.push_back(in);
    }

    resCountInv = countInversions(input);
    printf("Sorted array... ");
    for (i = 0; i < in_size; ++i) {
        printf("%d ", input[i]);
    }
    printf("\n");

    printf("Total inversions %u\n", resCountInv);

    return 0;
}
