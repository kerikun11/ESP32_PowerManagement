# ESP32_PowerManagement

C++ Wrapper for ESP32 Power Management Function

## Install

This is a component of ESP-IDF.

```sh
cd YOUR_PROJECT_DIR
mkdir components # make local components directory if it does not exist
git clone https://github.com/kerikun11/ESP32_PowerManagement components/power_management
```

## Example

```cpp
#include "PowerManagement.h"

extern "C" void app_main() {
  PowerManagement::init();
}

```