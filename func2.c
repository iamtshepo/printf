#include "main.h"

/********* PRINT POINTER *********/
/**
 * print_pointer - Prints the value of a pointer variable
 * @flags:  Calculates active flags
 * @width: Get width
 * @precision: The Precision specification
 * @size: The Size specifier
 * @types: The List a of arguments
 * @buffer: The Buffer array to handle print

 * Return: Return the Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[e], BUFF_SIZE - e - 1)); // is another option */
	return (write_pointer(buffer, ind, length,
				width, flags, padd, extra_c, padd_start));
}


/************** PRINT REVERSE STRING ************/
/**
 * print_reverse - Printing a reverse string.
 * @types: The List arr of arguments
 * @buffer: The Buffer array to handle print
 * @flags:  The Calculates active flags
 * @width: Get width
 * @precision: The Precision specification
 * @size: The Size specifier
 * Return: Return the Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int e, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = "%r";
	}
	for (e = 0; str[e]; e++)
		;

	for (e = e - 1; e >= 0; e--)
	{
		char z = str[e];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/*************** PRINTS A STRING IN ROT13 **************/
/**
 * print_rot13string - Prints a string in rot13.
 * @types: List arr of arguments
 * @buffer: The Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Get width
 * @precision: The Precision specification
 * @size: The Size specifier
 * Return: Returns the Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int e, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (e = 0; str[e]; e++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[e])
			{
				x = out[k];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			x = str[e];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

/************ PRINT NON PRINTABLE ***********/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List arr of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int e = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[e] != '\0')
	{
		if (is_printable(str[e]))
			buffer[e + offset] = str[e];
		else
			offset += append_hexa_code(str[e], buffer, e + offset);

		e++;
	}

	buffer[e + offset] = '\0';

	return (write(1, buffer, e + offset));
}


