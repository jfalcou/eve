// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
int main()
{ 
  eve::wide pf = { 0.0f, 1.0f, 4.0f, -2.0f, eve::inf(eve::as<float>()), 0.0f, eve::minf(eve::as<float>()), 1.0f};
  eve::wide qf = { 1.0f, -1.0f, 3.0f, -0.0f, 1.0f, 0.0f, 0.0f, -0.0f};

  std::cout << "<- pf                             = " << pf << "\n";
  std::cout << "<- qf                             = " << qf << "\n";

  std::cout << "-> atan2pi(pf, qf)                = " << eve::atan2pi(pf, qf) << "\n";
  std::cout << "-> atan2pi[pedantic](pf, qf)      = " << eve::atan2pi[eve::pedantic](pf, qf) << "\n";
  std::cout << "-> atan2pi[ignore_last(2)](pf, qf)= " << eve::atan2pi[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> atan2pi[pf != -2.0f](pf, qf)   = " << eve::atan2pi[pf != -2.0f](pf, qf) << "\n";
}

