// This file contains multiplle generic numerical methods

float derivative_forward_difference_method(float *x_before, float x_after,
    float *y_before, float y_after)
{
/*
This function calculates the numerical derivative using the forward difference
numerical method.

-----------
Parameters:
float x_before
    :)
float x_after
    :)
float y_before
    :)
float y_after
    :)

--------
Returns:
float y_derivative
*/
float y_derivative;

return y_derivative;
}

float integration_trapezoidal_method(float *x_before, float x_after,
    float *y_before, float y_after)
{
/*
This function calculates the numerical integration using the trapezoidal
numerical method.

-----------
Parameters:
float x_before
    :)
float x_after
    :)
float y_before
    :)
float y_after
    :)

--------
Returns:
float y_integral
*/
float y_integral;
y_integral = ( (*y_before + y_after) / 2 ) * (x_after - *x_before);

*x_before = x_after;
*y_before = y_after;
return y_integral;
}