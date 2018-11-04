

namespace BG {  // Blum-Goldwasser

class Cipher {
 public:
  Cipher(int p, int q) : p_(p), q_(q) {}
  ~Cipher() = default;

  // moving and copying is forbidden
  Cipher(const Cipher&) = delete;
  Cipher(Cipher&&) = delete;
  Cipher& operator=(const Cipher&) = delete;
  Cipher& operator=(Cipher&&) = delete;

  // encrypt and decrypt





 private:

  // only use const member variables in classes where moving is forbidden
  const int p_;
  const int q_;
  const int X0_;
}

}