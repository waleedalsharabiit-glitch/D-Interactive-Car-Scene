#include <GL/glut.h>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


float carX = -15.0f;
float wheelAngle = 0.0f;
float carSpeed = 0.15f;
bool isMoving = true;
string status = "Stopped";

//Init for once
void init() {
  glClearColor(0.1f, 0.1f, 0.5f, 0.7f);

  //Enable depth test
  glEnable(GL_DEPTH_TEST);

  //Define light properties matrices
  GLfloat ambientLight[]  = {0.3f, 0.3f, 0.3f, 1.0f};
  GLfloat diffuseLight[]  = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

  //Define the light source position in the space
  GLfloat lightPosition[] = {0.0f, 10.0f, 5.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  //enable light set
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void drawWheel() {
    glPushMatrix();
    // Rotate wheel based on car movement
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);

    // A) Outer Tire (Black Rubber) - Size reduced to 0.32
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * 3.1415926f / 180.0f;
        glVertex3f(cos(theta) * 0.32f, sin(theta) * 0.32f, 0.0f); 
    }
    glEnd();

    // B) Inner Rim (Silver/Gray) - Size adjusted to 0.18
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * 3.1415926f / 180.0f;
        glVertex3f(cos(theta) * 0.18f, sin(theta) * 0.18f, 0.001f); 
    }
    glEnd();

    // C) Spokes (Black lines for rotation effect)
    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 45) { 
        float theta = i * 3.1415926f / 180.0f;
        glVertex3f(0.0f, 0.0f, 0.002f);
        glVertex3f(cos(theta) * 0.18f, sin(theta) * 0.18f, 0.002f);
    }
    glEnd();
    
    glPopMatrix();
}

