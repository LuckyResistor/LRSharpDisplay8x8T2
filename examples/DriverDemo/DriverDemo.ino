//
// Lucky Resistor's Sharp Display Driver 8x8 Pixel
// ---------------------------------------------------------------------------
// (c)2015 by Lucky Resistor. See LICENSE for details.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//


// This is a demonstration of the driver features.


#include <LRSharpDisplayT2.h>

#include "Fonts.h"


// Create a global instance of the display driver.
lr::SharpDisplay sharpDisplay(11, 9, 10);


void setup() {
  sharpDisplay.begin();
  sharpDisplay.setFont(Fonts::a);
}


void loop() {
  // Write the welcome message.
  sharpDisplay.clear();
  sharpDisplay.setCharacter(0, 0, 'a');
  sharpDisplay.writeText(F("Welcome!\nThis is the text oriented Sharp display driver.\n\n"));
  delay(1000);
  
  // Display some values.
  for (uint8_t i = 1; i < 30; ++i) {
    const uint8_t value = analogRead(7);
    sharpDisplay.writeText(F("V "));
    sharpDisplay.writeText(String(i));
    sharpDisplay.writeText(F(": "));
    sharpDisplay.writeText(String(value));
    sharpDisplay.writeCharacter('\n');
    delay(200);
  }
  delay(500);
  
  // Scroll a portion of the text around.
  sharpDisplay.clear();
  sharpDisplay.writeText(F("\x88\x89\x89\x8a\n\x8b\x8f \x8b\n\x8b \x8f\x8b\n\x98\x89\x89\x99"));
  delay(500);
  lr::SharpDisplay::ScrollDirection sd[] = {lr::SharpDisplay::ScrollRight, lr::SharpDisplay::ScrollDown, lr::SharpDisplay::ScrollLeft, lr::SharpDisplay::ScrollUp};
  for (uint8_t i = 0; i < 4; ++i) {
    for (uint8_t j = 0; j < 4; ++j) {
      for (uint8_t k = 0; k < 8; ++k) {
        sharpDisplay.scrollScreen(sd[j]);
        delay(30);
      }
    }
  }
  for (uint8_t k = 0; k < 12; ++k) {
    sharpDisplay.scrollScreen(lr::SharpDisplay::ScrollDown);
    delay(30);
  }
  
  // Inversion of characters.
  sharpDisplay.clear();
  for (uint8_t i = 0; i < 4; ++i) {
    for (uint8_t j = 0; j < i; ++j) {
      sharpDisplay.writeCharacter(' ');
    }
    sharpDisplay.writeText(F("Normal\n"));
    for (uint8_t j = 0; j < i; ++j) {
      sharpDisplay.writeCharacter(' ');
    }
    sharpDisplay.setTextInverse(true);
    sharpDisplay.writeText(F("Inverse\n"));
    sharpDisplay.setTextInverse(false);
  }
  delay(2000);
  
  // Display all characters and rotate them.
  uint8_t offset = 0;
  for (int l = 0; l < 50; l++) {
    uint8_t character = offset;
    for (uint8_t row = 0; row < sharpDisplay.getScreenHeight(); ++row) {
      for (uint8_t column = 0; column < sharpDisplay.getScreenWidth(); ++column) {
        sharpDisplay.setCharacter(row, column, character);
        ++character;
      }
    }
    ++offset;
    delay(200);
  }
    
}



