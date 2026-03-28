/*
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/ztest.h>
#include <zephyr/sys/util.h>

#include "app_logic.h"

static uint32_t last_state;
static int send_calls;

int bt_lbs_send_button_state(uint32_t button_state)
{
	ARG_UNUSED(button_state);
	return 0;
}

static int mock_sender(uint32_t state)
{
	send_calls++;
	last_state = state;
	return 0;
}

static void reset_mocks(void)
{
	last_state = 0;
	send_calls = 0;
	app_logic_init();
	app_logic_set_button_sender(mock_sender);
}

ZTEST(app_logic, test_press_updates_state_and_notifies)
{
	reset_mocks();

	app_logic_handle_button_change(BIT(0), BIT(0), BIT(0));

	zassert_true(app_logic_get_button_state(), "Button state should be true");
	zassert_equal(1, send_calls, "Expected one notification");
	zassert_equal(BIT(0), last_state, "Expected pressed mask");
}

ZTEST(app_logic, test_release_updates_state_and_notifies)
{
	reset_mocks();

	app_logic_handle_button_change(BIT(0), BIT(0), BIT(0));
	send_calls = 0;

	app_logic_handle_button_change(0, BIT(0), BIT(0));

	zassert_false(app_logic_get_button_state(), "Button state should be false");
	zassert_equal(1, send_calls, "Expected notification on release");
	zassert_equal(0, last_state, "Expected released mask");
}

ZTEST(app_logic, test_irrelevant_button_is_ignored)
{
	reset_mocks();

	app_logic_handle_button_change(BIT(1), BIT(1), BIT(0));

	zassert_false(app_logic_get_button_state(),
		      "State must remain false when mask not set");
	zassert_equal(0, send_calls, "No notifications expected");
}

ZTEST_SUITE(app_logic, NULL, NULL, NULL, NULL, NULL);
