.. _function-dist:

####
dist
####

**Required header:** ``#include <eve/function/dist.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ dist = {};
   }

Function object the distance of  two :ref:`Values <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise distance of two :ref:`Values <concept-value>`.


Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of a :ref:`Value <concept-value>`.
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

  - if the expected result is not representable in the parameter return type the result is undefined.

  - With the :ref:`saturated_ <feature-decorator>` decorator the result is saturated (so never undefined).

*******
Example
*******

.. include:: ../../../../test/doc/core/dist.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/dist.txt
  :literal:
