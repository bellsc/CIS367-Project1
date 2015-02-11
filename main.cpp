#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <algorithm>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>
#include "TvStand.h"
#include "Tv.h"
#include "Bookcase.h"
#include "Cartridge.h"
#include "Cd.h"

#undef GLFW_DLL
#include <GLFW/glfw3.h>

using namespace std;

TvStand tvStand;
Tv tv;
Bookcase bookcase;
Cartridge grayCart, blackCart, redCart, yellowCart;
UnitCube redGame, greenGame, whiteGame, blackGame;
UnitCube wii, clck, xbox;
Cd cd;
vector<Cd> cds;
vector<pair<GLushort,glm::vec3>> cdRandRotations;

bool show_lines = false;

void init_model();
void win_refresh(GLFWwindow*);
float arc_ball_rad_square;
int screen_ctr_x, screen_ctr_y;

glm::mat4 camera_cf; // {glm::translate(glm::mat4(1.0f), glm::vec3{0,0,-5})};
glm::mat4 tv_cf, stand_cf, cartridge_cf, game_cf, topCd_cf, topGame_cf;
vector<glm::mat4*> cfs;
short cf_index = 0;


void err_function (int what, const char *msg) {
    cerr << what << " " << msg << endl;
}


void win_resize (GLFWwindow * win, int width, int height)
{
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    screen_ctr_x = w / 2.0;
    screen_ctr_y = h / 2.0;
    float rad = min(h,w)/2;
    arc_ball_rad_square = rad * rad;
    /* Use the entire window for our view port */
    glViewport(0, 0, width, height);
    /* Use GL_PROJECTION to select the type of synthetic camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* near-plane(1) & far-plane(10) are always POSITIVE and they measure
     * the distances along the Z-axis in front of the camera */
    gluPerspective(60.0, static_cast<float> (width)/ static_cast<float> (height), 1, 30);
}

void win_refresh (GLFWwindow *win) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    /* place the camera using the camera coordinate frame */
    glMultMatrixf (glm::value_ptr(camera_cf));


    /* draw the axes */
