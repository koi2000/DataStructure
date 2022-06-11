#include<bits/stdc++.h>

using namespace std;
struct ListNode {
    int val;
    struct ListNode *next;
};

ListNode *create(int a[], int n);

ListNode *sort(struct ListNode *head);

void output(ListNode *head);

ListNode *insert(ListNode *head, int n);

ListNode *remove(ListNode *head, int n);

int main() {
    int a[10000];
    int n, ins, rm;
    cin >> n >> ins >> rm;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ListNode *list = create(a, n);
    output(list);
    list = sort(list);
    output(list);
    list = insert(list, ins);
    output(list);
    list = remove(list, rm);
    output(list);
    return 0;
}


ListNode *create(int a[], int n) {
    int i;
    struct ListNode *head, *ne, *end;
    head = NULL;
    for (i = 0; i < n; i++) {
        ne = (struct ListNode *) malloc(sizeof(struct ListNode));
        ne->val = a[i];
        if (i == 0) {
            head = ne;
            end = ne;
        } else {
            end->next = ne;
            ne->next = NULL;
            end = ne;
        }
    }
    return head;
    //TODO:填写创建链表的函数
}

ListNode *sort(struct ListNode *head) {
    int j, i, k, t;
    struct ListNode *p;
    j = 1;
    for (k = 0; k < j + 1; k++) {
        p = head;
        for (i = 0; p->next != NULL; i++) {
            if (p->val > p->next->val) {
                t = p->next->val;
                p->next->val = p->val;
                p->val = t;
            }
            p = p->next;
        }
        j = i;
    }
    return head;
    //TODO：填写链表排序的函数
}

void output(ListNode *head) {
    while (head != NULL) {
        printf("%d\n", head->val);
        head = head->next;
    }
    //TODO：填写输出每个节点值的函数
}

ListNode *insert(ListNode *head, int n) {
    struct ListNode *p, *q, *k;
    p = head;
    while (p != NULL) {
        if (head->val >= n) {
            k = (struct ListNode *) malloc(sizeof(struct ListNode));
            head = k;
            k->val = n;
            k->next = p;
            break;
        }
        q = p->next;
        if (n >= p->val && n <= q->val) {
            k = (struct ListNode *) malloc(sizeof(struct ListNode));
            p->next = k;
            k->val = n;
            k->next = q;
            break;
        }
        if (q == NULL) {
            k = (struct ListNode *) malloc(sizeof(struct ListNode));
            p->next = k;
            k->val = n;
            k->next = NULL;
            break;
        }
        p = q;
    }
    return head;
    //TODO：填写向有序链表插入值的函数
}

ListNode *remove(ListNode *head, int n) {
    struct ListNode *p, *q, *h;
    p = head;
    h = head;
    q = p->next;
    while (p != NULL) {
        if (p == head) {
            if (p->val == n) {
                head = q;
                p->next = NULL;
                free(p);
                break;
            }
        }
        if (p->val == n) {
            h->next = q;
            p->next = NULL;
            free(p);
            break;
        }
        h = p;
        p = q;
        q = p->next;
    }
    return head;
    //TODO:填写删除链表中指定值的函数
}