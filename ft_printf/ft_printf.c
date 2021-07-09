#include <unistd.h>
#include <stdarg.h>

int ft_strlen(char *str){
    int i = 0;

    while(*str++)
        i++;
    return(i);
}

int ft_numlen(long long num, int base_len){
    unsigned int len = 1;

    while(num >= base_len){
        len++;
        num /= base_len;
    }
    return (len);
}

void ft_putnbr(long long num, int base_len, char *base){
    char c;

    if(num >= base_len)
        ft_putnbr(num / base_len,  base_len, base);
    c = base[(num % base_len)];
    write(1, &c, 1);
}

int ft_printf(const char *format, ... ){
    va_list list;
    char *str;
    char *base;
    long long num = 0;
    int width = 0, prs = 0, prs_len = 0, len = 0, base_len = 0,
        negative = 0, zeros = 0, spaces = 0, ret = 0;

    va_start(list, format);
    while(*format){
        if(*format == '%'){
            format++;
            width = 0, prs = 0, prs_len = 0, len = 0, base_len = 0,
            negative = 0, zeros = 0, spaces = 0;
            while(*format >= '0' && *format <= '9'){
                width = width * 10 + (*format - '0');
                format++;
            }
            if(*format == '.'){
                prs = 1;
                format++;
                while(*format >= '0' && *format <= '9'){
                    prs_len = prs_len * 10 + (*format - '0');
                    format++;
                }
            }
            if(*format == 's'){
                str = va_arg(list, char *);
                if(!str)
                    str = "(null)";
                len = ft_strlen(str);
            }
            else if(*format == 'd'){
                base_len = 10;
                base = "0123456789";
                num = va_arg(list, int);
                if(num < 0){
                    negative = 1;
                    num = -num;
                }
                len = ft_numlen(num, base_len);
            }
            else if(*format == 'x'){
                base_len = 16;
                base = "0123456789abcdef";
                num = va_arg(list, unsigned int);
                len = ft_numlen(num, base_len);
            }
            if(prs){
                if(prs_len > len && *format != 's')
                    zeros = prs_len - len;
                if(prs_len < len && *format == 's')
                    len = prs_len;
                if(!prs_len && (*format == 's' || !num))
                    len = 0;
            }
            spaces = width - zeros - len - negative;

            while(spaces-- > 0){
                write(1, " ", 1);
                ret++;
            }
            if(negative){
                write(1, "-", 1);
                ret++;
            }
            while(zeros-- > 0){
                write(1, "0", 1);
                ret++;
            }
            if(*format == 's')
                write(1, str, len);
            else if(len)
                ft_putnbr(num, base_len, base);
            ret += len;
        } else {
            write(1, &*format, 1);
            ret++;
        }
        format++;
    }
    va_end(list);
    return (ret);
}
