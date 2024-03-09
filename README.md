# UBB_Lab2-Extra--OOP
This repo contains the Caesar's Cypher Breaker based on Frequency Analysis By Razvan-Andrei Bocra

# Frequency Analysis
Frequency analysis relies on the fact that some letters (or combination of letters ) occur more in a
language, regardless of the text size. For example, in English the letters E, A are the most frequent,
while the Z and Q are the least frequent. This method is a bruteforce method because it generates all possible shifts
of a text using the famous Caesar's Cypher method, and for each shift computes Chi Distance. In the end, the algorithm
returns the shift which has the lowest Chi Distance.

# Usage
Run the main.c file and select an option:
-for option 1 input the text you want to encrypt and the key
-for option 2 input the text you wish to decrypt