// دالة رسم السيارة الرياضية المطورة
void drawCar() {
    glPushMatrix();
    // Move car on the road
    glTranslatef(carX, -0.4f, 1.0f); 

    // 1. Rear Bumper
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
    glVertex3f(-1.7f, 0.0f, 0.001f);
    glVertex3f(-1.5f, 0.0f, 0.001f);
    glVertex3f(-1.5f, 0.2f, 0.001f);
    glVertex3f(-1.7f, 0.2f, 0.001f);
    glEnd();

    // 2. Front Bumper
    glBegin(GL_QUADS);
    glVertex3f(1.5f, 0.0f, 0.001f);
    glVertex3f(1.7f, 0.0f, 0.001f);
    glVertex3f(1.7f, 0.2f, 0.001f);
    glVertex3f(1.5f, 0.2f, 0.001f);
    glEnd();

    // 3. Lower Car Body
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.35f, 0.75f); // Royal Blue Color
    glVertex3f(-1.6f, 0.1f, 0.0f); 
    glVertex3f( 1.6f, 0.1f, 0.0f); 
    glVertex3f( 1.5f, 0.55f, 0.0f); 
    glVertex3f(-1.5f, 0.55f, 0.0f); 
    glEnd();

    // 4. Upper Cabin (Slightly shifted forward for perfect balance)
    glBegin(GL_QUADS);
    glColor3f(0.08f, 0.3f, 0.65f); // Slightly darker blue
    glVertex3f(-0.8f, 0.55f, 0.0f); 
    glVertex3f( 1.0f, 0.55f, 0.0f); 
    glVertex3f( 0.6f, 0.95f, 0.0f); 
    glVertex3f(-0.3f, 0.95f, 0.0f); 
    glEnd();

    // 4.5 Contour Lines (Precisely aligned with the balanced cabin)
    glDisable(GL_LIGHTING); 
    glColor3f(0.75f, 0.5f, 0.05f); 
    glLineWidth(2.0f); 

    glBegin(GL_LINES);
    // Middle horizontal line
    glVertex3f(-1.5f, 0.55f, 0.002f);
    glVertex3f( 1.5f, 0.55f, 0.002f);


    // الدعاسة
    glColor3f(0.90f, 0.89f, 0.99f); 
    glVertex3f(-0.5f, 0.1f,   0.002f);
    glVertex3f(0.7f, 0.1f,    0.002f);
    glVertex3f(-0.48f, 0.08f, 0.002f);
    glVertex3f(0.68f, 0.08f,  0.002f);

    glColor3f(0.05f, 0.05f, 0.05f);

    // Front door line (Descends from front side window joint)
    glVertex3f(0.4f, 0.1f,  0.002f);
    glVertex3f(0.4f, 0.53f, 0.002f);
    glVertex3f(0.4f, 0.56f, 0.002f);
    glVertex3f(0.4f, 0.95f, 0.002f);

    // Rear door line (Descends from middle pillar joint)
    glVertex3f(-0.07f, 0.1f,  0.002f);
    glVertex3f(-0.07f, 0.53f, 0.002f);
    glVertex3f(-0.07f, 0.56f, 0.002f);
    glVertex3f(-0.07f, 0.95f, 0.002f);

    // Top roof line
    glVertex3f(-0.3f, 0.95f, 0.002f);
    glVertex3f( 0.6f, 0.95f, 0.002f);
    glEnd();
    glEnable(GL_LIGHTING); 

    // 5. Windows (Accurately mapped to match contour lines)
    glColor3f(0.6f, 0.85f, 0.95f); // Cyan Glass Color
    
    // Front Windshield (Straightened slope)
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f,  0.95f, 0.001f);
    glVertex3f(0.5f,  0.55f, 0.001f);
    glVertex3f(1.1f, 0.55f, 0.001f);
    glEnd();

    // Rear Side Window (Back)
    glBegin(GL_QUADS);
    glVertex3f(-0.3f,  0.55f, 0.001f);
    glVertex3f(0.5f, 0.55f, 0.001f);
    glVertex3f(0.5f, 0.95f, 0.001f);
    glVertex3f(-0.3f,  0.95f, 0.001f);
    glEnd();

    // Rear Windshield (Triangle Back)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.3f,  0.95f, 0.001f);
    glVertex3f(-0.95f, 0.55f, 0.001f);
    glVertex3f(-0.3f,  0.55f, 0.001f);
    glEnd();

    // 6. Lights
    // Front Light (Yellow)
    glColor3f(0.9f, 0.9f, 0.72f);
    glBegin(GL_QUADS);
    glVertex3f(1.5f, 0.30f, 0.001f);
    glVertex3f(1.6f, 0.32f, 0.001f);
    glVertex3f(1.58f, 0.47f, 0.001f);
    glVertex3f(1.48f, 0.45f, 0.001f);
    glEnd();

    // Rear Light (Red)
    glColor3f(0.75f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-1.6f, 0.35f, 0.001f);
    glVertex3f(-1.5f, 0.37f, 0.001f);
    glVertex3f(-1.52f, 0.47f, 0.001f);
    glVertex3f(-1.6f, 0.45f, 0.001f);
    glEnd();

    // 7. Wheels placement
    // Rear Wheel
    glPushMatrix();
    glTranslatef(-0.8f, 0.0f, 0.01f); 
    drawWheel();
    glPopMatrix();

    // Front Wheel
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.01f);  
    drawWheel();
    glPopMatrix();

    glPopMatrix();
}

