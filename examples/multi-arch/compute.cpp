//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [compute]
#include <eve/forward.hpp>
#include <eve/detection.hpp>

#include <dlfcn.h>
#include <span>
#include <sstream>
#include <unistd.h>

auto load_kernel()
{
  // Load the dynamic library
  static auto handle = []()
  {
    void* handle = nullptr;
    if(!handle && eve::is_supported(eve::avx2)  ) handle = dlopen("./libcompute_haswell.so", RTLD_NOW);
    if(!handle && eve::is_supported(eve::sse4_1)) handle = dlopen("./libcompute_sse4.so", RTLD_NOW);
    if(!handle && eve::is_supported(eve::sse2)  ) handle = dlopen("./libcompute_sse2.so", RTLD_NOW);
    return handle;
  }();

  return handle;
}

void compute(std::span<float> data)
{
  // Fetch the function pointer from its symbol
  static auto impl = [](auto h)
  {
    using func_t  = void (*)(float*, std::size_t);
    func_t f = h ? (func_t)(dlsym(h, "compute_kernel")) : nullptr;
    return f;
  }(load_kernel());

  // Call the actual implementation
  impl(data.data(), data.size());
}
//! [compute]
