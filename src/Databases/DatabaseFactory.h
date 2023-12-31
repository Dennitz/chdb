#pragma once

#include <Interpreters/Context_fwd.h>
#include <Databases/IDatabase.h>

namespace DB
{

class ASTCreateQuery;

class DatabaseFactory
{
public:
    static DatabasePtr get(const ASTCreateQuery & create, const String & metadata_path, ContextPtr context);

    static DatabasePtr getImpl(const ASTCreateQuery & create, const String & metadata_path, ContextPtr context);
};

}
