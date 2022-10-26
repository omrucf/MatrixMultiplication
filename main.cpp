/*
Name: Omar Yossuf
SID: 900212166
Instructor: Nada GabAllah
Course: CSCE 2203
Section #03
Date: Oct 25th, 2022
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

typedef vector<vector<int> > mtrx;

mtrx MatrixMult(mtrx, mtrx, int &);

mtrx MatrixAdd(mtrx, mtrx);

mtrx MatrixSub(mtrx, mtrx);

void printMatrix(const mtrx);

mtrx createMatrix(int);

mtrx brute(mtrx, mtrx, int &);

int main()
{
    srand((unsigned) time(NULL));

    mtrx 
    M1 = 
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }, 

    M2 = 
    {
        {-1, -2, -3, -4},
        {-5, -6, -7, -8},
        {-9, -10, -11, -12},
        {-13, -14, -15, -16}
    };

    int c = 0;

    mtrx res = MatrixMult(M1, M2, c);

    printMatrix(res);

    // bounus

    cout << "k,size,brute,recursive\n";

    int countM = 0, countB = 0;

    for(int i = 1; i <= 25; i++)
    {
        M1 = createMatrix(i);
        M2 = createMatrix(i);
        
        MatrixMult(M1, M2, countM);
        brute(M1, M2, countB);

        cout << i << ","
             << pow(2, i) << ","
             << countB << ","
             << countM << endl;
    }

    return 0;
}

mtrx MatrixMult(mtrx M1, mtrx M2, int &count)
{
    int size = M1.size();

    mtrx res((size), vector<int> (size));

    if(size == 1)
    {
        res[0][0] = M1[0][0] * M2[0][0];
        count++;
        return res;
    }

    mtrx A((size / 2), vector<int> (size / 2)), P1((size / 2), vector<int> (size / 2));
    mtrx B((size / 2), vector<int> (size / 2)), P2((size / 2), vector<int> (size / 2));
    mtrx C((size / 2), vector<int> (size / 2)), P3((size / 2), vector<int> (size / 2));
    mtrx D((size / 2), vector<int> (size / 2)), P4((size / 2), vector<int> (size / 2));
    mtrx E((size / 2), vector<int> (size / 2)), P5((size / 2), vector<int> (size / 2));
    mtrx F((size / 2), vector<int> (size / 2)), P6((size / 2), vector<int> (size / 2));
    mtrx G((size / 2), vector<int> (size / 2)), P7((size / 2), vector<int> (size / 2));
    mtrx H((size / 2), vector<int> (size / 2));

    for(int i = 0; i < size / 2; i++)
    {
        for(int j = 0; j < size / 2; j++)
        {
            A[i][j] = M1[i][j];
            B[i][j] = M1[i][j + size / 2];
            C[i][j] = M1[i + size / 2][j];
            D[i][j] = M1[i + size / 2][j + size / 2];

            E[i][j] = M2[i][j];
            F[i][j] = M2[i][j + size / 2];
            G[i][j] = M2[i + size / 2][j];
            H[i][j] = M2[i + size / 2][j + size / 2];
        }
    }
    

    P1 = MatrixMult(A, MatrixSub(F, H), count),
    P2 = MatrixMult(MatrixAdd(A, B), H, count),
    P3 = MatrixMult(MatrixAdd(C, D), E, count),
    P4 = MatrixMult(D, MatrixSub(G, E), count),
    P5 = MatrixMult(MatrixAdd(A, D), MatrixAdd(E, H), count),
    P6 = MatrixMult(MatrixSub(B, D), MatrixAdd(G, H), count),
    P7 = MatrixMult(MatrixSub(A, C), MatrixAdd(E, F), count);

    mtrx
    z11((size / 2), vector<int> (size / 2)),
    z12((size / 2), vector<int> (size / 2)),
    z21((size / 2), vector<int> (size / 2)),
    z22((size / 2), vector<int> (size / 2));

    z11 = MatrixAdd(MatrixSub(MatrixAdd(P5, P4), P2), P6),
    z12 = MatrixAdd(P1, P2),
    z21 = MatrixAdd(P3, P4),
    z22 = MatrixSub(MatrixSub(MatrixAdd(P1, P5), P3),P7);

    for(int i = 0; i < size / 2; i++)
    {
        for(int j = 0; j < size / 2; j++)
        {
            res[i][j] = z11[i][j];
            res[i][j + size / 2] = z12[i][j];
            res[i + size / 2][j] = z21[i][j];
            res[i + size / 2][j + size / 2] = z22[i][j];
        }
    }
    return res;

}

mtrx MatrixSub(mtrx M1, mtrx M2)
{
    int size = M1.size();

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            M1[i][j] -= M2[i][j];
    return M1;
}

mtrx MatrixAdd(mtrx M1, mtrx M2)
{
    int size = M1.size();

     for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            M1[i][j] += M2[i][j];
    return M1;
}

void printMatrix(const mtrx m)
{

    int size = m.size();

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
            cout << "\t" << m[i][j] << "\t|";
        cout << endl;
        for(int i = 0; i < size; i++)
            cout <<"-----------------";
        cout << endl;
    }
}

mtrx createMatrix(int size)
{
    size = pow(2, size);
    mtrx M(size, vector<int> (size));

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            M[i][j] = rand() % 200 - 100;

    return M;
}

mtrx brute(mtrx M1, mtrx M2, int &count)
{
    int size = M1.size();

    mtrx M(size, vector<int> (size));

    for(int i = 0; i < size; i++)
        for(int j = 0; j< size; j++)
            for(int k = 0; k < size; k++)
            {
                M[i][j] += M1[i][k] * M2[k][j];
                count++;
            }
    return M;
}