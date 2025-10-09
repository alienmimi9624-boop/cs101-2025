#include <stdio.h>

int main() {
    FILE *fw, *fr;

    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1, 1.2, 1.3};

    int ra[3];
    char rb[4];
    float rc[3];

    fw = fopen("a.bin", "wb");
    fwrite(a, sizeof(a), 1, fw);
    fwrite(b, sizeof(char), 3, fw);
    fwrite(c, sizeof(c), 1, fw);
    fclose(fw);

    fr = fopen("a.bin", "rb");
    fread(ra, sizeof(ra), 1, fr);
    fread(rb, sizeof(char), 3, fr);
    rb[3] = '\0';
    fread(rc, sizeof(rc), 1, fr);
    fclose(fr);

    for (int i = 0; i < 3; i++)
        printf("%d ", ra[i]);
    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%c ", rb[i]);
    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%.6f ", rc[i]);
    printf("\n");

    return 0;
}
