#include <iostream>

double average (const int* a, const int n);
std::pair <int, int> MinMax (const int* a, const int n);
int CountLessThanZero (const int* a, const int n);

int main() {
    int n;
    const int cPrecision = 1;
    std::cin >> n;
    int* a {new int[n]};
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cout << std::fixed;
    std::cout.precision(cPrecision);
    std::cout << average(a, n) << "\n";
    std::cout << MinMax(a, n).first << " " << MinMax(a,n).second << "\n";
    std::cout << CountLessThanZero(a, n) << "\n";
    delete[] a;
    a = nullptr;
    return 0;
}
double average (const int* a, const int n) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i];
    }
    double doubleans = ans;
    return doubleans / n;
}
std::pair <int, int> MinMax (const int* a, const int n) {
    std::pair <int, int> ans;
    ans.first = a[0];
    ans.second = a[0];
    for (int i = 1; i < n; i++) {
        ans.first = std::min(ans.first, a[i]);
        ans.second = std::max(ans.second, a[i]);
    }
    return ans;
}
int CountLessThanZero (const int* a, const int n) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            ans++;
        }
    }
    return ans;
}

