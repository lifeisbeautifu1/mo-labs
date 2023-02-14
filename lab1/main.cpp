#include <bits/stdc++.h>

#define int long long

using namespace std;


double variant9(double x) {
    return abs(pow(x - 2, 3));
}

tuple<double, double, double> fibonacci(double (*func)(double), double a, double b, double ε, double Δ) {
    int N = (b - a) / Δ;
    vector<int> f(2, 1);
    do {
        f.push_back(f[f.size() - 1] + f[f.size() - 2]);
    } while (f[f.size() - 1] < N);
    double S = f.size() - 1;
    double l = (b - a) / f[S];
    int k = 1;
    double x1 = a + l * f[S - 2];
    double first = func(x1);
    double x2 = b - l * f[S - 2];
    double second = func(x2);
    while (k != S - 1) {
        if (first < second) {
            b = x2;
            k++;
            if (k == S - 1) {
                break;
            }
            x2 = x1;
            second = first;
            x1 = a + l * f[S - 1 - k];
            first = func(x1);
        } else {
            a = x1;
            k++;
            if (k == S - 1) {
                break;
            }
            x1 = x2;
            first = second;
            x2 = b - l * f[S - 1 - k];
            second = func(x2);
        }
    }
    x2 = x1 + ε;
    second = func(x2);
    if (first < second) {
        b = x1;
    } else {
        a = x1;
    }
    tuple<double, double, double> res((b + a) / 2, (b - a) / 2 , S);
    return res;
}

double golden_ratio = (sqrt(5) + 1) / 2;

tuple<double, double, double> golden_section_method(double (*func)(double), double a, double b, double ε, double Δ) {
    int N = 0;
    double d = a + (b - a) / golden_ratio;
    double c = b - (b - a) / golden_ratio;
    double first  = func(c);
    double second = func(d);
    N += 2;
    while (b - a  > 2 * Δ) {
        if (first < second) {
            b = d;
            d = c;
            c = b - (b - a) / golden_ratio;
            second = first;
            first = func(c);
            N++;
        } else {
            a = c;
            c = d;
            d = a + (b - a) / golden_ratio;
            first = second;
            second = func(d);
            N++;
        }
    }
    tuple<double, double, double> res((b + a) / 2, (b - a) / 2 , N);
    return res;
}


tuple<double, double, double> dih(double (*func)(double), double a, double b, double ε, double Δ) {
    int N = 0;
    while (b - a > 2 * Δ) {
        double x1 = (a + b) / 2 - ε;
        double x2 = (a + b) / 2 + ε;
        N += 2;
        if (func(x1) > func(x2)) {
            a = x1;
        } else {
            b = x2;
        }
    }
    tuple<double, double, double> res((b + a) / 2, (b - a) / 2 , N);
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double a = 0, b = 5;
    double Δ  = 0.001;
    double ε = 0.0001;
    
    cout << "Dichotomy method: " << '\n';
    tuple<double, double, double> res = dih(variant9, a, b, ε, Δ);
    cout << "Xmin = " << get<0>(res) << " Δ = " << get<1>(res) << " N = " << get<2>(res) << '\n';
    
    cout << "Golden section search: " << '\n';
    tuple<double, double, double> res2 = golden_section_method(variant9, a, b, ε, Δ);
    cout << "Xmin = " << get<0>(res2) << " Δ = " << get<1>(res2) << " N = " << get<2>(res2) << '\n';
    
    cout << "Fibonacci-Kiefer search: " << '\n';
    tuple<double, double, double> res3 = fibonacci(variant9, a, b, ε, Δ);
    cout << "Xmin = " << get<0>(res3) << " Δ = " << get<1>(res3) << " N = " << get<2>(res3) << '\n';
    return 0;
    
}
