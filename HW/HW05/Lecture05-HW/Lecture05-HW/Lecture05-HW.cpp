#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

//학번 : 202127064
//이름 : 이지호
float zoom = 1.0f;
double StartX, StartY;
bool dragging = false;
bool ScalePM = false;
float cameraX = 0.0f;
float cameraY = 0.0f;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { // 왼쪽 버튼 클릭 시, 드래그 ON 크기 확대 OFF
        dragging = true;
        ScalePM = false;
        glfwGetCursorPos(window, &StartX, &StartY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) { // 오른쪽 버튼 클릭 시, 드래그 OFF 크기 확대 ON
        dragging = true;
        ScalePM = true;
        glfwGetCursorPos(window, &StartX, &StartY);
    }
    else if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_RELEASE) {
        dragging = false; 
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (dragging) {
        float sen = 0.01f; // 마우스 감도 설정
        float X = xpos - StartX; // 초기 X좌표 설정
        float Y = ypos - StartY; // 초기 Y좌표 설정
        if (ScalePM) { //별 확대 축소
            if (X > 0) { // 마우스의 커서가 +X좌표에 있으면 별의 스케일을 키움
                zoom *= (1.0f + sen * X);
                if (zoom <= 0.05f) // 별의 최소 크기 제한
                {
                    zoom = 0.05f;
                }
            }
            else if (X < 0) { // 마우스의 커서가 -X좌표에 있으면 별의 스케일을 줄임
                zoom /= (1.0f - sen * X);
                if (zoom <= 0.05f) // 별의 최소 크기 제한
                {
                    zoom = 0.05f;
                }
            }
        }
        else { // 별의 이동 제어
            cameraX -= sen * X;
            cameraY += sen * Y;
        }
        StartX = xpos; // 좌표 받아오기
        StartY = ypos;
    }
}

void setProjection() {
    glMatrixMode(GL_PROJECTION); //화면의 시점과 원근 투영 설정하는 모드(행렬 지정 모드)
    glLoadIdentity(); //행렬 속성 초기화
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f); //화면의 정육면체로 뽑아서 좌,우,하,상 공간을 설정하고 1~100의 크기까지 투영하여 원근감을 나타냄.  
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 모드로 전환
}

void drawStar() {
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 1.0f);
    //점1
    glVertex2f(0.2f, 0.1f);
    //점2
    glVertex2f(0.8f, 0.1f);
    //점3
    glVertex2f(0.3f, -0.3f);
    //점4
    glVertex2f(0.5f, -0.8f);
    //점5
    glVertex2f(0.0f, -0.5f);
    //점6
    glVertex2f(-0.5f, -0.8f);
    //점7
    glVertex2f(-0.3f, -0.3f);
    //점8
    glVertex2f(-0.8f, 0.1f);
    //점9
    glVertex2f(-0.2f, 0.1f);
    //점10
    glVertex2f(0.0f, 0.8f);

    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1200, 800, "Counting Star", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        setProjection();

        glLoadIdentity();
        glTranslatef(-cameraX, -cameraY, -5.0f); // 별 이동 좌표
        glScalef(zoom, zoom, 1.0f); // 별 크기 좌표

        //별 그리기
        drawStar();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}