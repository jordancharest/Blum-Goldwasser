#ifndef BLUM_GOLDWASSER_CIPHER_H
#define BLUM_GOLDWASSER_CIPHER_H

#include <bitset>
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdlib>
#include <tuple>

namespace mp = boost::multiprecision;

// ----------------------------------------------------------------------------
int mod_inverse(int a, int mod) {
  int i = ceil((mod-1)/a);
  for (; i < mod; ++i) {
    if ((a * i) % mod == 1)
      return i;
  }
  return 1;
}

// ============================================================================
namespace BG {  // Blum-Goldwasser 
class Cipher {
 public:
  Cipher(int p, int q) : p_(p), q_(q) { N_ = p_ * q_; }
  ~Cipher() = default;

  // moving and copying is forbidden
  Cipher(const Cipher&) = delete;
  Cipher(Cipher&&) = delete;
  Cipher& operator=(const Cipher&) = delete;
  Cipher& operator=(Cipher&&) = delete;

  // encrypt and decrypt
  template <std::size_t size>
  std::tuple<std::bitset<size>, unsigned long long> encrypt(
                                                    std::bitset<size> plaintext, 
                                                    unsigned long long X);
  template <std::size_t size>
  std::bitset<size> decrypt(std::bitset<size> ciphertext, int X);

 private:
  // decryption helper - arbitrary precision modular arithmetic
  int compute_r(int prime, int len, int y);

  // only use const member variables in classes where moving is forbidden
  const int p_;
  const int q_;
  int N_;
};

// Class Definitions
// ----------------------------------------------------------------------------
template <std::size_t size>
std::tuple<std::bitset<size>, unsigned long long> Cipher::encrypt(
                                                  std::bitset<size> plaintext, 
                                                  unsigned long long X) {
  if (X < 1 || X >= N_){
    std::cerr << "Invalid X0. Cannot encrypt.\n";
    return std::make_tuple(NULL, NULL);
  }

  // Blum Blum Shub random bit generation
  std::bitset<size> random_bits;
  for (int i = 0; i < size; ++i) {
    random_bits[i] = X & 1;
    X = (X * X) % N_;
  }

  std::bitset<size> ciphertext = plaintext ^ random_bits;
  return std::make_tuple(ciphertext, X);
}

// ----------------------------------------------------------------------------
template <std::size_t size>
std::bitset<size> Cipher::decrypt(std::bitset<size> ciphertext, int XL) {

  // calculate the X0 that the encryptor used
  int rp = this->compute_r(p_, ciphertext.size(), XL);
  int rq = this->compute_r(q_, ciphertext.size(), XL);
  unsigned long long X;
  X = ((q_ * mod_inverse(q_, p_)) * rp + p_ * mod_inverse(p_, q_) * rq) % N_;

  // Use X0 to initiate Blum Blum Shub random bit generation
  std::bitset<size> random_bits;
  for (int i = 0; i < size; ++i) {
    random_bits[i] = X & 1;
    X = (X * X) % N_;
  }

  return ciphertext ^ random_bits;
}

// ----------------------------------------------------------------------------
int Cipher::compute_r(int prime, int len, int y) {
  mp::cpp_int temp = ((prime + 1)/4);
  mp::cpp_int exp = mp::pow(temp, len);

  mp::cpp_int r = mp::powm(mp::cpp_int(y), exp, prime);
  return static_cast<int>(r);
}
} // namespace BG

#endif // BLUM_GOLDWASSER_CIPHER_H