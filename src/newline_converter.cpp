#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX_PATH_LEN (1024)

void convert(int choice);
void charRead(void);

int main()
{
    int choice;

    printf("Newline Converter\n");
    printf("1 = Convert to Windows\n2 = Convert to Linux\n3 = Character reader (debug only)\nAnything else to exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    setbuf(stdin, NULL);

    if (choice == 1) convert(1);
    else if (choice == 2) convert(2);
    else if (choice == 3) charRead();
    else printf("Bye!\n");

    return 0;
}

void convert(int choice)
{
    char *fpath = new char[MAX_PATH_LEN + 1];
    int c;

    printf("Input file path: ");
    cin.getline(fpath, MAX_PATH_LEN);
    FILE *fin = fopen(fpath, "rb");
    if (!fin) {
        printf("Input file error!\n");
        exit(-1);
    }
    FILE *fout = fopen(strcat(fpath, ".new"), "wb");

    if (choice == 1) {
        // Convert to Windows: \n -> \r\n
        c = fgetc(fin);
        while (!feof(fin)) {
            if (c == '\n')
                fprintf(fout, "\r\n");
            else
                fprintf(fout, "%c", c);
            c = fgetc(fin);
        }
    }
    else {
        // Convert to Linux: \r\n -> \n
        c = fgetc(fin);
        while (!feof(fin)) {
            if (c != '\r')
                fprintf(fout, "%c", c);
            c = fgetc(fin);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("Operation successful.\n");
}

void charRead()
{
    int n, cnt;
    char c;
    char *fpath = new char[MAX_PATH_LEN + 1];

    printf("Input file path: ");
    cin.getline(fpath, MAX_PATH_LEN);
    FILE *fin = fopen(fpath, "rb");
    if (!fin) {
        printf("Input file error!\n");
        exit(-1);
    }

    printf("Input number of chars to read: ");
    scanf("%d", &n);

    for (cnt = 0; cnt < n; cnt++) {
        fscanf(fin, "%c", &c);
        if (feof(fin)) break;
        if ((int)c >= 32 && (int)c <= 126)
            printf("%d\t%c\n", (int)c, c);
        else
            printf("%d\n", (int)c);
    }

    fclose(fin);
    printf("Operation successful.\n");
}
