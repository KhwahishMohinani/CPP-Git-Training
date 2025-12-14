#include "Elevator.h"
#include "constants.h"
#include <thread>
#include <chrono>
#include <gtest/gtest.h>

class ElevatorTest : public ::testing::Test
{
protected:
    Elevator *elevator;

    void SetUp() override
    {
        elevator = new Elevator(0);
    }

    void TearDown() override
    {
        delete elevator;
    }
};

TEST_F(ElevatorTest, GivenNewElevator_WhenConstructed_ThenIdleAtZero)
{
    EXPECT_EQ(elevator->getCurrentFloor(), 0);
    EXPECT_EQ(elevator->getState(), State::Idle);
    EXPECT_TRUE(elevator->getStops().empty());
}

TEST_F(ElevatorTest, GivenNewElevator_WhenCreated_ThenDirectionIsNone)
{
    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::None);
}

TEST_F(ElevatorTest, GivenIdleElevator_WhenUpStopAdded_ThenDirectionIsUp)
{
    elevator->addStop(3, 'u');

    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Up);
}

TEST_F(ElevatorTest, GivenIdleElevator_WhenDownStopAdded_ThenDirectionIsDown)
{
    elevator->addStop(-1, 'd');

    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Down);
}

TEST_F(ElevatorTest, GivenMovingUpElevator_WhenStepping_ThenDirectionRemainsUp)
{
    elevator->addStop(3, 'u');

    elevator->step();

    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Up);
}

TEST_F(ElevatorTest, GivenNewElevator_WhenConstructed_ThenStopsAreEmpty)
{
    EXPECT_TRUE(elevator->getStops().empty());
}

TEST_F(ElevatorTest, GivenElevator_WhenDirectionSetToUp_ThenDirectionIsUp)
{
    elevator->setElevatorDirection(ElevatorDirection::Up);

    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Up);
}

TEST_F(ElevatorTest, GivenElevator_WhenDirectionSetToDown_ThenDirectionIsDown)
{
    elevator->setElevatorDirection(ElevatorDirection::Down);

    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Down);
}

TEST_F(ElevatorTest, GivenInvalidFloor_WhenAddStopCalled_ThenReturnsFalse)
{
    bool result = elevator->addStop(MIN_FLOOR - 1, 'u');

    EXPECT_FALSE(result);
    EXPECT_TRUE(elevator->getStops().empty());
    EXPECT_EQ(elevator->getState(), State::Idle);
}

TEST_F(ElevatorTest, GivenInvalidAboveMaxFloor_WhenAddStopCalled_ThenRejected)
{
    bool result = elevator->addStop(MAX_FLOOR + 1, 'd');

    EXPECT_FALSE(result);
    EXPECT_TRUE(elevator->getStops().empty());
    EXPECT_EQ(elevator->getState(), State::Idle);
}

TEST_F(ElevatorTest, GivenDuplicateStop_WhenAddStopCalled_ThenRejected)
{
    EXPECT_TRUE(elevator->addStop(3, 'u'));
    EXPECT_FALSE(elevator->addStop(3, 'u'));

    auto stops = elevator->getStops();
    ASSERT_EQ(stops.size(), 1);
    EXPECT_EQ(stops[0], 3);
}

TEST_F(ElevatorTest, GivenValidStop_WhenAddStopCalled_ThenStopIsAdded)
{
    bool result = elevator->addStop(2, 'u');

    EXPECT_TRUE(result);

    auto stops = elevator->getStops();
    ASSERT_EQ(stops.size(), 1);
    EXPECT_EQ(stops[0], 2);
}

TEST_F(ElevatorTest, GivenMultipleUpStops_WhenAdded_ThenSortedAscending)
{
    elevator->addStop(5, 'u');
    elevator->addStop(2, 'u');
    elevator->addStop(4, 'u');

    std::vector<int> expected{2, 4, 5};
    EXPECT_EQ(elevator->getStops(), expected);
}

TEST_F(ElevatorTest, GivenMultipleDownStops_WhenAdded_ThenSortedDescending)
{
    elevator->addStop(1, 'd');
    elevator->addStop(-1, 'd');
    elevator->addStop(0, 'd');

    std::vector<int> expected{1, 0, -1};
    EXPECT_EQ(elevator->getStops(), expected);
}

