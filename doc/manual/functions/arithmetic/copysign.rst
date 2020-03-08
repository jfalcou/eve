.. _function-copysign:

########
copysign
########

**Required header:** ``#include <eve/function/copysign.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ copysign = {};
   }

Function object computing the first  :ref:`Values <concept-value>` with the sign of the second.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise value the first parameter with the sign of the second.


Parameters
**********

* Each parameter must be an instance of :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

Example
*******

.. include:: ../../../../test/doc/core/copysign.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/copysign.txt
  :literal:
