    //Arduino Security & Alarm System//
    
    #include <LiquidCrystal.h> 
    #include <Keypad.h>
    #define buzzer 8
    #define trigPin 9
    #define echoPin 10
    
    long durasi;
    int jarak, awaljarak, jaraksekarang, i;
    int pesanlayar =0;
    
    String password="1234";
    String tempPassword;
    
    boolean teraktivasi = false;  // kondisi alarm
    boolean diaktivasi;
    boolean aktivasialarm = false;
    boolean alarmteraktivasi = false;
    boolean passwordmasuk;        // kondisi input password untuk stop alarm
    boolean gantipassword = false;
    boolean passwordterganti = false;
    
    const byte ROWS = 4;         //4 baris
    const byte COLS = 4;         //4 kolom
   
    char keypressed;
                                 // mendefinisikan simbol yang ada di keypad
                                 
    char keyMap[ROWS][COLS] = 
    {
      {'1','2','3','A'},
      {'4','5','6','B'},
      {'7','8','9','C'},
      {'*','0','#','D'}
    };
    
    byte rowPins[ROWS] = {14, 15, 16, 17}; //baris pinout keypad
    byte colPins[COLS] = {18, 19, 20, 21}; //kolom pinout keypad
    
    Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS); 
    
    LiquidCrystal lcd(1, 2, 4, 5, 6, 7);    // Membuat objek untuk LC 
                                            // Parameter: (rs, enable, d4, d5, d6, d7) 
    
    void setup() 
    { 
      lcd.begin(16,2); 
      pinMode(buzzer, OUTPUT); // Set buzzer sebagai output
      pinMode(trigPin, OUTPUT); // Set the trigPin sebagai Output
      pinMode(echoPin, INPUT); // Set the echoPin sebagai Input
    }

    void loop() 
    {
       if (aktivasialarm) 
       {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Alarm akan");
          lcd.setCursor(0,1);
          lcd.print("aktif dalam");
   
          int countdown = 5;    // 5 detik countdown sebelum alarm aktif
          while (countdown != 0) 
          {
            lcd.setCursor(13,1);
            lcd.print(countdown);
            countdown--;
            tone(buzzer, 700, 100);
            delay(1000);
          }
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Alarm Aktif!");
          awaljarak = getDistance();
          aktivasialarm = false;
          alarmteraktivasi = true;
       }
       
      if (alarmteraktivasi == true)
      {
          jaraksekarang = getDistance() + 10;
          
      if ( jaraksekarang < awaljarak) 
          {
          tone(buzzer, 1000);  // Mengirim 1KHz sinyal buzzer
          lcd.clear();
          enterPassword();
          }
      }
      if (!alarmteraktivasi) 
      {
      
      if (pesanlayar == 0 )
      {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A - Aktivasi");
          lcd.setCursor(0,1);
          lcd.print("B - Ubah Pass");
          pesanlayar = 1;
      }
      
  keypressed = myKeypad.getKey();
     if (keypressed =='A')
     {                            //jika A ditekan, aktivasi alarm
        tone(buzzer, 1000, 200);
        aktivasialarm = true;            
     }

     else if (keypressed =='B') 
     {
        lcd.clear();
        int i=1;
        tone(buzzer, 2000, 100);
        tempPassword = "";
        lcd.setCursor(0,0);
        lcd.print("Pass Saat Ini");
        lcd.setCursor(0,1);
        lcd.print(">");
        gantipassword = true;
        passwordterganti = true; 
          
     while(passwordterganti) 
     {      
        keypressed = myKeypad.getKey();
        
      if (keypressed != NO_KEY)
      {
        
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
          keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
          keypressed == '8' || keypressed == '9' ) 
      {
            tempPassword += keypressed;
            lcd.setCursor(i,1);
            lcd.print("*");
            i++;
            tone(buzzer, 2000, 100);
      }
      }
      
      if (i > 5 || keypressed == '#') 
      {
        tempPassword = "";
        i=1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Pass Saat Ini");
        lcd.setCursor(0,1);
        lcd.print(">"); 
      }
      
      if ( keypressed == '*') 
      {
        i=1;
        tone(buzzer, 2000, 100);
        
        if (password == tempPassword) 
        {
          tempPassword="";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Set Pass Baru");
          lcd.setCursor(0,1);
          lcd.print(">");

          while(gantipassword) 
          {
            keypressed = myKeypad.getKey();
            
            if (keypressed != NO_KEY)
            {
              
              if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                  keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                  keypressed == '8' || keypressed == '9' ) 
              {
                tempPassword += keypressed;
                lcd.setCursor(i,1);
                lcd.print("*");
                i++;
                tone(buzzer, 2000, 100);
              }
            }
            
            if (i > 5 || keypressed == '#') 
            {
              tempPassword = "";
              i=1;
              tone(buzzer, 2000, 100);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Set Pass Baru");
              lcd.setCursor(0,1);
              lcd.print(">");
            }
            
            if ( keypressed == '*') 
            {
              i=1;
              tone(buzzer, 2000, 100);
              password = tempPassword;
              gantipassword = false;
              passwordterganti = false;
              pesanlayar = 0;
            }            
          }
        }
      }
    }
   }
 }
}

void enterPassword() 
{
  int k=5;
  tempPassword = "";
  teraktivasi = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" *** ALARM *** ");
  lcd.setCursor(0,1);
  lcd.print("Pass>");
  
      while(teraktivasi) 
      {
      keypressed = myKeypad.getKey();
      
        if (keypressed != NO_KEY)
        {
          if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
              keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
              keypressed == '8' || keypressed == '9' ) 
          {
              tempPassword += keypressed;
              lcd.setCursor(k,1);
              lcd.print("*");
              k++;
          }
        }
        
      if (k > 9 || keypressed == '#') 
      {
        tempPassword = "";
        k=5;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" *** ALARM *** ");
        lcd.setCursor(0,1);
        lcd.print("Pass>");
      }
      
      if ( keypressed == '*') 
      {
        
        if ( tempPassword == password ) 
        {
          teraktivasi = false;
          alarmteraktivasi = false;
          noTone(buzzer);
          pesanlayar = 0; 
        }
        
          else if (tempPassword != password) 
          {
            lcd.setCursor(0,1);
            lcd.print("Salah! Coba Lagi");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" *** ALARM *** ");
            lcd.setCursor(0,1);
            lcd.print("Pass>");
          }
      }    
   }
}

// fungsi tambahan ultrasonik sensor
long getDistance(){
  //int i=10;
  
  //while( i<=10 ) {
  
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set trigPin HIGH selama 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // membaca echoPin
  durasi = pulseIn(echoPin, HIGH);
  
  // menghitung jarak
  jarak = durasi*0.034/2;
  
  //jumlahjarak += jarak;
  //}
  //int rataratajarak= jumlahjarak/10;
  
  return jarak;
}
