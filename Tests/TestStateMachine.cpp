#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "stubs.hpp"

#include "BaseState.hpp"

class TestStateWithEvents: public CBaseState
{
public:
    TestStateWithEvents(const char* name, Scrim::ICanvas* pCanvas, Scrim::IStateManager* pSM):
        CBaseState(name, pCanvas), pStateManager(pSM)
    {
        once(this, &TestStateWithEvents::TestPressCallback, pSM, Scrim::KEY_PRESS);
        once(this, &TestStateWithEvents::TestReleaseCallback, pSM, Scrim::KEY_RELEASE);
        once(this, &TestStateWithEvents::TestMouseMoveCallback, pSM, Scrim::MOUSE_MOVE);
        once(this, &TestStateWithEvents::TestMousePressCallback, pSM, Scrim::MOUSE_PRESS);
        once(this, &TestStateWithEvents::TestMouseReleaseCallback, pSM, Scrim::MOUSE_RELEASE);

        on(this, &TestStateWithEvents::TestContinuousPressCallback, pSM, Scrim::KEY_RELEASE);
    }
    virtual ~TestStateWithEvents()
    {
    }

    using EventObject = Scrim::EventObject;

    MOCK_METHOD1(TestPressCallback, void(EventObject obj));

    MOCK_METHOD1(TestReleaseCallback, void(EventObject obj));

    MOCK_METHOD1(TestMouseMoveCallback, void(EventObject obj));

    MOCK_METHOD1(TestMousePressCallback, void(EventObject obj));

    MOCK_METHOD1(TestMouseReleaseCallback, void(EventObject obj));

    MOCK_METHOD1(TestContinuousPressCallback, void(EventObject obj));

    void OnEnter(){}
    void OnLeave(){}
    void Update(){}
    void Draw(){}
    void ProcessCmd(const char* cmd, void* params){}
    void OnResize(Scrim::IRenderWindow* pWnd){}
private:
    Scrim::IStateManager* pStateManager = nullptr;
};

class CStateEventsTest: public testing::Test
{
public:
    CStateEventsTest(void) = default; 
    ~CStateEventsTest(void) = default;
    void SetUp()
    {
        input = std::make_unique<Scrim::Input>();
        sm = std::make_unique<Scrim::StateManager>();
        input->AddListener(sm.get());
        sm->AddState<TestStateWithEvents>("test", nullptr, sm.get());
        st = static_cast<TestStateWithEvents*>(sm->GetState());
        ic = std::make_unique<InputControllerStub<42, 16, 0x1, 0x89>>();
        ic->Load(input.get(), nullptr, false);
    }
    void TearDown()
    {
        input->RemoveListener(sm.get());
    }
    std::unique_ptr<Scrim::IInput> input = nullptr;
    std::unique_ptr<Scrim::StateManager> sm = nullptr;
    std::unique_ptr<Scrim::IInputController> ic = nullptr;
    TestStateWithEvents* st = nullptr;
};

TEST_F(CStateEventsTest, TestStateAsInputListenerCase)
{
    ASSERT_FALSE(input == nullptr);
    ASSERT_FALSE(sm == nullptr);
    ASSERT_FALSE(ic == nullptr);
    ASSERT_FALSE(st == nullptr);
    EXPECT_CALL(*st, TestPressCallback(testing::_)).Times(1);
    EXPECT_CALL(*st, TestReleaseCallback(testing::_)).Times(1);
    EXPECT_CALL(*st, TestMouseMoveCallback(testing::_)).Times(1);
    EXPECT_CALL(*st, TestMousePressCallback(testing::_)).Times(1);
    EXPECT_CALL(*st, TestMouseReleaseCallback(testing::_)).Times(1);
    EXPECT_CALL(*st, TestContinuousPressCallback(testing::_)).Times(testing::AnyNumber());
    ic->CaptureInput();
    ic->CaptureInput();
    ic->CaptureInput();
}
