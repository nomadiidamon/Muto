#pragma once
#include "Enums.h"
#include <string>

namespace Muto {

	struct MutoResult
	{
		MU_RETURN Return = MU_RETURN::SUCCESS;
		std::string ResultMessage = "";

		MutoResult() = default;
		MutoResult(MU_RETURN RETURN, std::string MESSAGE)
			: Return(RETURN), ResultMessage(MESSAGE) {	}

		bool IsSuccess()
		{
			return Return == MU_RETURN::SUCCESS;
		}

		std::string ReturnError()
		{
			std::string Error = "";
			switch (Return)
			{
				case MU_RETURN::FAILURE:
					Error = "FAILURE";
					break;
				case MU_RETURN::FILE_NOT_FOUND:
					Error = "FILE_NOT_FOUND";
					break;
				case MU_RETURN::INVALID_ARGUMENT:
					Error = "INVALID_ARGUMENT";
					break;
				case MU_RETURN::OUT_OF_MEMORY:
					Error = "OUT_OF_MEMORY";
					break;
				case MU_RETURN::UNKNOWN_ERROR:
					Error = "UNKNOWN_ERROR";
					break;
				default:
					Error = "Undefined MU_RETURN";
			}
			return Error;
		}
	};
}
