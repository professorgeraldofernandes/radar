//////////////////////////////////////////////////////////////////////////
//                 ------ Ph�sis -------         
//               Projeto: Radar com HC-SR04            
//               Autor: Prof. Geraldo Fernandes                
//               Data: 02/02/2020 
//               C�digo no Arduino
//               Linguagem C++                     
/////////////////////////////////////////////////////////////////////////

#include <Servo.h>.

  // Aqui vamos definir o pino de Echo e Trigger do HC-SR04
  const int trig_Pino = 10;
  const int echo_Pino = 11;

  // Vamos criar duas vari�veis para calcular a distancia do objeto
  long tempo;
  int distancia;

  // Aqui criamos um objeto chamado 'Radar_Servo' o qual vamos controlar
  Servo Radar_Servo;

void setup() {
  
  // Vamos come�ar definindo o trigger como sa�da
  // e o Echo como entrada, al�m de iniciar a serial e o servo
  pinMode(trig_Pino, OUTPUT);
  pinMode(echo_Pino, INPUT);

  Serial.begin(9600);
  Radar_Servo.attach(12); // Aqui eu defino em qual pino o servo est� conectado
}

void loop() {
  
  // Aqui estamos fazendo um for para o servo girar de 15� at� 165�
    for(int i = 0; i <= 180; i++){
    Radar_Servo.write(i);
    delay(30);
    
    // Nessa parte, enquanto o servo gira, o sensor verifica
    // Se tem algum objeto e qual a distancia
    // Chamando a fun��o 'CalculandoDistancia()'
    distancia = calculandoDistancia();
   
    Serial.print(i);        // Mostra na serial qual o angulo de giro o servo est� naquele momento
    Serial.print(",");      // Aqui vamos separar o angulo da distancia calculada com uma v�rgula
    Serial.print(distancia); // Mostra a distancia que o sensor est� calculando
    Serial.print(".");      // Coloca um '.' depois da distancia para indexar no processing a distancia
    }

    // Os mesmos passos que fizemos para ele ir de 15� --> 165�
    // Vamos utilizar para ele voltar de 165� --> 15�
    for(int i = 180; i > 0 ; i--){
    Radar_Servo.write(i);
    delay(30);
    
    // Nessa parte, enquanto o servo gira, o sensor verifica
    // Se tem algum objeto e qual a distancia
    // Chamando a fun��o 'CalculandoDistancia()'
    distancia = calculandoDistancia();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distancia);
    Serial.print(".");
  }
}

    // Aqui vamos criar a fun��o que utilizamos ali em cima
    // Para poder calcular a distancia sabe?
    int calculandoDistancia(){
 
    digitalWrite(trig_Pino, LOW);  // Aqui vou desligar o trigger para poder realizar os pulsos
    delayMicroseconds(2);

    // Aqui � onde um ligo o trigger por 10 ms
    // Que � o tempo para calcular a distancia
    digitalWrite(trig_Pino, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_Pino, LOW);
    
    tempo = pulseIn(echo_Pino, HIGH);  // Aqui setamos o Echo para capitar o pulso ultrassonico e voltar o tempo que ele demorou
    
    distancia = tempo*0.034/2;  // Por fim, esta � a f�rmula que utilizamos para converter o tempo na distancia do objeto at� o sensor
    return distancia;
}