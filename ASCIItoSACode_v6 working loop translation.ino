//Preprocessor debugging tags

//#define CURRENT 
//#define DEBUG
//#define SUCCESSTEST
//#define ERRRORMES

//------------------------------------------------------------------------------------------

//For part 1 of the assignment I chose to create 2 arrays, one for SA-Code and one for ASCII
//The index num of each array points to the corresponding pairs, i.E. ASCII letter "A" is at index [0] and the corresponding SA-Code is as well

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
// ARRAYS for the translation of SA and ASCII code
const int arraySize = 48; //storing ASCII A-Z (+26) and special symboles (+10) numeric 0-9 (+10) and an error character (+1), and a space " " (+1)
String seriaLoutput = "";
String userInput ="";

const char ASCIIvalues [arraySize] ={
  'A', //index 0
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z', //index 25
  '.', //index 26
  ',', 
  '\'', //this is an apostrophe with escape character
  '?',
  '!',
  '+',
  '-',
  '*',
  '/',
  '=', //index 35
  '1', //index 36
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  '0', //index 45
  ' ', //space
  '#' //error
  };


char * saCodeValues [arraySize] ={
  "+", //index 0 -> A
  "@@+", //B
  "@+>",//C
  "+@", //D
  "@", //E
  "@+@", //F
  "@++", //G
  "++", //H
  "@@", //I
  "+@@", //J
  "+>", //K
  "@@>", //L
  "@+", //M
  ">+", //N
  "@>", //O
  ">@", //P
  "+@>", //Q
  "@>+", //R
  "@>@", //S
  ">", //T
  ">>", //U
  "+++", //V
  "++@", //W
  "+>@", //X
  "@>>", //Y
  "++>", //index 25 -> Z
  ">@@", //index 26 -> .
  ">@+", //index 27 -> ,
  ">+@", //index 28 -> '
  ">++", //index 29 -> ?
  ">+>", //index 30 -> !
  ">>@", //index 31 -> +
  ">>+", //index 32 -> -
  ">>>", //index 33 -> *
  ">@>", //index 34 -> /
  ">+++>", //index 35 -> =
  ">@@+", //index 36 -> 1
  ">@@>", // 2
  ">@+@", //3
  ">@++", //4
  ">@+>", //5
  ">@>@", //6
  ">@>+", //7
  ">@>>", //8
  ">+@@", // index 44 -> 9
  ">@@@", //index 45 -> 0
  " ", //space between words
  "@@@@@@" //error
  };

//---------------------------------------------------------------------------------------------------------------
//The folowing function is istening for user input and casting it into a corresponding variable 

// String getUserInput() {
//   while (userInput == "") {
//     Serial.println("What would you like to translate?");
//     while (!Serial.available()) {
//       ;
//     }
//     userInput = Serial.readString();
//   }
//   #ifdef DEBUG
//   Serial.println(userInput);
//   #endif
// }

//---------------------------------------------------------------------------------------------------------------
// Single value translation functions

//ASCII to SA Code
//Function takes character c and capitalises it if needed, then looks for equivalent in array and returns the SA-string at the corresponding position 
//in the other array, where it has found the match

char * asciiChar2SAstring (char c) {
  char t = toupper(c); //Translates all alphabetic chars to upper case
  for (int i = 0; i < (arraySize -1); i++) {
    if (t == ASCIIvalues[i]) {
      return saCodeValues[i];
    }
  }
  return saCodeValues[(arraySize - 1)]; //position of the error character
}


//SA Code to ASCII
//This function loops through saCodeValues to find a matching string and then retuns the corresponding char in the ASCIIvalues array at the same position
char saCodeString2ASCIIchar (String s) {
  int l = s.length();
  if(l < 6) { //SA Code only represents characters up to 5 different symboles. Therefor we can say that any longer String will result in the error character
    for (int i = 0; i < (arraySize - 1); i++) { 
      if (s.equals(saCodeValues[i])) {
        return ASCIIvalues[i];
      }
    }  
  } else {
    return (ASCIIvalues[arraySize - 1]); //error character is stored at last position in array
  }
}

//------------------------------------------------------------------------------------------------------
//Translation of ASCII string to SA-Code

String translateAsciiString2saCodeString (String input) {
  String output = "";
   
  input = userInput;
  char * passASCIIchar;
  for (int i = 0; i < input.length(); i++) {
    if((input[i] == ASCIIvalues[46])||(input[i+1] == ASCIIvalues[46])) { //if the current or following chracter are equal to ' '
      passASCIIchar = asciiChar2SAstring(input[i]);
      output += passASCIIchar; //just add the current character at [i]
    } else {
        if(i < ((input.length())-1)){ //unless the loop is on the last position in the array:
        passASCIIchar = asciiChar2SAstring(input[i]);
        output += passASCIIchar;  //asciiChar2SAstring iterates through the input String and stores it's results in the output variable
        output += "/"; //and adds this symbole between 2 characters in a word
        } else { //on the last position just add the character
        passASCIIchar = asciiChar2SAstring(input[i]);
        output += passASCIIchar; 
        }
    }
    #ifdef DEBUG
    Serial.println(output);
    #endif
  }
  return output;
}

