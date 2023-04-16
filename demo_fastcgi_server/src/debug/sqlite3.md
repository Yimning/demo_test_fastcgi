
### sqlite3命令
可以按照以下步骤创建一个名为userlist的数据表，并将具有accountNumber，passWord，cardID和userName四个字段的JSON对象插入到新创建的表中，其中accountNumber作为主键：

打开终端或命令提示符窗口，并进入包含数据库文件的目录。

执行sqlite3命令启动SQLite命令行工具，并打开目标数据库文件。例如，要打开名为mydatabase.db的数据库文件，可以输入以下命令：
```
sqlite3 mydatabase.db
```
在SQLite命令行提示符下，输入以下CREATE TABLE语句来创建userlist表：
```
CREATE TABLE userlist (
  accountNumber TEXT PRIMARY KEY NOT NULL,
  passWord TEXT NOT NULL,
  cardID TEXT ,
  userName TEXT 
);

CREATE TABLE userlist (
  accountNumber TEXT PRIMARY KEY NOT NULL,
  passWord TEXT NOT NULL,
  cardID TEXT ,
  userName TEXT 
)CHARACTER SET utf8;
```
创建了一个名为userlist的数据表，其中包含四个字段：accountNumber、passWord、cardID 和 userName。 accountNumber 字段被指定为主键，并使用NOT NULL约束表示该字段不能为空。所有字段都是文本类型。

使用INSERT INTO语句将一个具有accountNumber，passWord，cardID和userName四个字段的JSON对象插入到新创建的表中。例如，以下语句将插入一个名为张三的用户的记录：
```
INSERT INTO userlist (accountNumber, passWord, cardID, userName)
VALUES ('1', '1', '123456', '张三');
```

如果要在userlist表中添加一个名为age的整数列.在SQLite命令行提示符下，输入以下ALTER TABLE语句来修改userlist表并添加age列：
```
ALTER TABLE userlist ADD COLUMN age INTEGER;
```
向userlist表中添加了一个名为age的整数列。
```
UPDATE userlist SET age=18 WHERE accountNumber='1';

# 新插入一条记录
INSERT INTO userlist (accountNumber, passWord, cardID, userName,age)
VALUES ('2', '1', '456789', '李四',20);
```

使用SELECT语句查询新创建的表是否已成功。
```
SELECT * FROM userlist;
```

查询 userlist 表中 accountNumber 值为 "1" 的所有列，并将它们作为结果返回。
```
SELECT * FROM userlist WHERE accountNumber='1';
```

删除 userlist 表中 accountNumber 为 "user1" 的记录，可以执行以下 DELETE 语句：
```
DELETE FROM userlist WHERE accountNumber='user1';
```

在SQLite命令行提示符下，使用.exit命令关闭SQLite命令行工具并退出。
```
.exit
```


### C语言代码实现sqlite3
```
#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // 创建表格
    char *sql_create = "CREATE TABLE IF NOT EXISTS students(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INT);";

    rc = sqlite3_exec(db, sql_create, callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // 插入数据
    char *sql_insert = "INSERT INTO students(name, age) VALUES('Tom', 22);"
                       "INSERT INTO students(name, age) VALUES('Jack', 23);"
                       "INSERT INTO students(name, age) VALUES('Mary', 21);";

    rc = sqlite3_exec(db, sql_insert, callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // 查询数据
    char *sql_select = "SELECT * FROM students;";

    rc = sqlite3_exec(db, sql_select, callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // 更新数据
    char *sql_update = "UPDATE students SET age = 25 WHERE name = 'Tom';";

    rc = sqlite3_exec(db, sql_update, callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // 删除数据
    char *sql_delete = "DELETE FROM students WHERE id = 1;";

    rc = sqlite3_exec(db, sql_delete, callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    return 0;
}
```
在这个示例中，我们使用了以下SQLite3预定义宏：
SQLITE_OK：操作成功完成的返回码。
sqlite3_open()：打开数据库连接函数。
sqlite3_errmsg()：获取最近一次发生错误的文本描述。
sqlite3_close()：关闭数据库连接函数。
SQLITE_CALLBACK：用于执行查询操作时指定回调函数。
sqlite3_exec()：执行SQL语句的函数。
这个示例展示了如何使用SQLite3预定义宏在C程序中执行增删改查操作。需要注意的是，编写SQLite3程序时应该避免出现SQL注入漏洞，对用户输入进行适当的检查和过滤。为了更好地保障数据安全，可以使用SQLite3提供的参数化查询功能。


