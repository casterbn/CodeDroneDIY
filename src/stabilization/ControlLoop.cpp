#include "ControlLoop.h"

void ControlLoop::SetGains(const float _params[4]) {
    G = _params[0];
    Kp = _params[1];
    Kd = _params[2];
    Ki = _params[3];
}

void ControlLoop::Reset() {
    errorPrev = 0;
    integrator = 0;
}

int ControlLoop::ComputeCorrection(float _cmd, float _pos, float _loopTime) {
    error = _cmd - _pos;
    integrator = integrator + error;
    int correction =
            (int)(G * (Kp * error + Kd * ((error - errorPrev) / (_loopTime)) + Ki * integrator));

    errorPrev = error;

    // Correction in us
    return correction;
}

void ControlLoop::PrintGains(void) {
    Serial.print("G: ");
    Serial.print(G);
    Serial.print(" Kp: ");
    Serial.print(Kp);
    Serial.print(" Kd: ");
    Serial.print(Kd);
    Serial.print(" Ki: ");
    Serial.println(Ki);
}