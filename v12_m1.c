#include <stdio.h>
#include <string.h>
#include <ctype.h>

void count_case(const char *s, int *lower, int *upper)
{
    *lower = 0;
    *upper = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (islower(c))
            (*lower)++;
        else if (isupper(c))
            (*upper)++;
    }
}

int main(void)
{
    char s[256];
    int lower, upper;

    printf("Satr kiriting: ");
    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("Kiritishda xato\n");
        return 1;
    }
    s[strcspn(s, "\n")] = '\0';

    count_case(s, &lower, &upper);

    printf("Kichik harflar soni: %d\n", lower);
    printf("Katta harflar soni: %d\n", upper);

    if (lower > upper)
        printf("Natija: kichik harflar ko'p\n");
    else if (upper > lower)
        printf("Natija: katta harflar ko'p\n");
    else
        printf("Natija: kichik va katta harflar soni teng\n");

    return 0;
}
