#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void to_int(char *s, int *arr, int *size)
{
    *size = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '0' || s[i] == '1')
        {
            arr[*size] = s[i] - '0';
            (*size)++;
        }
        else
        {
            printf("Invalid input: Only binary digits (0 or 1) are allowed.\n");
            exit(1);
        }
    }
}

int bitstuff(int *data, int size, int *stuffed)
{
    int b1 = 0;
    int j = 0;

    for (int i = 0; i < size; i++)
    {
        if (data[i] == 1)
        {
            b1++;
            stuffed[j++] = data[i];
            if (b1 == 5)
            {
                stuffed[j++] = 0;
                b1 = 0;
            }
        }
        else
        {
            stuffed[j++] = data[i];
            b1 = 0;
        }
    }

    return j;
}

int unbitstuff(int *data, int size, int *unstuffed)
{
    int b1 = 0;
    int j = 0;

    for (int i = 0; i < size; i++)
    {
        if (data[i] == 1)
        {
            b1++;
            unstuffed[j++] = data[i];
        }
        else
        {
            if (b1 == 5)
            {
                b1 = 0;
                continue;
            }
            unstuffed[j++] = data[i];
            b1 = 0;
        }
    }

    return j;
}

int main()
{
    char s[100];
    int data[100], stuffed[200], unstuffed[200];
    int size = 0, stuffed_size = 0, unstuffed_size = 0;

    printf("Enter a binary string: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    to_int(s, data, &size);

    stuffed_size = bitstuff(data, size, stuffed);

    unstuffed_size = unbitstuff(stuffed, stuffed_size, unstuffed);

    printf("Original Data:   ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", data[i]);
    }
    printf("\n");

    printf("Stuffed Data:    ");
    for (int i = 0; i < stuffed_size; i++)
    {
        printf("%d", stuffed[i]);
    }
    printf("\n");

    printf("Unstuffed Data:  ");
    for (int i = 0; i < unstuffed_size; i++)
    {
        printf("%d", unstuffed[i]);
    }
    printf("\n");

    return 0;
}
