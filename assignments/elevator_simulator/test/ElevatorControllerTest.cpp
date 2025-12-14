#include "ElevatorController.h"
#include "MockElevator.h"
#include <gtest/gtest.h>

class ElevatorControllerTest : public ::testing::Test
{
protected:
    ElevatorController controller;
    MockElevator elevator1;
    MockElevator elevator2;
};

TEST_F(ElevatorControllerTest, GivenValidElevator_WhenAddElevatorCalled_ThenDoesNotCrash)
{
    controller.addElevator(&elevator1);
    SUCCEED();
}

TEST_F(ElevatorControllerTest, GivenNullElevator_WhenAddElevatorCalled_ThenReturnsFalse)
{
    EXPECT_FALSE(controller.addElevator(nullptr));
}

TEST_F(ElevatorControllerTest, GivenInvalidDirection_WhenAddRequestCalled_ThenReturnsFalseAndQueueRemainsEmpty)
{
    controller.addElevator(&elevator1);
    controller.addElevator(&elevator2);

    ElevatorRequest request{2, 5, 'x', 0};

    EXPECT_FALSE(controller.addRequest(request));
    EXPECT_TRUE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenValidUpRequest_WhenAddRequestCalled_ThenReturnsTrueAndQueueNotEmpty)
{
    controller.addElevator(&elevator1);
    controller.addElevator(&elevator2);

    ElevatorRequest request{1, 6, 'u', 0};

    EXPECT_TRUE(controller.addRequest(request));
    EXPECT_FALSE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenValidDownRequest_WhenAddRequestCalled_ThenReturnsTrueAndQueueNotEmpty)
{
    controller.addElevator(&elevator1);
    controller.addElevator(&elevator2);

    ElevatorRequest request{5, 2, 'd', 0};

    EXPECT_TRUE(controller.addRequest(request));
    EXPECT_FALSE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenDelayedRequest_WhenAddRequestCalled_ThenReturnsTrueAndQueueNotEmpty)
{
    controller.addElevator(&elevator1);
    controller.addElevator(&elevator2);

    ElevatorRequest request{2, 4, 'u', 100};

    EXPECT_TRUE(controller.addRequest(request));
    EXPECT_FALSE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenMultipleValidRequests_WhenAddRequestCalled_ThenAllAreQueued)
{
    controller.addElevator(&elevator1);
    controller.addElevator(&elevator2);

    EXPECT_TRUE(controller.addRequest({0, 3, 'u', 0}));
    EXPECT_TRUE(controller.addRequest({5, 1, 'd', 0}));

    EXPECT_FALSE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenNoRequests_WhenChecked_ThenQueueIsEmpty)
{
    EXPECT_TRUE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenNoElevators_WhenAllElevatorsIdleCalled_ThenReturnsTrue)
{
    EXPECT_TRUE(controller.allElevatorsIdle());
}

TEST_F(ElevatorControllerTest, GivenAllIdleElevatorsWithNoStops_WhenAllElevatorsIdleCalled_ThenReturnsTrue)
{
    EXPECT_CALL(elevator1, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(elevator1, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));

    EXPECT_CALL(elevator2, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(elevator2, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));

    controller.addElevator(&elevator1);
    controller.addElevator(&elevator2);

    EXPECT_TRUE(controller.allElevatorsIdle());
}

TEST_F(ElevatorControllerTest, GivenMovingElevator_WhenAllElevatorsIdleCalled_ThenReturnsFalse)
{
    MockElevator elevator;

    EXPECT_CALL(elevator, getState()).WillRepeatedly(testing::Return(State::MovingUp));
    EXPECT_CALL(elevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));

    controller.addElevator(&elevator);

    EXPECT_FALSE(controller.allElevatorsIdle());
}

TEST_F(ElevatorControllerTest, GivenIdleElevatorWithPendingStops_WhenAllElevatorsIdleCalled_ThenReturnsFalse)
{
    MockElevator elevator;

    EXPECT_CALL(elevator, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(elevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{3, 5}));

    controller.addElevator(&elevator);

    EXPECT_FALSE(controller.allElevatorsIdle());
}

