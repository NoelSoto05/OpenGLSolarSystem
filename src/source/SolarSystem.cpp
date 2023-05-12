#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"
#include "model.h"
#include "filesystem.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);
void createSphere(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

// settings
const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 1200;

// camera
// Position the camera slightly higher and look towards the center.
Camera camera(glm::vec3(0.0f, 25.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -45.0f);


float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool rotFlg1 = false;
float angle = 0.0f;

//sphere properties
//unsigned int sphereVAO;
//unsigned int sphereVBO, sphereEBO;
unsigned int indexCount;
//sun VAO
unsigned int sunVAO, sunVBO, sunEBO;
//earth VAO
unsigned int earthVAO, earthVBO, earthEBO;
//Mercury VAO
unsigned int mercVAO, mercVBO, mercEBO;
//Venus VAO
unsigned int venusVAO, venusVBO, venusEBO;
//Mars VAO
unsigned int marsVAO, marsVBO, marsEBO;
//Jupiter VAO
unsigned int jupiterVAO, jupiterVBO, jupiterEBO;
// saturn VAO
unsigned int saturnVAO, saturnVBO, saturnEBO;
//uranus VAO
unsigned int uranusVAO, uranusVBO, uranusEBO;
//neptune VAO
unsigned int neptuneVAO, neptuneVBO, neptuneEBO;

//planet textures

unsigned int sunTexture;
unsigned int mercTexture;
unsigned int venusTexture;
unsigned int earthTexture;
unsigned int marsTexture;
unsigned int jupiterTexture;
unsigned int saturnTexture;
unsigned int uranusTexture;
unsigned int neptuneTexture;




int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Final Project Solar System/Planets Noel Soto", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader shader("../../src/shader/6.4.cubemaps.vert", "../../src/shader/6.4.cubemaps.frag");
    Shader skyboxShader("../../src/shader/6.4.skybox.vert", "../../src/shader/6.4.skybox.frag");

    //sphere Shaders

    Shader sphereShader("../../src/shader/sphereVert.vert", "../../src/shader/sphereFrag.frag");


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
   

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    /*Creating the sphere for each planet, each has their own VAO, VBO, and EBO so that i can perform different actions on each one*/
    //sun sphere
    createSphere(sunVAO, sunVBO, sunEBO);
    //mercury sphere
    createSphere(mercVAO, mercVBO, mercEBO);
    //venus sphere
    createSphere(venusVAO, venusVBO, venusEBO);
    //earth sphere
    createSphere(earthVAO, earthVBO, earthEBO);
    //mars sphere
    createSphere(marsVAO, marsVBO, earthEBO);
    //jupiter sphere
    createSphere(jupiterVAO, jupiterVBO, jupiterEBO);
    //saturn sphere
    createSphere(saturnVAO, saturnVBO, saturnEBO);
    //uranus sphere
    createSphere(uranusVAO, uranusVBO, uranusEBO);
    //neptune sphere
    createSphere(neptuneVAO, neptuneVBO, neptuneEBO);


   
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // load textures
    // ------------- textures for planets

    sunTexture = loadTexture("../../src/resources/textures/planets/2k_sun.jpg");
    mercTexture = loadTexture("../../src/resources/textures/planets/2k_mercury.jpg");
    venusTexture = loadTexture("../../src/resources/textures/planets/2k_venus.jpg");
    earthTexture = loadTexture("../../src/resources/textures/planets/earth2k.jpg");
    marsTexture = loadTexture("../../src/resources/textures/planets/2k_mars.jpg");
    jupiterTexture = loadTexture("../../src/resources/textures/planets/2k_jupiter.jpg");
    saturnTexture = loadTexture("../../src/resources/textures/planets/2k_saturn.jpg");
    uranusTexture = loadTexture("../../src/resources/textures/planets/2k_uranus.jpg");
    neptuneTexture = loadTexture("../../src/resources/textures/planets/2k_neptune.jpg");



    //textures for skybox
    vector<std::string> faces
    {
        FileSystem::getPath("resources/textures/skybox/blue/bkg1_right.png"),
        FileSystem::getPath("resources/textures/skybox/blue/bkg1_left.png"),
        FileSystem::getPath("resources/textures/skybox/blue/bkg1_top.png"),
        FileSystem::getPath("resources/textures/skybox/blue/bkg1_bot.png"),
        FileSystem::getPath("resources/textures/skybox/blue/bkg1_front.png"),
        FileSystem::getPath("resources/textures/skybox/blue/bkg1_back.png"),
    };
    unsigned int cubemapTexture = loadCubemap(faces);

    // shader configuration
    // --------------------
    shader.use();
    shader.setInt("skybox", 0);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
    // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        // activate sphere shader
        sphereShader.use();

        // set shader uniforms
        sphereShader.setMat4("view", view);
        sphereShader.setMat4("projection", projection);
        sphereShader.setVec3("cameraPos", camera.Position);

        // Time Warping
        float timeScale = 10.0f; // speed up time so that 1 real second = 1 simulation year
        float simulationTime = timeScale * (float)glfwGetTime(); // this gives the time in simulation days since the program started
        float sizeScale = 2.0;

        // Draw the sun
        glm::mat4 sunModel = glm::mat4(1.0f);

        // rotate the sun around its own y-axis
        // The Sun rotates approximately once every 27 Earth days near its equator.
        float sunRotationSpeed = simulationTime / 27.0f;
        sunModel = glm::rotate(sunModel, sunRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

        sunModel = glm::scale(sunModel, glm::vec3(2.0f, 2.0f, 2.0f)); // scale the sun

        sphereShader.setMat4("model", sunModel);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTexture);
        glBindVertexArray(sunVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);



        // Draw Mercury
        glm::mat4 mercModel = glm::mat4(1.0f); // reset model matrix 

        // Mercury's rotation period is 58.6 Earth days
    // Mercury's year is 88 Earth days
        float mercRotationSpeed = simulationTime / 86.6f;
        float mercOrbitSpeed = simulationTime / 88.0f;

        // Rotate Mercury around the Sun
        float mercOrbitRadius = 5.0f;
        mercModel = glm::translate(mercModel, glm::vec3(mercOrbitRadius * cos(mercOrbitSpeed), 0.0f, mercOrbitRadius * sin(mercOrbitSpeed))); // move the planet in a circular path
        mercModel = glm::rotate(mercModel, mercRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate the planet around its own y-axis

        mercModel = glm::scale(mercModel, glm::vec3(0.10f * sizeScale, 0.10f * sizeScale, 0.10f * sizeScale)); // scale down the planet
        sphereShader.setMat4("model", mercModel);
        glBindTexture(GL_TEXTURE_2D, mercTexture);
        glBindVertexArray(mercVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

        // Draw Venus
        glm::mat4 venusModel = glm::mat4(1.0f); // reset model matrix 

        float venusRotationSpeed = simulationTime / 90.0f;
        float venusOrbitSpeed = simulationTime / 225.0f;

        // Rotate venus around the Sun
        float VenusOrbitRadius = 10.0f;
        venusModel = glm::translate(venusModel, glm::vec3(VenusOrbitRadius * cos(venusOrbitSpeed), 0.0f, VenusOrbitRadius * sin(venusOrbitSpeed)));
        venusModel = glm::rotate(venusModel, venusRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

        venusModel = glm::scale(venusModel, glm::vec3(0.095f * sizeScale, 0.095f * sizeScale, 0.095f * sizeScale)); // scale down the planet
        sphereShader.setMat4("model", venusModel);
        glBindTexture(GL_TEXTURE_2D, venusTexture);
        glBindVertexArray(venusVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

        // Draw the earth
        glm::mat4 earthModel = glm::mat4(1.0f); // reset model matrix 

        // Earth: rotation period = 1 Earth day, year = 1 Earth year
        float earthRotationSpeed = simulationTime/ 10;
        float earthOrbitSpeed = simulationTime/ 200;

        // Rotate the Earth around the Sun
        float earthOrbitRadius = 15.0f;
        earthModel = glm::translate(earthModel, glm::vec3(earthOrbitRadius * cos(earthOrbitSpeed), 0.0f, earthOrbitRadius * sin(earthOrbitSpeed)));
        earthModel = glm::rotate(earthModel, earthRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

        earthModel = glm::scale(earthModel, glm::vec3(0.1f * sizeScale, 0.1f * sizeScale, 0.1f * sizeScale)); // scale down the planet
        sphereShader.setMat4("model", earthModel);
        glBindTexture(GL_TEXTURE_2D, earthTexture);
        glBindVertexArray(earthVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

        // Draw mars
        glm::mat4 marsModel = glm::mat4(1.0f); // reset model matrix 

        // Mars: rotation period = 1.03 Earth days, year = 1.88 Earth years
        float marsRotationSpeed = simulationTime / 10.5f;
        float marsOrbitSpeed = simulationTime / 10.88f;

        // Rotate around the Sun
        float marsOrbitRadius = 20.0f;
        marsModel = glm::translate(marsModel, glm::vec3(marsOrbitRadius * cos(marsOrbitSpeed), 0.0f, marsOrbitRadius * sin(marsOrbitSpeed)));
        marsModel = glm::rotate(marsModel, marsRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

        marsModel = glm::scale(marsModel, glm::vec3(0.053f * sizeScale, 0.053f * sizeScale, 0.053f * sizeScale)); // scale down the planet
        sphereShader.setMat4("model", marsModel);
        glBindTexture(GL_TEXTURE_2D, marsTexture);
        glBindVertexArray(marsVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

        // Draw Jupiter
        glm::mat4 jupiterModel = glm::mat4(1.0f); // reset model matrix 

        // Jupiter: rotation period = 0.41 Earth days, year = 11.86 Earth years
        float jupiterRotationSpeed = simulationTime / 0.41f;
        float jupiterOrbitSpeed = simulationTime / 11.86f;

        // Rotate around the Sun
        float jupiterOrbitRadius = 25.0f;
        jupiterModel = glm::translate(jupiterModel, glm::vec3(jupiterOrbitRadius * cos(jupiterOrbitSpeed), 0.0f, jupiterOrbitRadius * sin(jupiterOrbitSpeed)));
        jupiterModel = glm::rotate(jupiterModel, jupiterRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

        jupiterModel = glm::scale(jupiterModel, glm::vec3(1.0f , 1.0f , 1.0f )); // scale down the planet
        sphereShader.setMat4("model", jupiterModel);
        glBindTexture(GL_TEXTURE_2D, jupiterTexture);
        glBindVertexArray(jupiterVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);


        // Draw saturn
        glm::mat4 saturnModel = glm::mat4(1.0f); // reset model matrix 

        // Saturn: rotation period = 0.45 Earth days, year = 29.46 Earth years
        float saturnRotationSpeed = simulationTime / 0.45f;
        float saturnOrbitSpeed = simulationTime / 29.46f;

        // Rotate around the Sun
        float saturnOrbitRadius = 30.0f;
        saturnModel = glm::translate(saturnModel, glm::vec3(saturnOrbitRadius * cos(saturnOrbitSpeed), 0.0f, saturnOrbitRadius * sin(saturnOrbitSpeed)));
        saturnModel = glm::rotate(saturnModel, saturnRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

        saturnModel = glm::scale(saturnModel, glm::vec3(0.83f , 0.83f , 0.83f )); // scale down the planet
        sphereShader.setMat4("model", saturnModel);
        glBindTexture(GL_TEXTURE_2D, saturnTexture);
        glBindVertexArray(saturnVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

        // Draw Uranus
        glm::mat4 uranusModel = glm::mat4(1.0f); // reset model matrix 

        // Uranus: rotation period = 0.72 Earth days, year = 84 Earth years
        float uranusRotationSpeed = simulationTime / 0.72f;
        float uranusOrbitSpeed = simulationTime / 84.0f;

        // Rotate uranus around the Sun
        float uranusOrbitRadius = 35.0f;
        uranusModel = glm::translate(uranusModel, glm::vec3(uranusOrbitRadius * cos(uranusOrbitSpeed), 0.0f, uranusOrbitRadius * sin(uranusOrbitSpeed)));
        uranusModel = glm::rotate(uranusModel, uranusRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
      
        uranusModel = glm::scale(uranusModel, glm::vec3(0.36f * sizeScale, 0.36f * sizeScale, 0.36f * sizeScale)); // scale down the planet
        sphereShader.setMat4("model", uranusModel);
        glBindTexture(GL_TEXTURE_2D, uranusTexture);
        glBindVertexArray(uranusVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

      
        // Draw neptune
        glm::mat4 neptuneModel = glm::mat4(1.0f); // reset model matrix 

        // Neptune's rotation period is 0.67 Earth days
        // Neptune's year is 165 Earth years
        float neptuneRotationSpeed = simulationTime / 0.67f;
        float neptuneOrbitSpeed = simulationTime / 165.0f; 

        // Rotate around the Sun
        float neptuneOrbitRadius = 40.0f;
        // Rotate Neptune around the Sun
        neptuneModel = glm::translate(neptuneModel, glm::vec3(neptuneOrbitRadius * cos(neptuneOrbitSpeed), 0.0f, neptuneOrbitRadius * sin(neptuneOrbitSpeed))); // move the planet in a circular path
        neptuneModel = glm::rotate(neptuneModel, neptuneRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate the planet around its own y-axis

        neptuneModel = glm::scale(neptuneModel, glm::vec3(0.35f * sizeScale, 0.35f * sizeScale, 0.35f* sizeScale)); // scale down the planet
        sphereShader.setMat4("model", neptuneModel);
        glBindTexture(GL_TEXTURE_2D, neptuneTexture);
        glBindVertexArray(neptuneVAO);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
        


        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

 


    glfwTerminate();
    return 0;
}
//create a shphere 
void createSphere(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<unsigned int> indices;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
        }
    }

    bool oddRow = false;
    for (int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) //even rows: y == 0, y == 2; and so on
        {
            for (int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    indexCount = indices.size();

    std::vector<float> data;
    for (int i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i].x);
        data.push_back(positions[i].y);
        data.push_back(positions[i].z);
        if (uv.size() > 0)
        {
            data.push_back(uv[i].x);
            data.push_back(uv[i].y);
        }
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    float stride = (3 + 2) * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        rotFlg1 = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        rotFlg1 = false;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

