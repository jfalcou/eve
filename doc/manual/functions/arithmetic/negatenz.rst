.. _function-negatenz:

###########
negatenz
###########

**Required header:** ``#include <eve/function/negatenz.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ negatenz = {};
   }

Function object the computing the product of the first parameter with the non zero sign of the second (-1 or 1 according the sign bit).

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U> auto operator()( T const& v, U const& w ) noexcept;
 
*  Computes the element-wise product of the first parameter with the non zero sign of the second (-1 or 1 according the sign bit).

Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

Notes
*******

* Using regular call produces undefined behaviour if the second parameter is a Nan
* With the :ref:`pedantic_ <feature-decorator>` decorator the result is a Nan if the second parameter is a Nan.
* This function can return 0 only if the first parameter is zero.
  
*******
Example
*******

.. include:: ../../../../test/doc/core/negatenz.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/negatenz.txt
  :literal:
