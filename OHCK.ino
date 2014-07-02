
// Setup Pins, from ones place to sixteens place (i.e., backwards)
int pins[5] = {2, 3, 4, 5, 6};
//char buffer[2];



void setup()
{
    for(int i=0; i <= 4; i++)
    {pp
        pinMode(pins[i], INPUT_PULLUP);
    }
 
   Serial.begin(300);
  
    Keyboard.begin();

}




void loop()
{
    boolean buttonWasPressed = 0;
    int inputNum = 0; // The number that will be the letter. Within the while loop below, bits will only be set to 1 as buttons are pressed
    int currentNum = 0;
  
    // Outer loop for human timing (can't press exactly at the same time)
    // This loop checks that at least one button was pressed at one point
    // and that currently no buttons are presed (i.e., at least one button
    // was pressed and all were released)
    while(buttonWasPressed == 0 || currentNum != 0) 
    {
        for(int i=0; i <= 4; i++)
        { 
            if (digitalRead(pins[i]) == 0) 
            {
                bitWrite(inputNum,i, 1);
                bitWrite(currentNum,i, 1);
                buttonWasPressed = 1;
            }
            else
            {
                bitWrite(currentNum, i, 0);
                
            }
        }
        
        // To not overload the computer.
        delay(10);


    }

    // Tentatively set the character - we might change it later
    char character = inputNum + 96; //1 becomes a, etc 

    // Special characters, which don't follow ascii.
    if(inputNum == 27) character = 10; // New line
    if(inputNum == 28) character = 46; // Period
    if(inputNum == 29) character = 32; // Space 
    if(inputNum == 30) character = 8; // Backspace
    
    
    // Finally, print the character
    Keyboard.write(character); 

 
    // To not overload the computer. 
    delay(100);

}
