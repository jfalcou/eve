.. _function-rem:

###
rem
###

**Required header:** ``#include <eve/function/rem.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rem = {};
   }

Function object computing the remaider after division  of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T,typename U>               auto operator()( T const& x, U const& y ) noexcept;
   template<typename T,typename U, typename TAG> auto operator()( T const& x, U const& y, TAG const & ) noexcept;  

[1] * Computes the element-wise remainder after division of two :ref:`Values <concept-value>`.
[2] * Computes the element-wise remainder after division of two :ref:`Values <concept-value>` with rounding.


Parameters
**********

* Each of the two first parameters ``x`` and ``y``  must be an instance of :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.
* The third parameter type (if present) can be ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``, fixing the 
  rounding mode. For :ref:`Integral Values <concept-integralvalue>` the parameter rounding default to ``toward_zero_``.

Return value
**************

* If any of the two first parameters is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.



Notes
*****

  - the  call to ``rem(x, y)`` is equivalent to the call ``rem(x, y, toward_zero_)`` (similar the standard function ``std::fmod``).
  - the  call to ``rem(x, y, tag_)`` is equivalent to the call ``a-b*div(a, b, tag_));``
  - the  call to ``rem(x, y, to_nearest_)`` is similar the standard function ``std::remainder``
 
  - unsigned :ref:`integral Values <concept-integralvalue>` type are only supported by the regular call or its tagged equivalent, because in the other
    cases the remainder sign is not always positive.

  - Limiting values for :ref:`Ieee Values <concept-ieeevalue>` with the call ``rem(x, y)`` are the following:

       - if ``x`` is :math:`\pm\infty` , a Nan is returned;
       - if ``x`` is :math:`\pm0` and ``y`` is not ``0``, ``0`` is returned (if the sign of ``x`` matters the :ref:`pedantic_ <feature-decorator>`
         decorated version returns ``x``);
       - if ``y`` is :math:`\pm0`, a  Nan is returned;
       - if either argument is NaN, Nan is returned.


  - This object function can be called with :ref:`pedantic_ <feature-decorator>` decorator in which case pedantic_(div) is
   used internally instead of div.


Example
*******

.. include:: ../../../../test/doc/core/rem.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rem.txt
  :literal:
