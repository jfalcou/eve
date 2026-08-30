// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <optional>

void show(char const* what, std::optional<std::ptrdiff_t> r)
{
  std::cout << what;
  if( r ) std::cout << *r << "\n"; else std::cout << "nullopt\n";
}

int main()
{
  eve::wide<std::int32_t, eve::fixed<8>> w = {1, 0, 3, 0, 5, 0, 0, 8};
  auto m = w > 0;

  std::cout << "<- w                              = " << w << "\n";
  std::cout << "<- m = (w > 0)                    = " << m << "\n";

  show("-> last_true(m)                   = ", eve::last_true(m));
  show("-> last_true[eve::ignore_last(2)](m) = ", eve::last_true[eve::ignore_last(2)](m));
  show("-> last_true(w > 100)              = ", eve::last_true(w > 100));
}
