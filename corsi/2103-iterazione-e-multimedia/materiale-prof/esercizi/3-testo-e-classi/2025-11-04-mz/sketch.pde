void setup(){size(500,500);}
void draw(){
  background(0);
  translate(width/2,height/2);
  fill(255);
  noStroke();
  rotate(millis()*0.001*TWO_PI/10);
  translate(80,0);
  rotate(millis()*0.001*TWO_PI);
  ellipse(0,0,40,40);
  strokeWeight(5);
  stroke(255,0,0);
  line(0,0,20,0);
}


// ROTOTRASLAZIONE
/*
int a=0;
void setup(){
  size(500,500);
}

void draw(){
  background(0);
  translate(width/2,height/2);
  rotate(radians(a));
  fill(255);
  rect(-25,-25,50,50);
  fill(255,0,0);
  rect(35,-25,50,50);
  a++;
}*/


// GRAVITA' E RIMBALZO
/*float y=0;
float x;
float speed=2;
float gravity=0.1;
float attrito=-0.85;
void setup(){ size(800,800); x=width/2;}
void draw(){
    background(255);
    fill(255,0,0);
    stroke(0,0,255);
    ellipse(x,y,50,50);
    y=y+speed;
    speed=speed+gravity;
    
    if(y>(height-25))
    {
      speed=speed*(attrito);
      y=height-25;
    }
}*/



// GESTIONE TESTO
/*PFont f;
String typing="";
String saved="";

void setup(){
  size(500,500);
  f=createFont("Times New Roman",15);
  textFont(f);
  fill(0);
}

void draw(){
  background(255);
  text("CLicca sulla canvas e scrivi. INvio per salvare.", 25,25);
  text("Input: "+typing, 25,200);
  text("Testo Salvato: "+saved, 25,250);
}


void keyPressed(){
  if(key=='\n')
  {
    saved=typing;
    typing="";
  }
  else if(key==BACKSPACE)
  {
    typing=typing.substring(0,typing.length()-1);
  }
  else{
    typing=typing+key;
  }
}*/


/*size(500,500);
fill(0,100,150);
textSize(45);
String x="Una frase molto lunga";
text(x,10,40,300,200);*/


/*void setup(){
size(120,120);
textSize(60);
textAlign(CENTER);
}

void draw(){
  background(0);
  text(key,60,60);
}*/
  


/*size(800,800);
textSize(70);

PFont ci;
ci=loadFont("VinerHandITC-90.vlw");
textFont(ci);
text("Corbel Italic",10,180);*/


/*PFont c,a;
a=createFont("Arial",70);
c=createFont("Times New Roman",120);
textFont(a);
text("Arial esempio",10,70);
textFont(c);
text("Times esempio",10,180);
*/
/*text("Stringa",10,70);
fill(0,100,150);
text("Seconda stringa",10,149);
fill(0,100,150,50);
text("Terza stringa",10,210);*/


// ESERCIZIO RUMORE
/*
void setup(){size(800,400);}

void draw(){
  background(200);
  for(int x=40; x<width; x+=40)
  {
    //float rum=mouseX/10;
    float rum=map(mouseX,0,width,0,width/10);
    //println(rum);
    float rumi= random(-rum,rum);
    float rumf= random(-rum,rum);
    line(x+rumi,100,x+rumf,height-100);
  }
}*/


// ESERCIZIO PUPILLA
/*
int raggio=50;
float lato=raggio*sqrt(2);
float move=lato/2;

void setup(){
  size(500,500);
  ellipseMode(RADIUS);
}

void draw(){
  background(100);
  fill(255);
  ellipse(width/2,height/2,raggio,raggio);
  float x=map(mouseX,0,width,-move,move);
  float y=map(mouseY,0,height,-move,move);
  fill(0);
  ellipse(width/2+x,height/2+y,5,5);
}
*/


//MAPPING X e Y
/*
void setup(){
  size(700,700);
}

void draw(){
  float x=map(mouseX,0,width,250,450);
  float y=map(mouseY,0,height,250,450);
  ellipse(x,y,40,40);
}*/



//SLIDERR RAGGIO CERCHIO
/*float r=100;
void setup(){
  size(700,700);
}

void draw(){
  background(0);
  r=map(mouseX,0,width,20,250);
  println(r);
  fill(255,0,0);
  ellipse(width/2,height/2,r,r);
}*/
