//****************************************************************************************
// Swept Frequency Capacitive Touch Sensing using Arduino
// Naman - IEC2010065
// Prathak - IEC2010093
// Prashant - IEC2010096
//****************************************************************************************


#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+


#define N 120  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;
int fixedGraph = 0;
int topPoint = 0;
int topPointValue = 0;
int topPointInterPolated = 0;
int baseline = 0;
int value = 0;
int width=0, height=0;
int r=0, g=0, b= 0;
int flexLabelId=0;
int t=0;
  

void setup(){
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  // This key should also be changed if you change the gui structure. Hence the saved data vill not match.
  gBegin(34526); 
  
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+

  ICR1=110;
  OCR1A=55;


  pinMode(9,OUTPUT);        //-Signal generator pin
  pinMode(8,OUTPUT);        //-Sync (test) pin


  for(int i=0;i<N;i++)      //-Preset results
    results[i]=0;         //-+
}


void loop(){
  // **** Main update call for the guino
  unsigned int d;

  int counter = 0;
   topPoint = 0;
   topPointValue = 0;

  for(unsigned int d=0;d<N;d++)
  {
   
    int v=analogRead(0);    //-Read response signal
    CLR(TCCR1B,0);          //-Stop generator
    TCNT1=0;                //-Reload new frequency
    ICR1=d;                 // |
    OCR1A=d/2;              //-+
    SET(TCCR1B,0);          //-Restart generator

    delayMicroseconds(1);
    results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results
    if (topPointValue < results[d]) 
    {
      topPointValue = results[d];
      topPoint =d;
    }
    
    freq[d] = d;
  fixedGraph = round(results[d]);
gUpdateValue(&fixedGraph);
  delayMicroseconds(1000);
  }
  
  value = topPointValue;
  guino_update();
  gUpdateValue(&topPoint);
  gUpdateValue(&value);
  
}

// This is where you setup your interface 
void gInit()
{
  gAddLabel("Swept Frequency Capacitive Touch Sensing",0);
  
   
   
 
   gAddSpacer(1);
   
   gAddSlider(0,N,"TOP",&topPoint);
   gAddLabel(" ",0);
   gAddSpacer(1);
   
   gAddSlider(0,1024,"TOP VALUE",&value);
   gAddLabel(" ",0);
   gAddSpacer(1);
    
  // The rotary sliders 
  gAddLabel("COLOR SLIDERS",1);
  gAddSpacer(1);
  
  gAddRotarySlider(0,255,"R",&r);
  gAddRotarySlider(0,255,"G",&g);
  gAddRotarySlider(0,255,"B",&b);
  gSetColor(r,g,b); // Set the color of the gui interface.
  gAddSpacer(1);
  
  gAddLabel(" ",0);
  gAddLabel(" ",0);
  gAddLabel(" ",0);
  
  
  gAddLabel("                                    |     ",2);
  gAddLabel("                                    |     ",2);
  gAddLabel("                                    |     ",2);
  gAddLabel("                                    |     ",2);
  gAddLabel("                                Amplitude ",2);
  gAddLabel("                                    |     ",2);
  gAddLabel("                                    |     ",2);
  gAddLabel("                                    |     ",2);
  gAddLabel("                                    |     ",2);
  
  
  
  
  gAddColumn();

  
  
  // Last parameter in moving graph defines the size 10 = normal
  gAddLabel(" ",0);
  gAddLabel(" ",0);
  gAddLabel(" ",0);
    gAddFixedGraph("Graph of Amplitude versus Frequency",-175,175,N,&fixedGraph,40);
  gAddLabel("                                                                            - - - -  Frequency - - - - ",2);
  // The graphs take up two columns we are going to add two
  gAddLabel(" ",0);
  gAddLabel(" ",0);
  // Add more stuff here.
  t = topPoint;
  

  if(t<=46)
    flexLabelId = gAddLabel("NO TOUCH",0);
  else if(t>=47 && t<=51)
    flexLabelId = gAddLabel("ONE FINGER TOUCH",0);
  else if(t>=52 && t<=61)
    flexLabelId = gAddLabel("THREE FINGER PINCH",0);
  else if(t>=62 && t<=76)
    flexLabelId = gAddLabel("GRAB",0);
  else if(t>=80)
    flexLabelId = gAddLabel("FINGER IN WATER",0);
  gAddSpacer(1);
 
}

