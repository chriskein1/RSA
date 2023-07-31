# RSA
My C++ implementation of the RSA algorithm

 ----------------------------------
|  ______________________________  |
| |      	RSA Project   		     | |
| |                              | |
| |        CSCI 4900/6600        | |
| |       Chris Keiningham       | |
| |                              | |
| |______________________________| |
|                                  |
 ---------------------------------- 


i. Explanation / use of program


My implementation of the RSA Cryptosystem in C++ 11 for Selected Topics in Cyber Security (CSCI 4900-6600) at MTSU
The RSA algorithm is from 1977 by Ron Rivest, Adi Shamir, and Leonard Adleman.


The program will calculate the following:

- Two privately generated prime numbers, p and q
- Their product, n: p*q.
- Euler's Totient function, phi(n): (p-1) * (q-1).
- Public exponent, e such that e is relatively prime to phi(n) and between 1 and phi(n) exclusive.
- Private exponent, d such that d is the modular multiplicative inverse to e and phi(n).


Text will be encrypted character-by-character using ASCII, including whitespace, newlines, and special characters.


Text is encrypted using the private key:
- C = M^d (mod n)
Text is decrypted using the public key:
- M = C^e (mod n)


Plaintext is read from plaintext.txt
Encrypted text is read from plaintext.txt and saved to ciphertext.txt
Decrypted text is read from ciphertext.txt and saved to decoded.txt


Keys are 16-bit.


Algorithms used:
- Euclidean Algorithm (GCD)
- Extended Euclidean Algorithm (Modular Multiplicative Inverse)
- Primality Test (Efficiently determine if a number is prime)
- Modular Exponentiation (Efficiently calculate the encryption / decryption formula)




ii. How to use


Run Makefile in Terminal:
cd to directory
./RSA

Makefile: RSA - compiled using clang++ 11 for Mac

Note: May need to give permissions:
chmod a+x (file path)


When running the program, you are prompted to either encrypt (1) or decrypt (2).

If encrypting, you have the option to generate new keys (1) or provide your own keys (2).

Note: If providing your own private key to encrypt, you must know the corresponding public key to decrypt.


If generating keys, the public / private key pair will be displayed.

After encrypting, text from plaintext.txt will be saved to ciphertext.txt


If decrypting, you must provide the public key to decrypt.

Text will be read from cipher.txt and will be saved to decoded.txt


If file not found, program will terminate.




iii. Proof

C = (M^e) mod n 
M = (C^d) mod n

d is selected as the modular multiplicative inverse such that ed mod ϕ(n) = 1
Therefore, ed = 1 mod ϕ(n)

Knowing this,
C = (M^e) mod n
C^d = (M^e)^d mod n
C^d = (M^ed) mod n
C^d = (M^1 mod ϕ(n)) mod n
C^d = M mod n
C^d mod n = M
