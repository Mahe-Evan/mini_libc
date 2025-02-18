#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>

int my_strlen(char *str)
{
    void *handle;
    int (*my_strlen)(char *);
    int length;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    my_strlen = dlsym(handle, "strlen");
    if (!my_strlen) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    length = my_strlen(str);
    dlclose(handle);
    return length;
}

int my_strcmp(char *s1, char *s2)
{
    void *handle;
    int (*my_strcmp)(char *, char *);
    int result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    my_strcmp = dlsym(handle, "strcmp");
    if (!my_strcmp) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    result = my_strcmp(s1, s2);
    dlclose(handle);
    return result;
}

int my_strcasecmp(char *s1, char *s2)
{
    void *handle;
    int (*my_strcasecmp)(char *, char *);
    int result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    my_strcasecmp = dlsym(handle, "strcasecmp");
    if (!my_strcasecmp) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    result = my_strcasecmp(s1, s2);
    dlclose(handle);
    return result;
}

int my_strncmp(char *s1, char *s2, size_t n)
{
    void *handle;
    int (*my_strncmp)(char *, char *, size_t);
    int result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    my_strncmp = dlsym(handle, "strncmp");
    if (!my_strncmp) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    result = my_strncmp(s1, s2, n);
    dlclose(handle);
    return result;
}

char *my_strstr(char *str, char *to_find)
{
    void *handle;
    char *(*my_strstr)(char *, char *);
    char *result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_strstr = dlsym(handle, "strstr");
    if (!my_strstr) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    result = my_strstr(str, to_find);
    dlclose(handle);
    return result;
}

void *my_memcpy(void *dest, const void *src, size_t n)
{
    void *handle;
    void *(*my_memcpy)(void *, const void *, size_t);

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_memcpy = dlsym(handle, "memcpy");
    if (!my_memcpy) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    my_memcpy(dest, src, n);
    dlclose(handle);
    return dest;
}

void *my_memset(void *s, int c, size_t n)
{
    void *handle;
    void *(*my_memset)(void *, int, size_t);

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_memset = dlsym(handle, "memset");
    if (!my_memset) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    my_memset(s, c, n);
    dlclose(handle);
    return s;
}

void *my_memmove(void *dest, const void *src, size_t n)
{
    void *handle;
    void *(*my_memmove)(void *, const void *, size_t);

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_memmove = dlsym(handle, "memmove");
    if (!my_memmove) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    my_memmove(dest, src, n);
    dlclose(handle);
    return dest;
}

char *my_strchr(char *s, int c)
{
    void *handle;
    char *(*my_strchr)(char *, int);
    char *result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_strchr = dlsym(handle, "strchr");
    if (!my_strchr) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    result = my_strchr(s, c);
    dlclose(handle);
    return result;
}

char *my_strrchr(char *s, int c)
{
    void *handle;
    char *(*my_strrchr)(char *, int);
    char *result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_strrchr = dlsym(handle, "strrchr");
    if (!my_strrchr) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    result = my_strrchr(s, c);
    dlclose(handle);
    return result;
}

char *my_strpbrk(char *s, char *accept)
{
    void *handle;
    char *(*my_strpbrk)(char *, char *);
    char *result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return NULL;
    }
    my_strpbrk = dlsym(handle, "strpbrk");
    if (!my_strpbrk) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return NULL;
    }
    result = my_strpbrk(s, accept);
    dlclose(handle);
    return result;
}

