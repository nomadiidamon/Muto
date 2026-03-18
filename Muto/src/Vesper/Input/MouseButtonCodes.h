#pragma once
/// @file MouseButtonCodes.h
/// @author Damon S. Green II
/// @brief Defines mouse button codes for input handling within the Vesper engine.

namespace Vesper {

	/// @brief Alias for mouse button code type.
	using MouseCode = uint8_t;

	/// @namespace Vesper::Mouse
	/// @brief Namespace for mouse button codes.
	namespace Mouse {

		/// @brief Enumeration of mouse button codes.
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2,
		};
	}
}