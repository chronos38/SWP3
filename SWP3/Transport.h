#pragma once

#include <cstdint>

namespace Lupus {

	extern "C" struct Packet {
		uint32_t uLength;
		uint32_t uID;
		char cType;
		uint8_t* pBuffer;
	};

}
