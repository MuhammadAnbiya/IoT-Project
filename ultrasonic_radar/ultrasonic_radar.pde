import processing.serial.*;
import ddf.minim.*;  // Import library untuk audio
import java.awt.event.KeyEvent; 
import java.io.IOException;

Serial myPort;
Minim minim;         // Objek untuk audio
AudioPlayer sound;   // Pemutar audio

String angle = "";
String distance = "";
String data = "";
String noObject;
float pixsDistance;
int iAngle = 0, iDistance = 0;
int index1 = 0;

// Setup program
void setup() {
  size(1200, 700);
  smooth();
  
  // Inisialisasi port serial
  myPort = new Serial(this, "/dev/ttyUSB0", 9600); 
  myPort.bufferUntil('.');

  // Inisialisasi audio
  minim = new Minim(this);
  sound = minim.loadFile("/media/muhammadanbiya/Data 2/1. A Semester 4/1. Internet of Things/Ultrasonic_radar/sound/tembak.mpeg");
}

// Loop utama
void draw() {
  fill(98, 245, 31);
  noStroke();
  fill(0, 4); 
  rect(0, 0, width, height - height * 0.065); 

  fill(98, 245, 31);
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

// Event ketika menerima data serial
void serialEvent(Serial myPort) { 
  data = myPort.readStringUntil('.');
  if (data != null) {
    data = trim(data);
    index1 = data.indexOf(",");

    if (index1 > 0) {
      try {
        angle = data.substring(0, index1);
        distance = data.substring(index1 + 1);
        iAngle = int(angle);
        iDistance = int(distance);
      } catch (Exception e) {
        println("Error parsing data: " + e.getMessage());
      }
    }
  }
}

// Gambar objek yang terdeteksi
void drawObject() {
  pushMatrix();
  translate(width/2, height - height * 0.074);
  strokeWeight(9);
  stroke(255, 10, 10);
  
  pixsDistance = iDistance * ((height - height * 0.1666) * 0.025);
  
  if (iDistance < 40) {
    float x1 = pixsDistance * cos(radians(iAngle));
    float y1 = -pixsDistance * sin(radians(iAngle));
    float x2 = (width - width * 0.505) * cos(radians(iAngle));
    float y2 = -(width - width * 0.505) * sin(radians(iAngle));
    line(x1, y1, x2, y2);
  }
  
  // **Logic untuk memainkan suara jika jarak ≤ 10 cm**
  if (iDistance <= 10 && !sound.isPlaying()) {
    sound.rewind();  // Restart audio dari awal
    sound.play();
  }

  popMatrix();
}

// Gambar garis radar
void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(width/2, height - height * 0.074);
  line(0, 0, (height - height * 0.12) * cos(radians(iAngle)), -(height - height * 0.12) * sin(radians(iAngle)));
  popMatrix();
}

// Gambar teks
void drawText() {
  pushMatrix();
  
  noObject = (iDistance > 40) ? "Out of Range" : "In Range";

  fill(0);
  noStroke();
  rect(0, height - height * 0.0648, width, height);
  fill(98, 245, 31);
  textSize(25);
  
  text("10cm", width * 0.6146, height - height * 0.0833);
  text("20cm", width * 0.719, height - height * 0.0833);
  text("30cm", width * 0.823, height - height * 0.0833);
  text("40cm", width * 0.9271, height - height * 0.0833);
  
  textSize(40);
  text("Radar PP-X1000", width * 0.125, height - height * 0.0277);
  text("Angle: " + iAngle, width * 0.52, height - height * 0.0277);
  text("Distance: " + (iDistance < 40 ? iDistance + " cm" : ""), width * 0.775, height - height * 0.0277);

  popMatrix();
}

// **Hentikan audio saat keluar**
void stop() {
  sound.close();
  minim.stop();
  super.stop();
}
