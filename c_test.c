#include <stdio.h>
#include <math.h>

/**
 * @brief Compute the S-curve speed profile at a given pulse index.
 *
 * The formula used is: Y = Fstart + (Fend - Fstart) / (1 + exp(-flexible * (x - num) / num))
 *
 * @param pulse_index     Index of the current pulse (input value)
 * @param total_pulses    Total number of pulses in the motion profile
 * @param Fstart          Initial speed value
 * @param Fend            Final speed value
 * @param flexible        Flexibility parameter controlling the steepness of the curve
 * @param num             Total duration of the acceleration/deceleration process
 * @param step_distance   Distance (or angular displacement) represented by each pulse
 * @return double         Calculated width of the pulse at the given index
 */

double compute_S_curve_speed(double x, double Fstart, double Fend, double flexible, double num) {
    return Fstart + (Fend - Fstart) / (1.0 + exp(-flexible * (x - num) / num));}

double compute_pulse_width(int pulse_index, int total_pulses, double Fstart, double Fend, double flexible, double num, double step_distance) {
    double t = (double)pulse_index / total_pulses * num;  // Convert pulse index to time within the profile duration
    double speed_at_time = compute_S_curve_speed(t, Fstart, Fend, flexible, num);  // Calculate speed at the given time
    return step_distance / speed_at_time;  // Divide distance per pulse by speed to get pulse width
}

int main() {
    int total_pulses = 1000;  // Total number of pulses in the motion profile
    double initial_speed = 10.0;  // Starting speed (e.g., pulses per second)
    double final_speed = 1000.0; // Target speed (e.g., pulses per second)
    double flexibility = 10.0;   // Adjust this to control the curve's shape
    double duration = 10.0;      // Total duration of the speed change (acceleration and deceleration)
    double step_distance = 0.1;  // Distance (or angular displacement) represented by each pulse

    for (int i = 0; i < total_pulses; ++i) {
        double pulse_width = compute_pulse_width(i, total_pulses, initial_speed, final_speed, flexibility, duration, step_distance);
        printf("Pulse %d width: %.6f\n", i, pulse_width);
    }

    return 0;
}
