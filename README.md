# 🚘 VECTOR_MAJOR_PROJECT

## 💡 Real-Time Vehicle Status Monitoring System using CAN Protocol (LPC2129)

This project demonstrates a distributed embedded system for monitoring real-time vehicle status using the **Controller Area Network (CAN)** protocol. It simulates communication between three embedded nodes:

- **Main Node**: Central status display
- **Indicator Node**: Directional indicator control
- **Fuel Node**: Fuel level sensing

Built using the **LPC2129 (ARM7)** microcontroller and **MCP2551 CAN transceivers**, this system mimics how real vehicles share sensor/control data over a reliable CAN bus.

---

## 🔧 Key Features

- 📡 **Multi-node communication** via CAN protocol  
- 📊 Real-time fuel level and indicator status monitoring  
- 📟 LCD-based display at central node  
- ⚙️ Modular design for embedded systems and automotive use

---

## 🧩 System Nodes and Source Code Structure

### 🟢 1. Main Node

> Receives CAN data from other nodes and displays status on LCD.

- ✅ **Functionality**:
  - Receives messages from Indicator and Fuel Nodes
  - Displays direction and fuel level on 16x2 LCD

- 📁 **Files**:
  - `main_node.c` – CAN receive + LCD update logic
  - `lcd.c`, `lcd.h` – LCD display handling
  - `can.c`, `can.h` – CAN initialization and handling
  - `delay.c`, `delay.h` – Timing functions
  - `types.h` – Custom data types

---

### 🟡 2. Indicator Node

> Detects button presses for Left/Right indicators and sends status over CAN.

- ✅ **Functionality**:
  - Detects external switch interrupts (Left/Right)
  - Sends CAN frame with direction info

- 📁 **Files**:
  - `indicator_node.c` – Interrupt-based switch logic
  - `can.c`, `can.h` – CAN transmission
  - `delay.c`, `delay.h` – Delay utilities
  - `types.h` – Custom types

---

### 🔵 3. Fuel Node

> Reads analog fuel sensor input using ADC and transmits value over CAN.

- ✅ **Functionality**:
  - Reads analog fuel level via ADC
  - Sends value via CAN frame

- 📁 **Files**:
  - `fuel_node.c` – ADC read and CAN send logic
  - `adc.c`, `adc.h` – ADC setup and read
  - `can.c`, `can.h` – CAN handling
  - `delay.c`, `delay.h` – Delay utilities
  - `types.h` – Common type definitions

---

## 🔁 CAN Communication

- All nodes use **CAN1** peripheral on LPC2129
- CAN frame size: **8 bytes**
- **CAN Message IDs**:
  - Indicator Node → `0x100`
  - Fuel Node → `0x200`
  - Main Node listens to both

---

## 🔩 Hardware Components

| Component         | Description                                |
|------------------|--------------------------------------------|
| **LPC2129**       | ARM7 microcontroller (core of all nodes)   |
| **MCP2551**       | CAN transceiver IC                         |
| **16x2 LCD**      | Output display (Main Node)                 |
| **MMA7660**       | 3-Axis accelerometer (optional)            |
| **Fuel Sensor**   | Analog signal input (Fuel Node)            |
| **Switches & LEDs** | Used for indicator simulation           |
| **Power Supply**  | Regulated 5V DC                            |

---

## 🛠 Development Environment

- **Keil µVision** – Code development & debugging  
- **Flash Magic** – Flashing HEX files to LPC2129  
- **Embedded C** – Low-level firmware programming  
- **Proteus** *(optional)* – Circuit simulation  
- **GitHub** – Version control and collaboration  

---

## 📁 Suggested Folder Structure

```plaintext
VECTOR_MAJOR_PROJECT/
├── MAIN_NODE/
│   ├── main_node.c
│   ├── i2c.c, i2c.h
│   ├── lcd.c, lcd.h
│   ├── can.c, can.h
│   ├── delay.c, delay.h
│   └── types.h
│
├── INDICATOR_NODE/
│   ├── indicator_node.c
│   ├── can.c, can.h
│   ├── delay.c, delay.h
│   └── types.h
│
├── FUEL_NODE/
│   ├── fuel_node.c
│   ├── adc.c, adc.h
│   ├── can.c, can.h
│   ├── delay.c, delay.h
│   └── types.h
