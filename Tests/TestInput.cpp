#include <gtest/gtest.h>

#include "stubs.h"

constexpr int input_mouse_x = 42;
constexpr int input_mouse_y = 88;
constexpr int input_pressed_key = 0x1C;
constexpr int input_released_key = 0x1;

using icstub = InputControllerStub<input_mouse_x, input_mouse_y, input_pressed_key, input_released_key>;

class CInputTest: public testing::Test
{
public:
    CInputTest(void){}
    ~CInputTest(void){}
    void SetUp()
    {
        input = std::make_unique<Scrim::Input>();
        ic = std::make_unique<icstub>();
        ic->Load(input.get(), nullptr, false); 
    }
    void TearDown()
    {
    }
    std::unique_ptr<Scrim::IInput> input = nullptr;
    std::unique_ptr<Scrim::IInputController> ic = nullptr;
};

TEST_F(CInputTest, TestInputCase)
{
    ASSERT_FALSE(input == nullptr);
    ASSERT_FALSE(ic == nullptr);
    ic->CaptureInput();

    EXPECT_EQ(input->IsKeyPressed(input_pressed_key), true);
    EXPECT_EQ(input->IsKeyReleased(input_pressed_key), false);

    EXPECT_EQ(input->IsKeyPressed(input_released_key), false);
    EXPECT_EQ(input->IsKeyReleased(input_released_key), true);

    EXPECT_EQ(input->GetMousePosition().x, input_mouse_x);
    EXPECT_EQ(input->GetMousePosition().y, input_mouse_y);

    EXPECT_EQ(input->IsMouseButtonPressed(0), true);
    EXPECT_EQ(input->IsMouseButtonReleased(0), false);
    EXPECT_EQ(input->IsMouseButtonPressed(1), false);
    EXPECT_EQ(input->IsMouseButtonReleased(1), true);
}

