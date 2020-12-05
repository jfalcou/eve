#include <eve/eve.hpp>

#include "common.hpp"

#define DECLARE_TEST_FUNCTION(T, N) \
  auto loadu(const T* p, N) { \
    return eve::wide<T, N>{p}; \
  }

DELARE_ALL_FUNCTIONS

#undef DECLARE_TEST_FUNCTION

#define DECLARE_TEST_FUNCTION(T, N) \
  auto load(eve::aligned_ptr<const T, N() * sizeof(T)> p, N) { \
    return eve::wide<T, N>{p}; \
  }

DELARE_ALL_FUNCTIONS

#undef DECLARE_TEST_FUNCTION
