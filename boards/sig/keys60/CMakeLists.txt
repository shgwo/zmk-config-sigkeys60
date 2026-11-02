target_sources(app PRIVATE keys60_led.c)
target_sources_ifdef(CONFIG_KEYS60_OLED_RAW_TEST app PRIVATE keys60_oled_raw_test.c)
