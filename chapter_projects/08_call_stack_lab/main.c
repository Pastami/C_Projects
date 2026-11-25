#include <stdio.h>

// Macros related to the menu
#define FIBONACCI 1
#define BINARY_SEARCH 2
#define SUM_AND_REVERSE 3
#define EXIT 4

// Macros related to the fibonacci function
#define FIB_MIN 0
#define FIB_MAX 23

// Macros related to the binary_search function
#define BINARY_MIN (-20000)
#define BINARY_MAX 20000
#define ARRAY_LEN_MIN 1
#define ARRAY_LEN_MAX 10

// Macros related to the find_index function
#define INVALID_INDEX (ARRAY_LEN_MAX + 1)

// Macros related to the sum_and_reverse function
#define SUM_REV_MIN (-9999)
#define SUM_REV_MAX 9999

// Macros related to the read_number function
#define DIGIT_MIN '0'
#define DIGIT_MAX '9'
#define NUMBER_MAX 30000
#define INVALID_NUMBER 32767

void fibonacci(void);
int calculate_term(int n);

void binary_search(void);
void quicksort(int elements[], int low, int high);
int split(int elements[], int low, int high);
int find_index(int elements[], int searched_element, int low, int high);

void sum_and_reverse(void);
int sum_digits(int n);
void reverse_digits(int n);

int read_number(void);
void clean_buffer(void);

int main(void) {
	printf("============================\n");
	printf("       CALL STACK LAB       \n");
	printf("============================\n\n");

	int option = 0;
	do {
		printf("Choose an option:\n");
		printf("%d - Fibonacci sequence\n", FIBONACCI);
		printf("%d - Binary search\n", BINARY_SEARCH);
		printf("%d - Sum and reverse\n", SUM_AND_REVERSE);
		printf("%d - Exit\n\n", EXIT);

		printf("Option: ");
		option = read_number();

		putchar('\n');
		switch (option) {
			case FIBONACCI:
				fibonacci();
				break;
			case BINARY_SEARCH:
				binary_search();
				break;
			case SUM_AND_REVERSE:
				sum_and_reverse();
				break;
			case EXIT:
				printf("Closing...");
				break;
			default:
				printf("Invalid option!\n");
				break;
		}
		putchar('\n');
	} while (option != EXIT);

	return 0;
}

/*************************************************************************************
 * FIBONACCI: Print the title, receive the desired term of the Fibonacci sequence    *
 *            from read_number(), validate it and print each term of the sequence    *
 *            with the value returned by calculate_term().                           *
 *************************************************************************************/
void fibonacci(void) {
	printf("---FIBONACCI SEQUENCE---\n\n");

	int limit = 0;
	printf("Enter the desired term of the Fibonacci sequence (%d to %d): ", FIB_MIN, FIB_MAX);
	limit = read_number();

	// Validate input
	while (limit < FIB_MIN || limit > FIB_MAX) {
		printf("Invalid term!\n");
		printf("Enter the desired term of the Fibonacci sequence (%d to %d): ", FIB_MIN, FIB_MAX);
		limit = read_number();
	}

	putchar('\n');
	for (int term_counter = FIB_MIN; term_counter <= limit; term_counter++) {
		printf("F(%d) = %d\n", term_counter, calculate_term(term_counter));
	}
}

/*************************************************************************
 * CALCULATE_TERM: Calculate the term of the Fibonacci sequence from the *
 *                 two previous terms. The base cases end the recursion. *
 *************************************************************************/
int calculate_term(int n) {
	if (n == 0) {
		return 0;
	}

	if (n == 1) {
		return 1;
	}

	return calculate_term(n - 1) + calculate_term(n - 2);
}

/**********************************************************************************
 * BINARY_SEARCH: Print the title, receive the values of the elements of an array *
 *                with the length selected by the user, call quicksort() to sort  *
 *                the array elements, print the sorted array, call find_index()   *
 *                to find the index of an element selected by the user, then      *
 *                if the element is in the array, print its position, else print  *
 *                a message stating that the element is not in the current input. *
 **********************************************************************************/
