#include <bitset>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/math/special_functions/pow.hpp>

// #include <boost/math/special_functions/mpow.hpp>
#include <cstdlib>
#include <tuple>


namespace mp = boost::multiprecision;

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
  void decrypt(std::bitset<size> ciphertext, unsigned long long X);

  // decryption helper
  mp::cpp_int compute_r(int prime, int len, int y);

 private:

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
void Cipher::decrypt(std::bitset<size> ciphertext, unsigned long long X) {
  mp::cpp_int rp = this->compute_r(p_, ciphertext.size(), X);
  mp::cpp_int rq = this->compute_r(q_, ciphertext.size(), X);

  std::cout << "rp: " << rp << "\n";
  std::cout << "rq: " << rq << "\n";

}

// ----------------------------------------------------------------------------
mp::cpp_int Cipher::compute_r(int prime, int len, int y) {

  mp::cpp_int temp = ((prime + 1)/4);
  mp::cpp_int exp = mp::pow(temp, len);

  mp::cpp_int r = mp::powm(mp::cpp_int(y), exp, prime);
  return r;
}


// // right to left binary method of modular exponentiation
// mp::cpp_int modular_exponentiation(mp::cpp_int base, mp::cpp_int exp, mp::cpp_int mod) {
//   if (mod == 1) return 0;
//   mp::cpp_int result = 1;
//   base = base % mod;
//   while (exp > 0) {
//     if (exp & 1 == 1)
//       result = (result * base) % mod;

//     exp >>= 1;
//     base = (base * base) % mod;
//   }

//   return result;
// }





// function modular_pow(base, exponent, modulus)
//     if modulus = 1 then return 0
//     Assert :: (modulus - 1) * (modulus - 1) does not overflow base
//     result := 1
//     base := base mod modulus
//     while exponent > 0
//         if (exponent mod 2 == 1):
//            result := (result * base) mod modulus
//         exponent := exponent >> 1
//         base := (base * base) mod modulus
//     return result









} // namespace BG