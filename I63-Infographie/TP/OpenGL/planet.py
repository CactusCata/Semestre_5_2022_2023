#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

###############################################################
# portage de planet.c

from OpenGL.GL import *  # exception car prefixe systematique
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

###############################################################
# variables globales
year, day = 0, 0
quadric = None

###############################################################
# 

def init():
    global quadric
    glClearColor(0.0, 0.0, 1.0, 0.0)
    glShadeModel(GL_FLAT)
    quadric = gluNewQuadric()
    gluQuadricDrawStyle(quadric, GLU_LINE)

def display():
    glClear (GL_COLOR_BUFFER_BIT)
    glColor4f (1.0, 1.0, 1.0, 1.0)

    glPushMatrix()
    gluSphere(quadric, 1.0, 15, 15)
    glRotatef(year, 0.0, 1.0, 0.0)
    glTranslatef(2.0, 0.0, 0.0)
    glRotatef(day, 0.0, 1.0, 0.0)
    gluSphere(quadric, 0.2, 10, 8)
    glPopMatrix()

    glutSwapBuffers()

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

def keyboard(key, x, y):
    global day, year
    key = key.decode('utf-8')
    if key == 'j':
        day = (day + 10) % 360
    elif key == 'a':
        year = (year + 5) % 360
    elif key == 's':
        year = (year + 1) % 360
        pass
    elif key == '\033':
        # sys.exit( )  # Exception ignored
        glutLeaveMainLoop()
    glutPostRedisplay()  # indispensable en Python

###############################################################
# MAIN

glutInit(len(sys.argv), sys.argv)
# Option GLUT_DOUBLE: travail avec deux buffer d'affichage: c'est un swap buffer
# Option GLUT_RGBA  : travail avec le quadruplet rouge,vert,bleu,alpha
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA)

glutCreateWindow('planet')
glutReshapeWindow(512,512)

glutReshapeFunc(reshape)
glutDisplayFunc(display)
glutKeyboardFunc(keyboard)

init()

glutMainLoop()
