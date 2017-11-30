/*
 * Program to multiply two square matrices whose size is powers of 2 using 
 * two different divide and conquer techniques.
 */
#include <iostream>
#include <vector>

using namespace std;

void displayMatrix (const vector < vector <int> > matrix)
{
    vector <vector <int> >::const_iterator i;
    vector <int>::const_iterator j;

    for (i = matrix.begin(); i != matrix.end(); ++i) {
        for (j = i->begin(); j != i->end(); ++j) {
            printf("%-10d", *j);
        }
        printf("\n");
    }

    return;
}

vector < vector <int> > matrixAdd (const vector < vector <int> > matA, const vector < vector
                                   <int> > matB) 
{
    vector < vector <int> >  matC;
    vector <int> row;
    vector < vector <int> >::const_iterator i, k;
    vector <int>::const_iterator j,l;
    size_t aRows = 0, aCols = 0, bRows = 0, bCols = 0;
    
    i = matA.begin();
    k = matB.begin();

    aRows = matA.size();
    aCols = i->size();
    bRows = matB.size();
    bCols = k->size();

    if (aRows != bRows || aCols != bCols) {
        printf("Invalid matrix size for addition\n");
        exit(-1);
    }

    for (i = matA.begin(), k = matB.begin(); i != matA.end() && k != matB.end(); ++i, ++k) {
        for (j = i->begin(), l = k->begin(); j != i->end() && l != k->end();
                                                                ++j, ++l) {
            row.push_back(*j + *l);
        }
        matC.push_back(row);
        row.clear();
    }

    return matC;
}

vector < vector <int> > matrixSub (const vector < vector <int> > matA, const vector < vector
                                   <int> > matB) 
{
    vector < vector <int> >  matC;
    vector <int> row;
    vector < vector <int> >::const_iterator i, k;
    vector <int>::const_iterator j,l;
    size_t aRows = 0, aCols = 0, bRows = 0, bCols = 0;
    
    i = matA.begin();
    k = matB.begin();

    aRows = matA.size();
    aCols = i->size();
    bRows = matB.size();
    bCols = k->size();

    if (aRows != bRows || aCols != bCols) {
        printf("Invalid matrix size for subtraction\n");
        exit(-1);
    }

    for (i = matA.begin(), k = matB.begin(); i != matA.end() && k != matB.end(); ++i, ++k) {
        for (j = i->begin(), l = k->begin(); j != i->end() && l != k->end();
                                                                ++j, ++l) {
            row.push_back(*j - *l);
        }
        matC.push_back(row);
        row.clear();
    }

    return matC;
}

