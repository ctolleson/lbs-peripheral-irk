/*
 * Copyright (c) 2026
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef APP_LOGIC_H_
#define APP_LOGIC_H_

#include <stdbool.h>
#include <stdint.h>

typedef int (*app_logic_button_sender_t)(uint32_t state);

void app_logic_init(void);
void app_logic_set_button_sender(app_logic_button_sender_t sender);
bool app_logic_get_button_state(void);
void app_logic_handle_button_change(uint32_t button_state, uint32_t has_changed,
				    uint32_t relevant_mask);

#endif /* APP_LOGIC_H_ */
