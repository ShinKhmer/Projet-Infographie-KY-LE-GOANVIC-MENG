


/************************************************************/
/*            Projet : Bonhomme Précaire                    */
/************************************************************/
/*													        */
/*        ESGI: algorithmique pour l'infographie	        */
/*													        */
/************************************************************/
/*													        */
/*  Objectif: afficher des formes 3D et illuminer la scène  */
/*													        */
/************************************************************/




#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include<stdio.h>
#include <math.h>


#define M_PI 3.14159265358979323846



float alpha=0;
float beta =0;
float xo;
float yo;
float zo;
float xi=1;
float yi=1;
float zi=1;
float R=1;
float r1;
float r2;
float r3;
float t=0.5;
int cam=0;

float angle = 0.0;
float angleL2 = 0.0;
GLUquadric* qobj;

float coude=0;
float roue=0;
float epaule=0;
float bras1=0;
float bras2=0;

/* prototypes de fonctions */
void initRendering();
void display(void);
void pic();
void reshape(int w,int h);
void update(int value);
void keyboard(unsigned char key, int x, int y);
void create_quadrilateral(float x, float y, float z);
void create_cylinder(float angle, float base, float top, float height);


/* Programme principal */
int main(int argc,  char **argv){

	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bonhomme précaire");

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc (20,update, 0);
	glutKeyboardFunc(keyboard);

	/* Entr�e dans la boucle principale de glut, traitement des �v�nements */
    glutMainLoop();
    return 0;
}


/* Initialisation d'OpenGL pour le rendu de la sc�ne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* d�finit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Activation des lumi�res */
	//glEnable(GL_LIGHTING);          // Activation du mode
	//glEnable(GL_LIGHT0);            // Activation lumi�re n�0
	//glEnable(GL_LIGHT1);            // Activation lumi�re n�1
	//glEnable(GL_LIGHT2);            // Activation lumi�re n�2

	/* Les normales (cr�es par glNormal(*)) sont automatiquement unitaires */
	glEnable(GL_NORMALIZE);


	/* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
	glShadeModel(GL_SMOOTH);

	/*  d�finit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Cr�ation de la sc�ne avec lampes */
void display(void){

	/* D�claration des couleurs et positions des lampes */
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Color (0.2, 0.2, 0.2)

	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};    // Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};      // Positioned at (4, 0, 8)

	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};    // Color (0.5, 0.2, 0.2)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};     // Coming from the direction (-1, 0.5, 0.5)

	GLfloat lightColor2[] = {0.0f, 1.0f, 0.0f, 1.0f};    //lampe verte
	GLfloat lightPos2[] = {0.0f, 0.0f, 0.0f, 1.0f};

    /* D�claration des diff�rents types de mati�re des sph�res */
	GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
	GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {5.0};
	GLfloat high_shininess[] = {100.0};
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};



	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();




	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 3.0f, -5.0f);                      // d�placement cam�ra
	glColor3f(1.0f, 1.0f, 1.0f);


	// Ajout lumi�re ambiante
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);





    	// Ajout lumi�re positionnelle L0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);        // lumi�re diffuse
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);         // position

	// Ajout lumi�re positionnelle L1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor1);       // lumi�re sp�culaire
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


	xo=R*cos(beta)*sin(alpha);//R cos beta sin alpha
	yo=R*sin(beta);//R sin beta
	zo=R*cos(beta)*cos(alpha);//R cos alpha cos beta
	//beta�[-PI/2 ; PI/2]
	//alpha�[0; 2PI]

	xi=R*cos(beta)*sin(alpha)+xo;
	yi=R*sin(beta)+yo;
	zi=R*cos(beta)*cos(alpha)+zo;

	//xo=xo+t*(xi-xo);

	xo+=t*(xi-xo);
	yo+=t*(yi-yo);
	zo+=t*(zi-zo);

	gluLookAt(xo,yo,zo
           ,xi,yi,zi
           ,0,1,0);

/** TORSE**/
    /** TORSE PREMIERE PARTIE - LA PLUS HAUTE **/
    glPushMatrix();
        create_cylinder(90,2,2,4);
    glPopMatrix();

    /** TORSE DEUXIEME PARTIE **/
    glPushMatrix();
        glTranslatef(0,-4,0);
        create_cylinder(90,1,1,1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-5,0);
        create_cylinder(90,2,2,0.5);
    glPopMatrix();



/**BRAS GAUCHE**/
glPushMatrix();
  /*glTranslatef(1,0,0);
      glRotatef(epaule,0,2,1);*/
  glTranslatef(1,-0.5,-2);
  create_quadrilateral(2,1,1);

    glTranslatef(1,0,0);
    glutSolidSphere(0.5,16,32);

    glRotatef(coude,0,0,1);
    glTranslatef(1,0,0);
    create_quadrilateral(2,1,1);
glPopMatrix();


/** BRAS DROIT**/

glPushMatrix();
    /*glTranslatef(1,0,0);
        glRotatef(epaule,0,2,1);*/
    glTranslatef(1,-0.5,2);
    create_quadrilateral(2,1,1);

    glTranslatef(1,0,0);
    glutSolidSphere(0.5,16,32);

    glRotatef(coude,0,0,1);
    glTranslatef(1,0,0);
    create_quadrilateral(2,1,1);


glPopMatrix();


/** TETE**/


/** JAMBE GAUCHE**/
    glPushMatrix();
        glTranslatef(0,-6.5,-1);
        create_quadrilateral(1,2.5,1);

        glTranslatef(0,-1,0);
        glutSolidSphere(0.5,16,32);
        create_cylinder(90,0.5,0.5,2.5);

        create_quadrilateral(2,0.5,1);
    glPopMatrix();