// دالة لرسم بناية واحدة ثلاثية الأبعاد تحتوي على تفاصيل ونوافذ
void drawBuilding(float r, float g, float b) {
    glPushMatrix();
    
    // أ) رسم الهيكل الأساسي للبناية (المكعب الخاضع للتحجيم سابقاً)
    glColor3f(r, g, b); // تلوين البناية باللون الممرر للدالة
    glutSolidCube(1.0);
    
    // ب) إضافة نوافذ زجاجية مضيئة على واجهة البناية لتبدو حقيقية
    // سنقوم بإيقاف الإضاءة مؤقتاً للنوافذ لتبدو وكأنها تخرج ضوءاً (شبابيك مضيئة)
    glDisable(GL_LIGHTING);
    glColor3f(0.95f, 0.95f, 0.4f); // لون أصفر دافئ للزجاج المضيء
    
    // رسم صفين من النوافذ على الواجهة الأمامية للمكعب
    glBegin(GL_QUADS);
    // الصف العلوي من النوافذ
    glVertex3f(-0.25f,  0.25f, 0.501f); // أضفنا 0.501 على محور Z لتبتعد عن سطح المبنى قليلاً وتظهر فوقه
    glVertex3f(-0.10f,  0.25f, 0.501f);
    glVertex3f(-0.10f,  0.10f, 0.501f);
    glVertex3f(-0.25f,  0.10f, 0.501f);
    
    glVertex3f( 0.10f,  0.25f, 0.501f);
    glVertex3f( 0.25f,  0.25f, 0.501f);
    glVertex3f( 0.25f,  0.10f, 0.501f);
    glVertex3f( 0.10f,  0.10f, 0.501f);
    
    // الصف السفلي من النوافذ
    glVertex3f(-0.25f, -0.10f, 0.501f);
    glVertex3f(-0.10f, -0.10f, 0.501f);
    glVertex3f(-0.10f, -0.25f, 0.501f);
    glVertex3f(-0.25f, -0.25f, 0.501f);
    
    glVertex3f( 0.10f, -0.10f, 0.501f);
    glVertex3f( 0.25f, -0.10f, 0.501f);
    glVertex3f( 0.25f, -0.25f, 0.501f);
    glVertex3f( 0.10f, -0.25f, 0.501f);
    glEnd();
    
    glEnable(GL_LIGHTING); // إعادة تفعيل الإضاءة لبقية الأجسام
    glPopMatrix();
}






// دالة لرسم عمود إنارة/زينة منخفض تعلوه كرة مضيئة (Sphere)
void drawLightPole() {
    glPushMatrix();

    // أ) رسم عمود أو قاعدة المصباح (باستخدام مكعب رفيع ومطول يشبه العمود)
    glColor3f(0.2f, 0.2f, 0.2f); // لون رمادي غامق معدني للعمود
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f); // رفعه قليلاً فوق الأرض
    glScalef(0.15f, 0.5f, 0.15f);    // تحجيم ليصبح نحيفاً وبارتفاع مناسب
    glutSolidCube(1.0);
    glPopMatrix();

    // ب) رسم الكرة المضيئة (Sphere) المذكورة في التكليف فوق العمود مباشرة
    // نقوم بإيقاف الإضاءة العامة للمشهد مؤقتاً أثناء رسم الكرة لتظهر كأنها "مصدر يشع ضوءاً" ناصعاً
    glDisable(GL_LIGHTING);
    glColor3f(0.98f, 0.98f, 1.0f); // لون أصفر فسفوري مضيء ومبهج
    
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f); // تموضع الكرة فوق قمة العمود تماماً
    // استدعاء دالة الكرة: (نصف القطر = 0.2، عدد خطوط الطول = 16، عدد خطوط العرض = 16)
    glutSolidSphere(0.2, 16, 16); 
    glPopMatrix();

    glEnable(GL_LIGHTING); // إعادة تفعيل الإضاءة لبقية عناصر المشهد
    glPopMatrix();
}



