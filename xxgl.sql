DROP TABLE IF EXISTS `users`;

CREATE TABLE users(
    uno CHAR(6) NOT NULL,
    uname VARCHAR(10) NOT NULL,
    upassword VARCHAR(10) NOT NULL,
    uclass CHAR(1) NOT NULL DEFAULT 'A',
    PRIMARY KEY(uno)
) ENGINE = InnoDB, DEFAULT CHARSET = utf8;

INSERT INTO users
(uno, uname, upassword, uclass)
VALUES
("123", "nosql", "1234567", 'A');