/** JAMBE DROITE**/
    glPushMatrix();
        glTranslatef(0,-6.5,1);
        create_quadrilateral(1,2.5,1);

        glTranslatef(0,-1,0);
        glutSolidSphere(0.5,16,32);
        create_cylinder(90,0.5,0.5,2.5);

        create_quadrilateral(2,0.5,1);
    glPopMatrix();

/**ROUE**/
    int plop=0;
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();

        glRotatef(roue,0,0,1);
        glColor3d(1,1,1);
        glPushMatrix();
        glRotatef(90,0,0,1);
            glPushMatrix();
                gluQuadricDrawStyle(params,GLU_FILL);
                gluCylinder(params, 1, 1, 0.5, 16, 32);
            glPopMatrix();

            glPushMatrix();
                gluDisk(params,0,1,16,32);
            glPopMatrix();

            glTranslatef(0,0,0.5);
            glPushMatrix();
                gluDisk(params,0,1,16,32);
            glPopMatrix();

        glTranslatef(-0.5,1.2,-0.3);
        glRotatef(45,0,0,1);
        glRotatef(180,0,0,-1);
        for(;plop<8;plop++){

            glTranslatef(1,0.0,0.0);
            glRotatef(45,0,0,1);
            glPushMatrix();
            pic();
            glPopMatrix();
        }

        gluDeleteQuadric(params);
    glPopMatrix();



	glutSwapBuffers();

	/* On force l'affichage */
	glFlush();
}



/*Fonction des pics sur la roue*/

void pic(){
    float a[3]= {0.0,0.0,0.0};
    float b[3]= {0.3,  0.3,  0.3 };
    float c[3]= {0.3,  0.3, -0.2 };
    float d[3]= {-0.3,  0.3, -0.2 };
    float e[3]= { -0.3,  0.3,  0.3 };

        glBegin(GL_POLYGON);
        glVertex3f(c[0],c[1],c[2]);
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f(d[0],d[1],d[2]);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex3f( b[0],b[1],b[2]);
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f( e[0],e[1],e[2] );
        glEnd();

        glBegin(GL_POLYGON);
        glVertex3f( b[0],b[1],b[2]);
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f( c[0],c[1],c[2] );
        glEnd();


        glBegin(GL_POLYGON);
        glVertex3f(e[0],e[1],e[2]);
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f(d[0],d[1],d[2] );
        glEnd();


        glBegin(GL_POLYGON);
        glColor3d(1,0,0);glVertex3f(b[0],b[1],b[2]);
        glColor3d(0,1,0);glVertex3f(c[0],c[1],c[2]);
        glColor3d(0,0,1);glVertex3f(d[0],d[1],d[2]);
        glColor3d(1,1,1);glVertex3f(e[0],e[1],e[2]);
        glEnd();

}
/* Fonction de mise � jour: mouvements des objets*/
void update(int value){
    roue+=5;
    if (coude >= 60.0){
		bras1=1;
	}
	if(coude <=0)
    {
        bras1=0;
    }
    if(bras1==0)
    {
        coude += 1;
    }
	else if(bras1==1)
    {
        coude -= 1;
    }


    if (epaule >= 45.0){
		bras2=1;
	}
	if(epaule <= 0.0)
    {
        bras2=0;
    }
    if(bras2==0)
    {
        epaule += 1;
    }
	 if(bras2==1)
    {
        epaule -= 1;
    }
	glutPostRedisplay();
	glutTimerFunc(10,update, 0);


}


/*  Mise en forme de la sc�ne pour l'affichage */
void reshape(int w, int h){
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,	200.0);
}



/* Fonction de gestion au clavier des activations des lumi�res */
void keyboard(unsigned char key, int x, int y) {
		switch (key){

        case'o':
            beta +=((M_PI/2)/50);
            break;
        case 'l':
            beta -=((M_PI/2)/50);
            break;
        case 'm':
            alpha +=((2*M_PI)/50);
            break;
        case 'k':
            alpha -=((M_PI*2)/50);
            break;
        case 'p':
            R -=0.5;
            break;
        case 'i':
            R +=0.5;
            break;
        case 'z':
            t-=0.3;
            break;
        case 's':
            t+=0.3;
            break;
        case 'q':
            alpha += xo;

			case 'a':   /* activation lumi�re n�0 */
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glutPostRedisplay();
				break;

			case 'b':   /* activation lumi�re n�1*/
				glEnable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT2);
				glEnable(GL_LIGHT1);
				glutPostRedisplay();
				break;

            case 'c':   /* activation lumi�re n�2*/
				glEnable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
				glutPostRedisplay();
				break;

			case 'n':   /* activation des lumi�res  */
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
				glutPostRedisplay();
				break;

			case 'L':   /* d�sactivation des lumi�res  */
				glDisable(GL_LIGHTING);
				glutPostRedisplay();
				break;
				exit(0);
		}
}


/** FONCTION DE CREATION DE FORME **/

void create_quadrilateral(float x, float y, float z){
    glPushMatrix();
        glScalef(x, y, z);
        glutSolidCube(1);
    glPopMatrix();
}

void create_cylinder(float angle, float base, float top, float height){
    GLUquadric* params;
    params = gluNewQuadric();

        glPushMatrix();
            glRotatef(angle,1,0,0);
            gluQuadricDrawStyle(params,GLU_FILL);
            gluCylinder(params, base, top, height, 16, 32);   //quad,base,top,height,slices,stacks
        glPopMatrix();

        glPushMatrix();
            glRotatef(angle,1,0,0);
            gluDisk(params,0,base,16,32);
        glPopMatrix();

        glTranslatef(0,-height,0);
        glPushMatrix();
            glRotatef(angle,1,0,0);
            gluDisk(params,0,base,16,32);
        glPopMatrix();

    gluDeleteQuadric(params);
}
