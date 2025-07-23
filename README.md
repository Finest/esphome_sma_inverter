# SMA Bluetooth Client – ESP-IDF Port

Dieses Projekt ist ein vollständiger ESP-IDF-Port des SMA Bluetooth Serial-Clients, basierend auf der ursprünglichen ESPHome-Komponente.

## 🔧 Konfiguration

```bash
idf.py menuconfig
```

Setze dort:
- `CONFIG_SMA_INVERTER_MAC` – MAC-Adresse des SMA-Wechselrichters
- `CONFIG_SMA_INVERTER_PASSWORD` – 4-stelliges Passwort

## 🚀 Flashen

```bash
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

## 📁 Struktur

- `SMA_Inverter.cpp/.h` – vollständige BT-Kommunikation
- `smabluetooth_solar.cpp/.h` – Zustandsmaschine (Setup, Connect, Auth, Run)
- `app_main.c` – Einstiegspunkt, startet Loop
