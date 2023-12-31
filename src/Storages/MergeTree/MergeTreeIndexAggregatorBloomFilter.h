#pragma once

#include <Storages/MergeTree/MergeTreeIndices.h>
#include <Storages/MergeTree/MergeTreeIndexGranuleBloomFilter.h>
#include <Common/HashTable/HashSet.h>

namespace DB
{

class MergeTreeIndexAggregatorBloomFilter final : public IMergeTreeIndexAggregator
{
public:
    MergeTreeIndexAggregatorBloomFilter(size_t bits_per_row_, size_t hash_functions_, const Names & columns_name_);

    bool empty() const override;

    MergeTreeIndexGranulePtr getGranuleAndReset() override;

    void update(const Block & block, size_t * pos, size_t limit) override;

private:
    size_t bits_per_row;
    size_t hash_functions;
    const Names index_columns_name;

    std::vector<HashSet<UInt64>> column_hashes;
    size_t total_rows = 0;
};

}
