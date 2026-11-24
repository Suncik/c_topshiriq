#include <stdio.h>
#include <string.h>

long file_size(FILE *fp)
{
    long size;
    if (fseek(fp, 0, SEEK_END) != 0)
        return -1;
    size = ftell(fp);
    rewind(fp);
    return size;
}

int write_reverse(FILE *in, FILE *out, long size)
{
    for (long i = size - 1; i >= 0; i--) {
        int c;
        if (fseek(in, i, SEEK_SET) != 0)
            return -1;
        c = fgetc(in);
        if (c == EOF)
            return -1;
        fputc(c, out);
    }
    return 0;
}

int main(void)
{
    char name[256];
    FILE *in, *out;
    long size;

    printf("Fayl nomini kiriting (bo'sh qoldirilsa input.txt): ");
    if (fgets(name, sizeof(name), stdin) == NULL)
        name[0] = '\0';
    name[strcspn(name, "\n")] = '\0';
    if (name[0] == '\0')
        strcpy(name, "input.txt");

    in = fopen(name, "rb");
    if (in == NULL) {
        perror(name);
        return 1;
    }

    size = file_size(in);
    if (size < 0) {
        perror("fseek/ftell");
        fclose(in);
        return 1;
    }
    printf("Fayl hajmi: %ld bayt\n", size);

    out = fopen("reverse.txt", "wb");
    if (out == NULL) {
        perror("reverse.txt");
        fclose(in);
        return 1;
    }

    if (write_reverse(in, out, size) != 0) {
        perror("O'qishda xato");
        fclose(in);
        fclose(out);
        return 1;
    }

    fclose(in);
    fclose(out);
    printf("Teskari tartibdagi matn reverse.txt fayliga yozildi\n");
    return 0;
}
