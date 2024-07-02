# Door Locker Security System

This project implements a Door Locker Security System that allows unlocking a door using a password. The system consists of two ATmega32 microcontrollers, each serving a specific purpose within the system architecture. The project follows a layered architecture model with two main components:

1. **HMI_ECU (Human Machine Interface):**
   - Microcontroller: ATmega32
   - Components: 2x16 LCD, 4x4 keypad
   - Responsibilities: Interaction with the user by accepting inputs through the keypad and displaying messages on the LCD.

2. **Control_ECU:**
   - Microcontroller: ATmega32
   - Components: EEPROM, Buzzer, DC-Motor
   - Responsibilities: Processing and decision-making within the system, including password checking, door opening, and system alarm activation.

## System Sequence

The system operates according to the following sequence:

**Step 1: Create a System Password**
- The LCD displays the message "Please Enter Password."
- The user enters a password consisting of 5 numbers, with each number represented by a * on the screen.
- After entering the password, the user presses the enter button on the keypad.
- The system prompts the user to re-enter the same password for confirmation by displaying the message "Please re-enter the same Pass."
- The user enters the password again, following the same process as before.
- The HMI_ECU sends the two passwords to the Control_ECU through the UART communication.
- If the two passwords match, the system saves the password inside the EEPROM and proceeds to Step 2.
- If the passwords do not match, Step 1 is repeated.

**Step 2: Main Options**
- The LCD always displays the main system options.

**Step 3: Open Door +**
- The LCD displays the message "Please Enter Password."
- The user enters the password and presses the enter button.
- The HMI_ECU sends the entered password to the Control_ECU.
- The Control_ECU compares the entered password with the one saved in the EEPROM.
- If the passwords match:
  - The system rotates the DC motor clockwise (CW) for 15 seconds and displays the message "Door is Unlocking" on the screen.
  - The system holds the motor for 3 seconds.
  - The system rotates the DC motor anti-clockwise (A-CW) for 15 seconds and displays the message "Door is Locking" on the screen.

**Step 4: Change Password**
- The LCD displays the message "Please Enter Password."
- The user enters the password and presses the enter button.
- The HMI_ECU sends the entered password to the Control_ECU.
- The Control_ECU compares the entered password with the one saved in the EEPROM.
- If the passwords match, the system repeats Step 1.

**Step 5: Password Verification**
- If the passwords do not match during Step 3 (Open Door +) or Step 4 (Change Password):
  - The system asks the user for the password again.
  - The LCD displays the message "Please Enter Password."
  - The user enters the password and presses the enter button.
  - The HMI_ECU sends the entered password to the Control_ECU.
  - The Control_ECU compares the entered password with the one saved in the EEPROM.
  - If the passwords match, the system opens the door or changes the password, depending on the previous step.
  - If the passwords do not match again, the system asks the user for the password one last time.
  - If the passwords match on the third attempt, the system activates the buzzer for 1 minute, displays an error message on the LCD for 1 minute, and locks the system. No inputs from the keypad will be accepted during this time period.
  - After 1 minute, the system goes back to Step 2, displaying the main options on the LCD.

## System Requirements

### Microcontrollers
- Two ATmega32 microcontrollers with a frequency of 8 MHz are required for the project.

### GPIO Driver Requirements
1. The GPIO driver should be used in both ECUs.

### LCD Driver Requirements
1. A 2x16 LCD should be used.
2. Connect the LCD control and data bus pins to any pins of your choice in the MCU.
3. The LCD should be connected to the HMI_ECU.

### Keypad Driver Requirements
1. A 4x4 keypad should be used.
2. Connect the keypad pins to any pins of your choice in the MCU.
3. The keypad should be connected to the HMI_ECU.

### DC_Motor Driver Requirements
1. The motor should alwaysrotate in one direction for 15 seconds to unlock the door and then in the opposite direction for 15 seconds to lock the door.
2. Connect the motor driver pins to any pins of your choice in the MCU.
3. The motor should be connected to the Control_ECU.

### Buzzer Driver Requirements
1. A buzzer should be used to indicate an alarm condition.
2. Connect the buzzer to any pin of your choice in the MCU.
3. The buzzer should be connected to the Control_ECU.

### EEPROM Driver Requirements
1. The EEPROM should be used to store and retrieve the system password.
2. Connect the EEPROM pins to any pins of your choice in the MCU.
3. The EEPROM should be connected to the Control_ECU.

### UART Communication
1. The UART communication protocol should be used to transfer data between the HMI_ECU and Control_ECU.
2. Connect the TX and RX pins of the HMI_ECU to the RX and TX pins of the Control_ECU, respectively.

### System Design Considerations
1. The system should implement error handling and display appropriate error messages on the LCD in case of incorrect password entry or system lockout.
2. The system should have a timeout period for incorrect password entry attempts, after which the system should reset and return to the main options screen.
3. The system should have a power-on initialization sequence, where the LCD displays a welcome message and then proceeds to the main options screen.
4. The system should handle debouncing for the keypad buttons to ensure accurate input.
5. The system should handle any other necessary error conditions that may arise during operation.
