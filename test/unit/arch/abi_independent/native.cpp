//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "interface.hpp"

#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

namespace abi_test
{
  std::string_view native_abi_namespace() { return EVE_TEST_STRINGIFY(EVE_ABI_NAMESPACE); }

  bool native_supports_simd() { return eve::platform::supports_simd; }

  void square(eve::aligned_ptr<float, lanes> data, std::ptrdiff_t size)
  {
    eve::algo::transform_inplace(eve::algo::as_range(data, data.get() + size), eve::sqr);
  }

  int dot(eve::soa_ptr<int const*, int const*> data, std::ptrdiff_t size)
  {
    auto [a, b] = data.storage;
    return eve::algo::transform_reduce( eve::algo::views::zip(eve::algo::as_range(a, a + size), b)
                                      , [](auto x) { return get<0>(x) * get<1>(x); }
                                      , 0
                                      );
  }
}
