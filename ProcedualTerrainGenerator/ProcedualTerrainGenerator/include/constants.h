#pragma once

namespace constants {
	static const char* VERT_SHADER_PATH = "shaders/simple.vert";
	static const char* FRAG_SHADER_PATH = "shaders/simple.frag";

	static constexpr float SECOND_DURATION = 1.0;

	namespace camera {
		// Default camera values
		namespace defaultValues {
			static constexpr float YAW = 45;
			static constexpr float PITCH = 0;
			static constexpr float SPEED = 70.0f;
			static constexpr double SENSITIVITY = 0.05;
			static constexpr float FOV = 60;

		}
		static constexpr float MAX_FOV = 90;
		static constexpr float MIN_FOV = 1;
		static constexpr float ROTATION_INCREMENT = .5;
		static constexpr float MAX_PITCH= 89;
		static constexpr float MIN_PITCH= -89;
	}
	namespace inputTypes {
		enum class InputType { KEYBOARD, MOUSE_BUTTONS, MOUSE_SCROLL, MOUSE_DRAG };
	}
	static int SCROLL = -2;
	static int DRAG = -3;
}