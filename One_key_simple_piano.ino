//ASEEM THAPA
//SIMPLE ONE NOTE,ONE KEY KEYBOARD WITH MODALITY AND KEY CENTER CHANGE FUNCTIONS

//DEFINE GLOBAL VARIABLE:
int key_buttons_arr[8] = {2,4,5,6,7,8,9,10};   //DEFINE PIN NOs. for the 8 buttons used as notes
int output_pin1 = 3;                           //DEFINE PIN NO. for speaker 1
int output_pin2 = 11;                          //DEFINE PIN NO. for speaker 2
int mode_changer = 13;                         //DEFINE PIN NO. for modality change (supports minor <-> major)
int key_changer = 12;                          //DEFINE PIN NO. for key changer
//THIS ARRAY DEFINES THE FREQUENCIES FOR ALL NOTES FROM A4 to G#6 (NOTE: frequencies have to adjusted a little bit due to inconsistencies in the timer)----->
int notes_freq[24] = {460,500,530,565,600,640,670,715,760,810,870,925,980,1050,1120,1190,1260,1340,1420,1530,1630,1760,1880,2000}; //24 notes span starting from A5.
//THESE NEXT PARAMETERS ARE DEFINED TO DEFAULT VALUES----------------->
bool setup_complete = false;                   //USED FOR DEBUG
int key_sig = 0;                               //0 = default key center A, example: 1 will be A#. SUPPORTS UPTO A VALUE OF 11 (G#)
bool is_major = false;                         //for major key this value is true for minor key is false

//SETUP ALL PINS------------------------------------------------------>
void setup() {
  //SETUP SPEAKERS------------------>
  pinMode(output_pin1, OUTPUT);
  pinMode(output_pin2, OUTPUT);
  //SETUP ALL PUSHBUTTONS----------->
  pinMode(key_changer, INPUT_PULLUP);
  pinMode(mode_changer,INPUT_PULLUP);
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    pinMode(key_buttons_arr[i], INPUT_PULLUP); 
  }
  setup_complete = true;
}

//FUNCTION TO PLAY A GIVEN FREQUENCY:->
void playfreq(int freq)
{ 
   int f_time = 500000/freq;         //f = 1/T <=> T = 1/f (in seconds) <=> T = 1000000/f (in us) <=> T for on/off is half of this value (50%) duty cycle
   //USING BOTH SPEAKERS AS DEFAULT:->  
   digitalWrite(output_pin1, HIGH);
   digitalWrite(output_pin2, HIGH);
   delayMicroseconds(f_time);
   digitalWrite(output_pin1, LOW);
   digitalWrite(output_pin2, LOW);
   delayMicroseconds(f_time);
}

void loop() {
  //IF ANY BUTTON IS PRESSED PLAY CORRESPONDING NOTE:
  if (digitalRead(key_buttons_arr[0]) == LOW)
  {
    playfreq(notes_freq[key_sig]);
  }
  if (digitalRead(key_buttons_arr[1]) == LOW)
  {
    playfreq(notes_freq[key_sig+2]);
  }
  if (digitalRead(key_buttons_arr[2]) == LOW)
  {
    if(is_major) playfreq(notes_freq[key_sig+4]);
    else playfreq(notes_freq[key_sig+3]);
  }
  if (digitalRead(key_buttons_arr[3]) == LOW)
  {
     playfreq(notes_freq[key_sig+5]);
  }
  if (digitalRead(key_buttons_arr[4]) == LOW)
  {
    playfreq(notes_freq[key_sig+7]);
  }
  if (digitalRead(key_buttons_arr[5]) == LOW)
  {
    if(is_major) playfreq(notes_freq[key_sig+9]);
    else playfreq(notes_freq[key_sig+8]); 
  }
  if (digitalRead(key_buttons_arr[6]) == LOW)
  {
    if(is_major) playfreq(notes_freq[key_sig+11]);
    else playfreq(notes_freq[key_sig+10]);
  }
  if (digitalRead(key_buttons_arr[7]) == LOW)
  {
    playfreq(notes_freq[key_sig+12]);
  }

  //SPECIAL FUNCTIONS: change modality and change key center:->
  if (digitalRead(mode_changer) == LOW)
  {
    is_major = !(is_major); //change the modality
    delay(250);
  }
  if (digitalRead(key_changer) == LOW)
  {
    key_sig = (key_sig + 1) % 12; //change key signature
    delay(250);
  }

  //IDLE MODE (NO KEY PRESSED) => OUTPUT NOTHING.
  else 
  {
    digitalWrite(output_pin1, LOW); 
    digitalWrite(output_pin2, LOW); 
  }
}
