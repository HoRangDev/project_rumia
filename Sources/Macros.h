#pragma once

#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(target) if(target != nullptr) { delete target; target = nullptr; }
#endif