#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <tuple>
#include <eve/algo/concepts/relaxed.hpp>
#include <eve/views/iota.hpp>
#include <eve/views/zip.hpp>

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

// template <typename R, eve::floating_scalar_value T> auto linspace_view(R & r, T a, T b, ptrdiff_t n)
// {
//   r.resize(n);
//   auto io = eve::views::iota(T{0}, n);
//   T nm1 = eve::rec(eve::dec(T(n)));
//   auto f = [a, b, nm1](auto i){return eve::lerp(a, b, i*nm1); };
//   eve::algo::transform_to(eve::views::zip(io, r), f); // views::transform... are missing pipe operator also missing
//  //  T nm1 = eve::rec(eve::dec(T(n)));
//  //   auto f = [a, b, nm1](auto i){return eve::lerp(a, b, i*nm1); };
//  //   return eve::views::iota(T{0}, n) | eve::algo::transform_inplace(f);
//   return r;
// }

// template < eve::algo::relaxed_range R, eve::scalar_value T,  eve::scalar_value U> R linspace(R& r, T a, U b )
//   requires( eve::floating_scalar_value<decltype(eve::read(r.begin()))>)
// {
//   using elt_t = decltype(eve::read(r.begin()));
//   std::size_t siz = r.end()-r.begin();
//   if (siz == 0u) return r;
//   if (siz == 1u) {*r.begin() = elt_t(b); return r; }
//   if (a == b)    { eve::algo::fill(r, elt_t(a)); return r; }
//   elt_t invnm1 = eve::rec((elt_t(eve::dec(siz))));
//   elt_t c = b-a;
//   eve::algo::fill(r, invnm1);
//   *r.begin() = elt_t(0);
//   eve::algo::inclusive_scan_inplace(r, std::make_pair(eve::plus, eve::zero), elt_t(0));
//   if(eve::is_eqz(a) && c == elt_t(1)) return r;
//   auto f = [a, c](auto x){return eve::fam(a, c, x); };
//   eve::algo::transform_inplace(r, f);
//   return r;
// }

int main()
{
  auto print =  [](auto v){ for(auto i = v.begin();  i !=  v.end(); ++i) {std::cout << eve::read(i) << ' ';};  std::cout << '\n';};

  std::vector<float> r1(10);
  linspace(r1, 2, 6.3);
  print(r1);
  return 0;
}
