#include "rsa.h"

RSA::RSA()
{
    p = 61;
    q = 67;
    e = 17;
    fn = (p - 1) * (q - 1);
    n = p * q;
    d = (extend_euclid(fn, e) + fn) % fn;
    flag = 1;
}
void RSA::encrypt() {
    c = modular_multiplication(m, e, n);
}
void RSA::decrypt() {
    m = modular_multiplication(c, d, n);
}
/* 十进制转化为二进制数组 */
void RSA::switch_to_bit(int b, int bin[32]) {
    int n = 0;
    while (b > 0) {
        bin[n] = b % 2;
        n++;
        b /= 2;
    }
}
/* 模幂 */
int RSA::modular_multiplication(int a, int b, int n) {
    int f = 1;
    int bin[32];
    switch_to_bit(b, bin);
    for (int i = 31; i >= 0; i--) {
        f = (f * f) % n;
        if (bin[i] == 1) {
            f = (f * a) % n;
        }
    }
    return f;
}
/* 将两个数排序，大的在前面*/
void RSA::order(int &in1, int &in2) {
    int a = (in1 > in2 ? in1 : in2);
    int b = (in1 < in2 ? in1 : in2);
    in1 = a;
    in2 = b;
}
/* 求最大公约数 */
int RSA::gcd(int a, int b) {
    order(a, b);
    int r;
    if (b == 0) {
        return a;
    }
    else {
        while (true) {
            r = a % b;
            a = b;
            b = r;
            if (b == 0) {
                return a;
                break;
            }
        }
    }
}
/* 求乘法逆元 */
int RSA::extend_euclid(int m, int bin) {
    order(m, bin);
    int a[3], b[3], t[3];
    a[0] = 1, a[1] = 0, a[2] = m;
    b[0] = 0, b[1] = 1, b[2] = bin;
    if (b[2] == 0) {
        return a[2] = gcd(m, bin);
    }
    if (b[2] == 1) {
        return b[2] = gcd(m, bin);
    }
    while (true) {
        if (b[2] == 1) {
            return b[1];
            break;
        }
        int q = a[2] / b[2];
        for (int i = 0; i<3; i++) {
            t[i] = a[i] - q * b[i];
            a[i] = b[i];
            b[i] = t[i];
        }
    }
}

