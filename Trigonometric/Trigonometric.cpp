#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>

using namespace std;

struct Eq {
    double x = 0;
    double y = 0;
};

void strokeWrap(string& strokeX, string& strokeY, vector <Eq>& equations) {
    while (strokeX.find(" ") != -1) {
        Eq buff = { stod(strokeX.substr(0, strokeX.find(" "))), stod(strokeY.substr(0, strokeY.find(" "))) };
        strokeX.erase(0, strokeX.find(" ") + 1);
        strokeY.erase(0, strokeY.find(" ") + 1);
        equations.push_back(buff);
    }
}

double inputX() {
    cout << "Input X: ";
    double x;
    cin >> x;
    return x;
}

double cosCoef(int& n, vector <Eq>& equations, int j) {
    double sum = 0;
    for (int i = 0; i < ((n - 1) / 2); i++) {
        sum += equations[i].y * cos(2 * M_PI * i * j / (double)n);
    }
    return 1.0 / ((n - 1) / 2.0) * sum;
}

double sinCoef(int& n, vector <Eq>& equations, int j) {
    double sum = 0;
    for (int i = 0; i < ((n - 1) / 2); i++) {
        sum += equations[i].y * sin(2 * M_PI * i * j / (double)n);
    }
    return 1.0 / ((n - 1) / 2.0) * sum;
}

double cosSeries(double& x, int& n, vector <Eq>& equations, double& T) {
    double sum = 0;
    for (int i = 1; i < n; i++) { // ???
        sum += cosCoef(n, equations, i) * cos(2 * M_PI * i * (x - equations[0].x) / T);
    }
    return sum;
}

double sinSeries(double& x, int& n, vector <Eq>& equations, double& T) {
    double sum = 0;
    for (int i = 1; i < n; i++) { // ???
        sum += sinCoef(n, equations, i) * sin(2 * M_PI * i * (x - equations[0].x) / T);
    }
    return sum;
}

double cosZeroCoef(int& n, vector <Eq>& equations) {
    double sum = 0;
    for (int i = 0; i < ((n - 1) / 2); i++) {
        sum += equations[i].y;
    }
    return 1.0 / ((n - 1) / 2.0) * sum;
}

int main()
{
    double x = inputX();
    fstream matrixData("Polynomial.txt");
    vector <Eq> equations;

    while (!matrixData.eof()) {
        string buffX;
        string buffY;
        getline(matrixData, buffX);
        getline(matrixData, buffY);
        strokeWrap(buffX, buffY, equations);
    }

    int n = equations.size();
    double T = equations[equations.size() - 1].x - equations[0].x;

    cout << "Y(" << x << ") = " << cosZeroCoef(n, equations) + cosSeries(x, n, equations, T) + sinSeries(x, n, equations, T);
}
