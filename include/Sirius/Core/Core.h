
#pragma once

#define SRS_ASSERT(x, ...) { if(!(x)) { SRS_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#define SRS_CORE_ASSERT(x, ...) { if(!(x)) { SRS_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
