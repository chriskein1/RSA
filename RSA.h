#include <random>
#include <string>
#include <tuple>

typedef unsigned long ul;

class RSA {
private:
  ul p, q, d, phi;
  int bits;
  ul Euclidian(ul a, ul b);
  std::tuple<ul, ul, ul> ExtEuclid(ul a, ul b);
  ul InverseMod(ul a, ul b);
  ul GeneratePrime(std::mt19937 &mt);
  void GenerateKeys();
  void GenerateExponent(std::mt19937 &mt);
  ul ModularExponentiation(ul base, ul exp);

public:
  ul e, n;
  void Generate();
  void SetExponent(ul user_e);
  void SetN(ul user_n);
  void SetD(ul user_d);
  bool IsPrime(ul n);
  void PrintKeys();
  std::string EncryptText(std::string text);
  std::string DecryptText(std::string text);
  RSA();
  RSA(int b);
};