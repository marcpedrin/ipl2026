/*Design and test a structure bitfields.
Bitfield a;
a.firstbit = 1;
*/
#include <stdio.h>

/* ------------------------------------------------------------------ *
 *  Define a structure with bit-fields of various widths.              *
 *  Total = 1+2+3+4+5+6+1 = 22 bits, packed into 4 bytes (int).       *
 * ------------------------------------------------------------------ */
struct Bitfield {
  unsigned int firstbit : 1; /* holds 0 or 1              */
  unsigned int twobit : 2;   /* holds 0–3                 */
  unsigned int threebit : 3; /* holds 0–7                 */
  unsigned int fourbit : 4;  /* holds 0–15                */
  unsigned int fivebit : 5;  /* holds 0–31                */
  unsigned int sixbit : 6;   /* holds 0–63                */
  unsigned int lastbit : 1;  /* holds 0 or 1              */
};

/* ------------------------------------------------------------------ *
 *  print_bits – helper: print an unsigned int in binary (32 bits)     *
 * ------------------------------------------------------------------ */
void print_bits(unsigned int val, int nbits) {
  for (int i = nbits - 1; i >= 0; i--)
    printf("%u", (val >> i) & 1u);
}

/* ------------------------------------------------------------------ *
 *  display – show every field with its value and bit pattern          *
 * ------------------------------------------------------------------ */
void display(struct Bitfield a) {
  printf("\n+----------+-------+------+------------+\n");
  printf("| Field    | Width | Dec  | Binary     |\n");
  printf("+----------+-------+------+------------+\n");
  printf("| firstbit |   1   | %4u | ", a.firstbit);
  print_bits(a.firstbit, 1);
  printf("          |\n");
  printf("| twobit   |   2   | %4u | ", a.twobit);
  print_bits(a.twobit, 2);
  printf("         |\n");
  printf("| threebit |   3   | %4u | ", a.threebit);
  print_bits(a.threebit, 3);
  printf("        |\n");
  printf("| fourbit  |   4   | %4u | ", a.fourbit);
  print_bits(a.fourbit, 4);
  printf("       |\n");
  printf("| fivebit  |   5   | %4u | ", a.fivebit);
  print_bits(a.fivebit, 5);
  printf("      |\n");
  printf("| sixbit   |   6   | %4u | ", a.sixbit);
  print_bits(a.sixbit, 6);
  printf("     |\n");
  printf("| lastbit  |   1   | %4u | ", a.lastbit);
  print_bits(a.lastbit, 1);
  printf("          |\n");
  printf("+----------+-------+------+------------+\n");
  printf("sizeof(struct Bitfield) = %zu byte(s)\n", sizeof(struct Bitfield));
}

/* ------------------------------------------------------------------ */
int main() {
  struct Bitfield a;

  /* --- Test 1: manually assign as shown in the assignment --- */
  printf("=== Test 1: a.firstbit = 1 ===");
  a.firstbit = 1;
  a.twobit = 0;
  a.threebit = 0;
  a.fourbit = 0;
  a.fivebit = 0;
  a.sixbit = 0;
  a.lastbit = 0;
  display(a);

  /* --- Test 2: set every field to its maximum value --- */
  printf("\n=== Test 2: all fields at maximum ===");
  a.firstbit = 1; /* max for 1-bit  */
  a.twobit = 3;   /* max for 2-bit  */
  a.threebit = 7; /* max for 3-bit  */
  a.fourbit = 15; /* max for 4-bit  */
  a.fivebit = 31; /* max for 5-bit  */
  a.sixbit = 63;  /* max for 6-bit  */
  a.lastbit = 1;  /* max for 1-bit  */
  display(a);

  /* --- Test 3: overflow test (compiler wraps around) --- */
  printf("\n=== Test 3: overflow – assigning 5 to firstbit (1-bit field) ===");
  unsigned int overflow_val = 5;
  a.firstbit = overflow_val; /* 5 = 101b, only bit 0 stored => 1 */
  printf("\na.firstbit = 5  =>  stored value = %u  (only LSB kept)\n",
         a.firstbit);

  /* --- Test 4: interactive input --- */
  printf("\n=== Test 4: enter your own values ===\n");
  unsigned int temp;
  printf("firstbit  (0-1)  : ");
  scanf("%u", &temp); a.firstbit = temp;
  printf("twobit    (0-3)  : ");
  scanf("%u", &temp); a.twobit = temp;
  printf("threebit  (0-7)  : ");
  scanf("%u", &temp); a.threebit = temp;
  printf("fourbit   (0-15) : ");
  scanf("%u", &temp); a.fourbit = temp;
  printf("fivebit   (0-31) : ");
  scanf("%u", &temp); a.fivebit = temp;
  printf("sixbit    (0-63) : ");
  scanf("%u", &temp); a.sixbit = temp;
  printf("lastbit   (0-1)  : ");
  scanf("%u", &temp); a.lastbit = temp;
  display(a);

  return 0;
}