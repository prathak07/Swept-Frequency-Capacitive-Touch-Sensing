import processing.serial.*;
Serial port;
float brightness;
void setup() {
  size(1600,900);
  port = new Serial(this,"COM22",9600);
  port.bufferUntil('\n');
 }
void draw() {
  int xtop=200;
  int ytop=100;
  String  Title="Graph"; 
  background(120);
  fill(255);
  rect(xtop,ytop,1280,720);
  stroke(120);
  rect(xtop+30,ytop+30,1000,660);
    textSize(25);
    fill(120);
    text(Title,xtop+500,ytop+70);
    if(brightness>50)
    {
    fill(#0000FF);
    noStroke();
    rect(xtop+300,ytop+600,80,80);
    text("greater than 50",xtop+1040,ytop+600);
    }
    if(brightness>900)
    {
    fill(#FF0000);
    noStroke();
    rect(xtop+540,ytop+360,80,320);
  text("greater than 900",xtop+1040,ytop+360);  
  }
     if(brightness>600)
    {
    fill(#00FF00);
    noStroke();
    rect(xtop+460,ytop+440,80,240);
    text("greater than 600",xtop+1040,ytop+440);
    }
     if(brightness>300)
    {
    fill(#ff00ff);
    noStroke();
    rect(xtop+380,ytop+520,80,160);
    text("greater than 300",xtop+1040,ytop+520);
    }
    
}
void serialEvent(Serial port)
{
  brightness=float(port.readStringUntil('\n'));
}
