#include <iostream>
#include <vector>
#include <math.h>
#include <float.h>

using namespace std;

typedef struct pointSet_ {
    int64_t x;
    int64_t y;
} pointSet;

void display (const vector <pointSet> vec)
{
    vector <pointSet>::const_iterator it;

    for (it = vec.begin(); it != vec.end(); ++it) {
        printf("(%lld, %lld) ", it->x, it->y);
    }
    printf("\n");
    return;
}

double euclideanDistance (const pointSet &p1, const pointSet &p2)
{
    double distance = 0.0;

    distance = sqrt((pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)));

    return distance;
}
vector <pointSet> mergeHalves (const vector <pointSet> l, const vector <pointSet> r,
                  bool sortX)
{
    vector <pointSet> res;
    vector <pointSet>::const_iterator iLeft = l.begin();
    vector <pointSet>::const_iterator iRight = r.begin();

    while (iLeft != l.end() && iRight != r.end()) {
        if (sortX) {
            if (iLeft->x <= iRight->x) {
                res.push_back(*iLeft);
                iLeft++;
            } else {
                res.push_back(*iRight);
                iRight++;
            }
        } else {
            if (iLeft->y <= iRight->y) {
                res.push_back(*iLeft);
                iLeft++;
            } else {
                res.push_back(*iRight);
                iRight++;
            }
        }
    }

    while (iLeft != l.end()) {
        res.push_back(*iLeft);
        iLeft++;
    }

    while (iRight != r.end()) {
        res.push_back(*iRight);
        iRight++;
    }

    return res;
}

vector <pointSet> mergeSort (vector <pointSet> p, bool sortX)
{
    vector <pointSet> res, pLeft, pRight, leftHalf, rightHalf;
    size_t size = p.size(), i = 0;

    /* Base case */
    if (size < 2) {
        return p;
    }

    for (i = 0; i < (size / 2); ++i) {
        pLeft.push_back(p[i]);
    }

    for (i = (size / 2); i < size; ++i) {
        pRight.push_back(p[i]);
    }

    leftHalf = mergeSort(pLeft, sortX);
    rightHalf = mergeSort(pRight, sortX);
    res = mergeHalves(leftHalf, rightHalf, sortX);

    return res;
}

vector <pointSet> splitClosestPair (vector <pointSet> px, vector <pointSet> py,
                                    double delta)
{
    vector <pointSet> out;
    double xBar = 0.0, lowerBound = 0.0, upperBound = 0.0, minDist = 0.0,
           dist = 0.0;
    vector <pointSet> sy;
    uint64_t i = 0, j = 0;

    xBar = px[(px.size()/2) - 1].x;
    lowerBound = xBar - delta;
    upperBound = xBar + delta;
    minDist = delta;

    for (i = 0; i < py.size(); ++i) {
        if (py[i].x > lowerBound && py[i].x < upperBound) {
            sy.push_back(py[i]);
        }
    }

    for (i = 0; i < sy.size(); ++i) {
        for (j = (i+1); j < 8 && j < sy.size(); ++j) {
            dist = euclideanDistance(sy[i], sy[j]);
            if (dist < minDist) {
                minDist = dist;
                if (out.empty()) {
                    out.push_back(sy[i]);
                    out.push_back(sy[j]);
                } else {
                    out[0] = sy[i];
                    out[1] = sy[j];
                }
            }
        }
    }

    return out;
}

vector <pointSet> closestPair (vector <pointSet> px, vector <pointSet> py)
{
    vector <pointSet> res(2), pxLeft, pxRight, pyLeft, pyRight, leftClosestPair,
                      rightClosestPair, splitPair;
    size_t pxSize = 0, pySize = 0, i  = 0, j = 0;
    double dist = 0.0, minDist = DBL_MAX;

    pxSize = px.size();
    pySize = py.size();

    /* Base case */
    if (pxSize <= 3) {
        for (i = 0; i < pxSize; ++i) {
            for (j = (i+1); j < pxSize; ++j) {
                dist = euclideanDistance(px[i], px[j]);
                if (dist < minDist) {
                    minDist = dist;
                    res[0] = px[i];
                    res[1] = px[j];
                }
            }
        }
        return res;
    }

    for (i = 0; i < (pxSize / 2); ++i) {
        pxLeft.push_back(px[i]);
        pyLeft.push_back(py[i]);
    }

    for (i = (pxSize / 2); i <  pxSize; ++i) {
        pxRight.push_back(px[i]);
        pyRight.push_back(py[i]);
    }

    leftClosestPair  = closestPair(pxLeft, pyLeft);
    rightClosestPair = closestPair(pxRight, pyRight);
    minDist = euclideanDistance(leftClosestPair[0], leftClosestPair[1]);
    dist = euclideanDistance(rightClosestPair[0], rightClosestPair[1]);
    if (dist < minDist) {
        res = rightClosestPair;
        minDist = dist;
    } else {
        res = leftClosestPair;
    }

    splitPair = splitClosestPair(px, py, minDist);

    if (!splitPair.empty()) {
        dist = euclideanDistance(splitPair[0], splitPair[1]);
        if (dist < minDist) {
            minDist = dist;
            res = splitPair;
        }
    }

    return res;
}
int main ()
{
    uint64_t numElem = 0, i = 0;
    vector <pointSet> in, outX, outY, res;
    int64_t x = 0, y = 0;
    pointSet ps;
    double dist;

    printf("Enter the number of points in the point set: ");
    scanf("%llu", &numElem);

    for (i = 0; i < numElem; ++i) {
        printf("Enter the X and Y co-ordinates:\n");
        scanf("%lld %lld", &ps.x, &ps.y);
        in.push_back(ps);
    }

    outX = mergeSort(in, true);
    outY = mergeSort(in, false);
    res = closestPair(outX, outY);
    dist = euclideanDistance(res[0], res[1]);
    printf("Closest pair of points in the point set...\n");
    display(res);
    printf("Distance between closest pair of points: %.2f\n", dist);

    return 0;
}