TEST_F(ElevatorControllerTest, GivenMixedIdleAndBusyElevators_WhenAllElevatorsIdleCalled_ThenReturnsFalse)
{
    MockElevator idleElevator;
    MockElevator busyElevator;

    EXPECT_CALL(idleElevator, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(idleElevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));

    EXPECT_CALL(busyElevator, getState()).WillRepeatedly(testing::Return(State::MovingDown));
    EXPECT_CALL(busyElevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{2}));

    controller.addElevator(&idleElevator);
    controller.addElevator(&busyElevator);

    EXPECT_FALSE(controller.allElevatorsIdle());
}

TEST_F(ElevatorControllerTest, GivenNoElevators_WhenAssignRequestsCalled_ThenNoAssignmentsAreCreated)
{
    controller.addRequest({2, 5, 'u', 0});

    auto assignments = controller.assignRequests();

    EXPECT_TRUE(assignments.empty());
    EXPECT_FALSE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenSingleIdleElevator_WhenAssignRequestsCalled_ThenRequestIsAssigned)
{
    MockElevator elevator;

    EXPECT_CALL(elevator, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(elevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));
    EXPECT_CALL(elevator, getCurrentFloor()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(elevator, getElevatorDirection()).WillRepeatedly(testing::Return(ElevatorDirection::None));
    EXPECT_CALL(elevator, addStop(testing::_, testing::_)).Times(2).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(elevator, getId()).WillRepeatedly(testing::Return(1));

    controller.addElevator(&elevator);
    controller.addRequest({1, 4, 'u', 0});

    auto assignments = controller.assignRequests();

    ASSERT_EQ(assignments.size(), 1);
    EXPECT_EQ(assignments[0].elevatorId, 1);
    EXPECT_EQ(assignments[0].request.source, 1);
    EXPECT_EQ(assignments[0].request.destination, 4);
    EXPECT_TRUE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenUpAndDownRequests_WhenAssignRequestsCalled_ThenBothRequestsAreAssigned)
{
    MockElevator elevator;

    EXPECT_CALL(elevator, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(elevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));
    EXPECT_CALL(elevator, getCurrentFloor()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(elevator, getElevatorDirection()).WillRepeatedly(testing::Return(ElevatorDirection::None));
    EXPECT_CALL(elevator, addStop(testing::_, testing::_)).Times(4).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(elevator, getId()).WillRepeatedly(testing::Return(42));

    controller.addElevator(&elevator);

    controller.addRequest({1, 5, 'u', 0});
    controller.addRequest({6, 2, 'd', 0});

    auto assignments = controller.assignRequests();

    ASSERT_EQ(assignments.size(), 2);
    EXPECT_TRUE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenElevatorCannotServeRequest_WhenAssignRequestsCalled_ThenRequestRemainsQueued)
{
    MockElevator elevator;

    EXPECT_CALL(elevator, getState()).WillRepeatedly(testing::Return(State::MovingUp));
    EXPECT_CALL(elevator, getElevatorDirection()).WillRepeatedly(testing::Return(ElevatorDirection::Up));
    EXPECT_CALL(elevator, getCurrentFloor()).WillRepeatedly(testing::Return(5));
    EXPECT_CALL(elevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));

    controller.addElevator(&elevator);
    controller.addRequest({3, 1, 'd', 0});

    auto assignments = controller.assignRequests();

    EXPECT_TRUE(assignments.empty());
    EXPECT_FALSE(controller.isRequestQueueEmpty());
}

TEST_F(ElevatorControllerTest, GivenQueuedRequestAndIdleElevator_WhenAssignRequestsCalled_ThenRequestIsAssigned)
{
    MockElevator elevator;

    EXPECT_CALL(elevator, getState()).WillRepeatedly(testing::Return(State::Idle));
    EXPECT_CALL(elevator, getStops()).WillRepeatedly(testing::Return(std::vector<int>{}));
    EXPECT_CALL(elevator, getCurrentFloor()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(elevator, getElevatorDirection()).WillRepeatedly(testing::Return(ElevatorDirection::None));
    EXPECT_CALL(elevator, addStop(testing::_, testing::_)).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(elevator, getId()).WillRepeatedly(testing::Return(7));

    controller.addElevator(&elevator);
    controller.addRequest({2, 4, 'u', 0});

    auto assignments = controller.assignRequests();

    EXPECT_EQ(assignments.size(), 1);
}
