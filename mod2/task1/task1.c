#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findNameByLogin(char *login, char *name_buf) {
    FILE *file = fopen("/etc/passwd", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    char *line = (char*)malloc(1000 * sizeof(char));
    if (line == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(file);
        return 1;
    }

    while (fgets(line, 1000, file) != NULL) {
        int index = 0;
        while (login[index] != '\0' && line[index] == login[index]) {
            index++;
        }
        if (line[index] == ':') {  // same length
            index++;
            while (line[index++] != ':') {}
            while (line[index++] != ':') {}
            while (line[index++] != ':') {}
            int name_index = 0;
            while (line[index] != ':' && line[index] != ',') {
                name_buf[name_index++] = line[index++];
            }
            name_buf[name_index] = '\0';
            fclose(file);
            free(line);
            return 0;
        }
    }
    fclose(file);
    free(line);
    return 1;
}

int main() {
    char *login = (char*)malloc(100 * sizeof(char));
    if (!login) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    printf("Enter login: ");
    if (scanf("%s", login) != 1) {
        free(login);
        fprintf(stderr, "Scanf error\n");
        return 1;
    }
    if (login[0] == '\0') {
        free(login);
        printf("The username was entered incorrectly\n");
        return 0;
    }

    char *name = (char*)malloc(100 * sizeof(char));
    if (!name) {
        free(login);
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    if (findNameByLogin(login, name) != 0) {
        printf("User not found\n");
    } else {
        printf("User's name: %s\n", name);
    }

    free(name);
    free(login);
    return 0;
}
