//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gather.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <tts/tests/relation.hpp>

int main(int argc, char** argv)
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  using I_TYPE =  eve::detail::as_integer_t<EVE_TYPE>;
  int N = eve::cardinal_v<EVE_TYPE>;
  EVE_VALUE data[2*N];
  for(std::size_t i = 0;i<2*N;++i) data[i] = EVE_VALUE(1) + i;
  const EVE_VALUE* cdata = &data[0];
  auto g =  [&cdata](auto i){ return eve::gather(cdata, i); };
  EVE_REGISTER_BENCHMARK(g, EVE_TYPE
                        , eve::bench::random<I_TYPE>(0, 2*N-1));

  eve::bench::start_benchmarks(argc, argv);
}
