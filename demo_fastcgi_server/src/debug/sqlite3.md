
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