/*
    glBegin(GL_LINES);
    glColor3ub (255, 0, 0);
    glVertex2i (0, 0);
    glVertex2f (S * 1.1, 0);
    glColor3ub (0, 255, 0);
    glVertex2i (0, 0);
    glVertex2f (0, S * 1.1);
    glColor3ub (0, 0, 255);
    glVertex2i (0, 0);
    glVertex3f (0, 0, S * 1.1);
    glEnd();

*/
    //Tv
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(tv_cf));
    tv.render(show_lines);
    glPopMatrix();

    //tvStand
    glPushMatrix();
    glTranslatef(0,-1.912,0);
    glScalef(1.2,1,1);
    glMultMatrixf(glm::value_ptr(stand_cf));
    tvStand.render(show_lines);
    glPopMatrix();

    //Bookcase
    glPushMatrix();
    glTranslatef(3.6,-2.8,0);
    glScalef(1.7,1.3,1);
    bookcase.render(show_lines, 4);
    glPopMatrix();

    //Cartridge
    glPushMatrix();
    glTranslatef(3.8,-1.94,.1);
    glRotatef(90,0,1,0);
    grayCart.render(show_lines);
    glTranslatef(-.05,0,.1);
    grayCart.render(show_lines);
    glTranslatef(.05,0,.1);
    blackCart.render(show_lines);
    glTranslatef(0,0,.1);
    redCart.render(show_lines);
    glTranslatef(-.08,0,.1);
    grayCart.render(show_lines);
    glTranslatef(0,0,.1);
    yellowCart.render(show_lines);
    glPopMatrix();

    //Bottom shelf cartridge
    glPushMatrix();
    glTranslatef(3.6,-3.35,0);
    glMultMatrixf(glm::value_ptr(cartridge_cf));
    glRotatef(-90,1,0,0);
    glRotatef(-20,0,0,1);
    grayCart.render(show_lines);
    glPopMatrix();

    //Game cases on shelf
    glPushMatrix();
    glRotatef(-20,0,0,1);
    glTranslatef(.64,-.90,0);
    glScalef(.08,1.08,.8);

    short gameMove = 0;
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    whiteGame.render(show_lines);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    blackGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);

    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    whiteGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    greenGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    redGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    blackGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    redGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    greenGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    whiteGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove++,0,0);
    blackGame.render(show_lines);
    glPopMatrix();

    glTranslatef(0,.03,0);
    glPushMatrix();
    glTranslatef(gameMove,0,0);
    redGame.render(show_lines);
    glPopMatrix();

    glPopMatrix();

    //Game in cabinet
    glPushMatrix();
    glTranslatef(.65,-3.35,0);
    glMultMatrixf(glm::value_ptr(game_cf));
    glScalef(1.08,.08,.8);
    redGame.render(show_lines);
    glPopMatrix();

    //Game on bookshelf
    glPushMatrix();
    glTranslatef(3.4,1.7,.15);
    glMultMatrixf(glm::value_ptr(topGame_cf));
    glScalef(.8,.08,1.08);
    greenGame.render(show_lines);
    glPopMatrix();

    //wii
    glPushMatrix();
    glTranslatef(3.35,-2,.1);
    glScalef(.7,.24,1.02);
    wii.render(show_lines);
    glPopMatrix();

    //xbox
    glPushMatrix();
    glTranslatef(3.6,-.63,.2);
    glScalef(1.3,.4,.8);
    xbox.render(show_lines);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.4,-.57,.60);
    glScalef(.6,.1,.02);
    whiteGame.render(show_lines);
    glPopMatrix();

    //clock
    glPushMatrix();
    glTranslatef(3.6,.59,.2);
    glScalef(1.4,.3,.8);
    xbox.render(show_lines);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.64,.57,.60);
    glScalef(1.3,.15,.02);
    blackGame.render(show_lines);
    glPopMatrix();

    //CDs on shelf
    glPushMatrix();
    glTranslatef(-.6,-1.53,0);
    glRotatef(90,1,0,0);
    cds[4].render(show_lines);

    glTranslatef(.03,.04,-.05);
    cds[0].render(show_lines);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-.52,-1.43,.1);
    glMultMatrixf(glm::value_ptr(topCd_cf));
    glRotatef(90,1,0,0);
    cds[1].render(show_lines);
    glPopMatrix();

    //Floating CDs
    for(float i = 0; i < 10; i++){
        glPushMatrix();
        glTranslatef(-3.5,3.8 - i*.9,-1.2);
        glRotatef(cdRandRotations[i].first, cdRandRotations[i].second.x,
                cdRandRotations[i].second.y,
                cdRandRotations[i].second.z);
        cds[(int)i%5].render(show_lines);
        glPopMatrix();
    }

    /* must swap buffer at the end of render function */
    glfwSwapBuffers(win);
}

