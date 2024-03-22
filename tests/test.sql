create extension quack;
create table tbl (a varchar) using quack;
insert into tbl values ('hello');
select * from tbl;
