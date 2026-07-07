#include <stdio.h>
#include <stdbool.h>
// Define device states using typedef enum
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_STOPPED,
    STATE_ERROR
} DeviceState;
// Helper function: convert state to string for printing
const char* state_to_string(DeviceState s) {
    switch (s) {
        case STATE_IDLE:    return "IDLE";
        case STATE_RUNNING: return "RUNNING";
        case STATE_STOPPED: return "STOPPED";
        case STATE_ERROR:   return "ERROR";
        default:            return "UNKNOWN";
    }
}
int main(void) {
    // Initial state: the device starts in IDLE
    DeviceState current_state = STATE_IDLE;
    bool has_fault = false;    // C99 bool type (true/false)
    printf("=== Simple State Machine Demo ===\n");
    // Simulate a sequence of events
    for (int step = 1; step <= 5; step++) {
        printf("\n[Step %d] Current state: %s\n", step, state_to_string(current_state));
        // Perform actions and state transitions based on current state
        switch (current_state) {
            case STATE_IDLE:
                printf("  Action: Starting device...\n");
                // Transition: IDLE -> RUNNING (if no fault)
                if (!has_fault) {
                    current_state = STATE_RUNNING;
                }
                break;
            case STATE_RUNNING:
                printf("  Action: Device is running...\n");
                // Simulate a fault occurring at step 3
                if (step == 3) {
                    has_fault = true;
                    printf("  ! Fault detected !\n");
                    current_state = STATE_ERROR;
                } else {
                    // Normal transition: RUNNING -> STOPPED (after work done)
                    current_state = STATE_STOPPED;
                }
                break;
            case STATE_STOPPED:
                printf("  Action: Device stopped. Resetting...\n");
                // Transition: STOPPED -> IDLE
                current_state = STATE_IDLE;
                has_fault = false;   // Clear any previous fault
                break;
            case STATE_ERROR:
                printf("  Action: Handling error...\n");
                if (has_fault) {
                    printf("  Attempting recovery...\n");
                    has_fault = false;            // Clear fault
                    current_state = STATE_IDLE;   // Go back to IDLE
                }
                break;
            default:
                printf("  Unknown state!\n");
                break;
        }
        // Print the new state after transition
        printf("  -> New state: %s\n", state_to_string(current_state));
    }
    printf("\n=== Demo finished ===\n");
    return 0;
}