// revision 0
#include <eve/module/core.hpp>
#include <iostream>


int main()
{
  kumi::tuple t{1.0, 2.0, 3.0, 4.0, 5.0};
  std::cout << "t                                        "  << t << std::endl;
  std::cout << "eve::cumtrapz(t)                         " << eve::cumtrapz(t)                         << std::endl;
  std::cout << "eve::cumtrapz(1.0, 2.0, 3.0, 4.0, 5.0)   " << eve::cumtrapz(1.0, 2.0, 3.0, 4.0, 5.0)   << std::endl;
  std::cout << "eve::cumtrapz(t)                         " << eve::cumtrapz(t)                         << std::endl;
  std::cout << "eve::cumtrapz(0.5, t)                    " << eve::cumtrapz(0.5, t)                    << std::endl;
  std::cout << "eve::cumtrapz(t, t)                      " << eve::cumtrapz(t, t)                      << std::endl;
  std::cout << "eve::cumtrapz(t, kumi::map(eve::sqr, t)) " << eve::cumtrapz(t, kumi::map(eve::sqr, t)) << std::endl;
  std::cout << "eve::cumtrapz(eve::sqr, t)               " << eve::cumtrapz(eve::sqr, t)               << std::endl;
  using wf_t = eve::wide<double>;
  auto e = wf_t([](auto i,  auto){return eve::sqr(float(i)); });
  kumi::tuple wt{wf_t(e), 12.0f, 13.0f, 100.0f};
  std::cout << "wt                                       " << wt  << std::endl;
  std::cout << "eve::cumtrapz(wt)                        " << eve::cumtrapz(wt) << std::endl;
};
