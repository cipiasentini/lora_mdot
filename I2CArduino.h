/**
 * Copyright (c) 2017, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MBED_LORAWAN_I2CArduino_H_
#define MBED_LORAWAN_I2CArduino_H_

#include "mbed.h"

/*
 * Comunicacion i2c con arduino que va a tener todos los sensores
 */
class I2CARDUINO {
public:
    bool begin()
    {
        return false;
    };

    void startConversion() {};

    char * read()
    {
        i2c.read(addr, cmd, 30);
        return cmd;
    }

private:
    const int addr = 0x02;
    char cmd[30];
    I2C i2c(I2C_SDA, I2C_SCL);
};

#endif /* MBED_LORAWAN_DUMMYSENSOR_H_ */
