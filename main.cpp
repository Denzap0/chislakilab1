#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;


void matrixOut(vector <vector <double>> a, vector <double> y, int n, ofstream &fOut) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fOut << a[i][j] << "*x" << j;
            if (j < n - 1)
                fOut << " + ";
        }
        fOut << " = " << y[i] << endl;
    }
}

double *sle(vector<vector <double>> a, vector <double> y, int n) {
    double *x, max;
    int k, index;
    const double eps = 0.000001;
    x = new double[n];
    k = 0;
    while (k < n) {
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(a[i][k]) > max) {
                max = abs(a[i][k]);
                index = i;
            }
        }
        if (max < eps) {
            return nullptr;
        }
        for (int j = 0; j < n; j++) {
            swap(a[k][j], a[index][j]);
        }
        swap(y[k], y[index]);

        for (int i = k; i < n; i++) {
            double res = a[i][k];
            if (abs(res) < eps) continue;
            for (int j = 0; j < n; j++)
                a[i][j] /= res;
            y[i] /= res;
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                a[i][j] -= a[k][j];
            }
            y[i] -= y[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; k--) {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

void in(vector <vector <double>> &a, vector <double> &y, int n, ifstream &fIn) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (j < n) {
                fIn >> a[i][j];

            } else {
                fIn >> y[i];
            }
        }
    }
}


void out(double *x, vector <vector <double>> a, vector <double> y, int n, ofstream &fOut) {

    if (x == nullptr) {
        fOut << "UNDEFINED";
    } else {

        for (int i = 0; i < n; i++)
            fOut << "x" << i << " =" << x[i] << endl;
    }

}

int main() {
    double *x;
    int n;
    ifstream fIn("Matrix.txt");
    fIn >> n;
    vector<vector<double>> a1(n,vector<double>(n,n) );
    vector<double> a2;
    in(a1, a2, n, fIn);
    fIn.close();
    ofstream fOut("Answer.txt");
    matrixOut(a1, a2, n, fOut);
    x = sle(a1, a2, n);
    out(x, a1, a2, n, fOut);
    fOut.close();
    delete[] x;
    return 0;
}

