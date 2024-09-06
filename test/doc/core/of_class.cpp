// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  auto inf  = eve::inf(eve::as<double>());
  auto mind = eve::mindenormal(eve::as<double>());
  auto nan  = eve::nan(eve::as<double>());

  eve::wide wf0{0.0, 1.0, -2.0, nan, inf, mind, inf, -0.0};

  std::cout << "<- wf0                         = " << wf0 << "\n";

  std::cout << "-> of_class(wf0, eve::qnan   )                = " << eve::of_class(wf0, eve::qnan   ) << "\n";
  std::cout << "-> of_class(wf0, eve::poszero)                = " << eve::of_class(wf0, eve::poszero) << "\n";
  std::cout << "-> of_class(wf0, eve::negzero)                = " << eve::of_class(wf0, eve::negzero) << "\n";
  std::cout << "-> of_class(wf0, eve::posinf )                = " << eve::of_class(wf0, eve::posinf ) << "\n";
  std::cout << "-> of_class(wf0, eve::neginf )                = " << eve::of_class(wf0, eve::neginf ) << "\n";
  std::cout << "-> of_class(wf0, eve::denorm )                = " << eve::of_class(wf0, eve::denorm ) << "\n";
  std::cout << "-> of_class(wf0, eve::neg    )                = " << eve::of_class(wf0, eve::neg    ) << "\n";
  std::cout << "-> of_class(wf0, eve::snan   )                = " << eve::of_class(wf0, eve::snan   ) << "\n";
  std::cout << "-> of_class(wf0, eve::poszero|eve::negzero|eve::posinf) = " << eve::of_class(wf0, eve::poszero|eve::negzero|eve::posinf) << "\n";

}
