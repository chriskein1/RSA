# RSA Cryptosystem Project <br />
# CSCI 4900 - 6600 <br />
# Chris Keiningham <br />

<br />
i. Explanation / use of program
<br />

My implementation of the RSA Cryptosystem in C++ 11 for Selected Topics in Cyber Security (CSCI 4900-6600) at MTSU <br />
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


Plaintext is read from plaintext.txt <br />
Encrypted text is read from plaintext.txt and saved to ciphertext.txt <br />
Decrypted text is read from ciphertext.txt and saved to decoded.txt <br />


Keys are 16-bit.


Algorithms used:
- Euclidean Algorithm (GCD)
- Extended Euclidean Algorithm (Modular Multiplicative Inverse)
- Primality Test (Efficiently determine if a number is prime)
- Modular Exponentiation (Efficiently calculate the encryption / decryption formula)



<br />
ii. How to use
<br />

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



<br />
iii. Proof
<br />

C = (M^e) mod n  <br />
M = (C^d) mod n <br />

d is selected as the modular multiplicative inverse such that ed mod ϕ(n) = 1 <br />
Therefore, ed = 1 mod ϕ(n) <br />

Knowing this,
C = (M^e) mod n <br />
C^d = (M^e)^d mod n <br />
C^d = (M^ed) mod n <br />
C^d = (M^1 mod ϕ(n)) mod n <br />
C^d = M mod n <br />
C^d mod n = M <br />
