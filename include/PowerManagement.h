/**
 * @file PowerManagement.h
 * @author KERI kerikun11@gmail.com
 * @since 2018.06.28
 */
#pragma once

#include "esp_err.h"
#include "esp_pm.h"
#include "sdkconfig.h"
#include <functional>
#include <stdio.h>

class PowerManagement {
public:
  static void init(const bool light_sleep_enable = true) {
    esp_pm_config_esp32_t pm_config;
    pm_config.max_freq_mhz = CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ;
    pm_config.min_freq_mhz = 10;
#if CONFIG_FREERTOS_USE_TICKLESS_IDLE
    pm_config.light_sleep_enable = light_sleep_enable;
#else
    pm_config.light_sleep_enable = false;
#endif
    ESP_ERROR_CHECK(esp_pm_configure(&pm_config));
  }
  static void printLockStatus(FILE *stream = stdout) {
    ESP_ERROR_CHECK(esp_pm_dump_locks(stream));
  }

  class Lock {
  public:
    Lock(esp_pm_lock_type_t lock_type, const char *name) {
      ESP_ERROR_CHECK(esp_pm_lock_create(lock_type, 0, name, &lock_handle));
    }
    ~Lock() { ESP_ERROR_CHECK(esp_pm_lock_delete(lock_handle)); }
    void acquire() { ESP_ERROR_CHECK(esp_pm_lock_acquire(lock_handle)); }
    void release() { ESP_ERROR_CHECK(esp_pm_lock_release(lock_handle)); }
    void locked(std::function<void(void)> func) {
      acquire();
      func();
      release();
    }

  private:
    esp_pm_lock_handle_t lock_handle;
  };
};