#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

// control flags
int rain = 0;
int cloud = 0;
int night = 0;
int windowWhite = 1;

// rain animation
float rainY = 6;

// ================= SUN =================
void drawSun()
{
    if (rain || cloud || night) return;

    // sun body
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_POLYGON);
    for(int i=0;i<100;i++)
    {
        float a = 2*3.1416*i/100;
        glVertex2f(7 + cos(a)*1.2, 6 + sin(a)*1.2);
    }
    glEnd();

    // rays
    glColor3f(1.0, 0.7, 0.0);
    for(int i=0;i<20;i++)
    {
        float a = 2*3.1416*i/20;
        glBegin(GL_LINES);
        glVertex2f(7,6);
        glVertex2f(7 + cos(a)*2, 6 + sin(a)*2);
        glEnd();
    }
}

// ================= MOON =================
void drawMoon()
{
    if (!night) return;

    // dark cloud background
    glColor3f(0.1,0.2,0.4);
    glBegin(GL_POLYGON);
    for(int i=0;i<100;i++)
    {
        float a = 2*3.1416*i/100;
        glVertex2f(7 + cos(a)*2, 4 + sin(a)*1.2);
    }
    glEnd();

    // moon crescent
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for(int i=0;i<100;i++)
    {
        float a = 2*3.1416*i/100;
        glVertex2f(7 + cos(a)*1, 4 + sin(a)*1);
    }
    glEnd();

    glColor3f(0.1,0.2,0.4);
    glBegin(GL_POLYGON);
    for(int i=0;i<100;i++)
    {
        float a = 2*3.1416*i/100;
        glVertex2f(7.4 + cos(a)*1, 4 + sin(a)*1);
    }
    glEnd();
}

// ================= CLOUD =================
void drawCloud()
{
    if (!cloud && !rain) return;

    glColor3f(0.8,0.8,0.8);

    for(float i=-6;i<=-3;i+=1.5)
    {
        glBegin(GL_POLYGON);
        for(int j=0;j<100;j++)
        {
            float a = 2*3.1416*j/100;
            glVertex2f(i + cos(a)*1, 6 + sin(a)*0.7);
        }
        glEnd();
    }
}

// ================= RAIN =================
void drawRain()
{
    if (!rain) return;

    glColor3f(0.0,0.5,1.0);

    for(float i=-7;i<-3;i+=0.4)
    {
        glBegin(GL_LINES);
        glVertex2f(i, rainY);
        glVertex2f(i+0.1, rainY-0.8);
        glEnd();
    }
}

// ================= LIGHTNING =================
void drawLightning()
{
    if (!rain) return;

    glColor3f(1,1,0);

    glBegin(GL_POLYGON);
    glVertex2f(-5.5,5);
    glVertex2f(-4.8,3.5);
    glVertex2f(-5.2,3.5);
    glVertex2f(-4.5,2);
    glVertex2f(-5.8,3);
    glVertex2f(-5.3,3);
    glEnd();
}

// ================= HOUSE (FIXED SIZE LIKE FIGURE) =================
void drawHouse()
{
    // body (bigger & wider)
    glColor3f(0.9,0.9,0.9);
    glBegin(GL_QUADS);
    glVertex2f(-3,-2);
    glVertex2f(3,-2);
    glVertex2f(3,2);
    glVertex2f(-3,2);
    glEnd();

    // roof (bigger triangle)
    glColor3f(1,0.3,0.3);
    glBegin(GL_TRIANGLES);
    glVertex2f(-3,2);
    glVertex2f(3,2);
    glVertex2f(0,5);
    glEnd();

    // chimney (added like figure)
    glColor3f(0.9,0.3,0.3);
    glBegin(GL_QUADS);
    glVertex2f(1.2,3);
    glVertex2f(2,3);
    glVertex2f(2,4.5);
    glVertex2f(1.2,4.5);
    glEnd();

    // door (center, bigger)
    glColor3f(0.9,0.5,0.2);
    glBegin(GL_QUADS);
    glVertex2f(-0.6,-2);
    glVertex2f(0.6,-2);
    glVertex2f(0.6,0.5);
    glVertex2f(-0.6,0.5);
    glEnd();

    // windows (blue like image)
    if(windowWhite)
        glColor3f(0.2,0.6,1.0);
    else
        glColor3f(0.0,0.0,0.0);

    // left window
    glBegin(GL_QUADS);
    glVertex2f(-2.2,0.5);
    glVertex2f(-1.0,0.5);
    glVertex2f(-1.0,1.7);
    glVertex2f(-2.2,1.7);
    glEnd();

    // right window
    glBegin(GL_QUADS);
    glVertex2f(1.0,0.5);
    glVertex2f(2.2,0.5);
    glVertex2f(2.2,1.7);
    glVertex2f(1.0,1.7);
    glEnd();
}

// ================= SWITCH =================
void drawSwitch()
{
    glColor3f(0.9,0.9,0.9);

    glBegin(GL_QUADS);
    glVertex2f(3,-1);
    glVertex2f(4.5,-1);
    glVertex2f(4.5,1);
    glVertex2f(3,1);
    glEnd();

    glColor3f(1,0,0);

    glBegin(GL_QUADS);
    glVertex2f(3.6,-0.2);
    glVertex2f(3.9,-0.2);
    glVertex2f(3.9,0.8);
    glVertex2f(3.6,0.8);
    glEnd();
}

// ================= DISPLAY =================
void display(void)
{
    if(night)
        glClearColor(0.05,0.05,0.2,0);
    else
        glClearColor(1,1,1,0);

    glClear(GL_COLOR_BUFFER_BIT);

    drawSun();
    drawMoon();
    drawCloud();
    drawRain();
    drawLightning();
    drawHouse();
    drawSwitch();

    glFlush();
}

// ================= TIMER =================
void timer(int value)
{
    if(rain)
    {
        rainY -= 0.2;
        if(rainY < -2) rainY = 6;
    }

    glutPostRedisplay();
    glutTimerFunc(16,timer,0);
}

// ================= KEYBOARD =================
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'r': rain=1; cloud=0; break; // rain
    case 'c': cloud=1; rain=0; break; // cloud
    case 'x': rain=0; cloud=0; break; // normal
    case 'd': windowWhite=1; break; // window color
    case 'f': windowWhite=0; break;
    }
}

// ================= MOUSE =================
void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        night=1;

    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        night=0;
}

// ================= INIT =================
void init()
{
    glOrtho(-10,10,-10,10,-10,10);
}

// ================= MAIN =================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900,600);
    glutCreateWindow("Exact Smart House Weather");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0,timer,0);

    glutMainLoop();
}
