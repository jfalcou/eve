#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <tuple>
#include <eve/algo/concepts/relaxed.hpp>
#include "detail/print.hpp"

// an accurate linspace with transform and lerp
template < eve::algo::relaxed_range R, eve::scalar_value T,  eve::scalar_value U> R linspace(R& r, T a, U b )
  requires( eve::floating_scalar_value<decltype(eve::read(r.begin()))>)
{
  EVE_ASSERT(eve::is_finite(a), "a is not finite");
  EVE_ASSERT(eve::is_finite(b), "b is not finite");
   using elt_t = decltype(eve::read(r.begin()));
  std::size_t siz = r.end()-r.begin();
  if (siz == 0u) return r;
  if (siz == 1u) {*r.begin() = elt_t(b); return r; }
  if (a == b)    { eve::algo::fill(r, elt_t(a)); return r; }
  elt_t invnm1 = eve::rec((elt_t(eve::dec(siz))));
  auto io = eve::views::iota(elt_t{0}, siz);
  auto f = [a, b, invnm1](auto i){return eve::lerp(elt_t(a), elt_t(b), i*invnm1); };
  eve::algo::transform_to(eve::views::zip(io, r), f);
  return r;
}


int main()
{
  std::vector<float> r1(10);
  linspace(r1, 2, 6.3);
  eve::detail::print(r1);
  return 0;
}