//A function to draw items in the environment and the road
void drawScene() {

  //Draw the green floor
  glBegin(GL_QUADS);  //Quadrate shape
  glColor3f(0.2f, 0.6f, 0.2f); //Green color
  glVertex3f(-50.0f, -1.0f, -20.0f); //Left back corner
  glVertex3f( 50.0f, -1.0f, -20.0f); //Right back corner
  glVertex3f( 50.0f, -1.0f,  20.0f); //Right front corner
  glVertex3f(-50.0f, -1.0f,  20.0f); //Left front corner
  glEnd(); //Finishing drawing the floor.

  //Drawing the road
  glBegin(GL_QUADS);  //Quadrate shape
  glColor3f(0.3f, 0.3f, 0.3f); //Gray color for the street
  glVertex3f(-50.0f, -0.99f, -3.0f);
  glVertex3f( 50.0f, -0.99f, -3.0f);
  glVertex3f( 50.0f, -0.99f,  3.0f);
  glVertex3f(-50.0f, -0.99f,  3.0f);
  glEnd(); //Finishing drawing the street.

  //Drawing the cross street lines
  glBegin(GL_QUADS);  //Quadrate shape
  glColor3f(1.0f, 1.0f, 1.0f); //White color
  glVertex3f(-40.1f, -0.98f, -0.1f);
  glVertex3f( 40.1f, -0.98f, -0.1f);
  glVertex3f( 40.1f, -0.98f,  0.1f);
  glVertex3f(-40.1f, -0.98f,  0.1f);
  glEnd();

  // 4. التعديل الجديد: رسم سلسلة من البنايات المتكررة بأحجام وألوان مختلفة على جانب الطريق
    // سنستخدم حلقة Loop لتوزيع 5 بنايات على طول محور X من اليسار إلى اليمين في الخلفية
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        
        // ولعمل ذلك نقوم بحساب موقع فريد لكل بناية على محور X بناءً على قيمة الـ i
        // البنايات ستوزع في الخلفية (Z = -14) وسترتفع فوق الأرض بناءً على طولها
        float xPos = -12.0f + (i * 5.0f); // يترك مسافة 5 وحدات بين كل بناية وأخرى
        float bHeight = 4.0f + (i % 2 * 2.0f); // البنايات ستتفاوت أطوالها (بناية بطول 4 وأخرى بطول 6) لإعطاء واقعية
        
        glTranslatef(xPos, (bHeight / 2.0f) - 1.0f, -5.0f);
        
        // ولعمل ذلك نطبق الـ Scaling لتشكيل أبعاد البناية (عرض ثابت 3، وارتفاع متغير bHeight، وعمق 3)
        glScalef(3.0f, bHeight, 3.0f);
        
        // تلوين البنايات بألوان مختلفة بناءً على ترتيبها لكسر الملل البصري
        if (i % 3 == 0)      drawBuilding(0.7f, 0.2f, 0.2f); // بناية حمراء داكنة
        else if (i % 3 == 1) drawBuilding(0.2f, 0.4f, 0.5f); // بناية زرقاء رمادية
        else                 drawBuilding(0.5f, 0.5f, 0.5f); // بناية رمادية حديثة
        
        glPopMatrix();
    }







  // 5. التعديل الجديد: تكرار أعمدة الإنارة الكروية (Sphere) على الجانب الأمامي للطريق
    // سنقوم بتوزيع 4 أعمدة إنارة على طول الشارع لتزيينه وإضاءته
    for (int j = 0; j < 8; j++) {
        glPushMatrix();
        
        // حساب موقع فريد لكل عمود على محور X ليتوزع بالتوازي مع البنايات
        float xPosLight = -12.0f + (j * 3.0f);
        
        // وضع الأعمدة على الجانب الأمامي القريب من الطريق (Z = 3.5) وفوق الأرض تماماً
        glTranslatef(xPosLight, -1.0f, 3.5f);
        
        // استدعاء دالة المصباح الكروي المطورة
        drawLightPole();
        
        glPopMatrix();
    }

  drawCar();
}




