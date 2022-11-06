#include "stratum.h"

const int get_ethash_epoch_length()
{
	if (is_firopow)
		return 1300;
	if (is_kawpow)
		return 7500;
	return 0;
}

const int get_ethash_period_length()
{
	if (is_firopow)
		return 1;
	if (is_kawpow)
		return 3;
	return 0;
}

const int get_epoch_number(int block_number)
{
    return block_number ? block_number / get_ethash_epoch_length() : 0;
}
