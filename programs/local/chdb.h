#pragma once
#include <cstdint>
#include <stddef.h>

extern "C" {
typedef void* ChdbLocalServerPtr;

struct chdb_local_result
{
    char * buf;
    size_t len;
    void * _vec; // std::vector<char> *, for freeing
    double elapsed;
    uint64_t rows_read;
    uint64_t bytes_read;
    char * error_message;
};

struct chdb_init_result
{
   ChdbLocalServerPtr local_server;
   char * error_message;
};

chdb_init_result * chdb_connect(int argc, char ** argv);
void chdb_disconnect(ChdbLocalServerPtr obj);
chdb_local_result * chdb_query(ChdbLocalServerPtr obj, char * query, char * format);
void chdb_free_result(ChdbLocalServerPtr obj, chdb_local_result * result);
void chdb_set_named_collections(ChdbLocalServerPtr obj, char * named_collection_config_xml);
}
