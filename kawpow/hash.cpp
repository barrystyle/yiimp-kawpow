#include "stratum.h"

#include "helpers.hpp"
#include "include/ethash/progpow.hpp"

// 0cf15e36170dd73e79799f69b2ccc7241b4b54d414d06698a4ee837398aa7c95, 25, 0x4b7
// powhash: 0023635a6899090b05643f3f9d27bdc51e4b901a96f98a66ea0f95d6578d3b6b

uint256 kawpow_fullhash(uint256& header_hash, int& header_height, uint64_t& header_nonce, uint256& mix_hash)
{
    static ethash::epoch_context_ptr context{nullptr, nullptr};

    const auto epoch_number = ethash::get_epoch_number(header_height);
    if (!context || context->epoch_number != epoch_number) {
        context = ethash::create_epoch_context(epoch_number);
    }

    const auto hash = to_hash256(header_hash.ToString());
    const auto result = progpow::hash(*context, header_height, hash, header_nonce);
    mix_hash = uint256S(to_hex(result.mix_hash));
    uint256 result_hash = uint256S(to_hex(result.final_hash));

    return result_hash;
}

uint256 kawpow_hash(uint256& header_hash, int& header_height, uint64_t& header_nonce)
{
    uint256 mix_hash;
    return kawpow_fullhash(header_hash, header_height, header_nonce, mix_hash);
}
