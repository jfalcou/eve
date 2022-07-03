//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/forward.hpp>
#include <eve/detection.hpp>

#include <dlfcn.h>
#include <span>
#include <sstream>
#include <unistd.h>

void compute(std::span<float> data)
{
  /*
    We find and keep the proper runtime variant and store it once in a static variable,
    saving the cost of detection for every other calls.
  */
  static auto handle = []()
  {
    void* handle = nullptr;
    if(!handle && eve::is_supported(eve::avx2)  ) handle = dlopen("./libcompute_haswell.so", RTLD_NOW);
    if(!handle && eve::is_supported(eve::sse4_1)) handle = dlopen("./libcompute_sse4.so", RTLD_NOW);
    if(!handle && eve::is_supported(eve::sse2)  ) handle = dlopen("./libcompute_sse2.so", RTLD_NOW);
    return handle;
  }();

  /*
    In the same way, we fetch and store the actual symbol once
  */
  static auto impl = [](auto h)
  {
    using func_t  = void (*)(float*, std::size_t);
    func_t f = handle ? (func_t)(dlsym(h, "compute_kernel")) : nullptr;
    return f;
  }(handle);

  // If we got something, we call the actual implementation
  if(impl) impl(data.data(), data.size());
}
