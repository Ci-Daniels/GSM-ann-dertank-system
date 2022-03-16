// ------- Tank details ------//
const int total_height = 30; // Tank height in CM
const int hold_height = 25;// Water hold height in CM

//----- Your Phone no. -------//
char cntry_code[] = "+254"; // Country code
char ph[] = "0716485040"; // owner's (receiver's) phone no.

const int trigger = 2;
const int echo = 3;
int var_1 = 0;
char input_string[15];

long Time;
int distanceCM;
int resultCM;
int tnk_lvl = 0;
int sensr_to_wtr = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  sensr_to_wtr = total_height - hold_height;

  delay(20000);
  delay(20000);
  delay(20000);
  
  Serial.println("AT+CNMI=2,2,0,0,0");//decide how newly received messages should be handled ;All the fields in the response are comma-separated with first field being phone number. The second field is the name of person sending SMS. Third field is a timestamp while forth field is the actual message.
  delay(1000);
  Serial.println("AT+CMGF=1");//configuring TEXT mode;selects sms message format as text
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("System is ready to receive SMS commands.");//text content
  delay(100);
  Serial.println((char)26);
}

void loop()
{
  
}

void serialEvent()
{
  while (Serial.available())
  {
    if (Serial.find("/"))
    {
      delay(1000);
      while (Serial.available())
      {
        char input_char = Serial.read();
        input_string[var_1++] = input_char;
        if (input_char == '/')
        {
          if (!(strncmp(input_string, "status", 6)))
          {
            measure();
            Serial.print("AT+CMGS=");
            Serial.print("\"");
            Serial.print(cntry_code);
            Serial.print(ph);
            Serial.println("\"");
            delay(1000);
            Serial.print("Tank water level is: ");
            Serial.print(tnk_lvl);
            Serial.println("%");
            delay(100);
            Serial.println((char)26);
          }
          var_1 = 0;
          return;
        }
      }
    }
  }
}

void measure()
{
  delay(100);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  Time = pulseIn(echo, HIGH);
  distanceCM = Time * 0.034;
  resultCM = distanceCM / 2;

  tnk_lvl = map(resultCM, sensr_to_wtr, total_height, 100, 0);
  if (tnk_lvl > 100) tnk_lvl = 100;
  if (tnk_lvl < 0) tnk_lvl = 0;
}
