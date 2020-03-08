.. _function-minmag:

######
minmag
######

**Required header:** ``#include <eve/function/minmag.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ minmag = {};
   }

Function object computing the value of minimal magnitude between two :ref:`Values <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise value of minimal magnitude between two :ref:`Values <concept-value>`.

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

Options
*******

    With :ref:`concept-ieeevalue` types, there is three ways to call `minmag`:

    * With a regular call in which case if an element of ``x`` or ``y`` is a nan, the result 
      is system dependent as on various systems the intrinsics can act in different ways;

    * With the :ref:`pedantic_ <feature-decorator>` decorator, in which case the call
      is equivalent to ``if_else(abs(x) < abs(y), x, if_else(abs(x) > abs(y), y, pedantic_(min)(x,y)))``;

    * With the :ref:`numeric_ <feature-decorator>` decorator, in which case if an element of ``x`` or ``y`` is a nan 
      the result is always the other value.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T> constexpr               T         operator()( T a, T b ) noexcept;

* [1] Computes the element-wise value of minimal magnitude between both :ref:`wides <type-wide>`.
* [2,3] Computes the value of minimal magnitude between the scalar and each element of the :ref:`type-wide` instance.
* [4] Computes the value of minimal magnitude between both scalars.

Parameters
**********

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.
* **a**, **b**: Scalar values of type **T**

Return value
**************

* [1-3] A value with the same type as the :ref:`type-wide` parameter.
* [4] A value of type **T**.

Notes
*****

    There is three ways to call `minmag`:

    * ``minmag(x, y)`` in which case if ``x`` or ``y`` has a nan the result is system dependent as on various systems the intrinsics act differently

    * With :ref:`pedantic_ <feature-decorator>` decorator, in which case the call is equivalent to ``if_else(abs(x) < abs(y),x,y)``

    * With :ref:`numeric__ <feature-decorator>` decorator, in which case if ``x`` or ``y`` has a nan the corresponding result is the other value


Example
*******

.. include:: ../../../../test/doc/core/minmag.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/minmag.txt
  :literal:
