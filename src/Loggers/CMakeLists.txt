add_headers_and_sources(loggers .)

# Standard version depends on DBMS and works with text log
add_library(loggers ${loggers_sources} ${loggers_headers})
target_link_libraries(loggers PRIVATE dbms clickhouse_common_io)
if (TARGET ch_contrib::jemalloc)
    target_link_libraries(loggers PRIVATE ch_contrib::jemalloc)
endif ()

# Lightweight version doesn't work with textlog and also doesn't depend on DBMS
add_library(loggers_no_text_log ${loggers_sources} ${loggers_headers})
target_compile_definitions(loggers_no_text_log PUBLIC WITHOUT_TEXT_LOG=1)
target_link_libraries(loggers_no_text_log PRIVATE clickhouse_common_io)
