# pg_quack

pg_quack is PostgreSQL with Embedded DuckDB :duck:

## Installation

1. `make install`
1. (Optional) Create quack directory and set permissions so PostgreSQL process can write to it.
   Directory can be changed with `quack.data_dir` configuration parameter. By default, the
   directory is `quack` in your Postgres data directory.

```
postgres=# show quack.data_dir ;
           quack.data_dir
------------------------------------
 /opt/database/postgres/data/quack/
(1 row)

postgres=#
```

## Usage

```
CREATE TABLE quack_test (...) USING quack;
```

### Limitations

* Only COPY, INSERT, and SELECT are supported.
* Only single connection can execute INSERT and SELECT against quack table
* Limited support for only basic data types
* You cannot query between `quack` tables and other storage methods (including Postgres `heap` tables).
