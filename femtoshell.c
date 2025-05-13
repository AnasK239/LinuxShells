#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char userInput[10240];
    char cmd[10240];
    
    while (1) {
        printf("Femto shell prompt > ");
        
        if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
            printf("\n");
            return 0;
        }
        
        size_t inputLength = strcspn(userInput, "\n");
        userInput[inputLength] = '\0';
        
        if (inputLength == 0) {
            printf("\n");
            continue;
        }
        
        int index = 0;
        while (index < inputLength && userInput[index] != ' ' && userInput[index] != '\0') {
            cmd[index] = userInput[index];
            index++;
        }
        cmd[index] = '\0';
        
        if (strcmp(cmd, "exit") == 0) {
            printf("\nGood Bye\n");
            return 0;
        } else if (strcmp(cmd, "echo") == 0) {
            if (index + 1 < inputLength) {
                printf("\n%s\n", &userInput[index + 1]);
            } else {
                printf("\n\n");
            }
        } else if (index < inputLength && userInput[index] == ' ') {
            printf("\nInvalid command\n");
        } else {
            printf("\n%s\n", userInput);
        }
    }
    
    return 0;
}
