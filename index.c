#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
        printf("<form action=\"index.cgi\" method=\"post\">");
        printf("    <input type=\"hidden\" name=\"message\" value=\"0\">");
        printf("    <input type=\"text\" name=\"login\" id=\"login\" class=\"form-input\">\n");
        printf("    <input type=\"password\" name=\"password\" id=\"password\" class=\"form-input\">\n");
        printf("</form>");
        printf("<script>document.forms[0].submit();</script>");
*/
void getStatus(){
    long len;
    char *lenstr = getenv("CONTENT_LENGTH"), *data;
    if (!(lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || (data = (char *)malloc(len + 1)) == NULL))
    {
        fgets(data, len + 1, stdin);
        if (data[8] == '0')
        {
            printf("<p class=\"error\">Wrong login or password</p>");
        }
    }
}

// data = "message=0&login=test&password=pass"
void getPostData(char *data, char *log, char *password){
    long len;
    char *lenstr = getenv("CONTENT_LENGTH");
    if (!(lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || (data = (char *)malloc(len + 1)) == NULL))
    {
        fgets(data, len + 1, stdin);
    }
}

int main() {
    char *data, *log, *password;

    // Output the HTTP header
    printf("Content-Type:text/html;charset=utf-8\r\n\r\n");
    getPostData(data, log, password);

    // Output the HTML content
    printf("<!DOCTYPE html>\n");
    printf("<html lang=\"en\">\n");
    printf("<head>\n");
    printf("    <meta charset=\"UTF-8\">\n");
    printf("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    printf("    <link rel=\"stylesheet\" href=\"style.css\">\n");
    printf("    <title>Login Form</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("    <div class=\"container\">\n");
    printf("        <form method=\"post\" action=\"./traitement.cgi\" class=\"login-form\">\n");
    printf("            <label for=\"login\" class=\"form-label\">Login :</label>\n");
    printf("            <input type=\"text\" name=\"login\" id=\"login\" class=\"form-input\" value=\"%s\">\n", "");
    printf("            <label for=\"password\" class=\"form-label\">Password :</label>\n");
    printf("            <input type=\"password\" name=\"password\" id=\"password\" class=\"form-input\" value=\"%s\">\n", "");
    getStatus();
    printf("            <input type=\"submit\" value=\"Submit\" class=\"submit-button\">\n");
    printf("        </form>\n");
    printf("    </div>\n");
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}
