//
// Created by DELL on 2021/12/24.
//
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

void rankSort(vector<int> arr) {
    vector<int> rank;
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        rank.push_back(0);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] >= arr[j]) {
                rank[i]++;
            } else {
                rank[j]++;
            }
        }
    }
    vector<int> fin;
    fin.resize(n);
    for (int i = 0; i < n; i++) {
        fin[rank[i]] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        cout << fin[i] << endl;
    }
}

void chooseSort(vector<int> arr) {
    int n = arr.size();
    int maxs = arr[0];
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            maxs = max(maxs, arr[j]);
            if (maxs == arr[j]) {
                index = j;
            }
        }
        swap(arr[index], arr[n - i - 1]);
        index = 0;
        maxs = arr[0];
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << endl;
    }
}

void insertSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << endl;
    }
}

void my(vector<int> arr) {
    vector<int> a = arr;
    int len = arr.size();
    vector<int> b;
    b.resize(len);
    for (int seg = 1; seg < len; seg += seg) {
        for (int start = 0; start < len; start += seg + seg) {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2) {
                b[k++];
            }
        }
    }
}

template<class T>
T Select(T a[], int n, int k) // 驱动程序
{// 返回a[0:n-1]中第k小元素，数组a会被污染
    // 假定a[n]是一个伪最大元素
    if (k < 1 || k > n) return NULL;
    return select(a, 0, n - 1, k);
}

template<class T>
T select(T a[], int l, int r, int k) {
    if (l >= r) return a[l];
    int i = l, j = r + 1;
    T pivot = a[l];
    while (true) {// 把左侧>=pivot和右侧<=pivot的元素进行交换
        do { i++; } while (a[i] < pivot);
        do { j--; } while (a[j] > pivot);
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    if (j - l + 1 == k) return pivot;
    // 设置pivot
    a[l] = a[j];
    a[j] = pivot;
    if (j - l + 1 < k) return select(a, j + 1, r, k - j + l - 1);
    return select(a, l, j - 1, k);
}


int find(vector<int> arr, int l, int r, int k) {
    if (l >= r) {
        return arr[l];
    }
    int pivot = arr[l];
    int leftCursor = l;
    int rightCursor = r + 1;
    while (true) {
        do {
            leftCursor++;
        } while (arr[leftCursor] < pivot);
        do {
            rightCursor--;
        } while (arr[rightCursor] > pivot);
        if (leftCursor >= rightCursor) {
            break;
        }
        swap(arr[leftCursor], arr[rightCursor]);
    }
    arr[l] = arr[rightCursor];
    arr[rightCursor] = pivot;
    if (rightCursor - l + 1 == k) {
        //cout << arr[rightCursor] << endl;
        return arr[rightCursor];
    }
    if (rightCursor - l + 1 > k) {
        return find(arr, l, rightCursor - 1, k);
    }
    if (rightCursor - l + 1 < k) {
        return find(arr, rightCursor + 1, r, k - rightCursor + l - 1);
    }
}


void Merge(vector<int> &Array, int front, int mid, int end) {
    vector<int> LeftSubArray(Array.begin() + front, Array.begin() + mid + 1);
    vector<int> RightSubArray(Array.begin() + mid + 1, Array.begin() + end + 1);
    int idxLeft = 0, idxRight = 0;
    LeftSubArray.insert(LeftSubArray.end(), numeric_limits<int>::max());
    RightSubArray.insert(RightSubArray.end(), numeric_limits<int>::max());

    for (int i = front; i <= end; i++) {
        if (LeftSubArray[idxLeft] < RightSubArray[idxRight]) {
            Array[i] = LeftSubArray[idxLeft];
            idxLeft++;
        } else {
            Array[i] = RightSubArray[idxRight];
            idxRight++;
        }
    }
}

void MergeSort(vector<int> &Array, int front, int end) {
    if (front >= end)
        return;
    int mid = (front + end) / 2;
    MergeSort(Array, front, mid);
    MergeSort(Array, mid + 1, end);
    Merge(Array, front, mid, end);
}

void mergeSort(vector<int> arr) {
    vector<int> a = arr;
    vector<int> b;
    int len = arr.size();
    b.resize(a.size());
    for (int seg = 1; seg < len; seg += seg) {
        for (int start = 0; start < len; start += seg + seg) {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2) {
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            }
            while (start1 < end1) {
                b[k++] = a[start1++];
            }
            while (start2 < end2) {
                b[k++] = a[start2++];
            }
        }
        vector<int> temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        for (int i = 0; i < len; ++i) {
            b[i] = a[i];
        }
        b = a;
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }
}

void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j + 1] <= arr[j]) {
                swap(arr[j + 1], arr[j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << endl;
    }
}

void QuickSort(vector<int> &arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int ll = l;
    int rr = r;
    int middle = arr[(l + r) / 2];
    do {
        while (arr[ll] < middle) {
            ll++;
        }
        while (arr[rr] > middle) {
            rr--;
        }
        if (ll <= rr) {
            swap(arr[ll], arr[rr]);
            ll++;
            rr--;
        }
    } while (ll <= rr);
    if (l < rr) {
        QuickSort(arr, l, rr);
    }
    if (ll < r) {
        QuickSort(arr, ll, r);
    }
}

void quickSort(vector<int> &arr, int l, int r) {
    int middle = arr[l];
    if (l >= r) {
        return;
    }
    int ll = l;
    int rr = r + 1;
    while (true) {
        do {
            ll++;
        } while (arr[ll] < middle);
        do {
            rr--;
        } while (arr[rr] > middle);
        if (ll >= rr) {
            break;
        }
        swap(arr[ll], arr[rr]);
    }
    arr[l] = arr[rr];
    arr[rr] = middle;
    quickSort(arr, l, rr - 1);
    quickSort(arr, ll + 1, r);
}


int main() {
    int n, m;
    cin >> n;
    vector<int> a;
    //int a[n];
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        //a[i] = temp;
        a.push_back(temp);
    }
    //rankSort(a);
    //chooseSort(a);
    //bubbleSort(a);
    //insertSort(a);
    quickSort(a, 0, n - 1);
    //mergeSort(a);
    //cout<<find(a, 0, n - 1, 4);
    /*for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }*/
    return 0;
}

