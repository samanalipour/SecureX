/*
 * Menu.c
 *
 *  Created on: Oct 25, 2024
 *      Author: saman
 */
#include "Menu.h"

void Startup() {
  DEBUG_PRINT("Startup\n");
  // Read a single byte from the flash memory at BrandNew_address and store it in Brand_new.
  MY_FLASH_ReadN(BrandNew_address, &Brand_new, 1, DATA_TYPE_8);
  // Update the SSD1306 display to show the drawn bitmap.
  ssd1306_SetCursor (25,7);
  ssd1306_WriteString("SecureX", Font_11x18, 1);
  ssd1306_UpdateScreen();

  // Delay for 1000 milliseconds (1 second).
  HAL_Delay(1000);

  // Clear the SSD1306 display.
  ssd1306_clear();

  // Read 8 bytes from the flash memory at GlobalSalt_address and store it in GlobalSalt.
  MY_FLASH_ReadN(GlobalSalt_address, GlobalSalt, 8, DATA_TYPE_8);

  // Check if the device is brand new.
  if (Brand_new == 0) {
    // Print the Brand_new value for debugging purposes.
    DEBUG_PRINT("Brand new = %02x\n", Brand_new);

    // Clear the SSD1306 display.
    ssd1306_Fill(Black);

    // Set the cursor position on the SSD1306 display.
    ssd1306_SetCursor(15, 7);

    // Display "Brand new" text on the SSD1306 display using Font_11x18.
    ssd1306_WriteString("Brand new", Font_11x18, 1);

    // Update the SSD1306 display to show the text.
    ssd1306_UpdateScreen();

    // Delay for 2000 milliseconds (2 seconds).
    HAL_Delay(2000);

    // Clear the SSD1306 display.
    ssd1306_clear();
    // Generate a random number and store it in GlobalSalt.
    Get_rng(&hrng , GlobalSalt, 2);
    printArray("New Global Salt", GlobalSalt, sizeof(GlobalSalt));
    // Save the generated GlobalSalt to the flash memory at GlobalSalt_address.
    write_flash(GlobalSalt_address, GlobalSalt, 8);

    // Set the system state to Enrollment.
    state = Enrollment;
  } else {
    // If the device is not brand new, activate the wrong LEDs indication.
    //wrong_LEDs();
    DEBUG_PRINT("Not brand new\n");
    printArray("Saved Global Salt", GlobalSalt, sizeof(GlobalSalt));
    // Set the system state to Lock.
    state = Lock;
  }

}

void MainMenu() {
  DEBUG_PRINT("MainMenu\n");
  // Clear the SSD1306 display.
  ssd1306_clear();

  // Display the menu options at specified coordinates using Font_7x10.
  ssd1306_SetCursor(17, 5);
  ssd1306_WriteString("Lock", Font_6x8, 1);

  ssd1306_SetCursor(14, 19);
  ssd1306_WriteString("Reset", Font_6x8, 1);

  ssd1306_SetCursor(52, 5);
  ssd1306_WriteString("Enrollment", Font_6x8, 1);

  ssd1306_SetCursor(61, 19);
  ssd1306_WriteString("Timeout", Font_6x8, 1);

  // Highlight the current menu option based on MenuState.
  if (MenuState == Lock) {
    ssd1306_FillRectangle(14, 2, 41, 16, 1);
    ssd1306_SetCursor(17, 5);
    ssd1306_WriteString("Lock", Font_6x8, 0);
  }
  if (MenuState == Reset) {
    ssd1306_FillRectangle(11, 16, 47, 29, 1);
    ssd1306_SetCursor(14, 19);
    ssd1306_WriteString("Reset", Font_6x8, 0);
  }
  if (MenuState == Timeout) {
    ssd1306_FillRectangle(58, 16, 106, 29, 1);
    ssd1306_SetCursor(61, 19);
    ssd1306_WriteString("Timeout", Font_6x8, 0);
  }
  if (MenuState == Enrollment) {
    ssd1306_FillRectangle(49, 2, 115, 16, 1);
    ssd1306_SetCursor(52, 5);
    ssd1306_WriteString("Enrollment", Font_6x8, 0);
  }

  // Update the SSD1306 display to show the menu.
  ssd1306_UpdateScreen();

  while (1) {
    // If the device state is inactive, set the state to Lock and exit the loop.
    if (!DeviceState) {
      state = Lock;
      break;
    }

    // Check the button state.
    uint8_t btn_state = checkButtons();

    // If the 'up' button is pressed, decrement the menu state.
    if (btn_state == 0) { // up
      MenuState--;
      // If MenuState underflows, set it to the last menu option.
      if (MenuState == 255) MenuState = 3;
      state = Menu;
      break;
    }
    // If the 'down' button is pressed, increment the menu state.
    else if (btn_state == 1) { // down
      MenuState++;
      // If MenuState overflows, set it to the first menu option.
      if (MenuState == 4) MenuState = 0;
      state = Menu;
      break;
    }
    // If both buttons are pressed, set the state based on the current menu option.
    else if (btn_state == 2) { // both
      if (MenuState == 0) state = Lock;
      if (MenuState == 1) state = Reset;
      if (MenuState == 2) state = Timeout;
      if (MenuState == 3) state = Enrollment;
      if (MenuState == 4) state = Menu;
      break;
    }
  }
}

