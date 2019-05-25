# my-client

A simple course management system. It's my homework for the course **Database Systems**.

## Dependency

- MySQL

```makefile
# Debian-based Linux
sudo apt-get install mysql-server mysql-client
sudo mysql_secure_installation
```

- MySQL C development libraries

```makefile
# Debian-based Linux
sudo apt-get install libmysqlclient-dev
```

## Usage

1. Get the code.

```
git clone https://github.com/whichxjy/my-client.git
```

2. Change directory.

```
cd my-client
```

3. Create and initialize `xxgl` database in MySQL.

```sql
mysql> CREATE DATABASE xxgl;
mysql> USE xxgl;
mysql> SOURCE xxgl.sql;
```

4. Fill in the blank (host to connect to, username, password) in `src/main.c`.

5. Run the program.

```
make run
```
