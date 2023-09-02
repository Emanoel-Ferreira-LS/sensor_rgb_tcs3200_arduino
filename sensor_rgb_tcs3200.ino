// TCS230 sensor reading example
//
// This is just to show basic functionality without calibration.
// Utilises the non-blocking version of the reading function.
// Output uses the Serial console.
//
#include <MD_TCS230.h>
#include <FreqCount.h>

// Pin definitions
#define  S2_OUT  12
#define  S3_OUT  13
#define  OE_OUT   8    // LOW = ENABLED

int r,g,b;

MD_TCS230  CS(S2_OUT, S3_OUT, OE_OUT);

void setup()
{
  Serial.begin(57600);
  Serial.println("[Exemplo TCS230 Simples NON_BLOCKING]");
  Serial.println("\nMova o sensor para uma cor diferente para ver o valor RGB");
  Serial.println("Nota: Esses valores estão sendo lidos sem calibração do sensor");
  Serial.println("e provavelmente estarão longe da realidade");

  CS.begin();
}

void readSensorRGB()
{
  static  bool  waiting;
 
  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available())
    {
      colorData  rgb;
      
      CS.getRGB(&rgb);

      int red = rgb.value[TCS230_RGB_R];
      int green = rgb.value[TCS230_RGB_G];
      int blue = rgb.value[TCS230_RGB_B];
  
      String rgbString = "RGB [" + String(red) + "," + String(green) + "," + String(blue) + "]";
      Serial.println(rgbString);

      if(r > g && r > b){
        Serial.println("VERMELHO");
      }else if(g > b && g > r){
        Serial.println("VERDE");
      }else if(b > g && b > r){
        Serial.println("AZUL");
      }else{
        Serial.println("Sem cor");
      }

      waiting = false;
    }
  }
}

void loop()
{
  readSensorRGB();
}
