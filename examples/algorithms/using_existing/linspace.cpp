#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <tuple>
#include <eve/algo/concepts/relaxed.hpp>

  template < eve::algo::relaxed_range R>
  void print(R const & v)
  {
    std::cout << '{';
    auto n = v.end() - v.begin();
    auto cur = v.begin();
    if(n)
    {
      for(auto i = 1;  i !=  n; ++i, ++cur) {std::cout << +eve::read(cur) << ", ";};
      if (n) std::cout << +eve::read(cur) << "}\n";
    }
    else std::cout <<"}\n";
  }

// an accurate linspace with transform and lerp
template < eve::algo::relaxed_range R, eve::scalar_value T,  eve::scalar_value U> R linspace(R& r, T a, U b )
  requires( eve::floating_scalar_value<decltype(eve::read(r.begin()))>)
{
  EVE_ASSERT(eve::is_finite(a), "a is not finite");
  EVE_ASSERT(eve::is_finite(b), "b is not finite");
   using elt_t = decltype(eve::read(r.begin()));
  std::size_t siz = r.end()-r.begin();
  if (siz == 0u) return r;
  else if (siz == 1u) {*r.begin() = elt_t(b); return r; }
  else if (a == b)    { eve::algo::fill(r, elt_t(a)); return r; }
  else
  {
    elt_t invnm1 = eve::rec((elt_t(eve::dec(siz))));
    auto io = eve::views::iota(elt_t{0}, siz);
    auto op = [a, b, invnm1](auto i){return eve::lerp(elt_t(a), elt_t(b), i*invnm1); };
    eve::algo::transform_to(eve::views::zip(io, r), op);
    return r;
  }
}

// -----------------------

#include "test.hpp"

TTS_CASE("example for vector of floats")

{
  std::vector<float> r1(5);
  std::vector<float> r2{1.0f, 1.5f, 2.0f, 2.5f, 3.0f};
  linspace(r1, 1.0f, 3.0f);

  for(size_t i=0; i < r1.size() ; ++i)
  {
    TTS_ULP_EQUAL(r1[i], r2[i], 0.5);
  }
};
