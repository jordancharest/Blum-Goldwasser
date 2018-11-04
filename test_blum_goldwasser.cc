#include <bitset>
#include <cstdlib>
#include <iostream>
#include <tuple>

#include "blum_goldwasser.h"

int main(int argc, char** argv) {
  std::bitset<20> plaintext("10011100000100001100");
  int p = 499;
  int q = 547;
  BG::Cipher cipher(p, q);

  // encrypt
  unsigned long long X0 = 159201;
  std::bitset<20> ciphertext;
  unsigned long long XL; 
  std::tie(ciphertext, XL) = cipher.encrypt(plaintext, X0);
  std::cout << "Ciphertext: " << ciphertext << "\n";

  // decrypt
  std::bitset<20> decrypted = cipher.decrypt(ciphertext, XL);

  // original plaintext and decrypted text should match
  std::cout << "Plaintext: " << plaintext << "\n";
  std::cout << "Decrypted: " << decrypted << "\n";
  assert(plaintext == decrypted);
    
  return EXIT_SUCCESS;
}