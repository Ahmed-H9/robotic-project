# 🔐 RFID Door Lock System using Arduino
This project is a Smart Door Lock System built using Arduino and RFID technology.

The system allows access only to authorized RFID cards. When a valid card is scanned, the door unlocks automatically using a solenoid lock. Otherwise, access is denied with visual and sound alerts.

🎯 This project is designed for security applications like smart homes, offices, or labs.

## 🧰 Components Used

- Arduino Uno / Nano
- RC522 RFID Module
- RFID Tags / Cards (13.56MHz)
- Solenoid Lock (12V)
- Relay Module
- 16x2 LCD (I2C)
- Red LED & Green LED
- Buzzer
- Resistors (220Ω)
- 12V Power Supply
- Jumper Wires & Breadboard

- ## 🔌 Circuit Diagram

- on presentation


## 🧠 How It Works

1. User scans RFID card
2. System reads UID from the card
3. UID is compared with stored authorized UID
4. If matched:
   - Door unlocks
   - Green LED turns ON
   - Message shown on LCD
5. If not matched:
   - Red LED turns ON
   - Buzzer alerts
   - Access denied message
  
   ## 💻 Arduino Code

The main code is located in:
