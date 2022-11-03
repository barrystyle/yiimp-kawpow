
#include "stratum.h"

void client_record_difficulty(YAAMP_CLIENT *client)
{
	int e = current_timestamp() - client->last_submit_time;
	if(e < 500) e = 500;
	int p = 5;

	client->shares_per_minute = (client->shares_per_minute * (100 - p) + 60*1000*p/e) / 100;
	client->last_submit_time = current_timestamp();

//	debuglog("client->shares_per_minute %f\n", client->shares_per_minute);
}

void client_change_difficulty(YAAMP_CLIENT *client, double difficulty)
{
//	debuglog("change diff to %f %f\n", difficulty, client->difficulty_actual);

	if(difficulty <= 0) return;
	if(difficulty == client->difficulty_actual) return;

	client_send_difficulty(client, difficulty, false);
}

void client_adjust_difficulty(YAAMP_CLIENT *client)
{
	if(client->shares_per_minute > 100)
		client_change_difficulty(client, client->difficulty_actual*4);

	else if(client->shares_per_minute > 25)
		client_change_difficulty(client, client->difficulty_actual*2);

	else if(client->shares_per_minute > 20)
		client_change_difficulty(client, client->difficulty_actual*1.5);

	else if(client->shares_per_minute <  5)
		client_change_difficulty(client, client->difficulty_actual/2);
}

int client_send_difficulty(YAAMP_CLIENT *client, double difficulty, bool subscribe)
{
	uint256 share_target;
	diff_to_target(share_target, difficulty);

	if (subscribe) {
		client->share_target = share_target;
		client_call(client, "mining.set_target", "[\"%s\"]", client->share_target.ToString().c_str());
	} else {
		client->next_target = share_target;
	}

	return 0;
}

void client_initialize_difficulty(YAAMP_CLIENT *client)
{
	client->difficulty_actual = g_stratum_difficulty;
	diff_to_target(client->share_target, client->difficulty_actual);
}

