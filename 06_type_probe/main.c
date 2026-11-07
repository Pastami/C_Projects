#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// Number of bits in a byte
#define BITS 8

// Number of value bits in each integer type (without the sign bit)
#define CHAR_VALUE_BITS ((int) sizeof(char) * BITS - 1)
#define SHORT_VALUE_BITS ((int) sizeof(short) * BITS - 1)
#define INT_VALUE_BITS ((int) sizeof(int) * BITS - 1)
#define LONG_VALUE_BITS ((int) sizeof(long) * BITS - 1)
#define LONG_LONG_VALUE_BITS ((int) sizeof(long long) * BITS - 1)

// Define the maximum exponents of the floating-point types in base 2
// to calculate the largest finite number
#define FLOAT_MAX_EXPONENT 127
#define DOUBLE_MAX_EXPONENT 1023
#define LONG_DOUBLE_MAX_EXPONENT 16383

// Define the minimum exponents of the floating-point types in base 2
// to calculate the smallest normalized number
#define FLOAT_MIN_EXPONENT (-126)
#define DOUBLE_MIN_EXPONENT (-1022)
#define LONG_DOUBLE_MIN_EXPONENT (-16382)

#define CIPHER_SHIFT 3
#define ALPHABET_SIZE 26

// The cipher wraps around at the end of the alphabet. WRAP_LIMIT is the last
// letter that can be shifted without wrapping, and WRAP_START is the first
// one that must wrap
#define WRAP_LIMIT ('A' + ALPHABET_SIZE - CIPHER_SHIFT - 1)
#define WRAP_START (WRAP_LIMIT + 1)

typedef int Counter;

