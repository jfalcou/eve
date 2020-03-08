.. _function-negate:

###########
negate
###########

**Required header:** ``#include <eve/function/negate.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ negate = {};
   }

Function object the computing the product of the first parameter with the sign of the second.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U>  auto operator()( T const& x, U const& y ) noexcept;
 
*  Computes the element-wise product of the first parameter with the sign of the second.


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

*******
Notes
*******

* Using regular call produces undefined behaviour if the second parameter is a Nan
* With the :ref:`pedantic_ <feature-decorator>` decorator the result is a Nan if the second parameter is a Nan
* If the second parameter is 0 the result is 0 (except when the first parameter is a Nan) to avoid
  this problem you can use :ref:`negatenz <function-negatenz>`.
  
*******
Example
*******

.. include:: ../../../../test/doc/core/negate.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/negate.txt
  :literal:
