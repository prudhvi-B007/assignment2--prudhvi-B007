#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // open syslog
    openlog(NULL, 0, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Error: two arguments required: <writefile> <writestr>");
        fprintf(stderr, "Error: two arguments required: <writefile> <writestr>\n");
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // log debug message
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    FILE *fp = fopen(writefile, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Error opening file %s", writefile);
        perror("Error opening file");
        closelog();
        return 1;
    }

    if (fputs(writestr, fp) == EOF) {
        syslog(LOG_ERR, "Error writing to file %s", writefile);
        perror("Error writing to file");
        fclose(fp);
        closelog();
        return 1;
    }

    fclose(fp);
    closelog();
    return 0;
}

