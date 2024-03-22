dropdb --if-exists hydra
createdb hydra

psql -d hydra < tests/test.sql
# lldb -- psql -d hydra -f tests/test.sql
