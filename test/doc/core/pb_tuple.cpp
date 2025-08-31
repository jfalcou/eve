// revision 1
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

template < typename ... T> eve::common_value_t<T...> pipo(T ... rs)
{
  using r_t = eve::common_value_t<T...>;
   auto pipo = [] < typename P > (P pair0, auto xi){
    auto [p, eim1] = pair0;
    //  return P{p, xi};
    return eve::zip(p, xi);
  };
 kumi::tuple<r_t, r_t> p0{eve::one(eve::as<r_t>()),eve::zero(eve::as<r_t>())};
  ((p0 = pipo(p0,r_t(rs))),...);
  auto [r, e] = p0;
  return r+e;
};

int main()
{
  using r_t = eve::wide<float>;
  std::cout << "pipo(eve::one(eve::as<r_t>()),eve::one(eve::as<r_t>())) " << pipo(eve::one(eve::as<r_t>()),eve::one(eve::as<r_t>())) << std::endl;
};
