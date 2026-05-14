/*Write a function to print the bits in an integer.
Write a function to count no of 1 bits in an integer.*/

#include <stdio.h>

// Function to print the bits of an integer
void print_bits(int num) {
    int size = sizeof(int) * 8; // Number of bits in an integer
    for (int i = size - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
        if (i % 8 == 0) printf(" "); // Space after every byte for readability
    }
    printf("\n");
}

// Function to count the number of 1 bits in an integer
int count_ones(int num) {
    int count = 0;
    while (num != 0) {
        count += (num & 1);
        num = (unsigned int)num >> 1; // Logical shift right
    }
    return count;
}

int main() {
    int num;
    
    printf("Enter an integer: ");
    if (scanf("%d", &num) == 1) {
        printf("Binary representation: ");
        print_bits(num);
        
        int ones = count_ones(num);
        printf("Number of 1 bits: %d\n", ones);
    } else {
        printf("Invalid input.\n");
    }
    
    return 0;
}