#include <gtest/gtest.h>

#include "stubs.h"

#include "BaseState.hpp"
//TODO: mock
class TestStateWithEvents: public CBaseState
{
public:
    TestStateWithEvents(const char* name, ICanvas* pCanvas, IStateManager* pSM):
        CBaseState(name, pCanvas), pStateManager(pSM)
    {
        once(this, &TestStateWithEvents::TestPressCallback, pSM, KEY_PRESS);
        once(this, &TestStateWithEvents::TestReleaseCallback, pSM, KEY_RELEASE);
        once(this, &TestStateWithEvents::TestMouseMoveCallback, pSM, MOUSE_MOVE);
        once(this, &TestStateWithEvents::TestMousePressCallback, pSM, MOUSE_PRESS);
        once(this, &TestStateWithEvents::TestMouseReleaseCallback, pSM, MOUSE_RELEASE);
    }
    virtual ~TestStateWithEvents()
    {
    }

    void TestPressCallback(EventObject obj)
    {
        onPressFlag = !onPressFlag;
    }
    void TestReleaseCallback(EventObject obj)
    {
        onReleaseFlag = !onReleaseFlag;
    }
    void TestMouseMoveCallback(EventObject obj)
    {
        onMouseMoveFlag = !onMouseMoveFlag;
    }
    void TestMousePressCallback(EventObject obj)
    {
        onMousePressFlag = !onMousePressFlag;
    }
    void TestMouseReleaseCallback(EventObject obj)
    {
        onMouseReleaseFlag = !onMouseReleaseFlag;
    }

    bool GetPressSideEffect() { return onPressFlag; }
    bool GetReleaseSideEffect() { return onReleaseFlag; }
    bool GetMouseMoveSideEffect() { return onMouseMoveFlag; }
    bool GetMousePressSideEffect() { return onMousePressFlag; }
    bool GetMouseReleaseSideEffect() { return onMouseReleaseFlag; }

    void OnEnter(){}
    void OnLeave(){}
    void Update(){}
    void Draw(){}
    void ProcessCmd(const char* cmd, void* params){}
    void OnResize(IRenderWindow* pWnd){}
private:
    IStateManager* pStateManager = nullptr;
    bool onPressFlag = false;
    bool onReleaseFlag = false;
    bool onMouseMoveFlag = false;
    bool onMousePressFlag = false;
    bool onMouseReleaseFlag = false;
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
        ic = std::make_unique<InputControllerStub<42, 16, 0x1, 0x89>>();
        ic->Load(input.get(), nullptr, false);
    }
    void TearDown()
    {
        input->RemoveListener(sm.get());
    }
    std::unique_ptr<IInput> input = nullptr;
    std::unique_ptr<Scrim::StateManager> sm = nullptr;
    std::unique_ptr<IInputController> ic = nullptr;
};

#define GET_SE(EvtName) static_cast<TestStateWithEvents*>(sm->GetState())->Get##EvtName##SideEffect()

TEST_F(CStateEventsTest, TestStateAsInputListenerCase)
{
    ASSERT_FALSE(input == nullptr);
    ASSERT_FALSE(sm == nullptr);
    ASSERT_FALSE(ic == nullptr);
    EXPECT_FALSE(GET_SE(Press));
    EXPECT_FALSE(GET_SE(Release));
    EXPECT_FALSE(GET_SE(MouseMove));
    EXPECT_FALSE(GET_SE(MousePress));
    EXPECT_FALSE(GET_SE(MouseRelease));
    ic->CaptureInput();
    EXPECT_TRUE(GET_SE(Press));
    EXPECT_TRUE(GET_SE(Release));
    EXPECT_TRUE(GET_SE(MouseMove));
    EXPECT_TRUE(GET_SE(MousePress));
    EXPECT_TRUE(GET_SE(MouseRelease));
    ic->CaptureInput();
    EXPECT_TRUE(GET_SE(Press));
    EXPECT_TRUE(GET_SE(Release));
    EXPECT_TRUE(GET_SE(MouseMove));
    EXPECT_TRUE(GET_SE(MousePress));
    EXPECT_TRUE(GET_SE(MouseRelease));

}
