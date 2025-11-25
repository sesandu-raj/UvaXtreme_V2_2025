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
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'alienOrder' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY words
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* alienOrder(int n, int words_count, char** words) {
    int adj[26][26] = {{0}};
    int indegree[26] = {0};
    bool used[26] = {false};

    for (int i = 0; i < words_count; i++) {
        for (size_t j = 0; j < strlen(words[i]); j++) {
            used[words[i][j] - 'a'] = true;
        }
    }

    for (int i = 0; i < words_count - 1; i++) {
        char* w1 = words[i];
        char* w2 = words[i + 1];
        size_t len1 = strlen(w1);
        size_t len2 = strlen(w2);
        size_t minlen = len1 < len2 ? len1 : len2;
        bool found = false;

        for (size_t j = 0; j < minlen; j++) {
            if (w1[j] != w2[j]) {
                int u = w1[j] - 'a';
                int v = w2[j] - 'a';
                if (!adj[u][v]) {
                    adj[u][v] = 1;
                    indegree[v]++;
                }
                found = true;
                break;
            }
        }
        if (!found && len1 > len2) {
            char* inv = "Invalid";
            char* ret = malloc(strlen(inv) + 1);
            strcpy(ret, inv);
            return ret;
        }
    }

    char* result = malloc(27);
    int pos = 0;
    int queue[26];
    int front = 0, rear = 0;

    for (int i = 0; i < 26; i++) {
        if (used[i] && indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        result[pos++] = 'a' + u;
        for (int v = 0; v < 26; v++) {
            if (adj[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0 && used[v]) {
                    queue[rear++] = v;
                }
            }
        }
    }

    int used_count = 0;
    for (int i = 0; i < 26; i++) if (used[i]) used_count++;

    if (pos != used_count) {
        char* inv = "Invalid";
        char* ret = malloc(strlen(inv) + 1);
        strcpy(ret, inv);
        free(result);
        return ret;
    }

    result[pos] = '\0';
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** words_temp = split_string(rtrim(readline()));

    char** words = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* words_item = *(words_temp + i);

        *(words + i) = words_item;
    }

    // Write your code here

    char* result = alienOrder(n, n, words);

    fprintf(fptr, "%s\n", result);

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
