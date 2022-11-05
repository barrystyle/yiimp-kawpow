#ifndef KAWPOW_HASH_H
#define KAWPOW_HASH_H

#include "helpers.hpp"

const uint256 badhash = uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

void update_epoch(const int& coinid, int& height);
uint256 kawpow_fullhash(uint256& header_hash, uint64_t& header_nonce, uint256& mix_hash, int& coinid);
uint256 kawpow_hash(std::string& header_hash, std::string& header_nonce, std::string& mix_real, int& coinid);

#endif // KAWPOW_HASH_H