/* Usual method to multiply two square matrices */
vector < vector <int> > squareMatrixMultiplication (vector < vector <int> > matA,
                        vector < vector <int> > matB)
{
    vector < vector <int> > matC;
    vector < vector <int> > a, b, c, d, e, f, g, h, ae, bg, af, bh, ce, dg, cf,
                            dh, c11, c12, c21, c22;
    vector <int> row;
    uint64_t i = 0, j = 0;
    size_t aRows = 0, aCols = 0, bRows = 0, bCols = 0;

    aRows = matA.size();
    if (aRows) {
        aCols = matA[0].size();
    }

    bRows = matB.size();
    if (bRows) {
        bCols = matB[0].size();
    }

    if (!aRows || !bRows || !aCols || !bCols) {
        printf("Invalid matrix size\n");
        exit(1);
    }
   
    if (aRows == 1 && aCols == 1) {
        row.push_back(matA[aRows-1][aCols-1] * matB[bRows-1][bCols-1]);
        matC.push_back(row);
        return matC;
    }

    for (i = 0; i < (aRows/2); ++i) {
        for (j = 0; j < (aCols/2); ++j) {
            row.push_back(matA[i][j]);
        }
        a.push_back(row);
        row.clear();
    }

    for (i = 0; i < (aRows/2); ++i) {
        for (j = (aCols/2); j < aCols; ++j) {
            row.push_back(matA[i][j]);
        }
        b.push_back(row);
        row.clear();
    }

    for (i = (aRows/2); i < aRows; ++i) {
        for (j = 0; j < (aCols/2); ++j) {
            row.push_back(matA[i][j]);
        }
        c.push_back(row);
        row.clear();
    }

    for (i = (aRows/2); i < aRows; ++i) {
        for (j = (aCols/2); j < aCols; ++j) {
            row.push_back(matA[i][j]);
        }
        d.push_back(row);
        row.clear();
    }

    for (i = 0; i < (bRows/2); ++i) {
        for (j = 0; j < (bCols/2); ++j) {
            row.push_back(matB[i][j]);
        }
        e.push_back(row);
        row.clear();
    }

    for (i = 0; i < (bRows/2); ++i) {
        for (j = (bCols/2); j < aCols; ++j) {
            row.push_back(matB[i][j]);
        }
        f.push_back(row);
        row.clear();
    }

    for (i = (bRows/2); i < bRows; ++i) {
        for (j = 0; j < (bCols/2); ++j) {
            row.push_back(matB[i][j]);
        }
        g.push_back(row);
        row.clear();
    }

    for (i = (bRows/2); i < bRows; ++i) {
        for (j = (bCols/2); j < bCols; ++j) {
            row.push_back(matB[i][j]);
        }
        h.push_back(row);
        row.clear();
    }

    ae = squareMatrixMultiplication(a, e);
    bg = squareMatrixMultiplication(b, g);
    af = squareMatrixMultiplication(a, f);
    bh = squareMatrixMultiplication(b, h);
    ce = squareMatrixMultiplication(c, e);
    dg = squareMatrixMultiplication(d, g);
    cf = squareMatrixMultiplication(c, f);
    dh = squareMatrixMultiplication(d, h);

    c11 = matrixAdd(ae, bg);
    c12 = matrixAdd(af, bh);
    c21 = matrixAdd(ce, dg);
    c22 = matrixAdd(cf, dh);

    for (i = 0; i < (aRows/2); ++i) {
        row = c11[i];
        row.insert(row.end(), c12[i].begin(), c12[i].end());
        matC.push_back(row);
        row.clear();
    }

    for (i = 0; i < (aRows/2); ++i) {
        row = c21[i];
        row.insert(row.end(), c22[i].begin(), c22[i].end());
        matC.push_back(row);
        row.clear();
    }

    return matC;
}

