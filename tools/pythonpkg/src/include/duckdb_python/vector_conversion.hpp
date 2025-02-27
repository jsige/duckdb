//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb_python/array_wrapper.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb_python/pybind_wrapper.hpp"

#include "duckdb.hpp"

namespace duckdb {

enum class PandasType : uint8_t {
	BOOLEAN,
	TINYINT,
	SMALLINT,
	INTEGER,
	BIGINT,
	UTINYINT,
	USMALLINT,
	UINTEGER,
	UBIGINT,
	FLOAT,
	DOUBLE,
	TIMESTAMP,
	INTERVAL,
	VARCHAR,
	OBJECT
};

struct NumPyArrayWrapper {
	explicit NumPyArrayWrapper(py::array numpy_array) : numpy_array(move(numpy_array)) {
	}

	py::array numpy_array;
};

struct PandasColumnBindData {
	PandasType pandas_type;
	py::array numpy_col;
	idx_t numpy_stride;
	unique_ptr<NumPyArrayWrapper> mask;
};

class VectorConversion {
public:
	static void NumpyToDuckDB(PandasColumnBindData &bind_data, py::array &numpy_col, idx_t count, idx_t offset,
	                          Vector &out);

	static void BindPandas(py::handle df, vector<PandasColumnBindData> &out, vector<LogicalType> &return_types,
	                       vector<string> &names);
};

} // namespace duckdb
