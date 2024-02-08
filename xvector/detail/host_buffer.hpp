#pragma once

#ifdef XVEC_MU_SUPPORT
#include "mu/mu_host_buffer.hpp"    // IWYU pragma: export
#else                                   // MU_SUPPORT
#include "cpu/cpu_host_buffer.hpp"  // IWYU pragma: export
#endif
