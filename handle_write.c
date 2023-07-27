#include "main.h"

/********** WRITE THE HANDLE ********/
/**
 * handle_write_char - Printing a string
 * @c: The char types.
 * @buffer: The Buffer array to handle print
 * @precision: precision specifier
 * @size: Size specifier
 * @flags:  Calculates active flags.
 * @width: get width.
 * Return: Return the Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left of the buffer and paddind at right of the buffer */
	int e = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[e++] = c;
	buffer[e] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (e = 0; e < width - 1; e++)
		{	buffer[BUFF_SIZE - e - 2] = padd; }

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - e - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFF_SIZE - e - 1], width - 1) +
					write(1, &buffer[0], 1));
		}
	}

	return (write(1, &buffer[0], 1));
}



/**
 * write_unsgnd - Writing an unsigned number
 * @is_negative: The Number indicating if the num is negative
 * @ind: The Index at which the number starts in the buffer
 * @buffer: The Array of chars
 * @flags: The Flags specifiers
 * @width: The Width specifier
 * @precision: The Precision specifier
 * @size: The Size specifier
 *
 * Return: Return the Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the right of the bufer  and starts at position e */
	int length = BUFF_SIZE - ind - 1, e = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (e = 0; e < width - length; e++)
			buffer[e] = padd;

		buffer[e] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], e));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], e) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writing a memory address
 * @buffer: The Arrays of chars
 * @ind: The Index at which the number starts in the buffer
 * @length: The Length of number
 * @width: The Width specifier
 * @flags: The Flags specifier
 * @padd: The Char representing the padding
 * @extra_c: The Char representing extra char
 * @padd_start: The Index at which padding should start
 *
 * Return: Return the Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int e;

	if (width > length)
	{
		for (e = 3; e < width - length + 3; e++)
			buffer[e] = padd;
		buffer[e] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], e - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], e - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], e - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

/********* WRITE A NUMBER ************/
/**
 * write_number - Printing a string
 * @is_negative: List of arguments
 * @width: Tet width.
 * @precision: The Precision specifier
 * @size: The Size specifier
 * @ind: The Char types.
 * @buffer: The Buffer array to handle print
 * @flags:  Calculating active flags
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		padd = '0';
	}
	if (is_negative)
	{
		extra_ch = '-';
	}
	else if (flags & F_PLUS)
	{
		extra_ch = '+';
	}
	else if (flags & F_SPACE)
	{
		extra_ch = ' ';
	}

	return(write_num(ind, buffer, flags, width,
				precision, length, padd, extra_ch));
}

/**
 * write_num - Writing a number using a bufffer
 * @ind: The Index at which the number starts the buffer
 * @buffer: The Buffer
 * @flags: The Flags
 * @width: The Width
 * @prec: The Precision specifier
 * @length: The Number length
 * @padd: The Pading char
 * @extra_c: The Extra Char
 *
 * Return: Return the Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int e, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (e = 1; e < width - length + 1; e++)
			buffer[e] = padd;
		buffer[e] = '\0';
		if (flags & F_MINUS && padd == ' ')/*Assign extra Char to the buffer's left*/
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], e - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to the buff's left*/
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], e - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
			{	buffer[--padd_start] = extra_c; }
			return (write(1, &buffer[padd_start], e - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
	{	buffer[--ind] = extra_c; }
	return (write(1, &buffer[ind], length));
}