/* action: GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT */
void key_handler (GLFWwindow *win, int key, int scan_code, int action, int mods)
{
    if (action != GLFW_PRESS) return;

    else {
        glm::mat4 reset;
        switch (key) {

            //Select current CF
            case GLFW_KEY_LEFT:
                if(--cf_index == -1)
                    cf_index = cfs.size()-1;
                cout << cf_index << endl;
                break;
            case GLFW_KEY_RIGHT:
                if(++cf_index == cfs.size())
                    cf_index = 0;
                cout << cf_index << endl;
                break;

            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(win, true);
                break;

                //Show lines
            case GLFW_KEY_L:
                show_lines = !show_lines;
                break;

                //Translate
            case GLFW_KEY_W:    //up
                *cfs[cf_index] = glm::translate(glm::vec3{0, 0.1, 0}) * *cfs[cf_index];
                break;
                //Rotate
            case GLFW_KEY_A:    //left
                *cfs[cf_index] = glm::translate(glm::vec3{-0.1, 0, 0}) * *cfs[cf_index];
                break;
            case GLFW_KEY_S:    //down
                *cfs[cf_index] = glm::translate(glm::vec3{0, -0.1, 0}) * *cfs[cf_index];
                break;
                //Rotate
            case GLFW_KEY_D:    //right
                *cfs[cf_index] = glm::translate(glm::vec3{0.1, 0, 0}) * *cfs[cf_index];
                break;
            case GLFW_KEY_Z:    //back
                *cfs[cf_index] = glm::translate(glm::vec3{0, 0, -0.1}) * *cfs[cf_index];
                break;
            case GLFW_KEY_X:    //forth
                *cfs[cf_index] = glm::translate(glm::vec3{0, 0, 0.1}) * *cfs[cf_index];
                break;

            //Rotate
            case GLFW_KEY_T:    //pos x axis
                *cfs[cf_index] = glm::rotate((float)M_PI/8, glm::vec3{1, 0, 0}) * *cfs[cf_index];
                break;
            case GLFW_KEY_Y:    //pos y axis
                *cfs[cf_index] = glm::rotate((float)M_PI/8, glm::vec3{0, 1, 0}) * *cfs[cf_index];
                break;
            case GLFW_KEY_U:    //pos z axis
                *cfs[cf_index] = glm::rotate((float)M_PI/8, glm::vec3{0, 0, 1}) * *cfs[cf_index];
                break;
            case GLFW_KEY_G:    //neg x axis
                *cfs[cf_index] = glm::rotate((float)-M_PI/8, glm::vec3{1, 0, 0}) * *cfs[cf_index];
                break;
            case GLFW_KEY_H:    //neg y axis
                *cfs[cf_index] = glm::rotate((float)-M_PI/8, glm::vec3{0, 1, 0}) * *cfs[cf_index];
                break;
            case GLFW_KEY_J:    //neg z axis
                *cfs[cf_index] = glm::rotate((float)-M_PI/8, glm::vec3{0, 0, 1}) * *cfs[cf_index];
                break;

                //scale
            case GLFW_KEY_N:    //smaller
                *cfs[cf_index] = glm::scale(*cfs[cf_index],glm::vec3{0.9, 0.9, 0.9});
                break;
            case GLFW_KEY_M:    //bigger
                *cfs[cf_index] = glm::scale(*cfs[cf_index],glm::vec3{1.1, 1.1, 1.1});
                break;


                //camera presets
            case GLFW_KEY_1:    //default
                camera_cf = reset;
                camera_cf *= glm::translate(glm::vec3{0, 0, -8});
                break;
            case GLFW_KEY_2:    //behind looking down
                camera_cf = reset;
                camera_cf = glm::rotate((float)M_PI, glm::vec3{0, 1, 0}) * camera_cf;
                camera_cf = camera_cf * glm::translate(glm::vec3{0, -6, 10}) ;
                camera_cf = glm::rotate((float)M_PI/5, glm::vec3{1, 0, 0}) * camera_cf;
                break;
            case GLFW_KEY_3:    //looking at bookcase
                camera_cf = reset;
               // camera_cf = glm::rotate((float)M_PI, glm::vec3{0, 1, 0}) * camera_cf;
                camera_cf = camera_cf * glm::translate(glm::vec3{-3.5, -1, -4}) ;
                camera_cf = glm::rotate((float)M_PI/5, glm::vec3{1, 0, 0}) * camera_cf;
                break;
            case GLFW_KEY_4:    //looking from CD side
                camera_cf = reset;
                camera_cf = camera_cf * glm::translate(glm::vec3{8, 0, -2}) ;
                camera_cf = glm::rotate((float)M_PI/3, glm::vec3{0, 1, 0}) * camera_cf;
                break;
        }
    }
    win_refresh(win);
}

/*
    The virtual trackball technique implemented here is based on:
    https://www.opengl.org/wiki/Object_Mouse_Trackball
*/
void cursor_handler (GLFWwindow *win, double xpos, double ypos) {
    int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
    static glm::vec3 first_click;
    static glm::mat4 current_cam;
    static bool is_tracking = false;

    glm::vec3 this_vec;
    if (state == GLFW_PRESS) {
        float x = (xpos - screen_ctr_x);
        float y = -(ypos - screen_ctr_y);
        float hypot_square = x * x + y * y;
        float z;

        /* determine whether the mouse is on the sphere or on the hyperbolic sheet */
        if (2 * hypot_square < arc_ball_rad_square)
            z = sqrt(arc_ball_rad_square - hypot_square);
        else
            z = arc_ball_rad_square / 2.0 / sqrt(hypot_square);
        if (!is_tracking) {
            /* store the mouse position when the button was pressed for the first time */
            first_click = glm::normalize(glm::vec3{x, y, z});
            current_cam = camera_cf;
            is_tracking = true;
        }
        else {
            /* compute the rotation w.r.t the initial click */
            this_vec = glm::normalize(glm::vec3{x, y, z});
            /* determine axis of rotation */
            glm::vec3 N = glm::cross(first_click, this_vec);

            /* determine the angle of rotation */
            float theta = glm::angle(first_click, this_vec);

            /* create a quaternion of the rotation */
            glm::quat q{cos(theta / 2), sin(theta / 2) * N};
            /* apply the rotation w.r.t to the current camera CF */
            camera_cf = current_cam * glm::toMat4(glm::normalize(q));
        }
        win_refresh(win);
    }
    else {
        is_tracking = false;
    }
}

