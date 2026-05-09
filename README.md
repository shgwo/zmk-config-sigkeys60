# zmk-config-sigkeys60

[__TOC__]

This repository is structured as a **ZMK Module**. It provides a clean separation between core hardware definitions and user-specific configurations, allowing for easier maintenance across different hardware revisions.

---

## Environment Setup (devcontainer-cli)

This setup assumes you are using the `devcontainer` CLI to manage your development environment on a host like `rhetenor`.

### 1. Clone Repositories
Clone both the ZMK firmware and this configuration repository into the same parent directory:

```bash
git clone [https://github.com/zmkfirmware/zmk.git](https://github.com/zmkfirmware/zmk.git)
git clone <this-repo-url> zmk-config
```

### 2. Configure Bind Mounts
To make this config repository accessible inside the ZMK container, you need to modify the devcontainer configuration.

Edit `zmk/.devcontainer/devcontainer.json` and add this repository to the `mounts` array:

```json
"mounts": [
    "source=${localWorkspaceFolder}/../zmk-config,target=/workspaces/zmk-config,type=bind"
]
```

### 3. Spin up the Container
Navigate to the `zmk` directory and start the container:

```bash
cd zmk
devcontainer up --workspace-folder .
```

---

## Build Instructions

Use `devcontainer exec` to run the `west build` command from your host terminal.

### 1. Standard Build (User Customization)
Build the firmware using your personal keymap located in the `config/` directory.

```bash
devcontainer exec west build -s app -b keys60@rev_ansi62_rot/nrf52840 -- \
  -DBOARD_ROOT="/workspaces/zmk-config" \
  -DZMK_CONFIG="/workspaces/zmk-config/config"
```

*   **-DBOARD_ROOT**: Registers the mapped directory as a source for board definitions.
*   **-DZMK_CONFIG**: Instructs ZMK to use the keymap and user settings from the `config/` folder.

### 2. Hardware Default Build
To build using the default keymap bundled with the hardware definition:

```bash
devcontainer exec west build -s app -b keys60@rev_ansi62_rot/nrf52840 -- \
  -DBOARD_ROOT="/workspaces/zmk-config"
```

---

## Project Structure

*   **boards/**: Permanent hardware definitions (GPIO maps, pinctrl, and revisions).
*   **config/**: Your personal workspace for `keys60.keymap`.
*   **zephyr/module.yml**: Metadata required for Zephyr to recognize this repository as a ZMK module.

## Maintenance

### Pristine Build
If you change hardware revisions or paths and encounter persistent errors, remove the build cache:

```bash
devcontainer exec rm -rf build/
```

### Mount Verification
If the board is not found, verify that the container is running and the mount is active:
```bash
devcontainer exec ls /workspaces/zmk-config
```



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