void binary_search(void) {
	printf("---BINARY SEARCH---\n\n");

	printf("Enter the quantity of elements (%d to %d): ", ARRAY_LEN_MIN, ARRAY_LEN_MAX);
	int array_len = read_number();

	// Validate input
	while (array_len < ARRAY_LEN_MIN || array_len > ARRAY_LEN_MAX) {
		printf("Invalid quantity!\n");
		printf("Enter the quantity of elements (%d to %d): ", ARRAY_LEN_MIN, ARRAY_LEN_MAX);
		array_len = read_number();
	}

	// Store the values entered by the user in the array
	int elements[array_len];
	for (int i = 0; i < array_len; i++) {
		printf("Enter the value of the %d element (%d to %d): ", i + 1, BINARY_MIN, BINARY_MAX);
		elements[i] = read_number();

		// Validate input
		while (elements[i] < BINARY_MIN || elements[i] > BINARY_MAX) {
			printf("Invalid value!\n");
			printf("Enter the value of the %d element (%d to %d): ", i + 1, BINARY_MIN, BINARY_MAX);
			elements[i] = read_number();
		}
	}

	quicksort(elements, 0, array_len - 1);

	// Print the sorted array
	printf("\nSorted: ");
	for (int i = 0; i < array_len; i++) {
		printf("%d ", elements[i]);
	}
	putchar('\n');

	printf("Enter the value of the element to be searched (%d to %d): ", BINARY_MIN, BINARY_MAX);
	int searched_element = read_number();

	// Validate input
	while (searched_element < BINARY_MIN || searched_element > BINARY_MAX) {
		printf("Invalid value!\n");
		printf("Enter the value of the element to be searched (%d to %d): ", BINARY_MIN, BINARY_MAX);
		searched_element = read_number();
	}

	int searched_element_index = find_index(elements, searched_element, 0, array_len - 1);
	if (searched_element_index == INVALID_INDEX) {
		printf("The number is not in the current input!\n");
	} else {
		printf("Position: %d\n", searched_element_index + 1);
	}
}

/**********************************************************************************
 * QUICKSORT: Sort the array based on the low and high parameters with recursion. *
 **********************************************************************************/
void quicksort(int elements[], int low, int high) {
	if (low >= high) {
		return;
	}

	int middle = split(elements, low, high);
	quicksort(elements, low, middle - 1);
	quicksort(elements, middle + 1, high);
}

/*****************************************************************************
 * SPLIT: Split the array based on the partitioning element and return high, *
 *        which is the final position of the partitioning element.           *
 *****************************************************************************/
int split(int elements[], int low, int high) {
	int part_element = elements[low];

	for (;;) {
		while (low < high && part_element <= elements[high]) {
			high--;
		}

		if (low >= high) {
			break;
		}

		elements[low] = elements[high];
		low++;

		while (low < high && elements[low] <= part_element) {
			low++;
		}

		if (low >= high) {
			break;
		}

		elements[high] = elements[low];
		high--;
	}

	elements[high] = part_element;
	return high;
}

/*****************************************************************************
 * FIND_INDEX: Find the index of the searched array element using the binary *
 *             search algorithm. If the element is not in the array, return  *
 *             INVALID_INDEX.                                                *
 *****************************************************************************/
int find_index(int elements[], int searched_element, int low, int high) {
	if (low > high) {
		return INVALID_INDEX;
	}

	int middle = (low + high) / 2;

	if (searched_element < elements[middle]) {
		return find_index(elements, searched_element, low, middle - 1);
	}

	if (searched_element > elements[middle]) {
		return find_index(elements, searched_element, middle + 1, high);
	}

	return middle;
}