void TimeoutMenu() {
  DEBUG_PRINT("TimeoutMenu\n");
  // Static variable to store the previous reverse timer value. Initialized to the maximum 32-bit unsigned integer value.
  static uint32_t previousRevTimer = 0xFFFFFFFF;

  // Calculate the remaining timeout value by subtracting the current timer value from the timeout value.
  uint32_t RevTimer = TimeoutValue - Timer;

  // If the current reverse timer value is different from the previous value, update the display.
  if (RevTimer != previousRevTimer) {
    // Update the previous reverse timer value with the current value.
    previousRevTimer = RevTimer;

    // Clear the SSD1306 display.
    ssd1306_clear();

    // Set the cursor position on the SSD1306 display.
    ssd1306_SetCursor(15, 13);

    // Display the "Timeout in " text on the SSD1306 display using Font_7x10.
    ssd1306_WriteString("Timeout in ", Font_7x10, 1);

    // Convert the reverse timer value to a string.
    char str[12];
    itoa(RevTimer, str, 10);

    // Display the reverse timer value on the SSD1306 display using Font_7x10.
    ssd1306_WriteString(str, Font_7x10, 1);

    // Update the SSD1306 display to show the new content.
    ssd1306_UpdateScreen();
  }
}

void Enroll() {
  // Print "Enroll" for debugging purposes.
  DEBUG_PRINT("Enroll\n");

  // Clear the SSD1306 display.
  ssd1306_clear();

  // Display "Enter new pin" at the specified coordinates using Font_7x10.
  ssd1306_SetCursor(20, 2);
  ssd1306_WriteString("Enter new pin", Font_7x10, 1);

  // Draw a filled rectangle to create a box for the PIN input.
  //ssd1306_FillRectangle(3, 10, 122, 10, 1);

  // Draw lines to separate individual PIN input positions.
  for (int i = 0; i < 12; i++) {
    ssd1306_Line(6 + i*10, 27, 12 + i*10, 27, 1);
  }

  // Set the cursor to the first PIN input position and display '!' as a starting character.
  ssd1306_SetCursor(6, 18);
  ssd1306_WriteChar('!', Font_7x10, 1);

  // Update the SSD1306 display to show the initial PIN entry screen.
  ssd1306_UpdateScreen();

  // Initialize the flag to true to start the while loop, index to 0, and temp_num to 33 (ASCII '!')
  bool flag = true;
  uint8_t index = 0;
  uint8_t temp_num = 33;

  // Loop to handle PIN entry until the flag is set to false.
  while (flag) {
    // Check the state of the buttons.
    uint8_t temp = checkButtons();

    // If the 'up' button is pressed, increment temp_num and wrap around if it exceeds 126.
    if (temp == 0) {
      temp_num++;
      if (temp_num == 127) temp_num = 33;
      ssd1306_SetCursor(6 + index*10, 18);
      ssd1306_WriteChar((char)temp_num, Font_7x10, 1);
      ssd1306_UpdateScreen();
    }

    // If the 'down' button is pressed, decrement temp_num and wrap around if it goes below 33.
    if (temp == 1) {
      temp_num--;
      if (temp_num < 33) temp_num = 126;
      ssd1306_SetCursor(6 + index*10, 18);
      ssd1306_WriteChar((char)temp_num, Font_7x10, 1);
      ssd1306_UpdateScreen();
    }

    // If both buttons are pressed, handle the PIN entry.
    if (temp == 2) {
      // If the index is 11 (last position), save the entered PIN and exit the loop.
      if (index == 11) {
        password[index] = temp_num;
        flag = false;
        ssd1306_SetCursor(6 + index*10, 18);
        ssd1306_WriteChar('*', Font_7x10, 1);
        ssd1306_UpdateScreen();
        printArray("Input password ", password, sizeof(password));
        // Read the number of users from flash memory.
        MY_FLASH_ReadN(Nusers_address, &user_num, 1, DATA_TYPE_8);
        DEBUG_PRINT("Num of Users %d\n",user_num);
        // Generate and save a local salt.
        Get_rng(&hrng, LocalSalt, 2);
        printArray("Local salt ", LocalSalt, sizeof(LocalSalt));
        write_flash(MemDatastartpoint + (user_num * 72), LocalSalt, 8);

        // Generate and save an initialization vector (IV).
        Get_rng(&hrng, IV, 4);
        printArray("IV ", IV, sizeof(IV));
        write_flash(MemDatastartpoint + 8 + (user_num * 72), IV, 16);

        // Read the global salt from flash memory.
        MY_FLASH_ReadN(GlobalSalt_address, GlobalSalt, 8, DATA_TYPE_8);
        printArray("GlobalSalt ", GlobalSalt, sizeof(GlobalSalt));
        // Concatenate the global salt and password, and compute the SHA-256 hash.
        uint8_t temp[20];
        memcpy(temp, GlobalSalt, sizeof(GlobalSalt));
        memcpy(temp + sizeof(GlobalSalt), password, sizeof(password));
        printArray("Concatenated password ", temp, sizeof(temp));
        uint8_t computedSha256[32];
        sha256(temp, computedSha256, sizeof(temp));
        printArray("Hashed password ", computedSha256, sizeof(computedSha256));
        // Save the computed SHA-256 hash of the password.
        write_flash(MemDatastartpoint + 8 + 16 + (user_num * 72), computedSha256, 32);

        // Generate a master key.
        Get_rng(&hrng ,MasterKey, 4);
        printArray("MasterKey ", MasterKey, sizeof(MasterKey));
        // Concatenate the local salt and password, and compute the SHA-256 hash.
        memcpy(temp, LocalSalt, sizeof(LocalSalt));
        memcpy(temp + sizeof(LocalSalt), password, sizeof(password));
        printArray("Concatenated masterKey ", temp, sizeof(temp));
        sha256(temp, computedSha256, sizeof(temp));
        printArray("Hashed masterKey ", temp, sizeof(temp));
        // Encrypt the master key using AES-CBC.
        uint8_t computedAES[16];
        AESCBC(MasterKey, sizeof(MasterKey), computedSha256, sizeof(computedSha256), IV, sizeof(IV), computedAES);
        printArray("Encrypted masterKey ", computedAES, sizeof(computedAES));
        // Save the encrypted master key.
        write_flash(MemDatastartpoint + 8 + 16 + 32 + (user_num * 72), computedAES, 16);

        // Update the "brand new" status in flash memory.
        uint8_t value = 1;
        write_flash(BrandNew_address, &value, 1);

        // Increment and save the number of users.
        user_num++;
        write_flash(Nusers_address, &user_num, 1);

        // Blink to indicate successful enrollment and clear the display.
        //blink();
        ssd1306_clear();

        // Set the system state to Lock.
        state = Lock;
      } else {
        // Save the entered character in the password array and move to the next position.
        password[index] = temp_num;
        temp_num = 33;
        ssd1306_SetCursor(6 + index*10, 18);
        ssd1306_WriteChar('*', Font_7x10, 1);
        ssd1306_UpdateScreen();
        index++;
        ssd1306_SetCursor(6 + index*10, 18);
        ssd1306_WriteChar((char)temp_num, Font_7x10, 1);
        ssd1306_UpdateScreen();
      }
    }
  }
}

