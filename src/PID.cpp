/*
Data: 06/2023
Autor: Pedro Ernesto Machado 
Classe que implementa os cálculos de um controlador
por técnica Proporcional-Integral-Derivativa.
*/
    #include "../include/PID.h"
    #include <Arduino.h>

    PID::PID(double Kp, double Ki, double Kd){
        this->Kp=Kp;
        this->Ki=Ki;
        this->Kd=Kd;
        actPrp=0;
        actInt=0;
        actDer=0;
        lastProcess = -1;
    }

    double PID::getControlSignal(){
        if (lastProcess == -1) { //Trata erro de inicialização
			amostraAnterior = amostra;
            lastErro=setpoint - amostra;
			lastProcess = millis();
		}

		double erro = setpoint - amostra;
		float deltaTime = (millis() - lastProcess) / 1000.0;
		lastProcess = millis();
		
            actPrp = erro * Kp;
            
            actInt = actInt + (lastErro * Ki) * deltaTime;
            
            actDer = (amostraAnterior - amostra) * Kd / deltaTime;
            
            amostraAnterior = amostra;
            lastErro = erro;
		
        ctrSig = actPrp + actInt + actDer;
		return signalValid(ctrSig);
    }
    
    int PID::signalValid(double ctrSig){
        
        ctrSig = (8300-ctrSig)/100;

        //limites da linearidade da relação disparo-potência
        ctrSig = ctrSig<2000 ? 2000 : ctrSig; 
        ctrSig = ctrSig>7500 ? 8000 : ctrSig;
        return ctrSig;
    }

    void PID::setPoint(double sp){
        setpoint = sp;
    }
    
    void PID::loadSample(double _amostra){
        amostra = _amostra;
    }

    void PID::setConstants(double Kp, double Ki, double Kd){
        this->Kp=Kp;
        this->Ki=Ki;
        this->Kd=Kd;
    };

