// This file contains all the functions related to the displacement sensors data
// acquisition

float interruptions_to_displacement(int interruptions, int interruptions_per_cycle, float wheel_radius)
{
/*
This function converts the number of interruptions into its respective angular
and linear displacement.

-----------
Parameters:
int interruptions_per_cycle
    :)
float wheel_radius
    :)
*/
float angular_displacement, linear_displacement;
double PI = 3.14159265358979323846;
angular_displacement = (interruptions/interruptions_per_cycle) * 2*PI;
linear_displacement = angular_displacement * wheel_radius;

return angular_displacement;
}

float voltage_to_angular_displacemment(int pot_value, int min_pot_value,
    int max_pot_value, float min_angle_value, float max_angle_value)
{
/*
This function calculates the angular displacement based on the change of the
resistance value of the potentiometer when its shaft is moved.

This functions assumes that the potentiometer used for measuring the angular
displacement is linear. Otherwise this function won't work.


-----------
Parameters:
int pot_value
    ;)
int ref_value,
    :)
float ref_angle
    :)
*/
float angle_value;
float eq_slope = (max_angle_value - min_angle_value)/((float) max_pot_value -
    (float) min_pot_value);
float eq_intersection_x = min_angle_value - eq_slope * (float) min_pot_value;
angle_value = eq_slope * pot_value + eq_intersection_x;

return angle_value;
}
