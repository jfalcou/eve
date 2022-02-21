#include <eve/wide.hpp>
#include <eve/product_type.hpp>
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
  using card_t = eve::cardinal_t<eve::wide<double>>;
  eve::wide<double> wd = [](auto i, auto) { return 1.25 * (i+1); };

  eve::wide<float       , card_t> wf = [](auto i, auto) { return 1.f/(1+i); };
  eve::wide<std::int16_t, card_t> wi = [](auto i, auto) { return i+1; };

  std::cout << "---- values"  << std::endl
            << "wf  = " << wf << std::endl
            << "wi  = " << wi << std::endl
            << "wd  = " << wd << std::endl << std::endl;
  std::cout << "---- zip as tuple"  << std::endl
            << "-> zip(wf,wi,wd) = " << eve::zip(wf,wi,wd)  << std::endl << std::endl;
  std::cout << "---- zip as UDT"  << std::endl
            << "-> zip(wf,wi,wd) = " << eve::zip(eve::as<data_block>(), wf,wi,wd)  << std::endl;

  return 0;
}