size_t my_strcspn(char *s, char *reject)
{
    void *handle;
    size_t (*my_strcspn)(char *, char *);
    size_t result;

    handle = dlopen("./libasm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    my_strcspn = dlsym(handle, "strcspn");
    if (!my_strcspn) {
        fprintf(stderr, "%s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    result = my_strcspn(s, reject);
    dlclose(handle);
    return result;
}

int main(void)
{
    printf("strlen 'Hello, World!' = %d\n", my_strlen("Hello, World!"));
    printf("strlen '' = %d\n", my_strlen(""));

    printf("strcmp equal = %d\n", my_strcmp("Hello, World!", "Hello, World!"));
    printf("strcmp < = %d\n", my_strcmp("Hallo, World!", "Hello, World!"));
    printf("strcmp > = %d\n", my_strcmp("Hello, World!", "Hallo World!"));
    printf("strcmp upper case diff = %d\n", my_strcmp("Hello, World!", "hello, World!"));
    printf("strcmp lower case diff = %d\n", my_strcmp("hello, World!", "Hello, world!"));

    printf("strncmp equal = %d\n", my_strncmp("Hello, World!", "Hello, World!", 13));
    printf("strncmp < = %d\n", my_strncmp("Hallo, World!", "Hello, World!", 13));
    printf("strncmp > = %d\n", my_strncmp("Hello, World!", "Hallo World!", 13));
    printf("strncmp upper case diff = %d\n", my_strncmp("Hello, World!", "hello, World!", 13));
    printf("strncmp lower case diff = %d\n", my_strncmp("hello, World!", "Hello, world!", 13));
    printf("strcmp length 1 = %d\n", my_strncmp("Hello, World!", "Hello, World!", 1));
    printf("strcmp length 1 but char 2 < = %d\n", my_strncmp("Hello, World!", "Hallo, World!", 1));

    printf("strchr in = %s\n", my_strchr("Hello, World!", 'W'));
    printf("strchr not in = %s\n", my_strchr("Hello, World!", 'z'));
    printf("strchir with \\0 = %s\n", my_strchr("Hello, World!", '\0'));

    printf("strrchr in = %s\n", my_strrchr("Hello, World!", 'o'));
    printf("strrchr not in = %s\n", my_strrchr("Hello, World!", 'z'));
    printf("strrchr with \\0 = %s\n", my_strrchr("Hello, World!", '\0'));

    char dest[14] = "\0";
    printf("memcpy = %s\n", (char *)my_memcpy(dest, "Hello, World!", 13));
    printf("memcpy overlap = %s\n", (char *)my_memcpy(dest + 5, dest, 5));
    printf("memcpy diff size = %s\n", (char *)my_memcpy(dest, "Test", 4));
    printf("memcpy diff size > lenght src = %s\n", (char *)my_memcpy(dest, "Test", 7));

    char str[14] = "hhhhh\0";
    printf("memset = %s\n", (char *)my_memset(str, 'a', 13));
    printf("memset /0 = %s\n", (char *)my_memset(str, '\0', 1));
    printf("memset int = %s\n", (char *)my_memset(str, 97, 13));

    char str2[14] = "hhhhh\0";
    printf("memmove = %s\n", (char *)my_memmove(str2, "Hello, World!", 13));
    printf("memmove overlap = %s\n", (char *)my_memmove(str2 + 5, str2, 5));
    printf("memmove diff size = %s\n", (char *)my_memmove(str2, "Test", 4));
    printf("memmove diff size > lenght src = %s\n", (char *)my_memmove(str2, "Test", 7));

    printf("strcasecmp equal = %d\n", my_strcasecmp("Hello, World!", "Hello, World!"));
    printf("strcasecmp < = %d\n", my_strcasecmp("Hallo, World!", "Hello, World!"));
    printf("strcasecmp > = %d\n", my_strcasecmp("Hello, World!", "Hallo World!"));
    printf("strcasecmp upper case diff = %d\n", my_strcasecmp("hello, World!", "hello, world!"));
    printf("strcasecmp lower case diff = %d\n", my_strcasecmp("hello, World!", "hello, world!"));
    printf("strcasecmp first car lower case diff = %d\n", my_strcasecmp("hello, World!", "Hello, World!"));
    printf("strcasecmp first car upper case diff = %d\n", my_strcasecmp("Hello, World!", "hello, World!"));

    printf("strstr in = %s\n", my_strstr("Hello, World!", "World"));
    printf("strstr not in = %s\n", my_strstr("Hello, World!", "z"));
    printf("strstr empty = %s\n", my_strstr("", "z"));
    printf("strstr empty = %s\n", my_strstr("Hello, World!", ""));

    printf("strpbrk in = %s\n", my_strpbrk("Hello, World!", "W"));
    printf("strpbrk not in = %s\n", my_strpbrk("Hello, World!", "z"));
    printf("strpbrk empty = %s\n", my_strpbrk("", "z"));
    printf("strpbrk empty = %s\n", my_strpbrk("Hello, World!", ""));
    printf("strpbrk in = %s\n", my_strpbrk("Hello, World!", "aeiou"));
    printf("strpbrk not in = %s\n", my_strpbrk("Hello, World!", "zy"));
    printf("strpbrk \\0 = %s\n", my_strpbrk("Hello, World!", "\0"));

    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "aeiou"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "z"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "zH"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "zHl"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "zHlo"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "xyz"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "W"));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", " "));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", ","));
    printf("strcspn = %ld\n", my_strcspn("Hello, World!", "!"));
    return 0;
}