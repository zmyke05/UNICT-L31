  char string1[] = "Ciao";
    puts("");
    printf("%s", string1);
    puts("");

    int len = strlen(string1);
    char reverse[len + 1];

    for (int i = 0; i < len; i ++)
    {
        reverse[i] = string1[len - 1 - i];
    }
    reverse[len] = '\0';
    printf("%s", reverse);
    puts("");