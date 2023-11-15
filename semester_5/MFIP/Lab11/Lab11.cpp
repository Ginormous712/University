#include <iostream>
//#include <cmath>
#include <time.h>
//#include <map>
#include <vector>
using namespace std;

class ElGamalscheme {
private:
    int p;
    int g;
    int message;
    int x;
    int y;
    int a;
    int b;
    vector<int> ciphertext;
    
    long long power(int a, int b) {
        long long result = a;

        for (size_t i = 1; i < b; i++)
        {
            result *= a;
        }
        return result;
    }

    int euclideanAlgorithm(int a, int m) {
        a = a % m;
        for (int x = 1; x < m; x++) {
            if ((a * x) % m == 1) {
                return x;
            }    
        }            
        return 1;
    }
public:
    ElGamalscheme(int p, int g, int message) : p(p), g(g), message(message), x(-1), y(-1), a(-1), b(-1) {
       
    }
    
    void encrypt() {
        cout << "Encrypring...\n";
        cout << "M = " << message << ";\tp = " << p << ";\tg = " << g << ".\n";
        x = rand() % (p - 1) + 1;
        cout << "Choosing random x from [ 1, p - 1 ]: " << x << endl;
        y = power(g, x) % p;
        cout << "Calculating public key\ny = g^x mod p = " << power(g, x) << " % " << p << " = " << y << endl;
        int k = rand() % (p - 1) + 1;
        cout << "Choosing random k from [ 1, p - 1 ]: " << k << endl;
        a = power(g, k) % p;
        cout << "Calculating a - the first number in ciphertext ( a, b )\na = g^k mod p = " 
            << power(g, k) << " % " << p << " = " << a << endl;
        b = (power(y, k) * message) % p;
        cout << "Calculating b - the second number in ciphertext ( a, b )\nb = (y^k * M) mod p = (" 
            << power(y, k) << " * " << message << ") % " << p << " = " << b << endl;
        cout << "Ciphertext ( " << a << " , " << b << " )\n";
    }

    void displayCiphertext() {
        cout << "( " << a << ", " << b << " )\n";
    }
    
    int decrypt() {
        int inv_x = euclideanAlgorithm(power(a, x), p);
        int decrypted_message = (b * inv_x) % p;
        cout << "Decrypting...\n";
        cout << "Calculation of M using formula\n";
        cout << "M = b * (a^(-x)) mod p = " << b << " * (" << inv_x << ") % " << p << " = " << decrypted_message << endl;
        return decrypted_message;
    }
    
};

int main() {
    int p = 11;     // Prime number 
    int g = 2;      // Primitive root mod p
    int M = 5;      // Message

    srand(time(NULL));
    
    ElGamalscheme el = ElGamalscheme(p, g, M);
    el.encrypt();
    cout << el.decrypt();
    return 0;
}