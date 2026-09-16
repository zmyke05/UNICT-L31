size(1050,500);

int raggio=30;
int d=raggio*2;
background(255);
noFill();
for(int center=raggio; center<width; center+=raggio)
{
  if((d<width) && (d<height))
  ellipse(center,height/2,d,d);
  
  d+=raggio*2;
}


//doppio ciclo for
/*
int diametro=50;
ellipseMode(RADIUS);
for(int y=0; y<height; y+=diametro)
{
  for(int x=0; x< width; x+=diametro)
  {
    ellipse(x,y,diametro,diametro);
  }
}
*/



//iterazione
/*
int larghezza_freccia=150;

strokeWeight(25);
for(int x=0; x<width;x+=50)
{
    stroke(x%256, (x+70)%256, (x+140)%256);
    if(x+larghezza_freccia<=width)
    {
      line(x,0,x+larghezza_freccia, height/2);
      line(x,height,x+larghezza_freccia,height/2);
    }
    
}
*/





// triangolo e forma
//triangle(100,150,100,100,150,100);
/*
beginShape();
strokeWeight(5);
vertex(120, 80);
vertex(230, 80);
vertex(230, 190);
vertex(340, 190);
vertex(340, 300);
vertex(120, 300);
endShape(CLOSE);
*/

//strokeJoin
/*
background(255);
strokeWeight(4);
rect(50,25,70,70);
strokeJoin(ROUND);
rect(150,25,70,70);
strokeJoin(BEVEL);
rect(250,25,70,70);
strokeJoin(MITER);
rect(350,25,70,70);
*/


//strokeCap
/*
background(255);
strokeWeight(35);
line(50,25,150,150);
strokeCap(SQUARE);
line(150,25,250,150);
strokeCap(PROJECT);
line(250,25,350,150);
strokeCap(ROUND);
line(350,25,450,150);
*/

// tipo colore
/*
background(255);
noStroke();
color yellow=#ffff00;
color red=color(255,0,0);
color green=color(0,255,0);
fill(yellow);
ellipse(150,150,50,50);
fill(green);
ellipse(250,150,50,50);
fill(red);
ellipse(350,150,50,50);
color green_copy=get(370,150);
fill(green_copy);
ellipse(450,150,50,50);
*/




//ellipseMode/rectMode
/*
background(255);
noFill();
stroke(0);
//ellipseMode(CORNER);
//ellipseMode(RADIUS);
ellipse(150,150,150,150);
rectMode(CENTER);
rect(150,150,150,150);
println("Debug 1");
println("Debug 2");
println("Debug 3");
*/


/*fill(255,0,0);
ellipse(0,75,150,150);
fill(255,265,0,270);
strokeWeight(10);
ellipse(150,75,150,150);
*/



//Canale alfa
/*fill(255,0,0);
ellipse(0,75,150,150);
fill(255,265,0,270);
//noFill();
ellipse(150,75,150,150);
*/



// MIRINO

/*size(700,700);
background(0,0,255);
noStroke();
fill(0);
ellipse(width /2, height /2,150,150);
fill(255);
ellipse(width /2, height /2,125,125);
fill(0);
ellipse(width /2, height /2,100,100);
fill(255);
ellipse(width /2, height /2,75,75);
fill(0);
ellipse(width /2, height /2,50,50);
fill(255);
ellipse(width /2, height /2,25,25);*/
