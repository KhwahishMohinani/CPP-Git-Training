#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int MAX_FLOOR = 7;
constexpr int MIN_FLOOR = -2;
constexpr int ELEVATOR_TICK_MS = 200;
constexpr int DOOR_OPEN_MS = 800;

const char ASSIGNED[] = "Assigned ";
const char ARROW[] = " -> ";
const char TO_ELEVATOR[] = " to Elevator ";
const char STATUS[] = "==================== STATUS ====================\n";
const char IDLE[] = "Idle";
const char MOVING_UP[] = "Moving Up";
const char MOVING_DOWN[] = "Moving Down";
const char DOOR_OPEN[] = "Door Open";
const char SEPARATOR[] = "================================================\n\n";
const char ELEVATOR_LABEL[] = "Elevator ";
const char FLOOR_LABEL[] = " | Floor: ";
const char STATE_LABEL[] = " | State: ";
const char STOPS_LABEL[] = " | Stops: ";
const char TEST_FILE_NAME[] = "test_requests.txt";

enum class State
{
    Idle,
    MovingUp,
    MovingDown,
    DoorOpen
};
enum class ElevatorDirection
{
    None,
    Up,
    Down
};

#endif