void LockDevice() {
  DEBUG_PRINT("LockDevice\n");
  // Set the device and timer states to false, indicating the device is locked and the timer is inactive.
  DeviceState = false;
  TimerState = false;

  // Clear the SSD1306 display.
  ssd1306_clear();

  // Display "Enter pin" at the specified coordinates using Font_7x10.
  ssd1306_SetCursor(32, 2);
  ssd1306_WriteString("Enter pin", Font_7x10, 1);

  // Draw a filled rectangle to create a box for the PIN input.
  //ssd1306_FillRectangle(3, 20, 122, 30, 1);

  // Draw lines to separate individual PIN input positions.
  for (int i = 0; i < 12; i++) {
    ssd1306_Line(6 + i*10, 27, 12 + i*10, 27, 1);
  }

  // Set the cursor to the first PIN input position and display '!' as a starting character.
  ssd1306_SetCursor(6, 18);
  ssd1306_WriteChar('!', Font_7x10, 1);

  // Update the SSD1306 display to show the initial PIN entry screen.
  ssd1306_UpdateScreen();

  // Initialize the flag to true to start the while loop, index to 0, and temp_num to 33 (ASCII '!').
  bool flag = true;
  uint8_t index = 0;
  uint8_t temp_num = 33;

  // Loop to handle PIN entry until the flag is set to false.
  while (flag) {
    // Check the state of the buttons.
    uint8_t temp = checkButtons();

    // If the 'up' button is pressed, increment temp_num and wrap around if it exceeds 126.
    if (temp == 0) {
      temp_num++;
      if (temp_num == 127) temp_num = 33;
      ssd1306_SetCursor(6 + index*10, 18);
      ssd1306_WriteChar((char)temp_num, Font_7x10, 1);
      ssd1306_UpdateScreen();
    }

    // If the 'down' button is pressed, decrement temp_num and wrap around if it goes below 33.
    if (temp == 1) {
      temp_num--;
      if (temp_num < 33) temp_num = 126;
      ssd1306_SetCursor(6 + index*10, 18);
      ssd1306_WriteChar((char)temp_num, Font_7x10, 1);
      ssd1306_UpdateScreen();
    }

    // If both buttons are pressed, handle the PIN entry.
    if (temp == 2) {
      // If the index is 11 (last position), save the entered PIN and exit the loop.
      if (index == 11) {
        password[index] = temp_num;
        flag = false;
        ssd1306_SetCursor(6 + index*10, 18);
        ssd1306_WriteChar('*', Font_7x10, 1);
        ssd1306_UpdateScreen();
        printArray("Input password", password, sizeof(password));
        // Check if the entered password is correct.
        if (CheckPassword()) {
          DEBUG_PRINT("Password is correct\n");
          // If the password is correct, load the user's salt, IV, and encrypted master key.
          MY_FLASH_ReadN(MemDatastartpoint + (CurrentUser*72), CurrentLocalSalt, 8, DATA_TYPE_8);
          MY_FLASH_ReadN(MemDatastartpoint + 8 + (CurrentUser*72), CurrentIV, 16, DATA_TYPE_8);
          MY_FLASH_ReadN(MemDatastartpoint + 8 + 16 + 32 + (CurrentUser*72), CurrentMasterKey, 16, DATA_TYPE_8);

          // Compute the SHA-256 hash of the concatenation of the local salt and password.
          uint8_t temp[20];
          memcpy(temp, CurrentLocalSalt, sizeof(CurrentLocalSalt));
          memcpy(temp + sizeof(CurrentLocalSalt), CurrentPassword, sizeof(CurrentPassword));
          uint8_t computedSha256[32];
          sha256(temp, computedSha256, sizeof(temp));

          // Decrypt the master key using AES with the computed SHA-256 hash as the key.
          DecryptAES(CurrentMasterKey, sizeof(CurrentMasterKey), computedSha256, sizeof(computedSha256), CurrentIV, sizeof(CurrentIV), CurrentMasterKey);

          // Print the decrypted master key for debugging purposes.
          printArray("Decrypted master key ", CurrentMasterKey, sizeof(CurrentMasterKey));

          // Blink to indicate successful decryption, set the device state to true, and change the state to Menu.
          //blink();
          DeviceState = true;
          state = Menu;
        } else {
          DEBUG_PRINT("Password is wrong\n");
          // If the password is incorrect, increment the wrong password counter.
          MY_FLASH_ReadN(WrongPassword_address, &WrongPassword, 1, DATA_TYPE_8);
          WrongPassword++;
          if (WrongPassword < 5) {
            // If the wrong password counter is less than 5, update the corresponding LED and flash memory.
            write_flash(WrongPassword_address, &WrongPassword, 1);

            // Trigger an alarm on the OLED and reset the state to Lock.
            OledAlarm();
            state = Lock;
          } else {
            // If the wrong password counter reaches 5, erase memory and reset the LEDs.
            EraseAlaram();
            EraseMem();
            //blink();
            // Set the state to Enrollment for re-enrollment.
            state = Enrollment;
          }
        }

        // Clear the SSD1306 display.
        ssd1306_clear();
      } else {
        // Save the entered character in the password array and move to the next position.
        password[index] = temp_num;
        temp_num = 33;
        ssd1306_SetCursor(6 + index*10, 18);
        ssd1306_WriteChar('*', Font_7x10, 1);
        ssd1306_UpdateScreen();
        index++;
        ssd1306_SetCursor(6 + index*10, 18);
        ssd1306_WriteChar((char)temp_num, Font_7x10, 1);
        ssd1306_UpdateScreen();
      }
    }
  }
}

