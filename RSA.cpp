#include "RSA.h"
#include <cmath>
#include <iostream>

RSA::RSA() {
  // Default constructor if bits are not specified
  bits = 16;
}

RSA::RSA(int b) { bits = b; }

void RSA::SetExponent(ul user_e) {
  e = user_e;
}

void RSA::SetN(ul user_n) {
  n = user_n;
}

void RSA::SetD(ul user_d) {
  d = user_d;
}

void RSA::Generate() { GenerateKeys(); }

// The Euclidian Algorithm is an efficient way to find the GCD of two numbers
ul RSA::Euclidian(ul a, ul b) {
  if (a < b)
    std::swap(a, b);

  while (b != 0) {
    ul r = a % b;
    a = b;
    b = r;
  }
  return a;
}

// Reference: UMBC
// The Extended Euclidian Algorithm is used to find the inverse modulus
std::tuple<ul, ul, ul> RSA::ExtEuclid(ul a, ul b) {

  if (b == 0)
    return std::make_tuple(a, 1, 0);

  ul d1, s1, t1;
  std::tie(d1, s1, t1) = ExtEuclid(b, a % b);
  ul d = d1;
  ul s = t1;
  ul t = s1 - (a / b) * t1; // note: integer division
  return std::make_tuple(d, s, t);
}

ul RSA::InverseMod(ul a, ul b) {
  ul d, s, t;
  std::tie(d, s, t) = ExtEuclid(a, b);
  return (s + b) % b;
}

// Reference: Wikipedia Primality Test
// Using k+=6 optimization
bool RSA::IsPrime(ul n) {
  if (n <= 1)
    return false;
  if (n == 2 || n == 3)
    return true;

  // Check remainder with 2 and 3, the most common prime factors
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  // Iterate until sqrt(n)
  // We do this because for any given n, the largest factors will be sqrt(n)
  // i += 6  to skip mod 2 or mod 3
  for (ul i = 5; i < sqrt(n); i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

ul RSA::GeneratePrime(std::mt19937 &mt) {
  int prime_bits = bits / 2 + 1;

  // I have found that [2^8, 2^9) guarantees n is at least 16 bits
  ul min = pow(2, prime_bits - 1);
  ul max = pow(2, prime_bits) - 1;

  ul prime_num;

  std::uniform_int_distribution<ul> distribution(min, max);

  do {
    prime_num = distribution(mt);
  } while (!IsPrime(prime_num));
  return prime_num;
}

void RSA::GenerateKeys() {

  std::random_device rd;
  std::mt19937 mt(rd());

  do {
    p = GeneratePrime(mt);
    q = GeneratePrime(mt);
  } while (p == q);

  n = p * q;
  phi = (p - 1) * (q - 1);

  do {
    GenerateExponent(mt);

    d = InverseMod(e, phi);
  } while (d < pow(2, bits));
}

void RSA::GenerateExponent(std::mt19937 &mt) {
  std::uniform_int_distribution<ul> distribution(pow(2, bits), phi - 1);

  do {
    e = distribution(mt);
    // GCD between e and phi must be 1 (relatively prime)
  } while (Euclidian(e, phi) != 1);
}

// Reference: Wikipedia
// Modular Exponentiation is an algorithm used to find exponention over modulus that reduces computation time drastically
ul RSA::ModularExponentiation(ul base, ul exp) {
  if (n == 1)
    return 0;

  ul c = 1;
  base = base % n;

  while (exp > 0) {
    if (exp % 2 == 1) {
      c = (c * base) % n;
    }
    // Bit shift
    exp = exp >> 1;
    base = (base * base) % n;
  }

  return c;
}

std::string RSA::EncryptText(std::string text) {
  std::string cipher_text;
  for (ul i = 0; i < text.length(); i++) {
    // C = (M^d) mod n
    ul c = ModularExponentiation(text[i], d);

    cipher_text += std::to_string(c) + " ";
  }
  return cipher_text;
}

std::string RSA::DecryptText(std::string text) {
  std::string plain_text;
  std::string num;
  for (ul i = 0; i < text.length(); i++) {
    if (text[i] >= '0' && text[i] <= '9') {
      num += text[i];
    } else if (!num.empty()){
      ul encoded = std::stoul(num);
      // M = (C^e) mod n
      char c = ModularExponentiation(encoded, e);
      plain_text += c;
      num = "";
    }
  }
  return plain_text;
}

void RSA::PrintKeys() {
  std::cout << "Public Key: {" << e << ", " << n << '}' << std::endl;
  std::cout << "Private Key: {" << d << ", " << n << '}' << std::endl;
}
