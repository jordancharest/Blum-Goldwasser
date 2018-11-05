# Blum-Goldwasser

The Blum-Goldwasser cryptosystem is a public-key or asymmetric encryption algorithm that is semantically secure, meaning that no meaningful information can be gained about the plaintext from the ciphertext. If Bob wants to send Alice a message, Alice generates a public key by picking two coprime numbers, `p` and `q` whose product is a Blum integer. For this example, the numbers are `p = 499` and `q = 547`, so the public key `N` is `p * q = 272,953 = N`. Alice sends the public key to Bob, which may done over an unsecure connection.

Bob chooses a secret number `X` such that `1 < X < N`. He then uses `X` and `N` in the Blum Blum Shub random bit generation algorithm to generate a random stream of bits with the same length as the plaintext. During that process, the value of `X` is modified for every new bit that is generated. He `xor`'s the random stream of bits with the plaintext to generate the ciphertext. He then sends the ciphertext and the last value of `X` to Alice. Alice uses `p` and `q` to generate the original value of `X` that Bob used, then runs through the Blum Blum Shub algorithm just as Bob did, generating the same random bits. She will then `xor` the random bits with the ciphertext to recover Bob's original plaintext message.

# Implementation
The entire implementation is contained in a templated header file, so it only needs to be `#include`d to be used; no explicit compilation is necessary. To compile the test program:

```bash
g++ -std=c++14 -O3 test_blum_goldwasser.cc
```

C++14 and Boost are **required**. It will not compile without it. This is due to needing Boost's arbitrary precision arithmetic in order to compute the extremely large modular exponentiations that are part of the decryption process.

To run:
```
./a.out
```

The message ('10011100000100001100') is hardcoded and re-compiling is necessary if you want to change it. Running the program results in the following output:
```
Ciphertext: 10110000000110000111
Plaintext: 10011100000100001100
Decrypted: 10011100000100001100
```
First, the message is encrypted, and the cipher text is printed. It is then decrypted. The plaintext and the decrypted text are both printed out and an assertion is made that `plaintext == decrypted`. If the assertion holds, the program exits normally.

