#include <stdio.h>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

string hexConvert(string, int, int, int);

char *mystrrev(char *temp1);

int main() {
    int B, b, p;
    string a;
    //原数的进制
    scanf("%d", &B);
    //后来的进制
    scanf("%d", &b);
    cin >> a;
    p = 8;
    string res = hexConvert(a, B, b, p);
    cout << res << endl;
    return 0;
}

string hexConvert(string num, int begin, int end, int precisition)//将浮点数num从begin进制转化成end进制(36进制以内)
{
    //先转化成十进制便于计算
    int int_D = 0;//十进制整数部分
    double dec_D = 0;//十进制小数部分
    double indexf = 1.0 / begin;//小数部分相应位的权重
    int isInt = 1, i = 0;
    while (i < num.length()) {
        if (num[i] == '.')//找到小数点，后面的是小数位
        {
            isInt = 0;
            i++;
            continue;
        }
        if (isInt)//处理整数位
        {
            int_D *= begin;
            if (num[i] >= '0' && num[i] <= '9')
                int_D += (num[i] - '0');
            if (num[i] >= 'a' && num[i] <= 'z')
                int_D += (num[i] - 'a' + 10);
            if (num[i] >= 'A' && num[i] <= 'Z')
                int_D += (num[i] - 'A' + 10);
        } else//处理小数位
        {
            if (num[i] >= '0' && num[i] <= '9')
                dec_D += indexf * (num[i] - '0');
            if (num[i] >= 'a' && num[i] <= 'z')
                dec_D += indexf * (num[i] - 'a' + 10);
            indexf /= begin;
        }
        i++;
    }
    //将转化好的十进制转化为目标进制
    char *ans;
    string int_T;
    string dec_T;
    int_T.resize(256);
    dec_T.resize(256);
    int int_T_index = 0, dec_T_index = 0;
    int tmp;
    int u = int_D;
    while (int_D)//处理整数位
    {
        tmp = int_D % end;
        if (tmp >= 0 && tmp <= 9)
            int_T[int_T_index++] = '0' + tmp;
        if (tmp >= 10 && tmp <= 35)
            int_T[int_T_index++] = 'a' + tmp - 10;
        int_D /= end;
    }
    int_T[int_T_index] = 0;
    char *temp_1 = const_cast<char *>(int_T.data());

    ans = mystrrev(temp_1);//整数部分是先获取的低位后获取的高位，所以要反转
    if (!u) strcat(ans, "0");

    if (dec_D) strcat(ans, ".");

    while (dec_D) {
        tmp = dec_D * end;
        if (tmp >= 0 && tmp <= 9)
            dec_T[dec_T_index++] = '0' + tmp;
        if (tmp >= 10 && tmp <= 35)
            dec_T[dec_T_index++] = 'a' + tmp - 10;
        dec_D *= end;
        dec_D -= (int) dec_D;
        if (dec_T_index == precisition)break;
    }
    dec_T[dec_T_index] = 0;
    const char *dec_tb = dec_T.data();
    strcat(ans, dec_tb);
    string s = string(ans);
    return s;
}

char *mystrrev(char *s) {
    /* h指向s的头部 */
    char *h = s;
    char *t = s;
    char ch;

    /* t指向s的尾部 */
    while (*t++) {};
    t--;    /* 与t++抵消 */
    t--;    /* 回跳过结束符'\0' */

    /* 当h和t未重合时，交换它们所指向的字符 */
    while (h < t) {
        ch = *h;
        *h++ = *t;    /* h向尾部移动 */
        *t-- = ch;    /* t向头部移动 */
    }

    return (s);
}

