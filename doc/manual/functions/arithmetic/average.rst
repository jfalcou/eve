.. _function-average:

###########
average
###########

**Required header:** ``#include <eve/function/average.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ average = {};
   }

Function object the average of  two :ref:`Values <concept-value>`.

********
Synopsis
********

.. code-block:: c++

   template<typename T> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise average of two :ref:`Values <concept-value>`.


Parameters
**********

* Each parameter must be a :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

*******
Notes
*******

* This function does not overflow.

* Using `average(x, y)` for :ref:`concept-ieeevalue` entries is similar to  `(x+y)/2`

* For :ref:`concept-integralvalue` types, it returns a rounded value at a distance guaranteed
  to be less than or equal to 0.5 of the average floating value, but may differ
  by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
  simd intrinsics, it is possible that the scalar results may differ by one unit from
  simd ones.

*******
Example
*******

.. include:: ../../../../test/doc/core/average.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/average.txt
  :literal:
