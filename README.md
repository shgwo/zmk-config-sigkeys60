# zmk-config-sigkeys60

[__TOC__]

# keys60 ZMK Module

This repository is structured as a **ZMK Module**. It provides a clean separation between core hardware definitions and user-specific configurations, allowing for easier maintenance across different hardware revisions.

---

## Build Instructions

This project is designed to be built within a **ZMK DevContainer** environment. To ensure the build system correctly identifies the board and your custom layout, specific arguments are required.

### 1. Standard Build (User Customization)
Use this command to build the firmware with your personal keymap located in the `config/` directory. **This is the recommended method for daily use.**

```bash
west build -s app -b keys60@rev_ansi62_rot/nrf52840 -- \
  -DBOARD_ROOT="/workspaces/zmk-config" \
  -DZMK_CONFIG="/workspaces/zmk-config/config"
```

*   **-DBOARD_ROOT**: Registers this repository as a source for board definitions.
*   **-DZMK_CONFIG**: Overrides the default settings with the contents of your `config/` folder.

### 2. Hardware Default Build
If you wish to build the "factory default" firmware using the keymap bundled with the hardware definition, omit the config argument:

```bash
west build -s app -b keys60@rev_ansi62_rot/nrf52840 -- \
  -DBOARD_ROOT="/workspaces/zmk-config"
```

---

## Project Structure

*   **boards/**: Contains permanent hardware definitions (GPIO maps, pinctrl, and revisions).
*   **config/**: Your personal workspace. Modify `keys60.keymap` here to change your layers and macros.
*   **zephyr/module.yml**: Enables Zephyr's module system to automatically discover the hardware metadata.

## Troubleshooting

### Clean Build
If you encounter unexpected errors after switching revisions or moving files, perform a pristine build by removing the build directory:

```bash
rm -rf build/
```

### Path Accuracy
Ensure that the paths provided in the `west build` command match the actual mount points in your DevContainer (default is `/workspaces/zmk-config`).
