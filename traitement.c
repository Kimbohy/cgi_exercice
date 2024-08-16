#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *login(char *data)
{
    int truth = 0, j = 0;
    char *log = (char *)malloc(strlen(data) + 1);
    for (int i = 0; data[i] != '&'; i++)
    {
        if (truth == 1)
        {
            log[j] = data[i];
            j++;
        }
        if (data[i] == '=')
        {
            truth = 1;
        }
    }
    log[j] = '\0';
    return log;
}

char *pass(char *data)
{
    int truth = 0, j = 0;
    char *password = (char *)malloc(strlen(data) + 1);
    for (int i = 0; data[i] != '\0'; i++)
    {
        if (truth == 2)
        {
            password[j] = data[i];
            j++;
        }
        if (data[i] == '=')
        {
            truth++;
        }
    }
    password[j] = '\0';
    return password;
}

// functon to check if the login an password is in the file database.txt
int logCheck(char *log, char *pass){
    FILE *file;
    char line[100];
    int found = 0;

    file = fopen("database.txt", "r");
    if (file == NULL) 
    {
        printf("<P>Error opening database file</P>");
        return -1;
    }

    while (fgets(line, sizeof(line), file)) 
    {
        char *stored_log = strtok(line, ",");
        char *stored_pass = strtok(NULL, ",");
        stored_pass[strlen(stored_pass) - 1] = '\0';

        if (strcmp(stored_log, log) == 0 && strcmp(stored_pass, pass) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) 
    {
        printf("<h2>Login successful</h2>");
        printf("<h1>Welcome %s</h1>", log);
        return 1;
    } 
    else
    {
        // send a post request to the page index.cgi (message="Wrong login or password")
        printf("<form action=\"index.cgi\" method=\"post\">");
        printf("    <input type=\"hidden\" name=\"message\" value=\"0\">");
        printf("    <input type=\"text\" name=\"login\" id=\"login\" class=\"form-input\" value=\"%s\">\n", log);
        printf("    <input type=\"password\" name=\"password\" id=\"password\" class=\"form-input\"value=\"%s\">\n", pass);
        printf("</form>");
        printf("<script>document.forms[0].submit();</script>");
        return 0;
    }
}


int main(void)
{
    char *data, *lenstr, *log, *password;
    long len;
    printf("Content-Type:text/html;charset=utf-8\r\n\r\n");
    lenstr = getenv("CONTENT_LENGTH");
    if (lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || (data = (char *)malloc(len + 1)) == NULL)
    {
        printf("<P>Error</P>");
    }
    else
    {
        fgets(data, len + 1, stdin);
        log = login(data);
        password = pass(data);
    }
    logCheck(log, password);
    return 0;
}