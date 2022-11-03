#ifndef KAWPOW_HASH_H
#define KAWPOW_HASH_H

#include "helpers.hpp"

void update_epoch(int& header_height);
uint256 kawpow_fullhash(uint256& header_hash, uint64_t& header_nonce, uint256& mix_hash);
uint256 kawpow_hash(uint256& header_hash, uint64_t& header_nonce);
uint256 kawpow_hash(std::string& header_hash, std::string& header_nonce, std::string& mix_real);

#endif // KAWPOW_HASH_H
