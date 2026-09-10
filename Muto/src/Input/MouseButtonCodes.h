#pragma once
/// @file MouseButtonCodes.h
/// @author Damon S. Green II
/// @brief Defines mouse button codes for input handling within the Muto engine.

namespace Muto {

	/// @brief Alias for mouse button code type.
	using MouseButtonCodes = uint8_t;

	/// @namespace Muto::Mouse
	/// @brief Namespace for mouse button codes.
	namespace Mouse {

		/// @brief Enumeration of mouse button codes.
		enum MouseButtonCodes
		{
			// From glfw3.h
			MBC_Button0 = 0,
			MBC_Button1 = 1,
			MBC_Button2 = 2,
			MBC_Button3 = 3,
			MBC_Button4 = 4,
			MBC_Button5 = 5,
			MBC_Button6 = 6,
			MBC_Button7 = 7,

			MBC_ButtonLast = MBC_Button7,
			MBC_ButtonLeft = MBC_Button0,
			MBC_ButtonRight = MBC_Button1,
			MBC_ButtonMiddle = MBC_Button2,
		};
	}
}