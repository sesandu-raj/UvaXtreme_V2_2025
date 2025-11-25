#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'countNotes' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER amount as parameter.
 */

int countNotes(int amount) {
     
        int sum=0;
        if(amount>=5000)
        {
            sum+=amount/5000;
            amount=amount%5000;
            //printf("5000 notes: %d\n",sum);
        }
        if(amount>=2000)
        {
            sum+=amount/2000;
            amount=amount%2000;
            //printf("2000 notes: %d\n",sum); 
        }
        if(amount>=1000)
        {
            sum+=amount/1000;
            amount=amount%1000;
            //printf("1000 notes: %d\n",sum); 
        }
        if(amount>=500)
        {
            sum+=amount/500;
            amount=amount%500;
            //printf("500 notes: %d\n",sum);
        }
        if(amount>=200)
        {
            sum+=amount/200;
            amount=amount%200;
            //printf("200 notes: %d\n",sum);
        }
        if(amount>=100)
        {
            sum+=amount/100;
            amount=amount%100;
            //printf("100 notes: %d\n",sum);
        }
        if(amount>=50)
        {
            sum+=amount/50;
            amount=amount%50;
            //printf("50 notes: %d\n",sum);
        }
        if(amount>=20)
        {
            sum+=amount/20;
            amount=amount%20; 
            //printf("20 notes: %d\n",sum);
        }
        if(amount>=10)
        {
            sum+=amount/10;
            amount=amount%10; 
            //printf("10 notes: %d\n",sum);
        }
        printf("%d  \n",sum);
            return sum;

    
    

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int amount = parse_int(ltrim(rtrim(readline())));


    int result =countNotes(amount);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
