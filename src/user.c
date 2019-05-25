#include <stdio.h>
#include <string.h>
#include "common.h"
#include "user.h"

// Check user's name and password
int check_username_password(MYSQL *conn) {
    // Check if the connection is ok
    if (conn == NULL) {
        return 0;
    }

    // Get user's name
    char name[10];
    printf("Please enter your name: ");
    scanf("%s", name);

    // Get user's password
    char passwd[10];
    printf("Please enter your password: ");
    scanf("%s", passwd);

    // Create a query statement
    char query[200];
    strcpy(query, "SELECT * FROM users WHERE uname=\"");
    strcat(query, name);
    strcat(query, "\" AND upassword=\"");
    strcat(query, passwd);
    strcat(query, "\";");
   
    // Check if the user exists
    if (mysql_query(conn, query) == 1) {
        print_error(conn, "mysql_query() failed");
        return 0;
    }
    else {
        // result set
        MYSQL_RES *res_set = mysql_store_result(conn);

        if (res_set == NULL) {
            print_error(conn, "mysql_store_result() failed");
            return 0;
        }

        int row = mysql_num_rows(res_set);
        mysql_free_result(res_set);

        if (row == 0) {
            printf("Fail to login.\n");
            return 0;
        }
        else {
            printf("Login succeeds.\n");
            return 1;
        }
    }
}
