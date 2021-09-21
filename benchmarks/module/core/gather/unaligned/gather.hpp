//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/gather.hpp>
#include <eve/memory/aligned_ptr.hpp>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  using I_VALUE =  eve::as_integer_t<EVE_VALUE>;
  using I_TYPE =  eve::as_integer_t<EVE_TYPE>;
  auto smin = I_VALUE(0);
  auto smax = I_VALUE(sizeof(EVE_VALUE)-1);
  int N = eve::cardinal_v<EVE_TYPE>;
  EVE_VALUE data[2*N];
  for(int i = 0;i<2*N;++i) data[i] = EVE_VALUE(1) + i;
  const EVE_VALUE* cdata = &data[0];
  auto g =  [&cdata](auto i){ return eve::gather(cdata, i); };
  auto arg0 = eve::bench::random_<I_VALUE>(smin,smax);
  eve::bench::experiment xp;

  run<I_TYPE> (EVE_NAME(gather) , xp, g, arg0);
}
