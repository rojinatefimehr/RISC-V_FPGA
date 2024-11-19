#include "xil_types.h"

// Macros for seven-segment display and button addresses
#define SEG_DISPLAY *((uint32_t *) 0x40030000)    // Anode control for first display
#define SEG_DISPLAY_1 *((uint32_t *) 0x40040000)  // Cathode control for first display
#define SEG_DISPLAY_2 *((uint32_t *) 0x40050000)  // Anode control for second display
#define SEG_DISPLAY_3 *((uint32_t *) 0x40060000)  // Cathode control for second display
#define BUTTONS *((uint32_t *) 0x40020000)        // Buttons

// Lookup table for cathode-based control (active-low for cathodes)
const uint8_t seg_values[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};

// Function to add a small delay
void delay(int count)
{
    volatile int i;
    for (i = 0; i < count; i++);
}

int main()
{
    uint8_t count1 = 0;          // Counter for the first seven-segment display
    uint8_t count2 = 0;          // Counter for the second seven-segment display
    uint32_t button_pressed1 = 0; // Track button state for BTN0
    uint32_t button_pressed2 = 0; // Track button state for BTN1

    // Initialize both anodes (off) and cathodes (all segments off)
    SEG_DISPLAY = 0x00;    // Turn off the anode for the first display
    SEG_DISPLAY_1 = 0xFF;  // Turn off all cathode segments for the first display
    SEG_DISPLAY_2 = 0x00;  // Turn off the anode for the second display
    SEG_DISPLAY_3 = 0xFF;  // Turn off all cathode segments for the second display

    while (1)
    {
        // Check if BTN0 is pressed (active low) for the first display
        if (BUTTONS & (1 << 0))
        {
            button_pressed1 = 1; // Set button pressed state for BTN0

            // Start counting as a timer for the first display
            while (button_pressed1)
            {
                // Enable the display by turning on the anode
                SEG_DISPLAY = 0xFF;

                // Update the cathode control for the current count
                SEG_DISPLAY_1 = seg_values[count1];

                // Add a delay for timer effect
                delay(100000);

                // Increment the counter
                count1++;
                if (count1 >= 10)
                {
                    count1 = 0; // Reset to 0 after reaching 9
                }

                // Exit if BTN0 is released
                if (!(BUTTONS & (1 << 0)))
                {
                    button_pressed1 = 0;
                    break;
                }
            }

            // Turn off the first display when counting stops
            SEG_DISPLAY = 0x00;
            SEG_DISPLAY_1 = 0xFF;
        }

        // Check if BTN1 is pressed (active low) for the second display
        if (BUTTONS & (1 << 1))
        {
            button_pressed2 = 1; // Set button pressed state for BTN1

            // Start counting as a timer for the second display
            while (button_pressed2)
            {
                // Enable the second display by turning on the anode
                SEG_DISPLAY_2 = 0xFF;

                // Update the cathode control for the current count
                SEG_DISPLAY_3 = seg_values[count2];

                // Add a delay for timer effect
                delay(100000);

                // Increment the counter
                count2++;
                if (count2 >= 10)
                {
                    count2 = 0; // Reset to 0 after reaching 9
                }

                // Exit if BTN1 is released
                if (!(BUTTONS & (1 << 1)))
                {
                    button_pressed2 = 0;
                    break;
                }
            }

            // Turn off the second display when counting stops
            SEG_DISPLAY_2 = 0x00;
            SEG_DISPLAY_3 = 0xFF;
        }
    }

    return 0;
}
