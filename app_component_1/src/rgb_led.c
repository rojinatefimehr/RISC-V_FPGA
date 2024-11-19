#include "xil_types.h"

// Macros for RGB LED, switch, and button addresses
#define RGB_LED *((uint32_t *) 0x40070000)        // First RGB LED control
#define RGB_LED_1 *((uint32_t *) 0x40080000)      // Second RGB LED control
#define SWITCHES *((uint32_t *) 0x40010000)       // Switches
#define LEDS *((uint32_t *) 0x40000000)           // LEDs
#define BUTTONS *((uint32_t *) 0x40020000)        // Buttons
// Macros for seven-segment display and button addresses
#define SEG_DISPLAY *((uint32_t *) 0x40030000)    // Anode control for first display
#define SEG_DISPLAY_1 *((uint32_t *) 0x40040000)  // Cathode control for first display
#define SEG_DISPLAY_2 *((uint32_t *) 0x40050000)  // Anode control for second display
#define SEG_DISPLAY_3 *((uint32_t *) 0x40060000)  // Cathode control for second display

// RGB colors (binary values to write to RGB_LED address)
enum RGB_COLORS {
    RED = 0x01,
    GREEN = 0x02,
    BLUE = 0x04
};

// Function to add a small delay
void delay(int count)
{
    volatile int i;
    for (i = 0; i < count; i++);
}

int main()
{
    // Turn off seven-segment displays initially
    SEG_DISPLAY = 0x00;    // Turn off the anode for the first display
    SEG_DISPLAY_1 = 0xFF;  // Turn off all cathode segments for the first display
    SEG_DISPLAY_2 = 0x00;  // Turn off the anode for the second display
    SEG_DISPLAY_3 = 0xFF;  // Turn off all cathode segments for the second display

    uint32_t rgb_state_1 = RED;  // Current RGB state for LED 1 (starts with RED)
    uint32_t rgb_state_2 = RED;  // Current RGB state for LED 2 (starts with RED)

    while (1)
    {
        // Ensure the seven-segment displays are off in each iteration
        SEG_DISPLAY = 0x00;
        SEG_DISPLAY_1 = 0xFF;
        SEG_DISPLAY_2 = 0x00;
        SEG_DISPLAY_3 = 0xFF;

        // Check switches to turn on associated LEDs for testing
        uint32_t switch_state = SWITCHES;  // Read switch states
        LEDS = switch_state;              // Directly map switches to LEDs

        // Check if BTN0 is pressed (active low) for RGB LED 1
        if (BUTTONS & (1 << 0))
        {
            // Set the current RGB state to LED 1
            RGB_LED = rgb_state_1;

            // Add a PWM-like delay to hold the color
            delay(5000);

            // Cycle to the next color for LED 1 (RED -> GREEN -> BLUE -> RED)
            if (rgb_state_1 == RED)
            {
                rgb_state_1 = GREEN;
            }
            else if (rgb_state_1 == GREEN)
            {
                rgb_state_1 = BLUE;
            }
            else if (rgb_state_1 == BLUE)
            {
                rgb_state_1 = RED;
            }

            // Wait until BTN0 is released to avoid multiple cycles
            while (BUTTONS & (1 << 0));
        }

        // Check if BTN1 is pressed (active low) for RGB LED 2
        if (BUTTONS & (1 << 1))
        {
            // Set the current RGB state to LED 2
            RGB_LED_1 = rgb_state_2;

            // Add a PWM-like delay to hold the color
            delay(5000);

            // Cycle to the next color for LED 2 (RED -> GREEN -> BLUE -> RED)
            if (rgb_state_2 == RED)
            {
                rgb_state_2 = GREEN;
            }
            else if (rgb_state_2 == GREEN)
            {
                rgb_state_2 = BLUE;
            }
            else if (rgb_state_2 == BLUE)
            {
                rgb_state_2 = RED;
            }

            // Wait until BTN1 is released to avoid multiple cycles
            while (BUTTONS & (1 << 1));
        }

        // Check if BTN2 is pressed (active low) to turn off both RGB LEDs
        if (BUTTONS & (1 << 2))
        {
            // Turn off both RGB LEDs
            RGB_LED = 0x00;
            RGB_LED_1 = 0x00;

            // Wait until BTN2 is released to avoid multiple cycles
            while (BUTTONS & (1 << 2));
        }
    }

    return 0;
}
