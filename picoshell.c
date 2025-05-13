#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

int picoshell_main(int argc, char **argv)
{
    char *line = NULL;
    size_t linecap = 0;

    while (1)
    {
        ssize_t linelen = getline(&line, &linecap, stdin);
        if (linelen < 0)
            break;

        if (linelen > 0 && line[linelen - 1] == '\n')
            line[linelen - 1] = '\0';

        char *p = line;
        while (*p == ' ')
            p++;
        if (*p == '\0')
            continue;

        char *copy = strdup(line);
        if (!copy)
        {
            perror("strdup");
            continue;
        }
        int n_tokens = 0;
        char *tok, *saveptr;
        for (tok = strtok_r(copy, " ", &saveptr);
             tok;
             tok = strtok_r(NULL, " ", &saveptr))
        {
            n_tokens++;
        }
        free(copy);

        char **args = (char **)malloc((n_tokens + 1) * sizeof(char *));
        if (!args)
        {
            perror("malloc");
            continue;
        }
        int i = 0;
        for (tok = strtok_r(line, " ", &saveptr);
             tok;
             tok = strtok_r(NULL, " ", &saveptr))
        {
            args[i++] = tok;
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0)
        {
            printf("Good Bye\n");
            free(args);
            break;
        }

        else if (strcmp(args[0], "cd") == 0)
        {
            char *dir = (n_tokens > 1 ? args[1] : getenv("HOME"));
            if (chdir(dir) != 0)
            {
                fprintf(stderr, "cd: %s: %s\n", dir, strerror(errno));
            }
        }

        else if (strcmp(args[0], "pwd") == 0)
        {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)))
                puts(cwd);
            else
                perror("pwd");
        }

        else if (strcmp(args[0], "echo") == 0)
        {
            for (int j = 1; j < n_tokens; j++)
            {
                fputs(args[j], stdout);
                if (j < n_tokens - 1)
                    putchar(' ');
            }
            putchar('\n');
        }

        else
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork");
            }
            else if (pid == 0)
            {
                execvp(args[0], args);

                fprintf(stderr, "%s: command not found\n", args[0]);
                _exit(127);
            }
            else
            {
                int status;
                if (waitpid(pid, &status, 0) < 0)
                    perror("waitpid");
            }
        }

        free(args);
    }

    free(line);
    return 0;
}
