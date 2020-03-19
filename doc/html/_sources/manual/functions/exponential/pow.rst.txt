.. _function-pow:

###########
pow
###########

**Required header:** ``#include <eve/function/pow.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ pow = {};
   }

Function object computing :math:`x^y`.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> auto operator()( T const& x, U const & y>

*  Computes  element-wise the first parameter raised to the power  of the second.


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

* Using ``pow(x, y)`` for :ref:`concept-ieeevalue` entries is similar to :math:`x^y`.

* The implementation is conform to the IEEE requirements, but no exeception is ever raised.

    - pow(:math:`+0`, exp), where exp is a negative odd integer, returns :math:`+\infty` 
    - pow(:math:`-0`, exp), where exp is a negative odd integer, returns :math:`-\infty`
    - pow(:math:`\pm0`, exp), where exp is negative, finite, and is an even integer or a non-integer, returns :math:`+\infty`
    - pow(:math:`\pm0`, :math:`-\infty`) returns :math:`+\infty`
    - pow(:math:`+0`, exp), where exp is a positive odd integer, returns :math:`+0`
    - pow(:math:`-0`, exp), where exp is a positive odd integer, returns :math:`-0`
    - pow(:math:`\pm0`, exp), where exp is positive non-integer or a positive even integer, returns :math:`+0`
    - pow(-1, :math:`\pm\infty`) returns 1
    - pow(+1, exp) returns 1 for any exp, even when exp is NaN
    - pow(base, :math:`\pm0`) returns 1 for any base, even when base is NaN
    - pow(base, exp) returns NaN if base is finite and negative and exp is finite and non-integer.
    - pow(base, :math:`-\infty`) returns :math:`+\infty` for any  :math:`|` base :math:`|<1`
    - pow(base, :math:`-\infty`) returns :math:`+0` for any :math:`|` base :math:`|>1`
    - pow(base, :math:`+\infty`) returns :math:`+0` for any :math:`|` base :math:`|<1`
    - pow(base, :math:`+\infty`) returns :math:`+\infty` for any :math:`|` base :math:`|>1`
    - pow(:math:`-\infty`, exp) returns :math:`-0` if exp is a negative odd integer
    - pow(:math:`-\infty`, exp) returns :math:`+0` if exp is a negative non-integer or even integer
    - pow(:math:`-\infty`, exp) returns :math:`-\infty` if exp is a positive odd integer
    - pow(:math:`-\infty`, exp) returns :math:`+\infty` if exp is a positive non-integer or even integer
    - pow(:math:`+\infty`, exp) returns :math:`+0` for any negative exp
    - pow(:math:`+\infty`, exp) returns :math:`+\infty` for any positive exp
    - except where specified above, if any argument is NaN, NaN is returned 

*  With :ref:`raw_ <feature-decorator>` decorator the computation uses the naive formula: :math:`e^{y \log x}` and so does 
   not care for limits and leads to lower accuracy. In particular it returns NaN for negative base


 
*******
Example
*******

.. include:: ../../../../test/doc/core/pow.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/pow.txt
  :literal:
