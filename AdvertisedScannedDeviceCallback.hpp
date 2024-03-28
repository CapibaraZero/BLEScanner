/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2023 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADVERTISED_SCANNED_DEVICE_CALLBACK_H
#define ADVERTISED_SCANNED_DEVICE_CALLBACK_H

#include "ArduinoJson.h"
#include "NimBLEDevice.h"

class AdvertisedScannedDeviceCallback : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice *advertisedDevice);
  DynamicJsonDocument advertised_devices =
      DynamicJsonDocument(ESP.getMaxAllocHeap());  // TODO: Set this dynamically
  void shrink_result() {
    advertised_devices.shrinkToFit();
    advertised_devices.garbageCollect();
  }
  uint8_t devices = 0;

 public:
  DynamicJsonDocument get_advertised_devices() {
    shrink_result();
    return advertised_devices;
  }
  void begin() { advertised_devices.clear(); };
  uint8_t get_advertised_devices_num() { return devices; };
};

#endif
