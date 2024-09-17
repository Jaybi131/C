  /* Praktikum_2 - Hardwarenahe Programmierung
  Name: 
    Denis Shegay
    Burak-Ali Özcekic
    Shinda Hassan
    Karnnipith Sopistakamol
  */

  #include <avr/io.h>
  #include <util/delay.h>

  #define carRedPin 4
  #define carGreenPin 2
  #define pedestrianRedPin 6
  #define pedestrianGreenPin 7
  #define yellowPin 3
  #define buttonPin 5

  volatile uint8_t isButtonPressed = 0;  // Flag to indicate button press

  void setup() {
    // Set pin directions
    DDRD |= (1 << carRedPin) | (1 << carGreenPin) | (1 << pedestrianRedPin) | (1 << pedestrianGreenPin) | (1 << yellowPin);
    DDRD &= ~(1 << buttonPin);  // Set button pin as input

    // Configure pull-up resistor for button input
    PORTD |= (1 << buttonPin);
  }

  void loop() {
    // Check button press
    if (!(PIND & (1 << buttonPin))) {
      if (!isButtonPressed) {  // First press
        isButtonPressed = 1;   // Update button pressed flag
            
            
            
        PORTD |= (1 << pedestrianRedPin);

        // Turn on Green light
        PORTD |= (1 << carGreenPin);
        _delay_ms(1000);
        // Delay for 1 second
        PORTD &= ~(1 << carGreenPin);
        //_delay_ms(1000);
        PORTD &= ~(1 << yellowPin);
        PORTD |= (1 << yellowPin);
        _delay_ms(1000);
        // Turn off Green light
        PORTD &= ~(1 << carGreenPin);
        PORTD &= ~(1 << yellowPin);
        // Turn on pedestrian green light and car red lights
        PORTD &= ~(1 << carGreenPin);
        //_delay_ms(500);
        PORTD |= (1 << carRedPin);
        _delay_ms(1000);
        PORTD &= ~(1 << pedestrianRedPin);



        //   PORTD &=  ~(1 << carRedPin);

        PORTD |= (1 << pedestrianGreenPin);  // |

        _delay_ms(4000);

      
        
        PORTD |= (1 << pedestrianRedPin);
        PORTD &= ~(1 << pedestrianGreenPin);
        _delay_ms(1000);
        
        // Turn on yellow light
        PORTD |= (1 << yellowPin);

        // Delay for 1 second
        _delay_ms(1000);

        // Turn off yellow light
        PORTD &= ~(1 << yellowPin);
        PORTD &= ~(1 << carRedPin);
        // Turn on car green light and pedestrian red light
        PORTD &= ~(1 << pedestrianGreenPin);
        PORTD &= ~(1 << carRedPin);
        

        PORTD |= (1 << pedestrianRedPin);
        
        PORTD |= (1 << carGreenPin);
       isButtonPressed = 0;
      } 
    }
  }