TEST_F(ElevatorTest, GivenIdleElevator_WhenUpStopAdded_ThenStateIsMovingUp)
{
    EXPECT_EQ(elevator->getState(), State::Idle);

    bool result = elevator->addStop(2, 'u');

    EXPECT_TRUE(result);
    EXPECT_EQ(elevator->getState(), State::MovingUp);
    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Up);
}

TEST_F(ElevatorTest, GivenIdleElevator_WhenDownStopAdded_ThenStateIsMovingDown)
{
    bool result = elevator->addStop(-1, 'd');

    EXPECT_TRUE(result);
    EXPECT_EQ(elevator->getState(), State::MovingDown);
    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Down);
}

TEST_F(ElevatorTest, GivenElevatorAtTargetFloor_WhenAddStopCalled_ThenDoorOpens)
{
    EXPECT_EQ(elevator->getCurrentFloor(), 0);

    bool result = elevator->addStop(0, 'u');

    EXPECT_TRUE(result);
    EXPECT_EQ(elevator->getState(), State::DoorOpen);
    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Up);
}

TEST_F(ElevatorTest, GivenMovingElevator_WhenAddStopCalled_ThenStateUnchanged)
{
    elevator->addStop(3, 'u');
    EXPECT_EQ(elevator->getState(), State::MovingUp);

    bool result = elevator->addStop(5, 'u');

    EXPECT_TRUE(result);
    EXPECT_EQ(elevator->getState(), State::MovingUp);
    EXPECT_EQ(elevator->getElevatorDirection(), ElevatorDirection::Up);
}

TEST_F(ElevatorTest, GivenIdleElevatorWithNoStops_WhenStepCalled_ThenNoActionTaken)
{
    EXPECT_EQ(elevator->getState(), State::Idle);

    bool result = elevator->step();

    EXPECT_FALSE(result);
    EXPECT_EQ(elevator->getState(), State::Idle);
}

TEST_F(ElevatorTest, GivenIdleElevatorWithStop_WhenStepCalled_ThenMovementStarts)
{
    elevator->addStop(2, 'u');

    bool result = elevator->step();

    EXPECT_TRUE(result);
    EXPECT_EQ(elevator->getState(), State::MovingUp);
}

TEST_F(ElevatorTest, GivenMovingUpElevator_WhenStepCalled_ThenFloorIncrements)
{
    elevator->addStop(2, 'u');

    elevator->step();

    EXPECT_EQ(elevator->getCurrentFloor(), 1);
    EXPECT_EQ(elevator->getState(), State::MovingUp);
}

TEST_F(ElevatorTest, GivenMovingDownElevator_WhenStepCalled_ThenFloorDecrements)
{
    elevator->addStop(-2, 'd');

    elevator->step();

    EXPECT_EQ(elevator->getCurrentFloor(), -1);
    EXPECT_EQ(elevator->getState(), State::MovingDown);
}

TEST_F(ElevatorTest, GivenMovingElevator_WhenTargetReached_ThenDoorOpens)
{
    elevator->addStop(1, 'u');

    bool result = elevator->step();

    EXPECT_TRUE(result);
    EXPECT_EQ(elevator->getCurrentFloor(), 1);
    EXPECT_EQ(elevator->getState(), State::DoorOpen);
}

TEST_F(ElevatorTest, GivenDoorOpen_WhenStepCalledBeforeTimeout_ThenRemainsOpen)
{
    elevator->addStop(1, 'u');
    elevator->step();
    elevator->step();

    bool result = elevator->step();

    EXPECT_FALSE(result);
    EXPECT_EQ(elevator->getState(), State::DoorOpen);
}

TEST_F(ElevatorTest, GivenUpwardMovement_WhenSteppingBeyondMax_ThenStopsAtMaxFloor)
{
    elevator->addStop(MAX_FLOOR, 'u');

    for (int floor = 0; floor < 20; ++floor)
        elevator->step();

    EXPECT_EQ(elevator->getCurrentFloor(), MAX_FLOOR);
}

TEST_F(ElevatorTest, GivenDownwardMovement_WhenSteppingBeyondMin_ThenStopsAtMinFloor)
{
    elevator->addStop(MIN_FLOOR, 'd');

    for (int floor = 0; floor < 20; ++floor)
        elevator->step();

    EXPECT_EQ(elevator->getCurrentFloor(), MIN_FLOOR);
}
