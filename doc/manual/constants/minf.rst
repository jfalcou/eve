.. _constant-minf:

Minf
====

**Required header** ``#include <eve/constant/inf.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Minf<Value>() noexcept
   }

This 'constant' returns the value minus infinity for  :ref:`concept-ieeevalue`
and the least type value for  :ref:`concept-integralvalue` (peculiarly `Zero` for unsigned integral types)


Template parameter
------------------

 -  ``Value`` : the returned value is of type ``Value``