/***************************************************************************************
 * SUM_AND_REVERSE: Print the title, receive one number, receive the sum of the digits *
 *                  from sum_digits(), print it, and call reverse_digits() to print    *
 *                  the reversed version of the number. If the number entered is out   *
 *                  of the range of the macros SUM_REV_MIN and SUM_REV_MAX, the input  *
 *                  is requested again. If the number is negative, the sign is applied *
 *                  at the moment of printing.                                         *
 ***************************************************************************************/
void sum_and_reverse(void) {
	printf("---SUM AND REVERSE---\n\n");

	printf("Enter a number to sum and reverse its digits (%d to %d): ", SUM_REV_MIN, SUM_REV_MAX);
	int n = read_number();

	// Validate input
	while (n < SUM_REV_MIN || n > SUM_REV_MAX) {
		printf("Invalid value!\n");
		printf("Enter a number to sum and reverse its digits (%d to %d): ", SUM_REV_MIN, SUM_REV_MAX);
		n = read_number();
	}

	printf("Sum: ");

	// If n is negative, print the '-' character
	if (n < 0) {
		putchar('-');
	}
	printf("%d\n", sum_digits(n));

	printf("Reversed: ");
	reverse_digits(n);
	putchar('\n');
}

/*******************************************************************************
 * SUM_DIGITS: Return the sum of each digit of n. If n is negative, convert it *
 *             to positive. The base case ends the recursion.                  *
 *******************************************************************************/
int sum_digits(int n) {
	if (n == 0) {
		return n;
	}

	// If n is negative, convert it to positive
	n = n > 0 ? n : -n;

	int digit = n % 10;
	n /= 10;

	return digit + sum_digits(n);
}

/*******************************************************************************************
 * REVERSE_DIGITS: Print each digit of n in reverse order. If n is negative, print the '-' *
 *                 sign and convert n to positive. The base case ends the recursion.       *
 *******************************************************************************************/
void reverse_digits(int n) {
	// If n is negative, print the '-' character
	if (n < 0) {
		putchar('-');
	}

	// If n is negative, convert it to positive
	n = n > 0 ? n : -n;

	int digit = n % 10;
	n /= 10;

	printf("%d", digit);

	if (n == 0) {
		return;
	}

	reverse_digits(n);
}

/****************************************************************************************
 * READ_NUMBER: Read each digit of a number with char type and assemble an int number,  *
 *              then return the number. If the input is invalid, return INVALID_NUMBER. *
 ****************************************************************************************/
int read_number(void) {
	char ch = getchar();

	char sign = 0;
	// If the number has a '-' sign, it is assigned to the variable sign.
	// Then getchar() reads another character and the character is assigned to ch
	if (ch == '-') {
		sign = ch;

		ch = getchar();
	}

	// If the next character is the newline, the input is invalid
	if (ch == '\n') {
		return INVALID_NUMBER;
	}

	int number = 0;
	// Assemble the number
	while (DIGIT_MIN <= ch && ch <= DIGIT_MAX) {
		int digit = ch - DIGIT_MIN;

		// Calculate the maximum value that the variable number can have
		// before it exceeds the value of NUMBER_MAX
		int max_accumulated = (NUMBER_MAX - digit) / 10;

		// If number is bigger than max_accumulated, it will exceed
		// NUMBER_MAX in the next operation. Call clean_buffer() and
		// return INVALID_NUMBER
		if (number > max_accumulated) {
			clean_buffer();

			return INVALID_NUMBER;
		}

		number = number * 10 + digit;

		ch = getchar();
	}

	// If the next character is not the newline, the input is invalid
	if (ch != '\n') {
		clean_buffer();

		return INVALID_NUMBER;
	}

	// If the value of sign is '-', return the negative value of number
	if (sign == '-') {
		return -number;
	}

	return number;
}

/******************************************************************************
 * CLEAN_BUFFER: Discard the remaining input including the newline character. *
 ******************************************************************************/
void clean_buffer(void) {
	while (getchar() != '\n') {
		;
	}
}
