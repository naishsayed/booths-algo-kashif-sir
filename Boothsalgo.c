#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BITS 4 // Number of bits for the binary representation

// Function to convert a binary string to an integer
int binaryToInt(const char* binary) {
    int value = 0;
    while (*binary) {
        value = (value << 1) | (*binary - '0');
        binary++;
    }
    return value;
}

// Function to perform Booth's algorithm for multiplication
void boothAlgorithm(const char* multiplicandBinary, const char* multiplierBinary, char* resultBinary) {
    // Convert binary strings to integers
    int multiplicand = binaryToInt(multiplicandBinary);
    int multiplier = binaryToInt(multiplierBinary);
    
    // Initialize the registers
    int A = multiplicand;
    int S = (~multiplicand + 1) & ((1 << NUM_BITS) - 1); // Two's complement of multiplicand
    int P = multiplier;
    int Q_1 = 0;

    // Extend P and Q_1 to the bit length
    P <<= NUM_BITS;
    Q_1 <<= NUM_BITS;

    // Booth's algorithm loop
    for (int i = 0; i < NUM_BITS; i++) {
        if ((P & 1) == 0 && Q_1 == 1) {
            // A = A + M
            P = (P + A) & ((1 << (NUM_BITS * 2)) - 1);
        } else if ((P & 1) == 1 && Q_1 == 0) {
            // A = A - M
            P = (P + S) & ((1 << (NUM_BITS * 2)) - 1);
        }
        // Arithmetic right shift
        Q_1 = P & 1;
        P >>= 1;
        if (P & (1 << (NUM_BITS - 1))) {
            P |= (1 << (NUM_BITS * 2 - 1));
        }
    }

    // Extract the result
    int result = P >> NUM_BITS;
    if (result & (1 << (NUM_BITS - 1))) {
        result -= (1 << NUM_BITS * 2);
    }

    // Convert result to binary string
    for (int i = NUM_BITS * 2 - 1; i >= 0; i--) {
        resultBinary[i] = (result & (1 << i)) ? '1' : '0';
    }
    resultBinary[NUM_BITS * 2] = '\0';
}

int main() {
    int m,n;
    printf("Enter the multiplicand binary: ");
    scanf("%d",&m);
    printf("Enter the multiplier binary: ");
    scanf("%d",&n);
    const char* multiplicandBinary = "m"; 
    const char* multiplierBinary = "n";   

    char resultBinary[NUM_BITS * 2 + 1];
    
    boothAlgorithm(multiplicandBinary, multiplierBinary, resultBinary);
    
    printf("Product: %s\n", resultBinary);
    return 0;
}
