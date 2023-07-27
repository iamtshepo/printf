#include "main.h"

/*************** PRINT UNSIGNED NUMBER ***********/
/**
 * print_unsigned - Printing an unsigned num
 * @types: List of arguments
 * @buffer: The Buffer array that handle print
 * @flags:  Calculates active flags
 * @width: Get width
 * @precision: The Precision specification
 * @size: The Size specifier
 * Return: Return the Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int e = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[e--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[e--] = (num % 10) + '0';
		num /= 10;
	}

	e++;

	return (write_unsgnd(0, e, buffer, flags, width, precision, size));
}

/******* PRINT UNSIGNED NUMBER IN OCTAL ******/
/**
 * print_octal - Printing an unsigned number in octal notation
 * @types: List of Arguments
 * @buffer: The Buffer Array to handle print
 * @flags:  Calculates Active Flags
 * @width: Get width
 * @precision: The Precision Specification
 * @size: The Size Specifier
 * Return: Return the Number of Chars Printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int e = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[e--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[e--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[e--] = '0';

	e++;

	return (write_unsgnd(0, e, buffer, flags, width, precision, size));
}

/******* PRINT UNSIGNED NUMBER IN HEXADECIMAL ********/
/**
 * print_hexadecimal - Printing an unsigned num in hexa-decimal Notation
 * @types: List of arguments
 * @buffer: The Buffer array to handle print
 * @flags:  Calculating active Flags
 * @width: Get width
 * @precision: The Precision Specification
 * @size: The Size Specifier
 * Return: Return the Number of Chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/******* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL *******/
/**
 * print_hexa_upper - Printing an unsigned number in upper hexadecimal Notation
 * @types: List of arguments
 * @buffer: The Buffer array to handle print
 * @flags:  Calculating Active Flags
 * @width: Get width
 * @precision: The Precision specification
 * @size: The Size specifier
 * Return: Return the Number of Chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/******** PRINT HEXX NUM IN LOWER OR UPPER *******/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int e = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[e--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[e--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[e--] = flag_ch;
		buffer[e--] = '0';
	}

	e++;

	return (write_unsgnd(0, e, buffer, flags, width, precision, size));
}

