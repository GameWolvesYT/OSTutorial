#include "string.h"
#include "memory.h"

//Gibt die Länge eines Strings zurück.
int strlen(const char* str) 
{
	int len = 0;
	while (str[len] != 0)
		len++;
	return len;
}

//Wandelt einen Integer zu einem Char Array um.
void int_to_str(int num, char* str) 
{
    int i, sign;
    
    if((sign = num) < 0) num = -num;
    
    i = 0;
    do 
    {
        str[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void uint_to_hex(unsigned int num, char* str)
{
	char* hexchars = HEX;
	int i = 0;
	
	do
	{
		str[i++] = hexchars[num % 16];
	} while((num /= 16) > 0);
	str[i] = '\0';
	
	reverse(str);
}

void uint_to_bin(unsigned int num, char* str, int len)
{
	int i = 0;
	
	do
	{
		str[i++] = ((num >> i) & 1) + '0';
	} while(i < len);
	str[i] = '\0';
	
	reverse(str);
}

void reverse(char* str) 
{
	char c;
    int i, j;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) 
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

char** split(char* str, char splitter, unsigned int maxlen, unsigned char* argc)
{
	(*argc) = 1;
	for (unsigned int i = 0; i < maxlen && str[i] != '\0'; i++)
		if (str[i] == splitter)
			(*argc)++;
	
	if ((*argc) == 0)
		return 0;
	
	int count = 0;
	char** splits = malloc(*argc);
	splits[0] = str;
	for (unsigned int i = 0; i < maxlen && str[i] != '\0'; i++)
	{
		if (str[i] == splitter)
		{
			str[i] = '\0';
			splits[++count] = &(str[i + 1]);
		}
	}
		
	return splits;
}

int strcmp(const char* a, const char* b)
{
	if (a == 0 ||  b == 0)
		return 0;
		
	for (int i = 0; ; i++)
	{
		if (a[i] == '\0' && b[i] != '\0')
			return -1;
		if (a[i] != '\0' && b[i] == '\0')
			return 1;
		if (a[i] == '\0' && b[i] == '\0')
			return 0;
		
		if (a[i] < b[i])
			return -1;
			
		if (a[i] > b[i])
			return 1;
	}
}