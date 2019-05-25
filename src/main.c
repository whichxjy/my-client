#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "common.h"
#include "user.h"
#include "course.h"

#define def_host_name NULL          // host to connect to
#define def_user_name NULL          // user name
#define def_password NULL           // password
#define def_db_name "xxgl"          // database to use
#define def_port_num 0              // port (use default)
#define def_socket_name NULL        // socket (use default)
#define def_client_flag 0           // client flag (none)

int main(int argc, char **argv) {
    // MySQL connection handler
    MYSQL *conn = mysql_init(NULL);
    
    if (conn == NULL) {
        print_error(NULL, "Fail to initialize");
        return EXIT_FAILURE;
    }

    // enum mysql_protocol_type prot_type = MYSQL_PROTOCOL_TCP;
    // mysql_options(conn, MYSQL_OPT_PROTOCOL, (void *)&prot_type);

    if (mysql_real_connect(
                    conn,
                    def_host_name,
                    def_user_name,
                    def_password,
                    def_db_name,
                    def_port_num,
                    def_socket_name,
                    def_client_flag)
                == NULL) {
        print_error(conn, "Fail to connect");
        return EXIT_FAILURE;
    }

    mysql_query(conn, "SET character_set_connection = utf8"); 
    mysql_query(conn, "SET character_set_server = utf8");
    mysql_query(conn, "SET character_set_client = utf8");
    mysql_query(conn, "SET character_set_database = utf8");
    mysql_query(conn, "SET character_set_results = utf8");
    mysql_query(conn, "SET NAMES utf8");

    if (check_username_password(conn)) {
        while (1) {
            printf("\n==========================================\n");
            printf("[Embedded MySQL for C application]\n");
            printf("Please select one function to execute:\n\n");
            printf("0--Exit.\n");
            printf("1--Create course table.\n");
            printf("2--Insert rows to course table.\n");
            printf("\n");

            // Function
            char fu[2];
            fu[0] = '0';

            printf("Your choice: ");
            scanf("%s", fu);

            if (fu[0] == '0') {
                break;
            }
            else if (fu[0] == '1') {
                create_course_table(conn);
            }
            else if (fu[0] == '2') {
                insert_rows_into_course_table(conn);
            }
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}

