#pragma once

// IWYU pragma: begin_exports
#include "host_buffer.hpp"

#ifdef XVEC_MU_SUPPORT
#include "mu/mu_device_buffer.hpp"
#else // MU_SUPPORT
#include "cpu/cpu_device_buffer.hpp"
#endif
// IWYU pragma: end_exports
