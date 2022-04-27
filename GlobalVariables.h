#pragma once
#include <mutex>

// avoid weird linker error when including this global variable in many places and using it!
__declspec(selectany) std::mutex theMutex;
