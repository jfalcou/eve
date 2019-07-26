.. _constant-nan:

Nan
====

**Required header** ``#include <eve/constant/nan.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Nan<Value>() noexcept
   }

This 'constant' returns the  :ref:`Value <concept-value>` Not a Number for  :ref:`concept-ieeevalue` entries
and zero for :ref:`concept-integralvalue` entries.


Template parameter
------------------


 -  ``Value`` : the returned value is of type ``Value``


