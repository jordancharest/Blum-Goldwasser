#include <bitset>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>


#include "blum_goldwasser.h"


int main(int argc, char** argv) {
  std::bitset<20> plaintext(std::string("10011100000100001100"));
  int p = 499;
  int q = 547;
  BG::Cipher cipher(p, q);

  // encrypt
  unsigned long long X0 = 159201;
  std::bitset<20> ciphertext;
  unsigned long long XL; 
  std::tie(ciphertext, XL) = cipher.encrypt(plaintext, X0);
  std::cout << "Ciphertext: " << ciphertext << "\n";
  std::cout << "XL: " << XL << "\n";


  // decrypt
  cipher.decrypt(ciphertext, XL);
    




  return EXIT_SUCCESS;
}