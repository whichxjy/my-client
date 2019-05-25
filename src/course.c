#include <stdio.h>
#include <string.h>
#include "common.h"
#include "course.h"

// Create course table
void create_course_table(MYSQL *conn) {
    // Check if the course table already exists
    MYSQL_RES *res_list = mysql_list_tables(conn, "course");

    if (res_list == NULL) {
        print_error(conn, "mysql_list_tables() failed");
        return;
    }

    int row = mysql_num_rows(res_list);
    mysql_free_result(res_list);

    if (row > 0) {
        // the course table already exists
        printf("The course table already exits. Do you want to delete it?\n");
        printf("Delete the table? (y--yes, n--no): ");
        char yn[2];
        scanf("%s", yn);
        if (yn[0] == 'y' || yn[0] == 'Y') {
            // Delete the course table
            if (mysql_query(conn, "DROP TABLE course;") == 0) {
                printf("Drop course table successfully!\n\n");
            }
            else {
                print_error(conn, "Fail to drop course table");
            }
        }
        else {
            // Not to drop course table
            return;
        }
    }

    // SQL statement for creating course table
    char create_sql[300];
    strcpy(create_sql, "CREATE TABLE course(");
    strcat(create_sql, " cno CHAR(1) NOT NULL,");
    strcat(create_sql, " cname CHAR(10) CHARACTER SET utf8 NULL,");
    strcat(create_sql, " cpno CHAR(1) NULL,");
    strcat(create_sql, " ccredit INT NULL,");
    strcat(create_sql, " PRIMARY KEY(cno)");
    strcat(create_sql, ") ENGINE = InnoDB, DEFAULT CHARSET = utf8;");

    // Create course table
    if (mysql_query(conn, create_sql) == 0) {
        printf("Create course table successfully.\n\n");
    }
    else {
        print_error(conn, "Fail to create course table");
    }
}

// Insert rows into course table
void insert_rows_into_course_table(MYSQL *conn) {
    // Check if the course table exists
    MYSQL_RES *res_list = mysql_list_tables(conn, "course");

    if (res_list == NULL) {
        print_error(conn, "mysql_list_tables() failed");
        return;
    }

    int row = mysql_num_rows(res_list);
    mysql_free_result(res_list);

    if (row == 0) {
        printf("The course table doesn't exist!\n");
        return;
    }

    while (1) {
        printf("\n=================================\n");

        // Get cno
        char cno[2]; 
        printf("Please input cno (e.g., 1): ");
        scanf("%s", cno);

        // Create a query statement
        char check_query[150];
        strcpy(check_query, "SELECT * FROM course WHERE cno=\"");
        strcat(check_query, cno);
        strcat(check_query, "\";");

        // Check if the course already exists
        if (mysql_query(conn, check_query) == 1) {
            print_error(conn, "mysql_query() failed");
            continue;
        }
        else {
            MYSQL_RES *res_set = mysql_store_result(conn);

            if (res_set == NULL) {
                print_error(conn, "mysql_store_result() failed");
                continue;
            }

            int row = mysql_num_rows(res_set);
            mysql_free_result(res_set);

            if (row > 0) {
                printf("The course already exists!\n\n");
                continue;
            }
        }

        // Get cname
        char cname[11];
        printf("Please input cname (e.g., 数据库系统): ");
        scanf("%s", cname);

        // Get cpno
        char cpno[2];
        printf("Please input cpno (e.g., 5): ");
        scanf("%s", cpno);

        // Get ccredit
        char ccredit[20];
        printf("Please input ccredit (e.g., 4): ");
        scanf("%s", ccredit);

        // Create insert statement
        char insert_sql[300];
        strcpy(insert_sql, "INSERT INTO course");
        strcat(insert_sql, "(cno, cname, cpno, ccredit) ");
        strcat(insert_sql, "VALUES");
        strcat(insert_sql, "(\"");
        strcat(insert_sql, cno);
        strcat(insert_sql, "\", \"");
        strcat(insert_sql, cname);
        strcat(insert_sql, "\", \"");
        strcat(insert_sql, cpno);
        strcat(insert_sql, "\", ");
        strcat(insert_sql, ccredit);
        strcat(insert_sql, ");");

        if (mysql_query(conn, insert_sql) == 0) {
            printf("Insert course successfully.\n\n");
        }
        else {
            print_error(conn, "Fail to insert course");
        }

        // Continue to insert?
        printf("Continue to insert?  (y--yes, n--no): ");
        char yn[2];
        scanf("%s", yn);
        if (yn[0] == 'y' || yn[0] == 'Y') {
            continue;
        }
        else {
            break;
        }
    }
}
