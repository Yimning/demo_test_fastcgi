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