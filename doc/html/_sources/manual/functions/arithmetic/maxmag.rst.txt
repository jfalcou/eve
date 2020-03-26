.. _function-maxmag:

######
maxmag
######

**Required header:** ``#include <eve/function/maxmag.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ maxmag = {};
   }

Function object computing the value of maximal magnitude between two :ref:`Values <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise value of maximal magnitude between two :ref:`Values <concept-value>`.

Parameters
**********

* Each parameter ``x`` and ``y`` must be a :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

Note
*******

    With :ref:`concept-ieeevalue` types, there is three ways to call `maxmag`:

    * With a regular call in which case if an element of ``x`` or ``y`` is a nan, the result 
      is system dependent as on various systems the intrinsics can act in different ways;

    * With the :ref:`pedantic_ <feature-decorator>` decorator, in which case the call
      is equivalent to ``if_else(abs(x) < abs(y), x, if_else(abs(x) > abs(y), y, pedantic_(max)(x,y)))``;

    * With the :ref:`numeric_ <feature-decorator>` decorator, in which case if an element of ``x`` or ``y`` is a nan 
      the result is always the other value.

Example
*******

.. include:: ../../../../test/doc/core/maxmag.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/maxmag.txt
  :literal:
