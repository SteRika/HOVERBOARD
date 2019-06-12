int motor = 9;       
int Mspeed = 0;
int Mspeedset = 0;
int Mdir = 8;
int Mdirset = 0;
int fadeAmount = 5;   
int directionLR = 0;


void setup() {
  pinMode(motor, OUTPUT);
  pinMode(Mdir, OUTPUT);
}


void loop() {
  analogWrite(motor, Mspeed);
  digitalWrite(Mdir, Mdirset);

  if(Mspeed > 240) {
     Mspeedset = 0;
    }

  if(Mspeed < 5) {
     Mspeedset = 1;
     Mdirset ++;
     if(Mdirset == 2){
        Mdirset = 0;
       }
    }

  if(Mspeedset == 1){
     Mspeed = Mspeed + 5;
    }

  if(Mspeedset == 0){
     Mspeed = Mspeed - 5;
    }
    
  delay(30);
}
