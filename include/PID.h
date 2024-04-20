/*
Data: 06/2023
Autor: Pedro Ernesto Machado 
Classe que implementa os cálculos de um controlador
por técnica Proporcional-Integral-Derivativa.
*/
#ifndef PID_H
#define PID_H

class PID{
    public:
        double Kp, Ki, Kd;
        double actPrp, actInt, actDer, ctrSig;
        double amostra, amostraAnterior;
        double setpoint;
        double lastProcess, lastErro;

        PID(double Kp, double Ki, double Kd);
        void setPoint(double sp);
        void setConstants(double Kp, double Ki, double Kd);
        void loadSample(double amostra);
        double getControlSignal();
        int signalValid(double ctrSig);
    };

#endif