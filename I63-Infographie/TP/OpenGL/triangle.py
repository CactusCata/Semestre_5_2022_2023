from OpenGL.GL import *  # exception car prefixe systematique
from OpenGL.GLU import *
from OpenGL.GLUT import *

y = 1.0
x = 1.0
rot = 0.0
bayer = True

def init():
    # Permet de normaliser les normales des sommets
    #glEnable(GL_NORMALIZE)
    # Permet de rendre les faces avant, arrière ou les deux
    #glEnable(GL_CULL_FACE)
    # Permet l'application d'une matrice de Bayer pour
    # donner l'illusion de smooth pour une bande de couleur
    # qui possède peu de différentes couleurs
    #glEnable(GL_DITHER)
    glClearColor(0.0, 0.0, 0.0, 0.0)
    #glShadeModel(GL_FLAT)

def display():
    # Clear l'ecran
    glClear(GL_COLOR_BUFFER_BIT)

    glBegin(GL_POLYGON)

    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(0.0, 1.0, 0.0)

    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(1.0, -1.0, 0.0)

    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(-1.0, -1.0, 0.0)

    glEnd()

    glutSwapBuffers()

def keyboard(key, _x, _y):
    global x, y, rot, bayer
    key = key.decode('utf-8')
    if key == 'q':
        x += 0.1
    elif key == 'd':
        x -= 0.1
    elif key == 'z':
        y += 0.1
    elif key == 's':
        y -= 0.1
    elif key == 'r':
        rot += 10
    elif key == 'b':
        if (bayer):
            bayer = False
            glDisable(GL_DITHER)
        else:
            bayer = True
            glEnable(GL_DITHER)
    elif key == '\033':
        # sys.exit( )  # Exception ignored
        glutLeaveMainLoop()
    glutPostRedisplay()  # indispensable en Python

def reshape(width, height):
    # On dis que la fenetre de dessin fait toute la fenetre
    glViewport(0, 0, width, height)

    # indique à OpenGL que les opérations de transformation 
    # suivantes doivent être appliquées à la matrice de projection
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if width <= height:
        glOrtho(-2.5, 2.5, -2.5*height/width, 2.5*height/width, -10.0, 10.0)
    else:
        glOrtho(-2.5*width/height, 2.5*width/height, -2.5, 2.5, -10.0, 10.0)
    glMatrixMode(GL_MODELVIEW)

if __name__ == "__main__":

    glutInit(len(sys.argv), sys.argv)
    # Option GLUT_DOUBLE: travail avec deux buffer d'affichage: c'est un swap buffer
    # Option GLUT_RGBA  : travail avec le quadruplet rouge,vert,bleu,alpha
    # Option GLUT_DEPTH : travail avec un buffer de profondeur (le Z-buffer)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)

    glutCreateWindow('test')
    glutReshapeWindow(512,512)

    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)

    init()

    glutMainLoop()