/* Strassen's method to multiply two square matrices */
vector < vector <int> > strassensMultiplication (vector < vector <int> > matA,
                        vector < vector <int> > matB)
{
    vector < vector <int> > matC;
    vector < vector <int> > a, b, c, d, e, f, g, h, p1, p2, p3, p4, p5, p6, p7,
                            FminusH, AplusB, CplusD, GminusE, AplusD, EplusH,
                            BminusD, GplusH, AminusC, EplusF, c11, c12, c21, c22;
    vector <int> row;
    uint64_t i = 0, j = 0;
    size_t aRows = 0, aCols = 0, bRows = 0, bCols = 0;

    aRows = matA.size();
    if (aRows) {
        aCols = matA[0].size();
    }

    bRows = matB.size();
    if (bRows) {
        bCols = matB[0].size();
    }

    if (!aRows || !bRows || !aCols || !bCols) {
        printf("Invalid matrix size\n");
        exit(1);
    }
   
    if (aRows == 1 && aCols == 1) {
        row.push_back(matA[aRows-1][aCols-1] * matB[bRows-1][bCols-1]);
        matC.push_back(row);
        return matC;
    }

    for (i = 0; i < (aRows/2); ++i) {
        for (j = 0; j < (aCols/2); ++j) {
            row.push_back(matA[i][j]);
        }
        a.push_back(row);
        row.clear();
    }

    for (i = 0; i < (aRows/2); ++i) {
        for (j = (aCols/2); j < aCols; ++j) {
            row.push_back(matA[i][j]);
        }
        b.push_back(row);
        row.clear();
    }

    for (i = (aRows/2); i < aRows; ++i) {
        for (j = 0; j < (aCols/2); ++j) {
            row.push_back(matA[i][j]);
        }
        c.push_back(row);
        row.clear();
    }

    for (i = (aRows/2); i < aRows; ++i) {
        for (j = (aCols/2); j < aCols; ++j) {
            row.push_back(matA[i][j]);
        }
        d.push_back(row);
        row.clear();
    }

    for (i = 0; i < (bRows/2); ++i) {
        for (j = 0; j < (bCols/2); ++j) {
            row.push_back(matB[i][j]);
        }
        e.push_back(row);
        row.clear();
    }

    for (i = 0; i < (bRows/2); ++i) {
        for (j = (bCols/2); j < aCols; ++j) {
            row.push_back(matB[i][j]);
        }
        f.push_back(row);
        row.clear();
    }

    for (i = (bRows/2); i < bRows; ++i) {
        for (j = 0; j < (bCols/2); ++j) {
            row.push_back(matB[i][j]);
        }
        g.push_back(row);
        row.clear();
    }

    for (i = (bRows/2); i < bRows; ++i) {
        for (j = (bCols/2); j < bCols; ++j) {
            row.push_back(matB[i][j]);
        }
        h.push_back(row);
        row.clear();
    }

    FminusH = matrixSub(f, h);
    AplusB  = matrixAdd(a, b);
    CplusD  = matrixAdd(c, d);
    GminusE = matrixSub(g, e);
    AplusD  = matrixAdd(a, d);
    EplusH  = matrixAdd(e, h);
    BminusD = matrixSub(b, d);
    GplusH  = matrixAdd(g, h);
    AminusC = matrixSub(a, c);
    EplusF  = matrixAdd(e, f);
    
    p1 = strassensMultiplication(a, FminusH);
    p2 = strassensMultiplication(AplusB, h);
    p3 = strassensMultiplication(CplusD, e);
    p4 = strassensMultiplication(d, GminusE);
    p5 = strassensMultiplication(AplusD, EplusH);
    p6 = strassensMultiplication(BminusD, GplusH);
    p7 = strassensMultiplication(AminusC, EplusF);

    c11 = matrixAdd(p5, p4);
    c11 = matrixSub(c11, p2);
    c11 = matrixAdd(c11, p6);

    c12 = matrixAdd(p1, p2);

    c21 = matrixAdd(p3, p4);

    c22 = matrixAdd(p1, p5);
    c22 = matrixSub(c22, p3);
    c22 = matrixSub(c22, p7);

    for (i = 0; i < (aRows/2); ++i) {
        row = c11[i];
        row.insert(row.end(), c12[i].begin(), c12[i].end());
        matC.push_back(row);
        row.clear();
    }

    for (i = 0; i < (aRows/2); ++i) {
        row = c21[i];
        row.insert(row.end(), c22[i].begin(), c22[i].end());
        matC.push_back(row);
        row.clear();
    }

    return matC;
}

int main()
{
    unsigned int aRows = 0, aCols = 0, bRows = 0, bCols = 0, i = 0, j = 0;
    vector < vector <int> > matrixA, matrixB, matrixC;
    vector <int> row;
    int val = 0;
    bool valid = false;

    while (!valid) {
        printf("Enter the number of rows of rows and cols in A matrix: ");
        scanf("%u %u", &aRows, &aCols);
        printf("Enter the number of rows of rows and cols in B matrix: ");
        scanf("%u %u", &bRows, &bCols);
        if ((aRows != aCols) || (bRows != bCols) || (aCols != bRows)) {
            printf("Invalid matrices' size\n");
        } else {
            valid = true;
        }
    }

    printf("Enter A matrix\n");
    for (i = 0; i < aRows; ++i) {
        for (j = 0; j < aCols; ++j) {
            scanf("%d", &val);
            row.push_back(val);
        }
        matrixA.push_back(row);
        row.clear();
    }
    
    printf("Enter B matrix\n");
    for (i = 0; i < bRows; ++i) {
        for (j = 0; j < bCols; ++j) {
            scanf("%d", &val);
            row.push_back(val);
        }
        matrixB.push_back(row);
        row.clear();
    }
    
    matrixC = squareMatrixMultiplication(matrixA, matrixB);
    printf("Matrix C = A . B ...\n");
    displayMatrix(matrixC);

    matrixC = strassensMultiplication(matrixA, matrixB);
    printf("Strassen's method C = A . B ...\n");
    displayMatrix(matrixC);

    return 0;
}
