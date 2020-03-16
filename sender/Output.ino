
int control=0;
void printdata(void)
{   


      if(control==15){
      Serial.println((int)ToDeg(pitch));
      Serial.println((int)ToDeg(roll));
      control=0;
      }
      else{
        control++;
        }
      
      

      
}
