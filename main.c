#include <stdio.h>
#include <stdlib.h>

int MMM(int X, int Y, int M, int m) {
  int i, T, Xi, T0, Y0, eta, Xi_Y, eta_M;

  T = 0;

  // Y0 is assigned the least significant bit of Y
  Y0 = Y & 1;

  // Execute loop m times where m is the bitwidth of X
  for (i = 0; i < m; i++) {
    // Xi is assigned the ith bit of X
    Xi = (X >> i) & 1;

    // T0 is assigned the least significant bit of T
    T0 = T & 1;

    // eta is assigned the result of the bitwise XOR of T0 and (Xi & Y0)
    eta = T0 ^ (Xi & Y0);

    // Xi_Y is assigned Y if Xi is non-zero, 0 otherwise
    Xi_Y = Xi ? Y : 0;

    // eta_M is assigned M if eta is non-zero, 0 otherwise
    eta_M = eta ? M : 0;

    // T is updated by adding Xi_Y and eta_M and then right-shifting the result by 1
    T = (T + Xi_Y + eta_M) >> 1;
  }

  // Adjust T to be smaller than M
  while ( T >= M) {
    T -= M;
  }

  return T;
}

int modular_exponentiation(int base, int exponent, int modulus) {
  int result = 1;

  while (exponent > 0) {
    if (exponent % 2 == 1) {
      result = MMM(result, base, modulus, 12);
    }

    base = MMM(base, base, modulus, 12);
    exponent /= 2;
  }

  return result;
}

int main(void) {
  
  int plaintext = 42;
  int encrypted;
  int decrypted;

  // Key generation

  // Choose two large prime numbers P and Q (length 512 - 2048 bits)
  int P = 59;
  int Q = 67;
  // The product of P and Q is used as the modulus
  int PQ = (P - 1) * (Q - 1);

  // Choose a public key exponent E such that 1 < E < PQ, E is not relatively prime to PQ
  int E = 17;

  // Calculate the private key exponent D such that DE = 1 mod PQ
  int D;      // Private key exponent
  // To be calculated using modular inverse

  // Encryption
  encrypted = modular_exponentiation(plaintext, E, PQ);
  printf("Encrypted: %d\n", encrypted);

  // Decryption
  decrypted = modular_exponentiation(encrypted, D, PQ);
  printf("Decrypted: %d\n", decrypted);

  exit(0);
}

