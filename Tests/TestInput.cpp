#include <gtest/gtest.h>

#include "stubs.h"

constexpr int input_mouse_x = 42;
constexpr int input_mouse_y = 88;
constexpr int input_key = 0x1C;
using icstub = InputControllerStub<input_mouse_x, input_mouse_y, input_key>;

class CGameTest: public testing::Test
{
public:
    CGameTest(void){}
    ~CGameTest(void){}
    void SetUp()
    {
        input = std::unique_ptr<Scrim::Input>(new Scrim::Input);    
        ic = std::unique_ptr<icstub>(new icstub);
        ic->Load(input.get(), nullptr, false); 
    }
    void TearDown()
    {
    }
    std::unique_ptr<IInput> input = nullptr;
    std::unique_ptr<IInputController> ic = nullptr;
};

TEST_F(CGameTest, TestInputCase)
{
    ASSERT_TRUE((bool)input);
    ic->CaptureInput();
    EXPECT_EQ(input->IsKeyPressed(input_key), true);
    EXPECT_EQ(input->IsKeyReleased(input_key), false);
    EXPECT_EQ(input->GetMousePosition().x, input_mouse_x);
    EXPECT_EQ(input->GetMousePosition().y, input_mouse_y);
}

