#include "PID.h"
#include <iostream>
#include <math.h>

using namespace std;

/*
* The complete PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  /*
  * Initialize PID coefficients (and errors, if needed)
  */
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;

  p_error = 0.0;
  d_error = 0.0;
  i_error = 0.0;

  previous_cte_= 0.0;
  tse = 0.0;
  cum_abs_error = 0.0;
}

void PID::UpdateError(double cte) {
  /**
   * Update PID errors based on cte.
   */
  p_error = cte;
  d_error = cte - previous_cte_;
  i_error += cte;

  previous_cte_ = cte;
  tse += p_error * p_error;
  cum_abs_error += fabs(cte);
}

double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
    return Kp * p_error + Kd * d_error + Ki * i_error;
}
