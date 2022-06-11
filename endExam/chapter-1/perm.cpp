//
// Created by DELL on 2021/12/24.
//
#include <bits/stdc++.h>

using namespace std;

void perm(vector<int> arr, int l, int r) {
    if (l == r) {
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else {
        for (int i = l; i < r; ++i) {
            swap(arr[i],arr[l]);
            perm(arr,l+1,r);
            swap(arr[l],arr[i]);
        }
    }

}

int main() {
    int n, m;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        int temp;
        //cin >> temp;
        a.push_back(i);
    }
    perm(a,0, n);
    return 0;
}
