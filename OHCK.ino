
// Setup characterPins, from ones place to sixteens place (i.e., backwards)
int characterPins[5] = {2, 3, 4, 5, 6};
int backspacePin = 7;
boolean blockTyping = 0;
//char buffer[2];



void setup()
{
    for(int i=0; i <= 4; i++)
    {
        pinMode(characterPins[i], INPUT_PULLUP);
    }
     
    pinMode(backspacePin,INPUT_PULLUP);
     
    //Serial.begin(9600);
  
    Keyboard.begin();

}




void loop()
{
    int inputNum = 0;


    // Outer loop for human timing (can't press exactly at the same time)
    for(int x=0; x < 1000; x++) 
    {
        for(int i=0; i <= 4; i++)
        {
            //Serial.print(digitalRead(characterPins[i]));
            if (digitalRead(characterPins[i]) == 0) bitWrite(inputNum,i,1);
            else bitWrite(inputNum,i,0);
        }   
    }

    
     boolean backspaceState = 0;
     if (digitalRead(backspacePin) == 0) backspaceState = 1;
 
 
    // Tentatively set the character - we might change it later
    char character = inputNum + 96; //1 becomes a, etc 
 
    Serial.println(character);
    Serial.println();

 
    if(inputNum == 0) 
    {
        Keyboard.releaseAll();
        blockTyping = 0;
    }
  
    // Check to see if any button is pressed, and that its
    // not the same as the previous one
    // if(inputNum != 0 && character != buffer[0])
    if(inputNum != 0 && blockTyping == 0 && backspaceState == 0)
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
    
        // Finally, print the character
        //Serial.println(character);
        Keyboard.press(character);
    
        // To give time to lift fingers without
        // remaining fingers typing unintentionally
        blockTyping = 1; 
    }
  
    if(backspaceState == 1)
    {
        character = 8;
        Keyboard.press(character);
        Serial.println("I got here!");
    }
    
    // Roll the buffer for the next round
    /*
    buffer[1] = buffer[0];
    buffer[0] = character; 
    */  

    // To not overload the computer. 
    delay(100);
  
 

}