void scroll_handler (GLFWwindow *win, double xscroll, double yscroll) {
    /* translate along the camera Z-axis */
    glm::mat4 z_translate = glm::translate((float)yscroll * glm::vec3{0, 0, 1});
    camera_cf =  z_translate * camera_cf;
    win_refresh(win);

}

void init_gl() {
    glEnable (GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
   // glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_CULL_FACE);
    glLineWidth(3.0);

    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    camera_cf *= glm::translate(glm::vec3{0, 0, -8});
}

void make_model() {
    grayCart.build(11, glm::vec3{.5, .5, .5}, 5);
    redCart.build(11, glm::vec3{.9, 0, .1}, 5);
    blackCart.build(11, glm::vec3{.1, .1, .1}, 5);
    yellowCart.build(11, glm::vec3{.9, .9, 0}, 5);
    tvStand.build();
    tv.build();
    bookcase.build();
    cd.build(glm::vec3{0, 0, .8}, 7);

    redGame.build(glm::vec3{.7,.2,.2}, 8);
    greenGame.build(glm::vec3{.2,.7,.2}, 8);
    whiteGame.build(glm::vec3{.7,.7,.7}, 8);
    blackGame.build(glm::vec3{.2,.2,.2}, 8);

    wii.build(glm::vec3{.2,.2,.2}, 5);
    clck.build(glm::vec3{.5,.5,.5}, 6);
    xbox.build(glm::vec3{.32,.32,.32}, 4);

    //different colors of cds
    vector<glm::vec3> cdColors;
    cdColors.push_back(glm::vec3{.8, 0, 0});
    cdColors.push_back(glm::vec3{.8, .8, 0});
    cdColors.push_back(glm::vec3{0, .8, 0});
    cdColors.push_back(glm::vec3{0, .8, .8});
    cdColors.push_back(glm::vec3{0, 0, .8});

    for (int i = 0; i < 5; i++) {
        cds.push_back(Cd{});
    }
    for (int i = 0; i < 5; i++) {
        cds[i].build(cdColors[i], 7);
    }

    for(int i = 0; i < 10; i++)
        cdRandRotations.push_back(make_pair(rand()%360, glm::vec3{rand()%2,rand()%2,rand()%2}));

    tv_cf = glm::scale(tv_cf, glm::vec3{1.2,.9,1});
}

int main() {
    srand(time(NULL));
    cfs.push_back(&tv_cf);
    cfs.push_back(&stand_cf);
    cfs.push_back(&cartridge_cf);
    cfs.push_back(&game_cf);
    cfs.push_back(&topCd_cf);
    cfs.push_back(&topGame_cf);

    if(!glfwInit()) {
        cerr << "Can't initialize GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    glfwSetErrorCallback(err_function);
    GLFWwindow * win;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    win = glfwCreateWindow(100, 50, "Entertainment Center", NULL, NULL);
    if (!win) {
        cerr << "Can't create window" << endl;
        exit (EXIT_FAILURE);
    }

    glfwSetWindowRefreshCallback(win, win_refresh);
    /* On Mac with Retina display there is a discrepancy between units measured in
     * "screen coordinates" and "pixels" */
    // glfwSetWindowSizeCallback(win, win_resize);  /* use this for non-retina displays */
    glfwSetFramebufferSizeCallback(win, win_resize); /* use this for retina displays */
    glfwSetKeyCallback(win, key_handler);
    glfwSetCursorPosCallback(win, cursor_handler);
    glfwSetScrollCallback(win, scroll_handler);
    glfwMakeContextCurrent(win);

    /* glewInit must be invoked AFTER glfwMakeContextCurrent() */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n", glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }

    /* GL functions can be called, only AFTER the window is created */
    const GLubyte *version = glGetString (GL_VERSION);
    printf ("GL Version is %s\n", version);


    glfwSetWindowSize(win, 450, 300);
    glfwSwapInterval(1);
    init_gl();
    make_model();

    int ev_num = 0;
    win_refresh(win);
    while (!glfwWindowShouldClose(win)) {
        glfwWaitEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
