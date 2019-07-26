.. _constant-inf:

Inf
====

**Required header** ``#include <eve/constant/inf.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Inf<Value>() noexcept
   }

This 'constant' returns the infinity value for  :ref:`concept-ieeevalue` 
and the largest type value for  :ref:`concept-integralvalue`


Template parameter
------------------

 -  ``Value`` : the returned value is of type ``Value``