### 使用SQLite3宏函数替换实现增删改查的简单示例：
```
#include <stdio.h>
#include <sqlite3.h>

#define SQL_CREATE(table, fields) \
    do { \
        const char *sql = "CREATE TABLE IF NOT EXISTS " #table "(" #fields ");"; \
        if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) { \
            fprintf(stderr, "SQL error: %s\n", errMsg); \
            sqlite3_free(errMsg); \
            sqlite3_close(db); \
            return 1; \
        } \
    } while (0)

#define SQL_INSERT(table, fields, values) \
    do { \
        const char *sql = "INSERT INTO " #table "(" #fields ") VALUES(" #values ");"; \
        if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) { \
            fprintf(stderr, "SQL error: %s\n", errMsg); \
            sqlite3_free(errMsg); \
            sqlite3_close(db); \
            return 1; \
        } \
    } while (0)

#define SQL_SELECT(table, fields, where) \
    do { \
        const char *sql = "SELECT " #fields " FROM " #table " WHERE " #where ";"; \
        if (sqlite3_exec(db, sql, callback, NULL, &errMsg) != SQLITE_OK) { \
            fprintf(stderr, "SQL error: %s\n", errMsg); \
            sqlite3_free(errMsg); \
            sqlite3_close(db); \
            return 1; \
        } \
    } while (0)

#define SQL_UPDATE(table, set, where) \
    do { \
        const char *sql = "UPDATE " #table " SET " #set " WHERE " #where ";"; \
        if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) { \
            fprintf(stderr, "SQL error: %s\n", errMsg); \
            sqlite3_free(errMsg); \
            sqlite3_close(db); \
            return 1; \
        } \
    } while (0)

#define SQL_DELETE(table, where) \
    do { \
        const char *sql = "DELETE FROM " #table " WHERE " #where ";"; \
        if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) { \
            fprintf(stderr, "SQL error: %s\n", errMsg); \
            sqlite3_free(errMsg); \
            sqlite3_close(db); \
            return 1; \
        } \
    } while (0)

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // 创建表格
    SQL_CREATE(students, id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INT);

    // 插入数据
    SQL_INSERT(students, name, 'Tom', age, 22);
    SQL_INSERT(students, name, 'Jack', age, 23);
    SQL_INSERT(students, name, 'Mary', age, 21);

    // 查询数据
    SQL_SELECT(students, *, 1);
    SQL_SELECT(students, *, age = 22);

    // 更新数据
    SQL_UPDATE(students, age = 25, name = 'Tom');

    // 删除数据
    SQL_DELETE(students, id = 1);

    sqlite3_close(db);

    return 0;
}
```

### SQLite3输出乱码的问题

设置连接编码方式
在打开数据库连接时，可以通过调用sqlite3_open_v2()函数并设置正确的编码方式来避免乱码问题。例如：
```
rc = sqlite3_open_v2("example.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, "utf-8");
```
需要注意的是，该设置仅在创建新数据库或打开现有数据库时使用。

数据库表编码方式
在创建数据库表时，应确保使用正确的编码方式。可以通过执行以下语句查询已创建的表的编码方式：
```
PRAGMA table_info(table_name);
```
如果编码方式不正确，可以通过以下语句更改表的编码方式：
```
ALTER TABLE table_name CONVERT TO utf8;
```


在执行查询操作时，需要将结果集中的数据进行编码转换。例如，如果结果集中的数据编码方式为UTF-8，而程序需要输出到GBK编码的终端，则需要将其转换成GBK编码，再进行输出。可以使用一些开源库，如iconv或libiconv，进行编码转换。

命令行参数设置
在处理sqlite3命令行工具输出的结果时，可以通过设置命令行参数“-separator”和“-newline”来避免乱码问题。例如：
```
sqlite3 -separator , -newline $'\r\n' example.db 'SELECT * FROM users;'
```
其中，“-separator”参数指定列分隔符为逗号，“-newline”参数指定行结束符为Windows格式的回车换行符。

需要注意的是，在调试过程中，要先确定乱码出现的具体位置，并仔细检查可能导致该问题的因素。



### 更改表字符集(方法1)

例如，要将名为userlist的表转换为UTF-8编码，可以执行以下操作：
```
CREATE TABLE userlist_new (
    -- 列定义
) CHARACTER SET utf8;

CREATE TABLE userlist_new (
  accountNumber TEXT PRIMARY KEY NOT NULL,
  passWord TEXT NOT NULL,
  cardID TEXT ,
  userName TEXT,
  age INT 
) CHARACTER SET utf8;
```
将原始表中的数据复制到新表中。可以使用以下语句：
```
INSERT INTO userlist_new SELECT * FROM userlist;
```

重命名新表，使其名称与原始表相同：
```
ALTER TABLE userlist RENAME TO userlist_old;
ALTER TABLE userlist_new RENAME TO userlist;
```
userlist_old是原始表的备份。在重命名完成后，可以将其删除。

需要注意的是，在进行此操作之前，应该备份原始表数据以便恢复。同时，还需要确保所有相关的索引和约束都正确地转移到了新表中。


### 更改表字符集(方法2)
SQLite不支持在表创建语句中使用CHARACTER SET或CHARSET来指定字符集。如果需要使用特定字符集创建表，可以考虑以下两种方法：

在创建数据库时指定默认字符集
在SQLite中，可以通过在创建数据库时设置参数来指定默认字符集。例如，要将默认字符集设置为UTF-8，可以执行以下操作：
```
sqlite3 mydatabase.db "PRAGMA encoding = 'UTF-8';"
```
这样，在创建表时，就会默认使用UTF-8编码。

通过ALTER TABLE命令修改字符集
如果已经创建了表，并且想要修改其字符集，可以使用ALTER TABLE命令。例如，要将名为userlist的表转换为UTF-8编码，可以执行以下操作：

```
ALTER TABLE userlist RENAME TO userlist_old;
CREATE TABLE userlist (
    accountNumber TEXT PRIMARY KEY NOT NULL,
    passWord TEXT NOT NULL,
    cardID TEXT ,
    userName TEXT,
    age INT
);
INSERT INTO userlist SELECT * FROM userlist_old;
DROP TABLE userlist_old;
```

首先将原始表重命名为备份表，然后创建一个新的userlist表，使用正确的字符集创建列。接着，将备份表中的数据复制到新表中，最后删除备份表。这样就完成了表的字符集转换。

需要注意的是，在进行此操作之前，应该备份原始表数据以便恢复。同时，还需要确保所有相关的索引和约束都正确地转移到了新表中。
