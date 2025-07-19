
---

## 📝 README : 


# Embedded Systems Projects ⚙️

This repository showcases my embedded systems work using STM32 microcontrollers, low-level C programming, and simulation tools.

---

## 📂 Repository Structure

- **C-Language Tasks /**
  - `main.c`, …
  - `Proteus/` — simulation schematics & PCB layout files

- **Embedded-C tasks /**
  - `main.c`,`Startup.c`,`Startup.s`,`Make_file.make`,`Linker_script.ld`, …
  -  mini tasks to toggle a led with many targets [Bluepill , Tivac]
  - `Proteus/` — simulation schematics & PCB layout files

- **Datastructure/**
  - Example usage code at FIFO & LIFO Algorithms included 
  - students database that can add or delete or edit students data at the database 
 
- **MCU/**
  - Example usage code at RCC included 

- **Drivers/**
  - MCAL Layer drivers to control MCU [ Bluepill ] prephirals : `RCC.c`,`RCC.h`,`GPIO.c`,`GPIO.h`,`ISR.c`,`ISR.h`,`USART.c`,`USART.h`,`SPI.c`,`SPI.h`,`I2C.c`,`I2C.h`,`TIMER.c`,`TIMER.h`, …
  - HAL Layer drivers to control Acuators using MCU [ Bluepill ] : `LCD.c`,`LCD.h`,`Keypad.c`,`Keypad.h`,`I2C_Slave_EEPROM.c`,`I2C_Slave_EEPROM.h`, … 

- **students_data_using_queue/**
  -  students database that can add or delete or edit students data at the database using Queue Algorithm: `Students_Data_Base.c`,`Students_Data_Base.h`, … 

- **High_pressure_detection_project/**
  -  using a pressure sensor to detect if the cabin pressure cross the safe zone and turn on an alarm: `Alarm_Minitor.c`,`Alarm_Minitor.h`, `driver.c`,`driver.h`,`driver.o`,`High_Pressure_Detection_System.elf.asm`,`High_Pressure_Detection_System.hex`,`Linker_script.ld`,`.m_file.map`,`makefile.make`,`Main_Algorithm.c`,`Main_Algorithm.h`,`Main_Algorithm.o`,`Pressure_Sensor_Driver.c`,`Pressure_Sensor_Driver.h`,`Pressure_Sensor_Driver.o`,`startup.o`,`startup.s`,… 

---

## 🚀 Highlight Projects

### 🅿️ students database using queue
- **Description**: students database that can add or delete or edit students data at the database 
- **Tools & Tech**: STM32CubeIDE, Queue Algorithm
- **Features**:
  - Add , Delete & Edit students information at the database 
  - Read data from a text file 
  - show any student data 
- **Path**: `students_data_using_queue/`

### 🔧 High pressure detection
- **Description**: Demonstrates speed and position control
- **Tech**: PWM, Timer interrupts, and feedback loops on STM32
- **Path**: `High_pressure_detection_project/`

---

## 🛠️ Setup & How to Run

1. Clone this repo:
   ```bash
   git clone https://github.com/omarehab15/embedded_systems.git
   cd embedded_systems

2. Open the project folder (e.g. `High_pressure_detection_project/`) in STM32CubeIDE or Keil.

3. If using simulation:

   * Open `.PRO` or `.PDSim` files in Proteus.
   * Build and run to simulate sensor and motor behavior.

4. To upload to hardware:

   * Build the firmware.
   * Flash it onto the STM32 board using ST-Link or programmer.

---

## 🎯 Skills & Technologies

| Category | Details                                             |
| -------- | --------------------------------------------------- |
| MCU      | STM32F103                                           |
| Language | C, HAL drivers                                      |
| Tools    | STM32CubeIDE, Keil, Proteus                         |
| Concepts | PWM, Timer interrupts, ADC, PID, Sensor interfacing |

---

## 👨‍💻 About the Author

**Omar Ehab** – Embedded Systems enthusiast exploring AI/ML integration and intelligent control systems.
GitHub: [omarehab15](https://github.com/omarehab15)

---
