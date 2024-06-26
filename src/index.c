#include <stdio.h> // printf(3)

#include <concord/discord.h>

#include "../headers/config.h"
#include "../headers/source/events/ready.h"
#include "../headers/source/events/interactionCreate.h"

void on_interaction(struct discord *client, const struct discord_interaction *event)
{
	switch (event->type) {
	case DISCORD_INTERACTION_APPLICATION_COMMAND:
		on_interaction_command(client, event);
		break;
	case DISCORD_INTERACTION_PING:
	case DISCORD_INTERACTION_MODAL_SUBMIT:
	case DISCORD_INTERACTION_MESSAGE_COMPONENT:
	case DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE:
		printf("%s\n", "Invalid event type received!\n");
		break;
	}
}

void on_ready(struct discord *client, const struct discord_ready *event) {
	on_event_ready(client, event);
}

int main(void)
{
	struct discord *client = discord_init(BOT_TOKEN);

	discord_set_on_ready(client, &on_ready);
	discord_set_on_interaction_create(client, &on_interaction);

	discord_run(client);
	return 0;
}

