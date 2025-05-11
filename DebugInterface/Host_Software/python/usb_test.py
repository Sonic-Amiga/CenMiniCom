# A very simple script for testing the board.
# Displays running LEDs pattern on each port of each chip
from pio_bus import bus
import time

dev = bus.find_devices()[0]
dev.write(0x18, [0x80] * 8) # Set everything to output
while True:
    for i in range(0, 8):
        leds_a = 1 << i          # port A - left-to-right
        leds_b = 0x80 >> i       # Port B - right-to-left
        leds_c = leds_a | leds_b # Port C - two LEDs moving in opposite directions
        dev.write(0x00, [leds_a] * 8) # Port A of all chips
        dev.write(0x08, [leds_b] * 8) # Port B of all chips
        dev.write(0x10, [leds_c] * 8) # Port C of all chips
        time.sleep(0.1)
