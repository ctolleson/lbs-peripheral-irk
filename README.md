# Peripheral LBS (nRF7002 DK)

This repository customizes Nordic Semiconductor's Bluetooth Peripheral LED Button Service sample for the `nrf7002dk/nrf5340/cpuapp` board. It adds a unit-tested button/LED abstraction and adapts the build configuration so the application targets this board exclusively.

## Prerequisites

- nRF Connect SDK v3.2.x (or newer) installed via Toolchain Manager at `/opt/nordic/ncs`.
- `west` available on your `PATH`.
- An `nrf7002dk` connected over USB (both VCOM interfaces enumerate as `/dev/tty.usbmodem*` on macOS).

## Building the application

From the repository root:

```bash
west build -b nrf7002dk/nrf5340/cpuapp
```

Artifacts are generated under `build/peripheral_lbs/zephyr/`.

## Running unit tests with Twister

Unit tests live under `tests/app_logic` and are wired up for Twister. To run them on real hardware:

1. **Allow access to the VCOM port** (macOS resets permissions every time the DK re-enumerates):
   ```bash
   sudo chmod a+rw /dev/tty.usbmodem0010507569511
   ```
2. Execute Twister with device testing enabled:
   ```bash
   HOME=$PWD west twister \
     -T tests/app_logic \
     -p nrf7002dk/nrf5340/cpuapp \
     --device-testing \
     --device-serial /dev/tty.usbmodem0010507569511
   ```

> **Note:** If your board enumerates under a different `/dev/tty.usbmodem*` node, update the device path in both commands accordingly.

## Repository layout

- `src/` – application entry point and `app_logic` helper.
- `boards/` – board overlay configurations for devices previously supported by the upstream sample.
- `tests/app_logic/` – ztest suite covering the button/LED logic.
- `sample.yaml` – Twister metadata restricted to `nrf7002dk/nrf5340/cpuapp`.
