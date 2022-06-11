//
// Created by DELL on 2022/1/2.
//
#include <bits/stdc++.h>

using namespace std;
int n;

void output(int **kay, int i, int j);


void allPairs(int **c, int **kay) {

    /*for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <=n ; ++j) {
            c[i][j]=a[i][j];
            kay[i][j]=0;
        }
    }*/
    for (int i = 1; i <= n; ++i) {
        c[i][i] = 0;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (c[i][k] != 0 && c[k][j] != 0 && (c[i][j] == 0 || c[i][j] > c[i][k] + c[k][j])) {
                    c[i][j] = c[i][k] + c[k][j];
                    kay[i][j] = k;
                }
            }
        }
    }
}

template<class T>
void outputPath(T **c, int **kay, T noEdge, int i, int j) {
    if (c[i][j] == noEdge) {
        cout << "no path" << endl;
    } else {
        cout << "path is" << endl;
        output(kay, i, j);
        cout << endl;
    }
}

void output(int **kay, int i, int j) {
    if (i == j) {
        return;
    }
    if (kay[i][j] == 0) {
        cout << j << endl;
    } else {
        output(kay, i, kay[i][j]);
        output(kay, kay[i][j], j);
    }
}

int main() {
    int q, b, c, d;
    cin >> q >> b >> c >> d;
    n = q;
    int **a = new int *[q + 1];

    for (int i = 0;i < q + 1; ++i) {
        a[i] = new int[q + 1];
        for (int j = 0; j < q + 1; ++j) {
            a[i][j] = 0;
        }
    }
    int **kay = new int *[q + 1];

    for (int i = 0; i < q + 1; ++i) {
        kay[i] = new int[q + 1];
        for (int j = 0; j < q + 1; ++j) {
            kay[i][j] = 0;
        }
    }
    for (int i = 0; i < 10; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 0) {
            a[y][z] = 1;
            a[z][y] = 1;
        } else {
            a[y][z] = 0;
            a[z][y] = 0;
        }
    }
    allPairs(a, kay);
    outputPath(a, kay, 0, 4, 5);
    return 0;
}
