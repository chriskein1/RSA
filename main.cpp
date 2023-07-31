// Project: RSA Algorithm
// CSCI 4900/6600 - Cyber Security
// Chris Keiningham

#include "RSA.h"
#include <fstream>
#include <iostream>
#include <string>

typedef unsigned long ul;

std::string ReadText(std::ifstream &file);
void SaveFile(std::string text, int enc_choice);
int main() {

  int bits = 16;
  RSA RSA(bits);

  int key_choice;
  int enc_choice;

    std::cout << "\n ----------------------------------\n"
              << "|  ______________________________  |\n"
              << "| |       RSA Cryptosystem       | |\n"
              << "| |     By Chris Keiningham      | |\n"
              << "| |______________________________| |\n"
              << "|                                  |\n"
              << " ---------------------------------- \n";

  std::cout << std::endl << "Encrypt (1) or decrypt (2)? ";
  std::cin >> enc_choice;

  while (enc_choice != 1 && enc_choice != 2) {
    std::cout << "Encrypt (1) or decrypt (2)? ";
    std::cin >> enc_choice;
  }

  if (enc_choice == 1) {
    std::cout << "Generate keys (1) or provide keys (2)? ";
    std::cin >> key_choice;

    while (key_choice != 1 && key_choice != 2) {
      std::cout << "Generate keys (1) or provide keys (2)? ";
      std::cin >> key_choice;
    }
  }

  if (enc_choice == 2 || key_choice == 2) {
    ul user_e, user_d, user_n;

    if (enc_choice == 2) {
      std::cout << "\nEnter public key for decryption\n";
      std::cout << "e = ";
      std::cin >> user_e;
      RSA.SetExponent(user_e);

      std::cout << "n = ";
      std::cin >> user_n;
      RSA.SetN(user_n);
    }

    if (enc_choice == 1) {
      std::cout << "\nEnter private key for encryption\n";
      std::cout << "d = ";
      std::cin >> user_d;
      RSA.SetD(user_d);

      std::cout << "n = ";
      std::cin >> user_n;
      RSA.SetN(user_n);
    }
  }

  else {
    std::cout << std::endl;
    RSA.Generate();
  }

  std::ifstream in_file;
  std::string RSA_text;
  if (enc_choice == 1)
    in_file.open("plaintext.txt");
  else
    in_file.open("ciphertext.txt");

  if (!in_file) {
    if (enc_choice == 1) {
      std::cout << "plaintext.txt not found!\n"; return 0;
    }
    else {
      std::cout << "ciphertext.txt not found!\n"; return 0;
    }
  }

  std::string text = ReadText(in_file);

  if (enc_choice == 1)
    RSA_text = RSA.EncryptText(text);
  else
    RSA_text = RSA.DecryptText(text);

  if (key_choice == 1)
    RSA.PrintKeys();
  std::cout << std::endl;

  SaveFile(RSA_text, enc_choice);

  return 0;
}

std::string ReadText(std::ifstream &file) {
  std::string text;
  std::string line;

  // Priming read
  getline(file, line);

  while (file) {
    text += line + '\n';
    getline(file, line);
  }
  file.close();

  return text;
}

void SaveFile(std::string text, int enc_choice) {
  std::ofstream out_file;
  if (enc_choice == 1) {
    out_file.open("ciphertext.txt");
    std::cout << std::endl
              << "   --------Text saved to---------\n"
              << "   -------ciphertext.txt---------\n";
  } else {
    out_file.open("decoded.txt");
    std::cout << std::endl 
              << "   ---------Text saved to--------\n"
              << "   ----------decoded.txt---------\n";
  }
  std::cout << std::endl;
  out_file << text;
  out_file.close();
}