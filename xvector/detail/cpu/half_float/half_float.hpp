#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-in-bool-context"
#pragma GCC diagnostic ignored "-Wregister"
#pragma GCC diagnostic ignored "-Wsign-compare"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-in-bool-context"
#pragma clang diagnostic ignored "-Wregister"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wnested-anon-types"
#endif

#include "./umHalf.h"  // IWYU pragma: export

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
