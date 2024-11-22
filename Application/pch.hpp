// pch.hpp: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_HPP
#define PCH_HPP





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "targetver.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN 
// Windows 헤더 파일
#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <olectl.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif


#ifdef _DEBUG
	#define cpp_new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define cpp_new new
#endif

#include <stdlib.h>

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#include <malloc.h>
#include <memory.h>
#include <tchar.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <cstdint>
#include <cstddef>
#include <stdexcept>

#include <iostream>

#include <string>
#include <vector>
#include <map>

#include <algorithm>

#include <functional>
#include <memory>
#include <thread>
#include <chrono>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================





#endif




