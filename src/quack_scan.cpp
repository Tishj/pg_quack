
//#ifdef FATAL
//#undef FATAL
//#endif

#include "duckdb.hpp"
#include "quack.hpp"

extern "C" {

#include "postgres.h"

#include "miscadmin.h"

#include "access/tableam.h"
#include "executor/executor.h"
#include "parser/parse_type.h"
#include "tcop/utility.h"
#include "catalog/pg_type.h"
#include "utils/syscache.h"
#include "utils/builtins.h"

}

namespace duckdb {

unique_ptr<TableRef> PostgresReplacementScan(ClientContext &context, const string &table_name, ReplacementScanData *data) {
	return nullptr;
}

} // namespace duckdb
