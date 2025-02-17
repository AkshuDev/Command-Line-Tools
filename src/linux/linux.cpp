#include <iostream>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

void DrawQuadrilateral() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.f, 1.f, -1.f, 1.f, 20.f);

    glMatrixMode(GL_MODEL_VIEW);
    glLoadIdentity();
    gluLookAt(0.f, 0.f, 10.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

    glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f); glVertex3f(-0.75f, -0.75f, 0.f);
        glColor3f(0.f, 1.f, 0.f); glVertex3f(0.75f, -0.75f, 0.f);
        glColor3f(0.f, 0.f, 1.f); glVertex3f(0.75f, 0.75f, 0.f);
        glColor3f(1.f, 1.f, 0.f); glVertex3f(-0.75f, 0.75f, 0.f);
    glEnd();
}

int main(int argc, char *argv[]){
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        std::cerr << "Error: Could not open display." << std::endl;
        return 1;
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy);

    if (vi == NULL) {
        std::cerr << "Error: No appropriate visual found." << std::endl;
        return 2;
    } else {
        std::cout << "Visual " << vi->visualid << " selected." << std::endl;
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "");
}