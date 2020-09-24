#include <iostream>
#include "cmath"
#include "fstream"

using namespace std;


void matrixOut(double **a, double *y, int n, ofstream& fOut) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fOut << a[i][j] << "*x" << j;
            if (j < n - 1)
                fOut << " + ";
        }
        fOut << " = " << y[i] << endl;
    }
}

double *gauss(double **a, double *y, int n) {
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
            return 0;
        }
        for (int j = 0; j < n; j++) {
            double res = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = res;
        }
        double res = y[k];
        y[k] = y[index];
        y[index] = res;

        for (int i = k; i < n; i++) {
            double res = a[i][k];
            if (abs(res) < eps) continue;
            for (int j = 0; j < n; j++)
                a[i][j] /= res;
            y[i] /= res;
            if (i == k) continue;
            for (int j = 0; j < n; j++)
                a[i][j] -= a[k][j];
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

void in(double** a, double* y, int n, ifstream& fIn){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fIn >> a[i][j];
        }
    }
    for(int i = 0; i < n;i++){
        fIn >> y[i];
    }
}


void out(double* x, double **a, double *y, int n, ofstream& fOut){

    if(x == 0){
        fOut << "UNDEFINED";
    }else{

        for (int i = 0; i < n; i++)
            fOut << "x" << i << " = " << x[i] << endl;
    }

}
int main() {
    double **a, *y, *x;
    int n;
    ifstream fIn("/Users/macbook/CLionProjects/untitled/Matrix.txt");
    fIn >> n;
    a = new double *[n];
    y = new double[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
    }
    in(a, y, n, fIn);
    fIn.close();
    ofstream fOut("/Users/macbook/CLionProjects/untitled/Answer.txt");
    matrixOut(a, y, n,fOut);
    x = gauss(a, y, n);
    out(x, a, y, n, fOut);
    fOut.close();
    return 0;
}

