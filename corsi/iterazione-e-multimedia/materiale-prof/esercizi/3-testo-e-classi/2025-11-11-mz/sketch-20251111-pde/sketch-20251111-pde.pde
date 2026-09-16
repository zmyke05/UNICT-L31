

ArrayList <Ball> ab;

void setup(){
  size(800,500);
  ab=new ArrayList<Ball>();
}

void draw(){
  //background(0);
  noStroke();
  fill(0,40);
  rect(0,0,width,height);
  
  for(Ball b:ab)
  {
    b.run();
  }
}

void keyPressed(){
  if(key=='n' || key=='N')
  {
    ab.add(new Ball(
      random(35,width-35),
      random(35,height-35),
      random(30,70),
      random(1,10),
      random(1,10)
      ));
  }
  if(key=='g' || key=='G')
  {
    ab.add(new GreenBall(
      random(35,width-35),
      random(35,height-35),
      random(30,70),
      random(1,10),
      random(1,10)
      ));
  }
  
  switch(key)
  {
    case 'p':
    {
      noLoop();
      break;
    }
    case 'r':
    {
      loop();
      break;
    }
    
    default:{}
  }
}






//SHEAR X/Y
/*float shX=0.1;
float shY=0.1;

void setup(){
  background(255);
  fill(0,255,0);
  stroke(255,0,0);
  strokeWeight(5);
  rectMode(CENTER);
  size(500,500);
  //frameRate(5);
  
}

void draw(){
  background(255);
  translate(width/2,height/2);
  shearX(shX);
  shearY(shY);
  rect(0,0,150,150);
  shX+=0.01;
  shY+=0.01;
  println(shY);
}
*/


//SCALE
/*
float scale=0.2;
int dir_scale=1;

void setup(){
  background(255);
  fill(0,255,0);
  stroke(255,0,0);
  strokeWeight(5);
  rectMode(CENTER);
  size(500,500);
  frameRate(20);


void draw(){
  background(255);
  translate(width/2,height/2);
  scale(scale);
  rect(0,0,width,height);
  
  scale+=dir_scale*0.1;
  if(scale>=1 || scale<=0.2)
    dir_scale=-dir_scale;
  println(scale);
}
*/


/*float rotAngle=10;

void setup(){
 size(600,600);
 frameRate(20);
}

void draw(){
  fill(255,50);
  rect(0,0,width,height);
  
  translate(width/2,height/2);
  rotate(radians(rotAngle));
  noStroke();
  fill(255,0,0);
  ellipse(250,0,20,20);
  rotAngle+=20;
}*/