void EraseAlaram() {
  DEBUG_PRINT("Erase memory\n");
  // Clear the SSD1306 display.
  ssd1306_clear();

  // Display "Memory" message at the specified coordinates using Font_11x18.
  ssd1306_SetCursor(8, 11);
  ssd1306_WriteString("Memory erasing:(", Font_7x10, 1);

  // Update the SSD1306 display to show the memory erasing message.
  ssd1306_UpdateScreen();

  // Delay for 3000 milliseconds (3 seconds) to allow the user to read the memory erasing message.
  HAL_Delay(3000);
}

void EraseMem(){
  uint8_t All_0[1000] = {0};
  write_flash(0, All_0, 1000);
}

void ResetFactory() {
  DEBUG_PRINT("Reset factory\n");
  // Clear the SSD1306 display.
  ssd1306_clear();

  // Draw a filled rectangle around the "No" option.
  //ssd1306_FillRectangle(71, 17, 25, 6, 1);

  // Display "Reset factory" at the specified coordinates using Font_7x10.
  ssd1306_SetCursor(18, 8);
  ssd1306_WriteString("Reset factory", Font_7x10, 1);

  // Display "Yes" and "No" options at the specified coordinates.
  ssd1306_SetCursor(38, 18);
  ssd1306_WriteString("Yes", Font_7x10, 1);
  ssd1306_SetCursor(78, 18);
  ssd1306_WriteString("No", Font_7x10, 0);

  // Update the SSD1306 display to show the initial reset factory screen.
  ssd1306_UpdateScreen();

  // Initialize the YesNo flag to false, indicating "No" is currently selected.
  bool YesNo = false;

  // Loop to handle user input until the device state changes or the user makes a selection.
  while (1) {
    // If the device is locked, change the state to Lock and break the loop.
    if (!DeviceState) {
      state = Lock;
      break;
    }

    // Check the state of the buttons.
    uint8_t btn_state = checkButtons();

    // If the 'up' button is pressed, select "Yes" and update the display.
    if (btn_state == 0) { // up
      ssd1306_clear();
      //ssd1306_FillRectangle(36, 35, 25, 12, 1);
      ssd1306_SetCursor(18, 8);
      ssd1306_WriteString("Reset factory", Font_7x10, 1);
      ssd1306_SetCursor(38, 18);
      ssd1306_WriteString("Yes", Font_7x10, 0);
      ssd1306_SetCursor(78, 18);
      ssd1306_WriteString("No", Font_7x10, 1);
      ssd1306_UpdateScreen();
      YesNo = true;
    }

    // If the 'down' button is pressed, select "No" and update the display.
    else if (btn_state == 1) { // down
      ssd1306_clear();
      //ssd1306_FillRectangle(71, 35, 25, 12, 1);
      ssd1306_SetCursor(18, 8);
      ssd1306_WriteString("Reset factory", Font_7x10, 1);
      ssd1306_SetCursor(38, 18);
      ssd1306_WriteString("Yes", Font_7x10, 1);
      ssd1306_SetCursor(78, 18);
      ssd1306_WriteString("No", Font_7x10, 0);
      ssd1306_UpdateScreen();
      YesNo = false;
    }

    // If both buttons are pressed, perform the action based on the selected option.
    else if (btn_state == 2) { // both
      // If "Yes" is selected, erase alarms and memory, reset LEDs, and change state to Enrollment.
      if (YesNo) {
        DEBUG_PRINT("Reset factory is applied\n");
        EraseAlaram();
        EraseMem();
        state = Enrollment;
      }

      // If "No" is selected, change the state back to Menu.
      if (!YesNo) {
        DEBUG_PRINT("Reset factory is denied\n");
        state = Menu;
      }
      // Break the loop after making a selection.
      break;
    }
  }
}


