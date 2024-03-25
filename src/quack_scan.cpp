
//#ifdef FATAL
//#undef FATAL
//#endif

#include "duckdb.hpp"
#include "quack.hpp"
#include "quack_scan.hpp"

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

// ------- Table Function -------

PostgresScanFunction::PostgresScanFunction()
    : TableFunction("postgres_scan", {LogicalType::POINTER}, PostgresFunc, PostgresBind, PostgresInitGlobal,
                    PostgresInitLocal) {
}

unique_ptr<FunctionData> PostgresScanFunction::PostgresBind(ClientContext &context, TableFunctionBindInput &input,
                                                            vector<LogicalType> &return_types, vector<string> &names) {
	auto desc = (reinterpret_cast<QueryDesc *>(input.inputs[0].GetPointer()));
	return nullptr;
}

unique_ptr<GlobalTableFunctionState> PostgresScanFunction::PostgresInitGlobal(ClientContext &context,
                                                                              TableFunctionInitInput &input) {
	return nullptr;
}

unique_ptr<LocalTableFunctionState> PostgresScanFunction::PostgresInitLocal(ExecutionContext &context,
                                                                            TableFunctionInitInput &input,
                                                                            GlobalTableFunctionState *gstate) {
	return nullptr;
}

void PostgresScanFunction::PostgresFunc(ClientContext &context, TableFunctionInput &data_p, DataChunk &output) {
	// Use the Table AM to scan from the postgres table
}

// ------- Table Function Info
// Essentially the state we can transfer from replacement scan

// ------- Replacement Scan -------

PostgresReplacementScanData::PostgresReplacementScanData(QueryDesc *desc) : desc(desc) {
}
PostgresReplacementScanData::~PostgresReplacementScanData() {
}

unique_ptr<TableRef> PostgresReplacementScan(ClientContext &context, const string &table_name,
                                             ReplacementScanData *data) {
	auto &scan_data = reinterpret_cast<PostgresReplacementScanData &>(*data);
	// Use 'QueryDesc *desc' to query the postgres table
	// We will return a custom table function scan with parameters (likely passing a pointer as parameter)

	// Then inside the table function we can scan tuples from the postgres table and convert them into duckdb vectors.
	auto table_function = make_uniq<TableFunctionRef>();
	vector<unique_ptr<ParsedExpression>> children;
	for (auto &param : info.parameters) {
		children.push_back(make_uniq<ConstantExpression>(Value::POINTER(CastPointerToValue(scan_data.desc))));
	}
	table_function->function = make_uniq<FunctionExpression>("postgres_scan", std::move(children));
	return std::move(table_function);
}

} // namespace duckdb
