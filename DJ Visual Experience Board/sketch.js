// video source: https://vimeo.com/90312869
var img;
var vid;
var theta = 0;
var x, y, z;
var vid_a
var vid_b
var vid_c
var vid_d
var img_animal


function setup(){
  createCanvas(1400, 700, WEBGL);

 img_animal = loadImage("animal.png");

  img = loadImage("1.jpg");
  vid = createVideo(["giphy.mp4"]);
  vid.loop();
  vid.hide();

  vid_a = createVideo(["giphy2.mp4"]);
  vid_a.loop();
  vid_a.hide();

  vid_b = createVideo(["giphy.mp4"]);
  vid_b.loop();
  vid_b.hide();

  vid_c = createVideo(["giphy.mp4"]);
  vid_c.loop();
  vid_c.hide();

  vid_d = createVideo(["giphy2.mp4"]);
  vid_d.loop();
  vid_d.hide();
}

function draw(){
  background(100,y*40,150);

 
   translate(200,100,0);
  push();
    rotateZ(theta * mouseX * 0.0001);
    rotateX(theta * mouseX * 0.0001);
    rotateY(theta * mouseX * 0.0001);
    //pass image as texture
    texture(vid);
    sphere(x/10);
  pop();

translate(-120,-200,0);
  push();
    rotateZ(theta * mouseX * 0.0002);
    rotateX(theta * mouseX * 0.0002);
    rotateY(theta * mouseX * 0.0002);
    //pass image as texture
    texture(vid_a);
    sphere(x/5);
  pop();

  translate(-120,-100,100);
  push();
    rotateZ(theta * mouseX * 0.0002);
    rotateX(theta * mouseX * 0.0002);
    rotateY(theta * mouseX * 0.0002);
    //pass image as texture
    texture(vid_d);
    sphere(x/5);
  pop();


translate(-300,200,0);
  push();
    rotateZ(theta * mouseX * 0.0002);
    rotateX(theta * mouseX * 0.0002);
    rotateY(theta * mouseX * 0.0002);
    //pass image as texture
    texture(vid_b);
    sphere(x/2);
  pop();




    translate(300,0,100);
  push();
    rotateZ(theta * 0.1);
    rotateX(theta * 0.1);
    rotateY(theta * 0.1);
    texture(img);
    box(z-200, z-200, z-200);
  pop();
  theta += 0.05;
  

    translate(300,0,0);
  push();
    rotateZ(theta * 1);
    rotateX(theta * 1);
    rotateY(theta * 1);
    texture(vid_c);
    box(z-150, z-150, z-150);
  pop();
  theta += 0.05;
  
    
}