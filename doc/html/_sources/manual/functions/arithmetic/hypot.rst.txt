.. _function-hypot:

#####
hypot
#####

**Required header:** ``#include <eve/function/hypot.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ hypot = {};
   }

Function object the :math:`l_2`-norm  of two or three :ref:`Ieee Values <concept-ieeevalue>` i.e. 
 :math:`\sqrt{x^2+y^2}` or :math:`\sqrt{x^2+y^2+z^2}`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T,typename U>             auto operator()( T const& x, U cons & y ) noexcept;
   template<typename T,typename U,typename V>  auto operator()( T const& x, U cons & y, V const & z ) noexcept;

* [1] Computes the element-wise hypot of the two entries.
* [2] Computes the element-wise hypot of the three entries.


Parameters
**********

* Each parameter must be an :ref:`Ieee Value <concept-ieeevalue>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Ieee Value <concept-ieeevalue>` type.

Return value
************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.


*****
Notes
*****

* With no decorator the call uses the naive formula
* With the :ref:`pedantic_ <feature-decorator>` decorator the result is more accurate and less prone to overflows.

*******
Example
*******

.. include:: ../../../../test/doc/core/hypot.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/hypot.txt
  :literal:
