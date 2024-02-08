#pragma once

#ifdef XVEC_MU_SUPPORT
#include "mu/mu_device_buffer.hpp"    // IWYU pragma: export
#else                                   // MU_SUPPORT
#include "cpu/cpu_device_buffer.hpp"  // IWYU pragma: export
#endif
