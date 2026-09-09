// revision 1
#include <eve/module/core.hpp>
#include <iostream>

struct data_block : eve::struct_support<data_block, float, std::int16_t,double>
{
  friend std::ostream& operator<<(std::ostream& os, data_block const& d)
  {
    return os << "{" << get<0>(d) << " x " << get<1>(d) << " - " << get<2>(d) << "}";
  }
};

int main()
{

  constexpr auto card = eve::cardinal_v<eve::wide<double>>;
  eve::wide<double> wd = [](auto i) { return 1.25 * (i+1); };

  eve::wide<float       , card> wf = [](auto i) { return 1.f/(1+i); };
  eve::wide<std::int16_t, card> wi = [](auto i) { return i+1; };

  std::cout << "-> zip(wf0,wi,wd)                       = " << eve::zip(wf,wi,wd)  << std::endl;
  std::cout << "-> zip(eve::as<data_block>(),wf,wi,wd)) = " << eve::zip(eve::as<data_block>(),wf,wi,wd)  << std::endl;
}