void OledAlarm() {
  DEBUG_PRINT("OLED alarm\n");
  // Clear the SSD1306 display.
  ssd1306_clear();

  // Display "Warning" message at the specified coordinates using Font_11x18.
  ssd1306_SetCursor(39, 4);
  ssd1306_WriteString("Warning", Font_7x10, 1);

  // Calculate the remaining attempts and display it.
  ssd1306_SetCursor(4, 18);
  ssd1306_WriteChar(4 - WrongPassword + '0', Font_7x10, 1);  // Display the number of remaining attempts.

  // Display " more attempts" message at the specified coordinates using Font_7x10.
  ssd1306_WriteString(" more attempts", Font_7x10, 1);

  // Update the SSD1306 display to show the warning message and remaining attempts.
  ssd1306_UpdateScreen();

  // Delay for 3000 milliseconds (3 seconds) to allow the user to read the warning message.
  HAL_Delay(3000);
}

bool CheckPassword() {
  uint8_t tempPassword[32]; // Buffer to hold a hashed password read from memory

  // Read the number of users stored in flash memory
  MY_FLASH_ReadN(Nusers_address, &user_num, 1, DATA_TYPE_8);

  // Iterate through each user's stored password to check against the provided password
  for (int i = 0; i < user_num; i++) {
    // Construct the hash of the provided password combined with the global salt
    uint8_t temp[20];
    memcpy(temp, GlobalSalt, sizeof(GlobalSalt)); // Copy global salt into temp buffer
    memcpy(temp + sizeof(GlobalSalt), password, sizeof(password)); // Append password to temp buffer
    uint8_t computedSha256[32];
    sha256(temp, computedSha256, sizeof(temp)); // Compute SHA-256 hash of temp buffer

    // Read the stored hashed password from flash memory
    MY_FLASH_ReadN(MemDatastartpoint + 8 + 16 + (i * 72), tempPassword, 32, DATA_TYPE_8);

    // Compare computed hash with stored hashed password
    if (memcmp(tempPassword, computedSha256, 32) == 0) {
      // If passwords match, store the current user and password for future reference
      CurrentUser = i;
      memcpy(CurrentPassword, password, sizeof(password));
      return true; // Password match found, return true
    }
  }

  return false; // No matching password found among stored hashes, return false
}