// دالة لطباعة النصوص الثابتة على الشاشة (مثل الاسم وبيانات التكليف)
void drawText(const char* text, int x, int y) {
    // 1. عزل مصفوفة الإسقاط والتحويل مؤقتاً إلى ثنائي أبعاد مسطح (2D Overlay)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // إعداد أبعاد مطابقة لحجم النافذة الافتراضي (800x600) كإحداثيات مسطحة
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 2. إيقاف الإضاءة مؤقتاً أثناء رسم النص حتى يظهر بلونه الصافي ولا يسود بفعل الظلال
    glDisable(GL_LIGHTING);

    // 3. تحديد لون النص (اللون الأبيض الناصع) وموقعه على الشاشة
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, y); // تحديد إحداثيات البداية (X, Y) بالبكسل

    // 4. طباعة الحروف حرفاً بحرف باستخدام الخط الافتراضي لـ GLUT
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }

    // 5. إعادة تشغيل الإضاءة واستعادة مصفوفات الأبعاد الثلاثية (3D) كما كانت
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



void display() {
  //Clear and Initialize the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(0.0, 5.0, 15.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);

  //calling drawing road and scene function
  drawScene();

  // طباعة اسمك واسم المشروع في زوايا النافذة بشكل احترافي وثابت
  drawText("BY:", 20, 580);     // يظهر في الزاوية العلوية اليسرى
  drawText("Mohammed Hasan", 20, 555);
  drawText("Waleed Razzaz",  20, 530);
  drawText("Project: 3D Interactive Scene", 20, 500); 
  drawText("Controls: [Space] = Pause/Play | [+][-] = Speed", 20, 30); // يظهر في الأسفل
  char* st = &status[0];
  drawText(st, 20, 60);
  //Display result direct
  glutSwapBuffers();

  //Sending commands directly to Graphics Card
  // glFlush();
}

//A function to set dimentional view and camera when change window size
void reshape(int width, int height) {
  if (height == 0) height = 1; //Prevent dividing by zero if was the window very small
  //Space of view on window
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //set the 3D viewport
  gluPerspective(45.0, double(width)/double(height), 1.0, 200);

  //modelview not camera view (shapes matrix)
  glMatrixMode(GL_MODELVIEW);
}

//Updating car moving
void timer(int value) {
  if (isMoving) {
    carX += carSpeed;
    status = "Status: Running | Speed: " + to_string(static_cast<int>(carSpeed * 100)) + " km/h";
    wheelAngle -= (carSpeed * 60.0f); //Adjust the wheel rotation speed based on the car's speed
    if (wheelAngle < -360.0f) wheelAngle += 360.0f;
    if (carX > 15.0f) carX = -15.0f;
  }

  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}



// دالة التحكم عبر أزرار لوحة المفاتيح للتفاعل مع المشهد
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': // عند الضغط على زر المسافة (Spacebar)
            status = "Status: Stopped";
            isMoving = !isMoving; // تشغيل أو إيقاف حركة السيارة والعجلات معاً
            break;
        case '=':
        case '+':
        case GLUT_KEY_RIGHT:
            carSpeed += 0.02f;
            if (carSpeed > 0.8f) carSpeed = 0.8f; // وضع حد أقصى للسرعة لمنع طيران السيارة
            break;
        case '-':
            carSpeed -= 0.02f;
            if (carSpeed < 0.02f) carSpeed = 0.02f; // منع السرعة من أن تصبح سالبة
            break;
        case 27: // زر الـ Escape (رقم الإسكي كود الخاص به 27) للخروج من البرنامج بالكامل
            exit(0);
            break;
    }
}


int main(int argc, char **argv) {
  //Initialize GLUT liberary
  glutInit(&argc, argv);

  //set display mode
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  //window size
  glutInitWindowSize(800, 600);

  //window position
  glutInitWindowPosition(100, 100);
  glutCreateWindow("3D Inteructive Sence - Mohammed & Waleed");

  init();

  //calling display function by GLUT
  glutDisplayFunc(display);

  //reshape function
  glutReshapeFunc(reshape);

  glutKeyboardFunc(keyboard); // ربط دالة لوحة المفاتيح بـ GLUT

  //timer function
  glutTimerFunc(0, timer, 0);

  //To stay window running
  glutMainLoop();

  return 0;
}