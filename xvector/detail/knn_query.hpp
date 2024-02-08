#pragma once

#ifdef XVEC_MU_SUPPORT
#include "mu/mu_knn_query.hpp"    // IWYU pragma: export
#else                                 // MU_SUPPORT
#include "cpu/cpu_knn_query.hpp"  // IWYU pragma: export
#endif
