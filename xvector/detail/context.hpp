#pragma once

#ifdef XVEC_MU_SUPPORT
#include "mu/mu_context.hpp"    // IWYU pragma: export
#else                                 // MU_SUPPORT
#include "cpu/cpu_context.hpp"  // IWYU pragma: export
#endif
