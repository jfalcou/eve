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

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U> auto operator()( T const& v, U const& w ) noexcept;
 
*  Computes the element-wise product of the first parameter with the non zero sign of the second (-1 or 1 according the sign bit).


.. rubric:: Parameters

* Each parameter can be an :ref:`Ieee Value <concept-ieeevalue>` or a scalar.
* All vectorized parameters must share the same type
* If at least one parameter is vectorized, all scalar paramaters will be converted to its base type prior any other computations
* If all parameters are scalar they must share the same floating type.

.. rubric:: Return value

* If any parameter is vectorized, a value of this type else a value of  the common type of the scalar parameters.


*******
Notes
*******

* Using regular call produces undefined behaviour if the second parameter is a Nan
* With the :ref:`pedantic_ <feature-decorator>` decorator the result is a Nan if the second parameter is a Nan
  
*******
Example
*******

.. include:: ../../../../test/doc/core/negatenz.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/negatenz.txt
  :literal:
