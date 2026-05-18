/*union decision {
unsigned char flags;
struct field {
int your_choice:1; tobe computed
int your_mothers_choice:1;
int your_fathers_choice:1;
int socially_acceptable:1;
int financially_viable:1;
int do_you_aptitude:1;
int do_you_likeit:1;
int decision:1;  to be computed
};

union decision input();
 Write an expression that closely matches how you make decision
void make_decision(union decision *d);
Print a nice narrative
void print_decsion(union decision d);
 think of an interesting use for flags and printt an interpretaion based on the
number stored in flags void print_conclusion_based_on_flags( union decision d);
*/

#include <stdio.h>

/* ------------------------------------------------------------------ *
 *  The union lets us view the same byte either as 'flags' (raw byte)  *
 *  or as individual 1-bit fields through the nested struct.           *
 * ------------------------------------------------------------------ */
union decision {
    unsigned char flags;
    struct {
        unsigned int your_choice         : 1;  /* bit 0 – computed   */
        unsigned int your_mothers_choice : 1;  /* bit 1              */
        unsigned int your_fathers_choice : 1;  /* bit 2              */
        unsigned int socially_acceptable : 1;  /* bit 3              */
        unsigned int financially_viable  : 1;  /* bit 4              */
        unsigned int do_you_aptitude     : 1;  /* bit 5              */
        unsigned int do_you_likeit       : 1;  /* bit 6              */
        unsigned int decision            : 1;  /* bit 7 – computed   */
    } field;
};

/* ------------------------------------------------------------------ *
 *  input() – ask the user all the yes/no questions                    *
 * ------------------------------------------------------------------ */
union decision input() {
    union decision d;
    d.flags = 0;
    int ans;

    printf("\nAnswer each question with 1 (Yes) or 0 (No):\n\n");

    printf("Does your MOTHER approve?          : ");
    scanf("%d", &ans); d.field.your_mothers_choice = ans & 1;

    printf("Does your FATHER approve?          : ");
    scanf("%d", &ans); d.field.your_fathers_choice = ans & 1;

    printf("Is it SOCIALLY acceptable?         : ");
    scanf("%d", &ans); d.field.socially_acceptable = ans & 1;

    printf("Is it FINANCIALLY viable?          : ");
    scanf("%d", &ans); d.field.financially_viable  = ans & 1;

    printf("Do you have the APTITUDE for it?   : ");
    scanf("%d", &ans); d.field.do_you_aptitude     = ans & 1;

    printf("Do you LIKE it?                    : ");
    scanf("%d", &ans); d.field.do_you_likeit       = ans & 1;

    return d;
}

/* ------------------------------------------------------------------ *
 *  make_decision() – compute your_choice and final decision           *
 *                                                                     *
 *  your_choice = aptitude AND likeit                                  *
 *  decision    = your_choice                                          *
 *                AND (financially_viable                              *
 *                     OR (mother approves AND father approves))       *
 *                AND socially_acceptable                              *
 * ------------------------------------------------------------------ */
void make_decision(union decision *d) {
    d->field.your_choice =
        d->field.do_you_aptitude & d->field.do_you_likeit;

    d->field.decision =
        d->field.your_choice &
        (d->field.financially_viable |
         (d->field.your_mothers_choice & d->field.your_fathers_choice)) &
        d->field.socially_acceptable;
}

/* ------------------------------------------------------------------ *
 *  print_decision() – human-friendly narrative                        *
 * ------------------------------------------------------------------ */
void print_decision(union decision d) {
    printf("\n========================================\n");
    printf("       D E C I S I O N   R E P O R T\n");
    printf("========================================\n");
    printf("  Mother approves        : %s\n", d.field.your_mothers_choice ? "YES" : "NO");
    printf("  Father approves        : %s\n", d.field.your_fathers_choice ? "YES" : "NO");
    printf("  Socially acceptable    : %s\n", d.field.socially_acceptable  ? "YES" : "NO");
    printf("  Financially viable     : %s\n", d.field.financially_viable   ? "YES" : "NO");
    printf("  You have the aptitude  : %s\n", d.field.do_you_aptitude       ? "YES" : "NO");
    printf("  You like it            : %s\n", d.field.do_you_likeit         ? "YES" : "NO");
    printf("  ---- computed ----\n");
    printf("  Your personal choice   : %s\n", d.field.your_choice ? "YES" : "NO");
    printf("  FINAL DECISION         : %s\n", d.field.decision    ? "GO FOR IT!" : "DON'T DO IT.");
    printf("========================================\n");

    if (d.field.decision) {
        printf("\nNarrative: Everything lines up — you have the passion,\n");
        printf("  the talent, the support, and it makes practical sense.\n");
        printf("  Trust yourself and take the leap!\n");
    } else if (!d.field.your_choice) {
        printf("\nNarrative: This one is not really YOU. Find something\n");
        printf("  that excites you AND plays to your strengths.\n");
    } else {
        printf("\nNarrative: There are still hurdles to clear. Address the\n");
        printf("  concerns flagged above before making a final commitment.\n");
    }
}

/* ------------------------------------------------------------------ *
 *  print_conclusion_based_on_flags() – interpret the raw byte         *
 *  Count set bits as a confidence score; also show the bit pattern.   *
 * ------------------------------------------------------------------ */
void print_conclusion_based_on_flags(union decision d) {
    unsigned char f = d.flags;
    int score = 0;
    unsigned char tmp = f;
    while (tmp) { score += (tmp & 1); tmp >>= 1; }

    printf("\n--- Flag Analysis (raw byte = 0x%02X = %u) ---\n", f, f);
    printf("Confidence score : %d / 8 bits set\n", score);

    if      (score >= 7) printf("Verdict: OUTSTANDING - virtually every factor says YES!\n");
    else if (score >= 5) printf("Verdict: STRONG      - the odds are firmly in your favour.\n");
    else if (score >= 3) printf("Verdict: MIXED       - weigh the pros and cons carefully.\n");
    else if (score >= 1) printf("Verdict: WEAK        - major concerns remain unresolved.\n");
    else                 printf("Verdict: NO WAY      - not a single factor supports this.\n");

    printf("Bit pattern (MSB to LSB): ");
    for (int i = 7; i >= 0; i--)
        printf("%d", (f >> i) & 1);
    printf("\n");
}

/* ------------------------------------------------------------------ */
int main() {
    printf("============================================\n");
    printf("  LIFE DECISION MAKER  (union + bit-fields)\n");
    printf("============================================\n");

    union decision d = input();
    make_decision(&d);
    print_decision(d);
    print_conclusion_based_on_flags(d);

    return 0;
}
