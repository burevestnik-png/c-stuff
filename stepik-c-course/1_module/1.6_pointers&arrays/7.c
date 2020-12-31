int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int string_count(char *str) {
    int counter = 0;
    for (int i = 0; str[i] != 0; i++) {
        counter++;
    }
    return counter;
}

int string_words(char *str) {
    int word_counter = 0;

    int temp_i = 0;
    for (int i = 0; str[i]; i++) {
        if (is_whitespace(str[i])) {
            continue;
        }

        word_counter++;
        temp_i = i;
        break;
    }

    for (int i = temp_i; str[i] != 0; i++) {
        if (is_whitespace(str[i])
            && !is_whitespace(str[i + 1])
            && str[i+1] != 0) {
            word_counter++;
        }
    }
    return word_counter;
}