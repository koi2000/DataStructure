//
// Created by DELL on 2022/1/2.
//
#include <bits/stdc++.h>

using namespace std;
vector<int> weight;
vector<int> value;
int num;

int f(int i, int cap) {
    if (i == num) {
        return cap >= weight[i] ? value[i] : 0;
    }
    if (weight[i] > cap) {
        return f(i + 1, cap);
    }
    return max(f(i + 1, cap), f(i + 1, cap - weight[i]) + value[i]);
}

int main() {
    int c;
    cin >> c;
    cin >> num;
    num--;

    for (int i = 0; i <= num; ++i) {
        int temp;
        cin >> temp;
        weight.push_back(temp);
    }
    for (int i = 0; i <= num; ++i) {
        int temp;
        cin >> temp;
        value.push_back(temp);
    }
    cout << f(0, c);
    return 0;
}
