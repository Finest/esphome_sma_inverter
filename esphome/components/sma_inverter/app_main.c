#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_spp_api.h"
#include "esp_system.h"

#include "SMA_Inverter.h"

static const char *TAG = "APP";

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Starting SMA SPP Bluetooth client");

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Init BT controller for CLASSIC BT (SPP)
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT));

    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    ESP_LOGI(TAG, "Bluetooth stack initialized");

    // Instantiate and run inverter loop (mocked version)
    smabluetooth_solar::SmaBluetoothSolar inverter;
    inverter.set_sma_inverter_bluetooth_mac(CONFIG_SMA_INVERTER_MAC);
    inverter.set_sma_inverter_password(CONFIG_SMA_INVERTER_PASSWORD);
    inverter.setup();

    while (true) {
        inverter.loop();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
