#ifndef displacement_sensors_h
#define displacement_sensors_h

float interruptions_to_displacement(int interruptions, int interruptions_per_cycle, float wheel_radius);
/*
This function converts the number of interruptions into its respective angular
and linear displacement.
*/
float voltage_to_angular_displacemment(int pot_value, int min_pot_value,
    int max_pot_value, float min_angle_value, float max_angle_value);
/*
This function calculates the angular displacement based on the change of the
resistance value of the potentiometer when its shaft is moved.

This functions assumes that the potentiometer used for measuring the angular
displacement is linear. Otherwise this function won't work.
*/
#endif