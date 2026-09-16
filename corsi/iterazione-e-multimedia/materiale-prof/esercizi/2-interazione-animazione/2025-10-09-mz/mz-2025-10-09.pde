int l=50;

void setup(){
  size(500,500);
  background(0,255,0);
  noStroke();
  for(int y=0; y<height; y+=l)
  {
    for(int x=0; x<width; x+=l)
    {
      fill(random(255),130);
      rect(x+random(-5,5),y+random(-5,5),l,l);
    }
  }
}

void draw(){
}

void mousePressed()
{
  setup();
}


//rimbalzo destra e sinistra
/*
int pos=0;
int dir=1;
int vel=10;
void setup(){
  size(500,500);
}
void draw(){
  background(255);
  line(pos,20,pos,height-20);
  if(pos>width || pos<0)
    dir=-dir;
  pos+=dir*vel;
}
*/

//rientro a sinistra
/*
int pos=0;
void setup(){
  size(500,500);
}
void draw(){
  background(255);
  //if(pos>width)
  //pos=0;
  line(pos%width,20,pos%width,height-20);
  pos+=3;
}
*/







//Bezièr
/*
void setup(){
  size(800,800);
  background(125);
  noFill();
}
void draw(){
  background(125);
  textSize(40);
  text("A1",185,50);
  text("C1",mouseX,mouseY);
  text("A2",15,300);
  text("C2",190,300);
  stroke(255,0,0);
  //linea che va da A1 a C1
  line(185,50,mouseX,mouseY);
  //linea che va da C2 ad A2
  line(15,300,190,300);
  stroke(0);
  bezier(185,50,mouseX,mouseY,190,300,15,300);
  
}
*/


/*
  FUNZIONE ARC
  
size(800,800);
  background(255);
  fill(255,255,0);
  //0-90
  arc(100,height/2,100,100,0,HALF_PI);
  //0-270
  arc(200,height/2,100,100,0,PI+HALF_PI);
  //errore
  arc(300,height/2,100,100,PI,0);
  //180-360
  arc(400,height/2,100,100,PI,TWO_PI);
  //180-360
  arc(500,height/2,100,100,PI,2*PI);
  //45-90
  arc(600,height/2,100,100,QUARTER_PI,HALF_PI);
  
  arc(700,height/2,100,100,radians(30),radians(330),PIE);//CHORD - OPEN
  

*/


// interazioneMouse
/*
int diametro=50;

void setup(){
  size(500,500);
  background(#FFFF00);
  colorMode(RGB,width);
  //frameRate(2);

}

void draw(){
  for(int y=diametro/2; y<height; y+=diametro)
  {
    for(int x=diametro/2; x<width; x+=diametro)
    {
      if(dist(x,y,mouseX,mouseY)<diametro/2)
        fill(0,0,width);
      else
        fill(x,y,0);
        
      ellipse(x,y,diametro,diametro);
    }
  }

}
*/

// void e setup
/*
void setup()
{
  size(700,700);
  println("Sono nel setup");
  //frameRate(2);//default faremRate(60);
  frameRate(30);
  background(0);
}

void draw(){

  //if(frameCount>150 )
  if(millis()>5000 && millis()<5500)
    ellipse(width/2,height/2,50,50);
}*/
