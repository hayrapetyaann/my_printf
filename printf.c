#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

void my_putchar(char c);
void my_putstr(const char *str);
void my_putint(int num);
void my_printf(const char* format, ...);

int main() {
    my_printf("%d, %c, %s\n", -10, 'A', "Hello");
    return 0;
}

void my_putchar(char c) {
    write(1, &c, 1);
}

void my_putstr(const char *str) {
    write(1, str, strlen(str));
}

void my_putint(int num) {
    char buffer[20]; 
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        my_putchar('0');
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    for (int j = i - 1; j >= 0; j--) {
        my_putchar(buffer[j]);
    }
}

void my_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd':
                    my_putint(va_arg(args, int));
                    break;
                case 'c':
                    my_putchar((char)va_arg(args, int));
                    break;
                case 's':
                    my_putstr(va_arg(args, char*));
                    break;
                default:
                    my_putchar(*format);
                    break;
            }
        } else {
            my_putchar(*format);
        }
        format++;
    }
    
    va_end(args);
}