//------------------------------------------------------------------------------------------------------
//The following function will aid in the translation of SA Code as well as the flashing of the lights
//The function distinguishes all 5 possible characters in SA Code and assigns them cases
//Later these 'cases' will be used to determine the behaviour of the program i.E how long it flashes, or 
//how it will treat individual chars in the String to be translated

int testSAcodeChar (char c) { //c refers to a single component within a string consisting of SA code letters
  int testCaseValue;
  if (c == '@') {
    testCaseValue = 1;
  } else if ( c == '+') {
    testCaseValue = 2;
  } else if ( c == '>') {
    testCaseValue = 3;
  } else if ( c == ' ') {
    testCaseValue = 4;
  } else if (c == '/') {
    testCaseValue = 5;
  } else {
    testCaseValue = 0;
  }
  return testCaseValue;
}


//------------------------------------------------------------------------------------------------------
//Translation of SA-Code String to ASCII

String translateSAcode2asciiString (String tinput) {
  String output = "";
  tinput = userInput;

  String translatedASCIIString = ""; //Final ASCII String 
  String futureASCIIcharacter = ""; //string to be populated by by SA Code values until it gets translated to an ASCII character
  char asciiChar;

  int inputLength = tinput.length();
 
  //the following for-loop tests the char at the position i of the String and then either adds the symbole to futureASCIIcharacter or translates
  // all characters in futureASCIIcharacter and moves it into translatedASCIIString
  for (int i = 0; i < inputLength; i++) {
    char testChar = tinput[i];
    char charCaseTest;
    charCaseTest = testSAcodeChar(testChar); 

    switch (charCaseTest) {
      case 1: //@
      futureASCIIcharacter += tinput[i];
      break;
      case 2: //+
      futureASCIIcharacter += tinput[i];
      break;
      case 3: //>
      futureASCIIcharacter += tinput[i];
      break;
      case 4: // ' ' 
      asciiChar = saCodeString2ASCIIchar(futureASCIIcharacter);
      translatedASCIIString += asciiChar;
      futureASCIIcharacter = "";
      translatedASCIIString += ' ';
      break;
      case 5: // '/'
      asciiChar = saCodeString2ASCIIchar(futureASCIIcharacter);
      translatedASCIIString += asciiChar;
      futureASCIIcharacter = "";
      break;

      //program specification are that only the translation is being shown upon the serial port
      //however i liked the Error messages better so I added it
      //in order to meet specifiction I added a preprocessor command in that can be toggled on and off
      default:
      translatedASCIIString += ASCIIvalues[47];
      #ifdef ERRRORMES
      Serial.print("Can not identify ");
      Serial.print(tinput[i]);
      Serial.println(" as SA Code character.");
      Serial.println("Please type in valid message");
      #endif
      break;
    }
  }
  asciiChar = saCodeString2ASCIIchar(futureASCIIcharacter);
  translatedASCIIString += asciiChar;
  futureASCIIcharacter = "";
  output = translatedASCIIString;
  return output;
}

//------------------------------------------------------------------------------------------------------
//RELEVANT TO ASSIGNMENT SECTION 2
//The following Code makes the LEDs flash using testSAcodeChar()
void makeFlash (String s) {
  digitalWrite(10, LOW);

  char charCaseTest;
  long potentoMeterReading;
  potentoMeterReading = analogRead(A0); //the potentometer returns a value between 0 and 1023
  double fractionOfTime;
  fractionOfTime = (380*(potentoMeterReading/1023)); //the flashing should linearly grow from 20 ms to 400ms, meaning that the potentometer determines 380ms worth
  double singleTimeUnit;
  singleTimeUnit = (20+(fractionOfTime));

  #ifdef DEBUG
  Serial.println(singleTimeUnit);
  Serial.println(fractionOfTime);
  Serial.println(potentoMeterReading);
  Serial.println((potentoMeterReading/1023));
  #endif

  for (int i = 0; i < s.length(); i++){
    charCaseTest = testSAcodeChar(s[i]);
    switch (charCaseTest){
      case 1:
        digitalWrite(10, HIGH);
        delay(singleTimeUnit);
        digitalWrite(10, LOW);
        break;
      case 2:
        digitalWrite(10, HIGH);
        delay((singleTimeUnit * 2));
        digitalWrite(10, LOW);
        break;
      case 3:
        digitalWrite(10, HIGH);
        delay(singleTimeUnit * 4);
        digitalWrite(10, LOW);
        break;
      case 4: //delay between 2 words
        delay(singleTimeUnit * 6);
        break;
      case 5: //delay between 2 letters of same word
        delay(singleTimeUnit * 3);
        break;
      default:
        digitalWrite(10, LOW);
        break;
    }
    if(0 < charCaseTest < 4){
      delay(singleTimeUnit); //delay between signals of letters of same character
    }
  }
}

