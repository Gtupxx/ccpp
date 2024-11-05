#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int>v{1,2,3,4,5};
    int &m = v[0];
    cout << &m << endl
         << &v[1];
}