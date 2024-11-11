/*!
   @file SEN0239.ino
   @brief Gravity Digital Adjustable Infrared Proximity Sensor for Arduino
   @n [Get the module here]()
   @n This example is a test sample.
   @n [Connection and Diagram](http://wiki.dfrobot.com.cn/index.php?title=(SKU:SEN0239)%E6%BC%AB%E5%8F%8D%E5%B0%84%E7%BA%A2%E5%A4%96%E7%BA%BF%E5%85%89%E7%94%B5%E5%BC%80%E5%85%B3#.E6.A0.B7.E4.BE.8B.E4.BB.A3.E7.A0.81)

   @copyright  [DFRobot](https://www.dfrobot.com), 2017
   @copyright GNU Lesser General Public License

   @author [lijun](ju.li@dfrobot.com)
   @version  V1.0
   @date  2017-05-15
*/
#define IR 4

void setup() 
{
  Serial.begin(9600);
  Serial.print("switch: ");
  pinMode(IR,INPUT);
}

void loop() 
{
  Serial.println("-------------------------RF-----------------------");
  if(digitalRead(IR) == 1){
    Serial.println("Switch: NO"); //NO if no obstacle within range
    delay(500);
  }
  else{
    Serial.println("Switch: YES");
    Serial.println();
    delay(500);
  }
}