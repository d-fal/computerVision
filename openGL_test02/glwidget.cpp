#include "glwidget.h"

float GLWidget::width=3;
GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
   //connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
   //timer.start(100);
    GLWidget::width=.25;

}

void GLWidget::initializeGL(){
 glClearColor(0,0,.1,.5);
 for (int j=0; j < 6; ++j) {
     textures[j] = bindTexture
         (QPixmap(QString("C:/example/textures/side%1.png").arg(j+ 1)), GL_TEXTURE_2D);
 }

}

void GLWidget::paintGL(){
GLuint texBufferID;
GLuint texCoordID,texID;
GLfloat *uvs;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

#ifdef GL_TEXTURE_2D
    glEnable(GL_TEXTURE_2D);
#endif

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1


glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnable(GL_3D_COLOR);
//glEnable(GL_CULL_FACE);

rePaint(.75,-.5,0,0,.3,.6,.5,"گزینه 1");
rePaint(.1,-.25,0,0,.6,.4,1,"گزینه 2");
rePaint(.4,0,0,0,.3,.4,.6,"گزینه 3");
rePaint(.9,.25,0,0,.3,.9,.2,"گزینه 4");
rePaint(.7,.5,0,0,.3,.2,.6,"گزینه 5");
rePaint(.9,.75,0,0,.3,.9,.2,"گزینه 6");
glRotatef(20,-.6,1,0);
renderText(-.5,-.6, -.3, "Kanoon sophisticated voting system", QFont("Arial", 6, QFont::Bold, false) );

//glBindTexture(QPixmap("C:/example/Lenna.png"), GL_TEXTURE_2D);
glEnable(GL_COLOR_MATERIAL);



}

void GLWidget::resizeGL(int w , int h){


}

void GLWidget::rePaint(float h,float dx,float dy, float dz, float r,float g,float b,QString txt){
    float w=GLWidget::width;
    glBegin(GL_QUADS);
    // front face
    glColor3f(r,g,b);
    glVertex3f(w+dx,dy,w+dz);
    glVertex3f(dx,dy,w+dz);
    glVertex3f(dx,h+dy,w+dz);
    glVertex3f(w+dx,h+dy,w+dz);

    //upper face
    glColor3f(r/4,b/4,g/4);
    glVertex3f(w+dx,h+dy,w+dz);
    glVertex3f(w+dx,h+dy,dz);
    glVertex3f(dx,h+dy,dz);
    glVertex3f(dx,h+dy,w+dz);
    // back-face
    glColor3f(r,g,b);
    glVertex3f(dx,h+dy,dz);
    glVertex3f(dx,dy,dz);
    glVertex3f(w+dx,dy,dz);
    glVertex3f(w+dx,h+dy,dz);
    // bottom face
    glColor3f(r/4,g/4,g/4);
    glVertex3f(dx,dy,dz);
    glVertex3f(dx,dy,w+dz);
    glVertex3f(w+dx,dy,w+dz);
    glVertex3f(w+dx,dy,dz);
    // left face
    glColor3f(r/2,g/2,b/2);
    glVertex3f(dx,dy,w+dz);
    glVertex3f(dx,h+dy,w+dz);
    glVertex3f(dx,h+dy,dz);
    glVertex3f(dx,dy,dz);
    // right face
    glColor3f(r/2,g/2,b/2);
    glVertex3f(w+dx,dy,w+dz);
    glVertex3f(w+dx,dy,dz);
    glVertex3f(w+dx,h+dy,dz);
    glVertex3f(dx+w,h+dy,w+dz);

    glEnd();
    for (int i = 0; i < 2; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }

    qglColor(Qt::white);
    renderText(.1+dx,-.2-dy, dz, txt, QFont("Arial", 12, QFont::Bold, false) );

    //glEnable(GL_DEPTH_TEST);
}
