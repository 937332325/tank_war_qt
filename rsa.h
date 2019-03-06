#ifndef RSA_H
#define RSA_H

class RSA
{
public:
    int p, q;
    int fn;
    int flag;
    int m, c;
    int d, n, e;
    RSA();
    void encrypt();
    void order(int &in1, int &in2);
    int gcd(int a, int b);
    int extend_euclid(int m, int bin);
    void switch_to_bit(int b, int bin[32]);
    int modular_multiplication(int a, int b, int n);
    void decrypt();
    //m 输入 c输出
};

#endif // RSA_H
