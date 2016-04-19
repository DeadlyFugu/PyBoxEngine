#pragma once

class Input {
public:
	Input();
	~Input();

	void PollDevice();
	bool Connected();

	float LeftAxisX();
	float LeftAxisY();
	float RightAxisX();
	float RightAxisY();
	float LeftTrigger();
	float RightTrigger();
	bool ButtonDown(int id);
};

extern Input input;
