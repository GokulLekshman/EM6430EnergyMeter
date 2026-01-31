# ⚡ EM6430EnergyMeter

**EM6430EnergyMeter** is an Arduino library for interfacing with the **EM6430 three-phase energy meter** using **Modbus RTU over RS-485**. It enables Arduino-based systems to read accurate, industrial-grade electrical and energy parameters using a simple and clean API.

---

## 🚀 Overview

The EM6430 energy meter is widely used in industrial electrical panels for measuring power consumption and power quality. This library abstracts Modbus RTU communication details such as frame creation, CRC calculation, and register handling, allowing developers to focus on **energy monitoring and analytics**.

---

## ✨ Features

* Supports EM6430 three-phase energy meter
* Modbus RTU communication (Function Code `0x03`)
* Automatic CRC handling
* Float-based readable values
* Simple Arduino-style API
* Lightweight and embedded-friendly

---

## 🔧 Hardware Requirements

* Arduino Uno / Nano / Mega / ESP32 (UART capable)
* RS-485 transceiver (MAX485, SP3485, etc.)
* EM6430 Energy Meter

---

## 📦 Installing the Library

### Method 1: Add ZIP Library (Recommended)

1. Download this repository as a ZIP file
2. Open **Arduino IDE**
3. Navigate to **Sketch → Include Library → Add .ZIP Library**
4. Select the downloaded ZIP
5. Restart Arduino IDE

### Method 2: Manual Installation

1. Clone or download the repository
2. Rename the folder to `EM6430EnergyMeter`
3. Copy it to:

```
Documents/Arduino/libraries/
```

4. Restart Arduino IDE

---

## 📚 Usage

### Include the Library

```cpp
#include <EM6430.h>
```

### Initialize the Meter

```cpp
EM6430 meter;

void setup() {
  Serial.begin(9600);
  meter.begin(9600);
}
```

---

## 📖 Full Command List

### 🔄 Current

| Command | Description       |
| ------- | ----------------- |
| A       | Current average   |
| A1      | Current – Phase 1 |
| A2      | Current – Phase 2 |
| A3      | Current – Phase 3 |

### 🔌 Voltage

| Command | Description                  |
| ------- | ---------------------------- |
| VLL     | Line-to-line average voltage |
| VLN     | Line-to-neutral voltage      |
| V12     | Phase 1 to Phase 2 voltage   |
| V23     | Phase 2 to Phase 3 voltage   |
| V31     | Phase 3 to Phase 1 voltage   |
| V1      | Phase 1 to neutral           |
| V2      | Phase 2 to neutral           |
| V3      | Phase 3 to neutral           |

### ⚡ Active Power

| Command | Description            |
| ------- | ---------------------- |
| W       | Total active power     |
| W1      | Active power – Phase 1 |
| W2      | Active power – Phase 2 |
| W3      | Active power – Phase 3 |

### 🔁 Reactive Power

| Command | Description              |
| ------- | ------------------------ |
| VAR     | Total reactive power     |
| VAR1    | Reactive power – Phase 1 |
| VAR2    | Reactive power – Phase 2 |
| VAR3    | Reactive power – Phase 3 |

### 🔋 Apparent Power

| Command | Description              |
| ------- | ------------------------ |
| VA      | Total apparent power     |
| VA1     | Apparent power – Phase 1 |
| VA2     | Apparent power – Phase 2 |
| VA3     | Apparent power – Phase 3 |

### 📐 Power Factor

| Command | Description            |
| ------- | ---------------------- |
| PF      | Average power factor   |
| PF1     | Power factor – Phase 1 |
| PF2     | Power factor – Phase 2 |
| PF3     | Power factor – Phase 3 |

### 🌀 Frequency

| Command | Description    |
| ------- | -------------- |
| Freq    | Frequency (Hz) |

### 🔋 Energy

| Command | Description             |
| ------- | ----------------------- |
| FwdWh   | Forward active energy   |
| FwdVAh  | Forward apparent energy |

---

## 🧪 Example

```cpp
meter.EM6430_Command(VLL, 1);
float voltage = meter.EM6430_Data();
```

---

## 📜 License

GNU Public License
