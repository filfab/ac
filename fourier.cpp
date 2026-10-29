#include <iostream>
#include <vector>
#include <complex>
// #include <cmath>

using namespace std;

const double PI = acos(-1.0);


vector<complex<double>> DFT(const vector<complex<double>>& a) {
    int n = a.size();
    vector<complex<double>> wynik(n);

    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            double kat = -2.0 * PI * k * j / n;
            complex<double> w(cos(kat), sin(kat));
            wynik[k] += a[j] * w;
        }
    }

    return wynik;
}


vector<complex<double>> IDFT(const vector<complex<double>>& a) {
    int n = a.size();
    vector<complex<double>> wynik(n);

    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            double kat = 2.0 * PI * k * j / n;
            wynik[k] += a[j] * complex<double>(cos(kat), sin(kat));
        }
        wynik[k] /= (double)n;
    }

    return wynik;
}


vector<complex<double>> splot(const vector<complex<double>>& a, const vector<complex<double>>& b) {
    int n = max(a.size(), b.size());

    vector<complex<double>> A(n), B(n);

    for (int i = 0; i < (int)a.size(); i++)
        A[i] = a[i];

    for (int i = 0; i < (int)b.size(); i++)
        B[i] = b[i];

    A = DFT(A);
    B = DFT(B);

    for (int i = 0; i < n; i++)
        A[i] *= B[i];

    return IDFT(A);
}


int main() {
    int n;
    cin >> n;

    vector<complex<double>> a(n);

    for (int i = 0; i < n; i++) {
        double x;
        cin >> x;
        a[i] = complex<double>(x, 0);
    }

    vector<complex<double>> wynik = DFT(a);

    for (int i = 0; i < n; i++) {
        cout << wynik[i] << '\n';
    }

    return 0;
}