.. _constant-minf:

Minf
====

**Required header** ``#include <eve/constant/inf.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Minf<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>` minus infinity for  :ref:`floating point Values <concept-IEEEvalue>` 
and the least type value for  :ref:`Integral typed Values <concept-integralvalue>` (peculiarly 0 for unsigned integral types)


Template parameter
------------------

 -  ``Value`` : the returned value is of type ``Value``

