#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<int >heights;
    cin >> n;
    int ans = n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        heights.push_back(t);
    }
    for (int i = 0; i < n; i++) {
        int temp = 0;
        int pre = heights[i];
        int pre1 = 0;
        int pre2 = n - 1;
        // while (heights[pre1] >= heights[i] && pre1 < i) {
        //     pre1++;
        // }
        // while (heights[pre2] >= heights[i] && pre2 > i) {
        //     pre2--;
        // }
        int temp1 = 0, temp2 = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (heights[j] >= pre) {
                temp1++;
            } else {
                pre = heights[j];
            }
            if (heights[pre1] >= heights[i - j] || heights[i - j] >= heights[i]) {
                temp2++;
            } else {
                pre1++;
            }
        }
        temp += min(temp1, temp2);
        temp1 = 0, temp2 = 0;
        pre = heights[i];
        pre1 = 0;
        pre2 = n - 1;
        for (int j = i + 1; j < n; j++) {
            if (heights[j] >= pre) {
                temp1++;
            } else {
                pre = heights[j];
            }
            if (heights[n - j + i] >= heights[pre2] || heights[n - j + i] >= heights[i]) {
                temp2++;
            } else {
                pre2++;
            }
        }
        temp += min(temp1, temp2);
        ans = min(ans, temp);
    }
    cout << ans << endl;
}