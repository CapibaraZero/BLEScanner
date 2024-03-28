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

#ifndef BLESCANNER_H
#define BLESCANNER_H

#include "AdvertisedScannedDeviceCallback.hpp"
#include "FS.h"

class BLEScanner {
 private:
  NimBLEScan *pBLEScan;
  AdvertisedScannedDeviceCallback *adv_device_callback;
  void create_scan();
  inline void start_scan(int scan_time);

 public:
  BLEScanner(int scan_time = 30);
  ~BLEScanner();
  bool is_scanning() { return pBLEScan->isScanning(); }
  DynamicJsonDocument get_result() {
    return adv_device_callback->get_advertised_devices();
  };
  void save_to_sd(FS sd, DynamicJsonDocument result);
  void restart_scan(int scan_time);
  uint8_t get_scanned_devices() {
    return adv_device_callback->get_advertised_devices_num();
  };
};

#endif