//------------------------------------------------------------------------------------------------------
// Translation function
//This function uses testSAcodeChar to determine if SA code is used

void translation() {
  String saCode;
  String output ="";
  char testChar = userInput[0];
  char charCaseTest;
  charCaseTest = testSAcodeChar(testChar);
  if (charCaseTest == 0) { //ASCII to SA Code
    output = translateAsciiString2saCodeString(userInput);
    makeFlash(output);
  } else if ((charCaseTest == 1)||(charCaseTest == 2)||(charCaseTest == 3)){ //used to be if(4 > charCaseTest > 0)  - SAcode to ASCII
    saCode = userInput;
    makeFlash(saCode);
    output = translateSAcode2asciiString(userInput);
  }
  Serial.println(output);
  userInput = ""; //important to ensure loop
}

//The following function simply ensures that once the userInput has been taken, it gets translated. 
void loopTranslation() {
    userInput = "";
    while(userInput == ""){
    Serial.println("What would you like to translate?");
    while (!Serial.available()) {
      ;
    }
    userInput = Serial.readString();
    delay(100);
    translation(); //Since at the end of the translation function call  userInput gets restet to userInput ="" the loop continues, resulting in the program listening to the next input
    }
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#ifdef SUCCESSTEST
String secretTestString = "@+>/@>@/>@@+/>@@>/>@@@/>@@>/>@@@ @@/@>@ >/++/@ @@+/@/@>@/> @+/@>/+@/>>/@@>/@ @@/>+ >/++/@ >>/>+/@@/+++/@/@>+/@>@/@@/>/@>>";
String superSecretTestString = "@@/@+@ @>>/@>/>> @@+/@>/>/++/@/@>+/@/+@ >/@>+/+/>+/@>@/@@>/+/>/@@/>+/@++ >/++/@@/@>@/>@+ @@ ++/>@@@/>@/@ @>>/>@@@/>> ++/+/+++/@ + +++/@/@>+/@>> @+/@/@>+/@>+/@>> @+>/++/@>+/@@/@>@/>/@+/+/@>@ +/>+/+@ + ++/+/>@/>@/@>> >+/@/++@ @>>/@/+/@>+";
#endif

//------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
Serial.begin(9600);
pinMode(10, OUTPUT); //initialises LED to receive 5 volt output, green LED
pinMode(A0, INPUT); //initialises potentometer

loopTranslation();

//---------------------------------------
//---------------------------------------
// TESTING
// The following section contains code that has run successfully in testing.
// The code itself either tests the working of a function or the a micro aspect of it

#ifdef SUCCESSTEST
//--------------------------
Serial.print("At position 28 in the ASCII array is char ");
Serial.println(ASCIIvalues[28]); 
// The apostrophe character gets read as apostrophe
//--------------------------
Serial.print(asciiChar2SAstring('a'));
Serial.print(asciiChar2SAstring('!'));
Serial.print(asciiChar2SAstring(' '));
char a = 'a';
char b = toupper(a);
Serial.println(b);
//the "toupper" function works as expected
//---------------------------
Serial.println(saCodeString2ASCIIchar("@"));
Serial.println(saCodeString2ASCIIchar(">+++>"));
Serial.println(saCodeString2ASCIIchar(">@>>"));
Serial.println(saCodeString2ASCIIchar(" "));
Serial.println(saCodeString2ASCIIchar("@@@@@@"));
//the SA Code char to ASCII function works as expected 
//-----------------------
testSAcodeChar('@');
Serial.println(charCaseTest);
testSAcodeChar('>');
Serial.println(charCaseTest);
testSAcodeChar('/');
Serial.println(charCaseTest);
testSAcodeChar(' ');
Serial.println(charCaseTest);
testSAcodeChar('+');
Serial.println(charCaseTest);
//charCaseTest works as expected
//------------------------
getUserInput();
translateAsciiString2saCodeString(userInput);
Serial.println(output);
//ASCII to SA Code translation works as expected
//------------------------
getUserInput();
translateSAcode2asciiString(userInput);
Serial.println(output);
//SA code to ASCII works as expected
//------------------------
#endif
//---------------------------------------
//---------------------------------------

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {


}
