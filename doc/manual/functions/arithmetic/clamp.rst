.. _function-clamp:

#####
clamp
#####

**Required header:** ``#include <eve/function/clamp.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ clamp = {};
   }

Function object clamping a :ref:`Values <concept-value>` btween two other


********
Synopsis
********

.. code-block:: c++

   template<typename T, typename U, typename V> constexpr T operator()( T x, U y, V z ) noexcept;

* performs element-wise clamp of the first parameter between the two other ones

.. rubric:: Parameters

* Each parameter must be an :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

.. rubric:: Return value

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

*****
Notes
*****

  - the second and third parameters (respectively x and y) must satisfy x<y or the result has undefined behaviour 

*******
Example
*******

.. include:: ../../../../test/doc/core/clamp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/clamp.txt
  :literal:
