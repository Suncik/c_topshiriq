#include <stdio.h>
#include <string.h>

#define MAX 256
#define RES_MAX 1024

int replace_all(const char *src, const char *old_w, const char *new_w, char *res, size_t res_size)
{
    size_t old_len = strlen(old_w);
    size_t new_len = strlen(new_w);
    size_t pos = 0;
    int count = 0;
    const char *p = src;
    const char *found;

    res[0] = '\0';
    if (old_len == 0) {
        strncpy(res, src, res_size - 1);
        res[res_size - 1] = '\0';
        return 0;
    }

    while ((found = strstr(p, old_w)) != NULL) {
        size_t part = (size_t)(found - p);
        if (pos + part + new_len >= res_size)
            return -1;
        memcpy(res + pos, p, part);
        pos += part;
        memcpy(res + pos, new_w, new_len);
        pos += new_len;
        p = found + old_len;
        count++;
    }

    if (pos + strlen(p) >= res_size)
        return -1;
    strcpy(res + pos, p);
    return count;
}

void read_line(const char *msg, char *buf, size_t size)
{
    printf("%s", msg);
    if (fgets(buf, (int)size, stdin) == NULL)
        buf[0] = '\0';
    buf[strcspn(buf, "\n")] = '\0';
}

int main(void)
{
    char text[MAX], old_w[MAX], new_w[MAX], result[RES_MAX];
    int n;

    read_line("Satr kiriting: ", text, sizeof(text));
    read_line("Almashtiriladigan so'z: ", old_w, sizeof(old_w));
    read_line("Yangi so'z: ", new_w, sizeof(new_w));

    n = replace_all(text, old_w, new_w, result, sizeof(result));
    if (n < 0) {
        printf("Xato: natija buferga sig'madi\n");
        return 1;
    }

    printf("Almashtirishlar soni: %d\n", n);
    printf("Natija: %s\n", result);
    return 0;
}
