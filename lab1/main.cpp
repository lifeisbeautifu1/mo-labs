#include <bits/stdc++.h>

#define int long long

using namespace std;

double variant9(double x) {
    return abs(pow(x - 2, 3));
}

double variant12(double x, double y, double z, pair<double, double> offset) {
    return pow(x - offset.first, 2) + cosh(y) + pow(z - offset.second, 4);
}

tuple<double, double, double> fibonacci(double (*func)(double), double a, double b, double ε, double Δ, int S) {

    vector<int> f(2, 1);
    do {
        f.push_back(f[f.size() - 1] + f[f.size() - 2]);
    } while (f.size() <= S);


    int k = 1;

    double x1 = a + f[S - 2] * (b - a) / f[S];
    double first = func(x1);

    double x2 = a + f[S - 1] * (b - a) / f[S];
    double second = func(x2);
    
    cout << x2 - x1 << '\n';
    int count = 2;

    while (true) {
        if (first < second) {
            b = x2;
            x2 = x1;
            second = first;
            x1 = a + f[S - k - 2] * (b - a) / f[S - k];
            k++;
            if (k == S - 2) {
                break;
            }
            first = func(x1);
            count++;

        } else {
            a = x1;
            x1 = x2;
            first = second;
            x2 = a + f[S - k - 1] * (b - a) / f[S - k];
            k++;
            if (k == S - 2) {
                break;
            }
            second = func(x2);
            count++;
        }
        cout << x2 - x1 << '\n';
        
    }
    
    x2 = x1 + ε;
    second = func(x2);
    count++;
    if (first < second) {
        b = x2;
    } else {
        a = x1;
    }
    return {(b + a) / 2, (b - a) / 2 , count};
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
    return {(b + a) / 2, (b - a) / 2 , N};
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
    return {(b + a) / 2, (b - a) / 2 , N};
}

tuple<double, double, double> findMin(double (*func)(double, double, double, pair<double, double>), tuple<double, double, double> start, tuple<double, double, double> p, pair<double, double> offset, const double α) {

    double x = (get<0>(start) - offset.first) * cos(α) - (get<2>(start) - offset.second) * sin(α);
    double y = get<1>(start);
    double z = (get<0>(start) - offset.first) * -sin(α) + (get<2>(start) - offset.second) * cos(α);
    
    int t = 1;
    const double X = get<0>(p);
    const double Y = get<1>(p);
    const double Z = get<2>(p);
    
    double res = func(x, y, z, offset);
    double result = func(x + X, y + Y, z + Z, offset);
    if (result < res) {
        do {
            res = result;
            result = func(x + X * t, y + Y * t, z + Z * t, offset);
            t++;
        } while (result < res);
    } else {
        t = -1;
        result = func(x, y, z, offset);
        do {
            res = result;
            result = func(x + X * t, y + Y * t, z + Z * t, offset);
            t--;
        } while (result < res);
    }
    if (t < 0) {
        t += 2;
    } else {
        t -= 2;
    }
    return {x + X * t, y + Y * t, z + Z * t};
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    
    cin.tie(NULL);
    
    tuple<double, double, double> start(3, 3, 3);
    
    pair<double, double> offset = {1, 1};
    
    tuple<double, double, double> p(1, 1, 1);
    
    const double α = 0;
    
    auto min = findMin(variant12, start, p, offset, α);
    
    cout << "(" << get<0>(min) << "," << get<1>(min) << "," << get<2>(min) << ")" << '\n';
    
 
//    double a = 0, b = 5;
//    double Δ  = 0.001;
//    double ε = 0.0001;

//    cout << "Dichotomy method: " << '\n';
//    tuple<double, double, double> res = dih(variant9, a, b, ε, Δ);
//    cout << "Xmin = " << get<0>(res) << " Δ = " << get<1>(res) << " N = " << get<2>(res) << '\n';
//
//    cout << "Golden section search: " << '\n';
//    tuple<double, double, double> res2 = golden_section_method(variant9, a, b, ε, Δ);
//    cout << "Xmin = " << get<0>(res2) << " Δ = " << get<1>(res2) << " N = " << get<2>(res2) << '\n';
//
//    cout << "Fibonacci-Kiefer search: " << '\n';
//    tuple<double, double, double> res3 = fibonacci(variant9, a, b, ε, Δ, 20);
//    cout << "Xmin = " << get<0>(res3) << " Δ = " << get<1>(res3) << " N = " << get<2>(res3) << '\n';
    return 0;
    
}
