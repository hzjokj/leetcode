#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define UNIV_WAY
#if defined(UNIV_WAY)
// Define the states of the traffic light
typedef enum { RED, YELLOW, GREEN } TrafficLightState;

// Function to update the state of the traffic light
TrafficLightState updateState(TrafficLightState currentState)
{
    switch (currentState) {
    case RED:
        return YELLOW;
    case YELLOW:
        return GREEN;
    case GREEN:
        return RED;
    default:
        return RED; // Default to Red state in case of an unknown state
    }
}

int test_traffic_light(void)
{
    TrafficLightState currentState = RED;

    while (1) {
        // Display the current state of the traffic light
        switch (currentState) {
        case RED:
            printf("Traffic Light: Red\n");
            break;
        case YELLOW:
            printf("Traffic Light: Yellow\n");
            break;
        case GREEN:
            printf("Traffic Light: Green\n");
            break;
        }

        // Simulate a delay for the state transition (in a real application, this might be timer-based)
        sleep(1); // Do nothing, just waste some time

        // Update the state of the traffic light
        currentState = updateState(currentState);
    }

    return 0;
}

#elif defined(FUNC_WAY)
// Define the states of the traffic light
typedef enum { RED, YELLOW, GREEN } TrafficLightState;

// Function prototypes for state functions
typedef void (*StateFunction)(void);

// Function declarations for each state
void redState(void);
void yellowState(void);
void greenState(void);

// Array of state function pointers
StateFunction stateFunctions[] = {redState, yellowState, greenState};

// Global variable to store the current state
TrafficLightState currentState = RED;

// State functions
void redState(void)
{
    printf("Traffic Light: Red\n");
    // Transition to the next state (Yellow)
    currentState = YELLOW;
}

void yellowState(void)
{
    printf("Traffic Light: Yellow\n");
    // Transition to the next state (Green)
    currentState = GREEN;
}

void greenState(void)
{
    printf("Traffic Light: Green\n");
    // Transition to the next state (Red)
    currentState = RED;
}

int test_traffic_light(void)
{
    while (1) {
        // Call the state function for the current state
        stateFunctions[currentState]();
        sleep(1);
    }

    return 0;
}

#elif defined(MULTI_THREAD_WAY)
// Define the states of the traffic light
typedef enum { RED, YELLOW, GREEN } TrafficLightState;

// Global variable to store the current state
TrafficLightState currentState = RED;

// Mutex to control access to the current state
pthread_mutex_t stateMutex = PTHREAD_MUTEX_INITIALIZER;

// Function representing the Red state
void *redState(void *arg)
{
    while (1) {
        pthread_mutex_lock(&stateMutex);
        currentState = RED;
        pthread_mutex_unlock(&stateMutex);
        printf("Traffic Light: Red\n");
        sleep(2); // Simulate a 2-second delay
    }
    return NULL;
}

// Function representing the Yellow state
void *yellowState(void *arg)
{
    while (1) {
        pthread_mutex_lock(&stateMutex);
        currentState = YELLOW;
        pthread_mutex_unlock(&stateMutex);
        printf("Traffic Light: Yellow\n");
        sleep(2); // Simulate a 2-second delay
    }
    return NULL;
}

// Function representing the Green state
void *greenState(void *arg)
{
    while (1) {
        pthread_mutex_lock(&stateMutex);
        currentState = GREEN;
        pthread_mutex_unlock(&stateMutex);
        printf("Traffic Light: Green\n");
        sleep(2); // Simulate a 2-second delay
    }
    return NULL;
}

int test_traffic_light(void)
{
    // Create threads for each state
    pthread_t redThread, yellowThread, greenThread;
    pthread_create(&redThread, NULL, redState, NULL);
    pthread_create(&yellowThread, NULL, yellowState, NULL);
    pthread_create(&greenThread, NULL, greenState, NULL);

    // Join threads (this will not be reached)
    pthread_join(redThread, NULL);
    pthread_join(yellowThread, NULL);
    pthread_join(greenThread, NULL);

    return 0;
}
#endif

