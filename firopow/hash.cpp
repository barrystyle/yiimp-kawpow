#include "stratum.h"
#include "include/progpow.hpp"

uint256 firopow_fullhash(uint256& header_hash, uint64_t& header_nonce, uint256& mix_hash, int& coinid)
{
    coin_context* context = get_coin_context(coinid);
    if (!context) {
        return badhash;
    }

    const auto hash = to_hash256(header_hash.ToString());
    const auto result = firopow::hash(*context->context, context->height, hash, header_nonce);
    mix_hash = uint256S(to_hex(result.mix_hash));
    uint256 result_hash = uint256S(to_hex(result.final_hash));

    return result_hash;
}

uint256 firopow_hash(std::string& header_hash, std::string& header_nonce, std::string& mix_real, int& coinid)
{
    uint256 mix_hash;

    uint256 header = uint256S(header_hash);
    uint64_t nonce = strtoull(header_nonce.c_str(), NULL, 16);
    uint256 result_hash = firopow_fullhash(header, nonce, mix_hash, coinid);

    mix_real = mix_hash.ToString();
    return result_hash;
}
