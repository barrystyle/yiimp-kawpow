#include "stratum.h"
#include "include/ethash/progpow.hpp"

int cache_height;
ethash::epoch_context_ptr context{nullptr, nullptr};

void update_epoch(int& header_height)
{
    CommonLock(&g_context_mutex);

    cache_height = header_height;
    const auto epoch_number = ethash::get_epoch_number(header_height);
    if (!context || context->epoch_number != epoch_number) {
        context = ethash::create_epoch_context(epoch_number);
    }

    CommonUnlock(&g_context_mutex);
}

uint256 kawpow_fullhash(uint256& header_hash, uint64_t& header_nonce, uint256& mix_hash)
{
    const auto hash = to_hash256(header_hash.ToString());
    const auto result = progpow::hash(*context, cache_height, hash, header_nonce);
    mix_hash = uint256S(to_hex(result.mix_hash));
    uint256 result_hash = uint256S(to_hex(result.final_hash));

    return result_hash;
}

uint256 kawpow_hash(uint256& header_hash, uint64_t& header_nonce)
{
    uint256 mix_hash;
    return kawpow_fullhash(header_hash, header_nonce, mix_hash);
}

uint256 kawpow_hash(std::string& header_hash, std::string& header_nonce, std::string& mix_real)
{
    uint256 mix_hash;

    uint256 header = uint256S(header_hash);
    uint64_t nonce = strtoull(header_nonce.c_str(), NULL, 16);
    uint256 result_hash = kawpow_fullhash(header, nonce, mix_hash);

    mix_real = mix_hash.ToString();
    return result_hash;
}