/*------------------------------------------------------------------*/
// Define the states of the light switch
typedef enum { OFF, ON } LightSwitchState;

// Function to update the state of the light switch
LightSwitchState toggleState(LightSwitchState currentState)
{
    if (currentState == OFF) {
        return ON;
    } else {
        return OFF;
    }
}

int test_light_switch(void)
{
    LightSwitchState currentState = OFF;

    while (1) {
        // Display the current state of the light switch
        if (currentState == OFF) {
            printf("Light Switch: OFF\n");
        } else {
            printf("Light Switch: ON\n");
        }

        // Get user input (0 to turn off, 1 to turn on)
        int userInput;
        printf("Enter 0 to turn OFF, 1 to turn ON: ");
        scanf("%d", &userInput);

        if (userInput == 0) {
            currentState = OFF;
        } else if (userInput == 1) {
            currentState = ON;
        } else {
            printf("Invalid input. Please enter 0 or 1.\n");
        }
    }

    return 0;
}

/*------------------------------------------------------------------*/
// Define the states of the door
typedef enum { DOOR_CLOSED, DOOR_OPEN } DoorState;

// Define the events that can trigger state transitions
typedef enum { EVENT_OPEN_DOOR, EVENT_CLOSE_DOOR } DoorEvent;

// Function to transition to a new state based on an event
DoorState transition(DoorState currentState, DoorEvent event)
{
    switch (event) {
    case EVENT_OPEN_DOOR:
        if (currentState == DOOR_CLOSED) {
            return DOOR_OPEN;
        }
        break;
    case EVENT_CLOSE_DOOR:
        if (currentState == DOOR_OPEN) {
            return DOOR_CLOSED;
        }
        break;
    }
    // No transition
    return currentState;
}

int test_door(void)
{
    DoorState currentState = DOOR_CLOSED;
    DoorEvent event;

    while (1) {
        // Display the current state of the door
        if (currentState == DOOR_CLOSED) {
            printf("Door State: Closed\n");
        } else {
            printf("Door State: Open\n");
        }

        // Get user input to trigger an event
        printf(
            "Enter 0 to open the door, 1 to close the door, or any other key to exit: ");
        scanf("%d", (int *)&event);

        // Perform the transition based on the event
        currentState = transition(currentState, event);

        // Clear the input buffer
        while (getchar() != '\n') {
        }

        // Check for an exit condition (e.g., user presses a key)
        if (event != 0 && event != 1) {
            break;
        }
    }

    return 0;
}

/*------------------------------------------------------------------*/
// Define the states of the FSM
typedef enum { STATE_A, STATE_B } State;

// Define the events that trigger state transitions
typedef enum { EVENT_START, EVENT_TIMEOUT } Event;

// Function to handle state A
void stateA(void)
{
    printf("State A\n");
}

// Function to handle state B
void stateB(void)
{
    printf("State B\n");
}

// Callback function for the timer event
void timerCallback(void)
{
    printf("Timer event occurred\n");
}

// Function to simulate a timer event
void startTimer(int seconds, Event event, void (*callback)())
{
    time_t startTime = time(NULL);
    while (difftime(time(NULL), startTime) < seconds) {
        // Waiting for the timer to expire
    }
    if (event == EVENT_TIMEOUT) {
        if (callback) {
            callback(); // Execute the callback function if provided
        }
    }
}

int test_state(void)
{
    State currentState = STATE_A;

    while (1) {
        switch (currentState) {
        case STATE_A:
            stateA();
            startTimer(2, EVENT_TIMEOUT, timerCallback);
            currentState = STATE_B;
            break;

        case STATE_B:
            stateB();
            startTimer(2, EVENT_TIMEOUT, timerCallback);
            currentState = STATE_A;
            break;
        }
    }

    return 0;
}
