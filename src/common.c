#include <stdio.h>
#include "common.h"

// Error-reporting function
void print_error(MYSQL *conn, char *message) {
    fprintf(stderr, "%s\n", message);
    if (conn != NULL) {
        fprintf(stderr, "Error %u (%s)\n", mysql_errno(conn), mysql_error(conn));
    }
}
