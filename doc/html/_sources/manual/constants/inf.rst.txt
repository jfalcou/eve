.. _constant-inf:

Inf
====

**Required header** ``#include <eve/constant/inf.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Inf<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>` infinity for  :ref:`floating point Values <concept-IEEEvalue>` 
and the largest type value for  :ref:`Integral typed Values <concept-integralvalue>`


Template parameter
------------------

 -  ``Value`` : the returned value is of type ``Value``

