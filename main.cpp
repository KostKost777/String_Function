#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>


int my_puts(const char* str);

const char* strchr(const char* str, char c);

size_t my_strlen(const char* str);

char* strcat(char *dest, const char *src);

char* strncat(char *dest, const char *src, size_t n);

char* strcpy(char* dest, const char* src);

char* strncpy(char* dest, const char* src, size_t n);

char* fgets(char* dest, size_t n, FILE* name);

char* strdup(const char* src);

int atoi(char* src);

ssize_t getline(char** dest, size_t* n, FILE* file);



int main()
{
    const char* hello = "Hello, world";
    my_puts(hello);
    char l = 'l';
    printf("%d\n", strchr(hello, l) - hello);

    printf("%d\n", my_strlen(hello));

    char a[] = "AAAA";
    const char* b = "Bbbbbbb";
    strncpy(a, b, 10);
    printf("%s\n", a);

    char g[] = {};
    FILE* f = NULL;
    f = fopen("t.txt", "r");
    fgets(g, 1000, f);
    printf("%s", g);


    char n[] = "AAAA";
    char* den = NULL;
    den = strdup(n);
    printf("%s\n", den);
    free(den);
    den = NULL;

    char m[] = "+1245ijtrb";
    printf("%d\n", atoi(m));

    char* ans = NULL;
    size_t buf = 5;
    FILE* file = NULL;
    file = fopen("t.txt", "r");
    getline(&ans, &buf, stdin);

    printf("ans:   %s\n", ans);
    free(ans);
    ans = NULL;

    fclose(file);
    fclose(f);
}

const char* strchr(const char* str, char c){
    assert(str != NULL);

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == c)
            return &str[i];
    }
    return NULL;
}

int my_puts(const char* str){
    assert(str != NULL);

    int status;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        int status = putchar(str[i]);
        if (status == EOF)
            return -1;
    }

    putchar('\n');
    return 0;
}

size_t my_strlen(const char* str){
    assert(str != NULL);

    size_t ans = 0;
    for (size_t i = 0; str[i] != '\0'; ++i)
        ans++;
    return ans;

}

char* strcat(char *dest, const char *src){
    assert(dest != NULL);
    assert(src != NULL);

    size_t size_dest = my_strlen(dest);
    size_t i = 0;

    while(true){
        dest[i + size_dest] = src[i];
        if (src[i] == '\0')
            break;
        i++;
    }

    return dest;
}

char* strncat(char *dest, const char *src, size_t n){
    assert(dest != NULL);
    assert(src != NULL);

    size_t size_dest = my_strlen(dest);
    size_t i = 0;

    while(i < n){
        dest[i + size_dest] = src[i];
        if (src[i] == '\0')
            break;
        i++;
    }
    dest[n + size_dest] = '\0';

    return dest;
}

char* strcpy(char* dest, const char* src){
    assert(dest != NULL);
    assert(src != NULL);

    size_t i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char* strncpy(char* dest, const char* src, size_t n){
    assert(dest != NULL);
    assert(src != NULL);

    size_t i = 0;
    while(src[i] != '\0' && i < n){
        dest[i] = src[i];
        i++;
    }
    i++;
    if (i < n) {
        dest[i] = '\0';
        i++;
    }

    return dest;
}

char* fgets(char* dest, size_t n, FILE* name){
    assert(dest != NULL);
    assert(name != NULL);

    n--;
    int char_from_file = '\0';
    size_t i = 0;
    while(i < n){
        char_from_file = fgetc(name);

        if (char_from_file == EOF)
            return NULL;
        else
            dest[i] = char_from_file;


        if (dest[i] == '\n')
            return dest;
    }
    dest[i + 1] = '\0';

    return dest;

}

char* strdup(const char* src){
    assert(src != NULL);

    char* rez = (char* )calloc(my_strlen(src) + 1, 1);
    strcpy(rez, src);

    return rez;
}

int atoi(char* src){
    assert(src != NULL);

    size_t i = 0;
    while (isspace(src[i]))
        i++;

    int sign = 1;

    if (src[i] == '-'){
        sign = -1;
        i++;
    }

    else if (src[i] == '+')
        i++;

    int ans = 0;
    while (src[i] != '\0') {

        if (isdigit(src[i])) {
            ans *= 10;
            ans += src[i] - '0';

        } else
            return sign * ans;
        i++;
    }
}

ssize_t getline(char** dest, size_t* n, FILE* file){
    assert(dest != NULL);
    assert(file != NULL);

    const int INCREASE_BUFFER = 2;
    const int DEFAULT_BUFFER = 1024;

    if (*dest == NULL){
        *n = DEFAULT_BUFFER;
        *dest = (char* )calloc(*n, sizeof(char));
    }

    char char_from_file = '\0';
    size_t counter = 0;
    while(true){
        char_from_file = (char)fgetc(file);

        if (char_from_file == EOF)
            return -1;

        else if (char_from_file == '\n')
            break;

        else if (counter > *n - 1){ //проверка выхода за гарницы массива
           (*n) *= INCREASE_BUFFER;
           char* check = (char* )realloc(*dest, *n);
           if (check == NULL){
                free(*dest);
                *dest = NULL;
                return -1;
           }
            *dest = check;
           (*dest)[counter] = char_from_file;
        }else
            //printf("%c\n", char_from_file);
            (*dest)[counter] = char_from_file;

        counter++;

    }

    (*dest)[counter] = '\0';

    return counter;
}

