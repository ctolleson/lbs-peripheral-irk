/*
 * Copyright (c) 2026
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <stddef.h>

#include "app_logic.h"

int bt_lbs_send_button_state(uint32_t button_state);

static app_logic_button_sender_t button_sender = bt_lbs_send_button_state;
static bool app_button_state;

void app_logic_init(void)
{
	app_button_state = false;
	app_logic_set_button_sender(NULL);
}

void app_logic_set_button_sender(app_logic_button_sender_t sender)
{
	button_sender = sender ? sender : bt_lbs_send_button_state;
}

bool app_logic_get_button_state(void)
{
	return app_button_state;
}

void app_logic_handle_button_change(uint32_t button_state, uint32_t has_changed,
				    uint32_t relevant_mask)
{
	if (!(has_changed & relevant_mask)) {
		return;
	}

	uint32_t state = button_state & relevant_mask;

	app_button_state = state ? true : false;

	if (button_sender) {
		button_sender(state);
	}
}
