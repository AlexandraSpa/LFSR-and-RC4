#include <iostream>
using namespace std;
int state[229], L;
void lshift()
{
    int i;
    for (i = 0; i < (L-1); i++)
    {
        state[i] = state[i + 1];
    }
    
}
int feedback(int k1, int k2, int k3) { //x^m + x^k1 + x^k2 + x^k3 + 1 primitive polynomial
    return (state[L-1] + state[k1 - 1] + state[k2 - 1] + state[k3 - 1])%2;
}
int feedback(int k) { //x^m + x^k + 1 primitive polynomial
    return (state[L - 1] + state[k - 1])%2;
}

void lfsrGenerator(int k1, int k2, int k3) {
    int outputbits[1024], newbit;
    
    for (int i = 0; i < 1024; i++) {
        outputbits[i++] = state[0];
        newbit = feedback(k1, k2, k3);
        lshift();
        state[L - 1] = newbit;
    }
    for (int i = 0; i < 1024; i++)
    {
        cout << outputbits[i]<<" ";
    }

}

void lfsrGenerator(int k) {
    int outputbits[1024], newbit;

    for (int i = 0; i < 1024; i++) {
        outputbits[i] = state[0];
        newbit = feedback(k);
        lshift();
        state[L - 1] = newbit;
    }
    for (int i = 0; i < 1024; i++)
    {
        cout << outputbits[i] << " ";
    }

}

//Crytosystem RC4

int K[16], l, S0[256], i, j, S[256], message[100], n, Z[300], ciphertext[100], decryptedMessage[100];

//output: initial state: (0, 0, S0)
void init() { //KSA
    for (int i = 0; i < 256; i++)
    {
        S0[i] = i;
    }
    j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S0[i] + K[i % l])%256;
        swap(S0[i], S0[j]);
    }
    i = j = 0;
    for (int i = 0; i < 256; i++) {
        S[i] = S0[i];
    }
}

int trans() { //keystream generator PRGA
    i= (i+1)%256;
    j = (j + S[i])%256;
    swap(S[i], S[j]);
    return S[(S[i] + S[j]) % 256]; //byte returning
}

void rc4KeystreamGenerate(int n) {
    init();
    int index = 0;
    while (n) {
        Z[index++] = trans(); //keystream in bytes
        n--;
    }
}
void rc4Encryption(int n) {
    rc4KeystreamGenerate(n);
    for (int i = 0; i < n; i++)
    {
        ciphertext[i] = message[i] ^ Z[i];
    }

}
void rc4Decryption() { //avem deja generat keystream ul Z, de la criptare
    //rc4KeystreamGenerate(n);
    for (int i = 0; i < n; i++)
    {
        decryptedMessage[i] = ciphertext[i] ^ Z[i];
    }

}

char input[100], input2[100]; //folositi pentru citirea de la tastatura in format char
int main()
{
    /*cout << "L: ";
    cin >> L;
    cout << endl;
    cout << "Enter the delay elements: ";
    cout << endl;
    for (int i = 0; i < L; i++)
    {
        cin >> state[i];
    }
    lfsrGenerator(1); //am ales 1 pentru exemplul dat, cu m=4;  */

    cout << endl;
    cout << "Message input: ";
    cin.getline(input, 100);
    n = strlen(input);
    for (int i = 0; i < n; i++) {
        message[i]= (int)(input[i]);
    }
    cout << "Key input: ";
    cin.getline(input2, 100);
    l = strlen(input2);
    for (int i = 0; i < l; i++) {
        K[i]= (int)(input2[i]);
    }
    cout << "Encrypted message: ";
    rc4Encryption(n);
    for (int i = 0; i < n; i++) {
        cout << (char)ciphertext[i] << " ";
    }
    cout << endl;
    cout << "Decrypted message: ";
    rc4Decryption(); //avem deja generat keystream ul Z, de la criptare
    for (int i = 0; i < n; i++) {
        cout << (char)decryptedMessage[i] << " ";
    }

}
