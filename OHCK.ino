
// Setup Pins, from ones place to sixteens place (i.e., backwards)
int pins[5] = {2, 3, 4, 5, 9};
//char buffer[2];



void setup()
{
  for(int i=0; i <= 4; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }
 
  //Serial.begin(9600);
  
  Keyboard.begin();

}




void loop()
{
 int inputNum = 0;

 for(int x=0; x < 15; x++)// Outer loop for human timing
 {
  for(int i=0; i <= 4; i++)
  {
    //Serial.print(digitalRead(pins[i]));
    if (digitalRead(pins[i]) == 0) bitWrite(inputNum,i,1);  
  }   
  }
  Serial.println();
  Serial.println(inputNum);
 
  // Tentatively set the character - we might change it later
  char character = inputNum + 96; //1 becomes a, etc 
 
 //Serial.println(character);
 //Serial.println();

  // Check to see if the key is the same as last time.
  // If its the same, assume its being held, so don't release
  // If there the character is 0, no button is being held; release. 
  if(inputNum == 0) Keyboard.releaseAll();

  
  // Check to see if any button is pressed, and that its
  // not the same as the previous one
  //pif(inputNum != 0 && character != buffer[0])
  if(inputNum != 0)
  {

    
    /*
    // If this is a new sentence, capitalize
    if(buffer[1] == 46 && buffer[0] == 32)
    {
      character = inputNum - 64;
    }
    */
    
    // Special characters, which don't follow ascii.
    if(inputNum == 29) character = 46; // Period
    if(inputNum == 30) character = 32; // Space 
    if(inputNum == 31) character = 8; // Backspace
    
    
    // Finally, print the character
    //Serial.println(character);
    Keyboard.press(character);
    
    
    
  }
  
  
  // Roll the buffer for the next round
  /*
  buffer[1] = buffer[0];
  buffer[0] = character; 
 */  


  delay(200);
  
 

}
