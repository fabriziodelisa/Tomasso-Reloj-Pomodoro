# Tomasso - Reloj Pomodoro

### TÉCNICA
La técnica pomodoro nace como una forma de mejorar la organización del tiempo de estudio, hoy difundido hacia otras áreas como la del trabajo.
La técnica consiste en bloques de media hora donde se estudia por 25 minutos y se descansa 5 minutos. Al completar cuatro ciclos se toma un descanso largo de 30 minutos y se vuelve a repetir.   

### FUNCIONALIDAD
Comienza el primer ciclo con un reloj que cuenta regresivamente desde el minuto 25. Al completar el ciclo de trabajo suena la alarma al mismo tiempo que titila el led. Al terminar la alarma inicia el periodo de descanso con un tiempo de 5 minutos. Luego vuelve a comenzar el ciclo completo, y al completar cuatro ciclos de trabajo inicia un descanso largo de 30 minutos.   
Cuenta con un pulsador para pausar/reanudar. Se puede observar en la pantalla el estado actual representado por los símbolos de play/pause. Al estar pausado titilará el led a modo de recordatorio.   
Cuenta con un pulsador para encender la luz del display. Por defecto se mantiene encendida durante 10 seg.   
Cuenta con un pulsador para reiniciar todo el reloj.   
El display muestra el reloj, el modo (trabajo/descanso), el estado (play/pause) y el número del ciclo actual.   

### MATERIALES
Se desarrollo un reloj cuenta atrás con base en arduino para suplir todas las necesidades asociadas a la implementación de esta técnica.
Se trabajó con los siguientes elementos:   
- placa arduino Uno.
- display lcd 16x2
- piezoelectrico / parlante
- resistencias fijas y variables
- led
- botoneras
- pila 9V  
