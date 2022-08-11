#include <eve/wide.hpp>
#include <eve/conditional.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_ft others = { 13.37f, 4.2f, 6.9f, 75.54f };

  auto mask = eve::ignore_last(2);

  std::cout << "---- simd" << '\n'
            << "<- pf                              = " << pf      << '\n'
            << "<- mask                            = " << mask
            << " / "                                   << mask.mask( eve::as<eve::logical<wide_ft>>()) << '\n'
            << "<- others                          = " << others  << '\n'
            << "-> replace_ignored(pf,mask,others) = " << eve::replace_ignored(pf,mask,others) << '\n';

  return 0;
}