int main(void) {
	printf("====================\n");
	printf("     TYPE PROBE     \n");
	printf("====================\n\n");

	for (;;) {
menu: ;
		printf("---MENU---\n\n");

		printf("1 - Integer type sizes\n");
		printf("2 - Base converter\n");
		printf("3 - Unsigned wraparound\n");
		printf("4 - Floating-point precision\n");
		printf("5 - Text analyzer\n");
		printf("6 - Conversion lab\n");
		printf("0 - Exit\n\n");

		printf("Choose an option: ");

		// Invalid value used when scanf fails
		int option = -1;

		scanf("%d", &option);

		// Discard the rest of the line
		while (getchar() != '\n') {
			;
		}

		// Do not print the two newline characters on exit
		if (option != 0) {
			printf("\n\n");
		}

		switch (option) {
			case 1: {
				printf("---INTEGER TYPE SIZES---\n\n");

				printf(">> Sizes\n\n");

				printf("Char:\t\t\t%zu byte(s)\n", sizeof(char));
				printf("Short:\t\t\t%zu byte(s)\n", sizeof(short));
				printf("Int:\t\t\t%zu byte(s)\n", sizeof(int));
				printf("Long:\t\t\t%zu byte(s)\n", sizeof(long));
				printf("Long long:\t\t%zu byte(s)\n\n", sizeof(long long));

				printf(">> Value Ranges\n\n");

				unsigned char unsigned_char_max = 1;

				// Calculate the maximum value that an unsigned type variable can handle
				// by starting at 1 and repeating "multiply by 2 and add 1" once for
				// each remaining bit of the type.
				for (int i = 1; i <= CHAR_VALUE_BITS; i++) {
					unsigned_char_max = unsigned_char_max * 2 + 1;
				}

				// Calculate the maximum value that a signed variable can handle
				// by dividing the corresponding unsigned maximum value by 2 and
				// truncating the fractional part
				signed char signed_char_max = unsigned_char_max / 2;

				// Calculate the minimum value that a signed variable can handle
				// by negating the maximum value and subtracting 1 since the
				// magnitude of the minimum is one greater than the maximum
				signed char signed_char_min = -signed_char_max - 1;

				char char_plain = -1;

				// char_plain is compared with 0 to determine whether it is signed;
				// if it is signed, it can hold -1, otherwise it wraps around,
				// so it is unsigned
				if (char_plain < 0) {
					printf("Char:\t\t\t%hhd to %hhd\n", signed_char_min, signed_char_max);
				} else {
					printf("Char:\t\t\t0 to %hhu\n", unsigned_char_max);
				}

				printf("Signed char:\t\t%hhd to %hhd\n", signed_char_min, signed_char_max);
				printf("Unsigned char:\t\t0 to %hhu\n", unsigned_char_max);


				unsigned short unsigned_short_max = 1;

				for (int i = 1; i <= SHORT_VALUE_BITS; i++) {
					unsigned_short_max = unsigned_short_max * 2 + 1;
				}

				short short_max = unsigned_short_max / 2;
				short short_min = -short_max - 1;

				printf("Short:\t\t\t%hd to %hd\n", short_min, short_max);
				printf("Unsigned short:\t\t0 to %hu\n", unsigned_short_max);


				unsigned int unsigned_int_max = 1;

				for (int i = 1; i <= INT_VALUE_BITS; i++) {
					unsigned_int_max = unsigned_int_max * 2 + 1;
				}

				int int_max = unsigned_int_max / 2;
				int int_min = -int_max - 1;

				printf("Int:\t\t\t%d to %d\n", int_min, int_max);
				printf("Unsigned int:\t\t0 to %u\n", unsigned_int_max);


				unsigned long unsigned_long_max = 1;

				for (int i = 1; i <= LONG_VALUE_BITS; i++) {
					unsigned_long_max = unsigned_long_max * 2 + 1;
				}

				long long_max = unsigned_long_max / 2;
				long long_min = -long_max - 1;

				printf("Long:\t\t\t%ld to %ld\n", long_min, long_max);
				printf("Unsigned long:\t\t0 to %lu\n", unsigned_long_max);


				unsigned long long unsigned_long_long_max = 1;

				for (int i = 1; i <= LONG_LONG_VALUE_BITS; i++) {
					unsigned_long_long_max = unsigned_long_long_max * 2 + 1;
				}

				long long long_long_max = unsigned_long_long_max / 2;
				long long long_long_min = -long_long_max - 1;

				printf("Long long:\t\t%lld to %lld\n", long_long_min, long_long_max);
				printf("Unsigned long long:\t0 to %llu\n\n", unsigned_long_long_max);

				break;
			}

			case 2: {
				printf("---BASE CONVERTER---\n\n");

				printf("Enter a non-negative number: ");

				char ch;
				unsigned long long number = 0;

				// -1 means that no digit was read yet. If it is still -1 after
				// the conversion, the input was not a valid number
				int digit = -1;

				// The first characters decide the base
				// "0x" or "0X": hexadecimal
				// "0" followed by "0" to "7": octal
				// "1" to "9": decimal
				// "0" alone: zero
				if ((ch = getchar()) == '0') {
					ch = getchar();

					if (toupper(ch) == 'X') {
						while ((ch = getchar()) != '\n') {
							// Convert the character to its numeric value; letters need their own
							// cases because ch - '0' only works for digits
							switch (toupper(ch)) {
								case '0': case '1': case '2': case '3': case '4':
								case '5': case '6': case '7': case '8': case '9':
									digit = ch - '0';
									break;
								case 'A':
									digit = 10;
									break;
								case 'B':
									digit = 11;
									break;
								case 'C':
									digit = 12;
									break;
								case 'D':
									digit = 13;
									break;
								case 'E':
									digit = 14;
									break;
								case 'F':
									digit = 15;
									break;
								default:
									printf("Invalid number!\n\n");

									// Discard the rest of the line
									while (getchar() != '\n') {
										;
									}

									goto menu;
							}

							number = number * 16 + digit;
						}
					} else if ('0' <= ch && ch <= '7') {
						while (ch != '\n') {
							if (ch < '0' || ch > '7') {
								printf("Invalid number!\n\n");

								while (getchar() != '\n') {
									;
								}

								goto menu;
							}

							digit = ch - '0';
							number = number * 8 + digit;

							ch = getchar();
						}
					} else if (ch == '\n') {
						digit = 0;
					}
				} else if ('1' <= ch && ch <= '9') {
					while (ch != '\n') {
						if (ch < '0' || ch > '9') {
							printf("Invalid number!\n\n");

							while (getchar() != '\n') {
								;
							}

							goto menu;
						}

						digit = ch - '0';
						number = number * 10 + digit;

						ch = getchar();
					}
				}

				if (digit == -1) {
					printf("Invalid number!\n\n");

					if (ch != '\n') {
						while (getchar() != '\n') {
							;
						}
					}

					goto menu;
				}

				printf("\nDecimal:\t%llu\n", number);
				printf("Octal:\t\t%llo\n", number);
				printf("Hexadecimal:\t%llX\n\n", number);
				break;
			}

			case 3: {
				printf("---UNSIGNED WRAPAROUND---\n\n");

				printf(">> Unsigned Char (Promoted To Int)\n\n");

				unsigned char char_wrap = 0;

				// 0 - 1 does not fit in an unsigned char, so the value
				// wraps around to the maximum of the type
				char_wrap -= 1;
				printf("Maximum:\t%hhu\n", char_wrap);

				// char_wrap is promoted to int in the subtraction, so sizeof
				// gives the size of an int on this platform
				printf("Operation size:\t%zu byte(s)\n", sizeof(char_wrap - 1));

				// char_wrap is promoted to int again, so the sum is
				// calculated as an int and does not wrap around
				printf("Maximum + 1:\t%d\n", char_wrap + 1);

				// Storing 256 back in an unsigned char wraps around to 0
				char_wrap += 1;
				printf("Stored back:\t%hhu\n", char_wrap);

				// char_wrap holds 0 now, and the promotion to int
				// makes 0 - 1 result in -1
				printf("Zero - 1:\t%d\n", char_wrap - 1);

				// Storing -1 back in an unsigned char wraps around
				// to the maximum, as in the first subtraction
				char_wrap -= 1;
				printf("Stored back:\t%hhu\n\n", char_wrap);


				printf(">> Unsigned Short (Promoted To Int)\n\n");

				unsigned short short_wrap = 0;

				short_wrap -= 1;
				printf("Maximum:\t%hu\n", short_wrap);
				printf("Operation size:\t%zu byte(s)\n", sizeof(short_wrap - 1));
				printf("Maximum + 1:\t%d\n", short_wrap + 1);

				short_wrap += 1;
				printf("Stored back:\t%hu\n", short_wrap);
				printf("Zero - 1:\t%d\n", short_wrap - 1);

				short_wrap -= 1;
				printf("Stored back:\t%hu\n\n", short_wrap);


				// From this point on, there is no further promotion to int.
				// The expressions are calculated in the variable's type,
				// so the "Stored back" line will no longer be shown because it
				// will show the same values as "Maximum + 1" and "Zero - 1"
				printf(">> Unsigned Int\n\n");

				unsigned int int_wrap = 0;

				int_wrap -= 1;
				printf("Maximum:\t%u\n", int_wrap);
				printf("Operation size:\t%zu byte(s)\n", sizeof(int_wrap - 1));

				int_wrap += 1;
				printf("Maximum + 1:\t%u\n", int_wrap);

				int_wrap -= 1;
				printf("Zero - 1:\t%u\n\n", int_wrap);


				printf(">> Unsigned Long\n\n");

				unsigned long long_wrap = 0;

				long_wrap -= 1;
				printf("Maximum:\t%lu\n", long_wrap);
				printf("Operation size:\t%zu byte(s)\n", sizeof(long_wrap - 1));

				long_wrap += 1;
				printf("Maximum + 1:\t%lu\n", long_wrap);

				long_wrap -= 1;
				printf("Zero - 1:\t%lu\n\n", long_wrap);


				printf(">> Unsigned Long Long\n\n");

				unsigned long long long_long_wrap = 0;

				long_long_wrap -= 1;
				printf("Maximum:\t%llu\n", long_long_wrap);
				printf("Operation size:\t%zu byte(s)\n", sizeof(long_long_wrap - 1));

				long_long_wrap += 1;
				printf("Maximum + 1:\t%llu\n", long_long_wrap);

				long_long_wrap -= 1;
				printf("Zero - 1:\t%llu\n\n", long_long_wrap);

				break;
			}

			case 4: {
				printf("---FLOATING-POINT PRECISION---\n\n");

				printf(">> Sizes\n\n");

				printf("Float:\t\t\t%zu byte(s)\n", sizeof(float));
				printf("Double:\t\t\t%zu byte(s)\n", sizeof(double));
				printf("Long double:\t\t%zu byte(s)\n\n", sizeof(long double));


				printf(">> Format Specifiers\n\n");

				printf("Float (123.456f):\n");
				printf("%%f:\t\t\t%f\n", 123.456f);
				printf("%%e:\t\t\t%e\n", 123.456f);
				printf("%%g:\t\t\t%g\n\n", 123.456f);

				printf("Double (123.456):\n");
				printf("%%f:\t\t\t%f\n", 123.456);
				printf("%%e:\t\t\t%e\n", 123.456);
				printf("%%g:\t\t\t%g\n\n", 123.456);

				printf("Long double (123.456L):\n");
				printf("%%f:\t\t\t%Lf\n", 123.456L);
				printf("%%e:\t\t\t%Le\n", 123.456L);
				printf("%%g:\t\t\t%Lg\n\n", 123.456L);


				printf(">> Significant Digits (0.1)\n\n");

				// The printf shows more digits than the
				// types' precision allows, so it is possible
				// to see the representation error in each type
				printf("Float:\t\t\t%.9e\n", 0.1f);
				printf("Double:\t\t\t%.17e\n", 0.1);
				printf("Long double:\t\t%.21Le\n\n", 0.1L);


				printf(">> Limits\n\n");

				printf("Float:\n");

				float float_epsilon = 1.0f / 2.0f;

				// The loop stops when adding half of the epsilon to 1
				// makes no difference, so the epsilon is the last
				// value that still makes a difference
				do {
					float_epsilon /= 2.0f;
				} while ((float_epsilon / 2.0f) + 1.0f != 1.0f);

				printf("Epsilon:\t\t%.9e\n", float_epsilon);

				float float_max_power = 1.0f;

				// The power is multiplied by 2 once per step until
				// the maximum exponent of the type is reached
				for (int i = 0; i < FLOAT_MAX_EXPONENT; i++) {
					float_max_power *= 2.0f;
				}

				// The largest mantissa is multiplied by the power
				float float_largest = (2.0f - float_epsilon) * float_max_power;

				printf("Largest finite:\t\t%.9e\n", float_largest);

				float float_min_power = 1.0f;

				// Here the power is divided by 2 down to the
				// minimum exponent of the type
				for (int i = 0; i > FLOAT_MIN_EXPONENT; i--) {
					float_min_power /= 2.0f;
				}

				// The smallest mantissa is multiplied by the power
				float float_smallest = 1.0f * float_min_power;

				printf("Smallest normalized:\t%.9e\n\n", float_smallest);


				printf("Double:\n");

				double double_epsilon = 1.0 / 2.0;

				do {
					double_epsilon /= 2.0;
				} while ((double_epsilon / 2.0) + 1.0 != 1.0);

				printf("Epsilon:\t\t%.17e\n", double_epsilon);

				double double_max_power = 1.0;

				for (int i = 0; i < DOUBLE_MAX_EXPONENT; i++) {
					double_max_power *= 2.0;
				}

				double double_largest = (2.0 - double_epsilon) * double_max_power;

				printf("Largest finite:\t\t%.17e\n", double_largest);

				double double_min_power = 1.0;

				for (int i = 0; i > DOUBLE_MIN_EXPONENT; i--) {
					double_min_power /= 2.0;
				}

				double double_smallest = 1.0 * double_min_power;

				printf("Smallest normalized:\t%.17e\n\n", double_smallest);


				printf("Long double:\n");

				long double long_double_epsilon = 1.0L / 2.0L;

				do {
					long_double_epsilon /= 2.0L;
				} while ((long_double_epsilon / 2.0L) + 1.0L != 1.0L);

				printf("Epsilon:\t\t%.21Le\n", long_double_epsilon);

				long double long_double_max_power = 1.0L;

				for (int i = 0; i < LONG_DOUBLE_MAX_EXPONENT; i++) {
					long_double_max_power *= 2.0L;
				}

				long double long_double_largest = (2.0L - long_double_epsilon) * long_double_max_power;

				printf("Largest finite:\t\t%.21Le\n", long_double_largest);

				long double long_double_min_power = 1.0L;

				for (int i = 0; i > LONG_DOUBLE_MIN_EXPONENT; i--) {
					long_double_min_power /= 2.0L;
				}

				long double long_double_smallest = 1.0L * long_double_min_power;

				printf("Smallest normalized:\t%.21Le\n\n", long_double_smallest);

				break;
			}

			case 5: {
				printf("---TEXT ANALYZER---\n\n");

				printf("c - Count characters\n");
				printf("s - Swap case\n");
				printf("e - Encrypt with Caesar cipher\n\n");

				printf("Choose an option: ");
				char ch_option = 0;
				scanf(" %c", &ch_option);

				// Discard the rest of the line
				while (getchar() != '\n') {
					;
				}

				switch (toupper(ch_option)) {
					case 'C': {
						printf("Enter a text: ");
						char ch_text = getchar();

						Counter characters = 0;
						Counter letters = 0;
						Counter digits = 0;
						Counter others = 0;

						while (ch_text != '\n') {
							characters++;

							if ('A' <= toupper(ch_text) && toupper(ch_text) <= 'Z') {
								letters++;
							} else if ('0' <= ch_text && ch_text <= '9') {
								digits++;
							} else {
								others++;
							}

							ch_text = getchar();
						}

						printf("\nCharacters:\t%d\n", characters);
						printf("Letters:\t%d\n", letters);
						printf("Digits:\t\t%d\n", digits);
						printf("Others:\t\t%d\n\n", others);

						break;
					}

					case 'S': {
						printf("Enter a text: ");
						char ch_text = getchar();

						printf("\nResult: \"");
						while (ch_text != '\n') {
							if ('a' <= ch_text && ch_text <= 'z') {
								putchar(ch_text - 'a' + 'A');
							} else if ('A' <= ch_text && ch_text <= 'Z') {
								putchar(ch_text - 'A' + 'a');
							} else {
								putchar(ch_text);
							}

							ch_text = getchar();
						}
						printf("\"\n\n");

						break;
					}

					case 'E': {
						printf("Enter a text: ");
						char ch_text = getchar();

						printf("\nResult: \"");
						while (ch_text != '\n') {
							if ('A' <= toupper(ch_text) && toupper(ch_text) <= WRAP_LIMIT) {
								putchar(ch_text + CIPHER_SHIFT);
							} else if (WRAP_START <= toupper(ch_text) && toupper(ch_text) <= 'Z') {
								// These letters would go past the end of the alphabet, so subtracting
								// the alphabet size wraps them around to the beginning
								putchar(ch_text + CIPHER_SHIFT - ALPHABET_SIZE);
							} else {
								putchar(ch_text);
							}

							ch_text = getchar();
						}
						printf("\"\n\n");

						break;
					}

					default: {
						printf("Invalid option!\n\n");
						break;
					}
				}

				break;
			}

			case 6: {
				printf("---CONVERSION LAB---\n\n");

				printf(">> Casts\n\n");

				printf("7 / 2:\t\t\t\t\t%d\n", 7 / 2);
				printf("(double) 7 / 2:\t\t\t\t%f\n", (double) 7 / 2);
				printf("(int) 3.99:\t\t\t\t%d\n\n", (int) 3.99);


				printf(">> Promotion\n\n");

				signed char ch_number = 100;

				// Signed char is promoted to int in the sum, so it does not overflow
				printf("Signed char 100 + signed char 100:\t%d\n", ch_number + ch_number);
				printf("Expression size:\t\t\t%zu byte(s)\n", sizeof(ch_number + ch_number));

				// 200 does not fit in a signed char, so the result is implementation-defined:
				// GCC keeps only the bits that fit in the type
				ch_number = ch_number + ch_number;

				printf("Stored back in signed char:\t\t%hhd\n\n", ch_number);


				printf(">> Assignment Truncation\n\n");

				// Assigning a double to an int discards the fractional part, with no rounding
				int int_example = 3.99;

				printf("Double 3.99 to int:\t\t\t%d\n", int_example);

				int_example = -3.99;

				printf("Double -3.99 to int:\t\t\t%d\n", int_example);

				// Assigning an int that does not fit in a signed char keeps only the bits that fit, as before
				signed char char_example = 300;

				printf("Int 300 to signed char:\t\t\t%hhd\n\n", char_example);


				printf(">> Signed Vs Unsigned Char\n\n");

				signed char char_signed = 200;
				unsigned char char_unsigned = 200;

				printf("Signed char 200:\t\t\t%hhd\n", char_signed);
				printf("Unsigned char 200:\t\t\t%hhu\n", char_unsigned);

				// An out-of-range value wraps around in an unsigned char, so -1 becomes the
				// maximum of the type
				char_signed = -1;
				char_unsigned = -1;

				printf("Signed char -1:\t\t\t\t%hhd\n", char_signed);
				printf("Unsigned char -1:\t\t\t%hhu\n\n", char_unsigned);


				printf(">> Sign Comparison\n\n");

				bool is_smaller = -1 < 1;

				if (is_smaller) {
					printf("-1 < 1:\t\t\t\t\ttrue\n");
				} else {
					printf("-1 < 1:\t\t\t\t\tfalse\n");
				}

				// -1 is converted to unsigned int, where it becomes the maximum value of the type,
				// so it is larger than 1
				is_smaller = -1 < 1u;

				if (is_smaller) {
					printf("-1 < 1u:\t\t\t\ttrue\n\n");
				} else {
					printf("-1 < 1u:\t\t\t\tfalse\n\n");
				}

				break;
			}

			case 0: {
				goto end_of_program;
			}

			default: {
				printf("Invalid option!\n\n");
				break;
			}
		}
	}
end_of_program: ;

	return 0;
}
