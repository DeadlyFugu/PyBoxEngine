#include "input.h"
#include <Windows.h>
#include <Xinput.h>

XINPUT_STATE controller_state;
bool controller_connected;
Input input;

Input::Input() {
}

Input::~Input() {
}

void Input::PollDevice() {
	controller_connected = XInputGetState(0, &controller_state);
}

bool Input::Connected() {
	return controller_connected;
}

float Input::LeftAxisX() {
	return (float) controller_state.Gamepad.sThumbLX / 32767;
}

float Input::LeftAxisY() {
	return (float) controller_state.Gamepad.sThumbLY / 32767;
}

float Input::RightAxisX() {
	return (float) controller_state.Gamepad.sThumbRX / 32767;
}

float Input::RightAxisY() {
	return (float) controller_state.Gamepad.sThumbRY / 32767;
}

float Input::LeftTrigger() {
	return (float) controller_state.Gamepad.bLeftTrigger / 255;
}

float Input::RightTrigger() {
	return (float) controller_state.Gamepad.bRightTrigger / 255;
}

bool Input::ButtonDown(int id) {
	return (controller_state.Gamepad.wButtons & (XINPUT_GAMEPAD_A >> id)) != 0;
}
