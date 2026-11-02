/*
 * Temporary direct SSD1306 test for the Keys60 board.
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(keys60_oled_raw_test, LOG_LEVEL_INF);

#define OLED_NODE DT_CHOSEN(zephyr_display)
#define I2C_NODE DT_BUS(OLED_NODE)
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_HEIGHT / 8)
#define OLED_I2C_CHUNK_SIZE 128

static uint8_t pattern[OLED_BUFFER_SIZE];

static void make_pattern(void) {
    for (size_t i = 0; i < sizeof(pattern); i++) {
        pattern[i] = (i & 0x01) ? 0xAA : 0x55;
    }
}

static void raw_test_thread(void *unused1, void *unused2, void *unused3) {
    ARG_UNUSED(unused1);
    ARG_UNUSED(unused2);
    ARG_UNUSED(unused3);

    static const struct i2c_dt_spec i2c = I2C_DT_SPEC_GET(OLED_NODE);
    static const uint8_t set_window[] = {
        0x20, 0x00,       /* horizontal addressing mode */
        0x21, 0x00, 0x7f, /* columns 0..127 */
        0x22, 0x00, 0x03, /* pages 0..3 */
    };

    if (!i2c_is_ready_dt(&i2c)) {
        LOG_ERR("OLED I2C device is not ready");
        return;
    }

    make_pattern();
    k_sleep(K_MSEC(2000));

    while (true) {
        int ret = i2c_burst_write_dt(&i2c, 0x00, set_window, sizeof(set_window));
        if (ret == 0) {
            for (size_t offset = 0; offset < sizeof(pattern); offset += OLED_I2C_CHUNK_SIZE) {
                ret = i2c_burst_write_dt(&i2c, 0x40, &pattern[offset], OLED_I2C_CHUNK_SIZE);
                if (ret != 0) {
                    break;
                }
            }
        }
        LOG_INF("direct I2C OLED write: %d", ret);
        k_sleep(K_MSEC(2000));
    }
}

K_THREAD_DEFINE(keys60_oled_raw_test_thread, 1024, raw_test_thread, NULL, NULL, NULL, 7, 0, 0);
