/* Pr�ctica 05: Modelo Jer�rquico                           Daniel Escobar Flores
   Fecha: 07/03/2025                                                    318187952 */

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float
hombro = 0.0f,
codo = 0.0f,
palma = 0.0f,
dedo1 = 0.0f,
dedo2 = 0.0f,
dedo2A = 0.0f,
dedo2B = 0.0f;

int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Pr�ctica 05: Modelado jerarquico - Escobar Flores Daniel", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection


	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp3 = glm::mat4(1.0f);


		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//Model 
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //Se genera la articulaaci�n
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f)); //donde movemos el pivote / Generamos la articulaci�n
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f)); //Tama�o de la caja 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		////Modelo antebrazo 
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar el codo
		model = glm::rotate(model, glm::radians(codo),glm::vec3(0.0f, 1.0f, 0.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f)); //Escalamos y dibujamos 
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B


		////Modelo palma 
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(palma), glm::vec3(0.0f, 1.0f, 0.0f));//Aplicamos la rotaci�n del codo 
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f)); //Ancho, Altura y profundidad
		color = glm::vec3(1.1f, 1.1f, 1.1f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		////---------------------------------------------------------
		//Dedo 1
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.43f)); //Izq-Der, Arriba-Abajo, Adelante-Atras 
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n en z para que vaya de arriba-abajo
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D 

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f)); //Izq-Der, Arriba-Abajo, Adelante-Atras 
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.03f, 0.0f, 0.0f)); //Izq-Der, Arriba-Abajo, Adelante-Atras 
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.35f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Dedo 3 --------------------------------------------------------
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.1f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n en z para que vaya de arriba-abajo
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D 

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.03f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.35f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Dedo 4 --------------------------------------------------------
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, 0.2f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n en z para que vaya de arriba-abajo
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D 

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.03f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.35f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		////--
		//Dedo 4 LISTO ---------------------------------------------------------
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.4f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n en z para que vaya de arriba-abajo
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D 

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.03f, 0.0f, 0.0f)); //Nos recorrimos 1.5 unidades para generar la palma
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.35f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Dedo 5 --------------------------------------------------------
		model = glm::translate(modelTemp2, glm::vec3(0.009f, -0.3f, -0.4f)); //Izq-Der, Arriba-Abajo, Adelante-Atras
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 1.0f, 0.0f));//Aplicamos la rotaci�n en z para que vaya de arriba-abajo
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D 

		//Modelo dedo 1B
		model = glm::translate(modelTemp, glm::vec3(0.06f, 0.0f, 0.0f)); //Izq-Der, Arriba-Abajo, Adelante-Atras
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 1.0f, 0.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Modelo dedo 1C
		model = glm::translate(modelTemp, glm::vec3(0.03f, 0.0f, 0.0f)); //Izq-Der, Arriba-Abajo, Adelante-Atras
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 1.0f, 0.0f));//Aplicamos la rotaci�n del codo 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Nos movemos una unidad para llegar al centro de la figura 
		model = glm::scale(model, glm::vec3(0.35f, 0.3f, 0.15f)); //Ancho, Altura y profundidad 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.01f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.001f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.001f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.05f;
	 //---------------------------------------------------------
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		 hombro += 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		 hombro -= 0.05f;
	 hombro = glm::clamp(hombro, -90.0f, 90.0f); // Restricci�n
	 //---------------------------------------------------------
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		 codo += 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		 codo -= 0.05f;
	 codo = glm::clamp(codo, -90.0f, 0.0f); // Restricci�n
	 //---------------------------------------------------------
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 palma += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 palma -= 0.08f;
	 palma = glm::clamp(palma, -55.0f, 55.0f); // Restricci�n
	 //---------------------------------------------------------
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		 dedo1 += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		 dedo1 -= 0.02f;
	 dedo1 = glm::clamp(dedo1, -30.0f, 0.0f); // Restricci�n
	 //---------------------------------------------------------
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		 dedo2 += 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		 dedo2 -= 0.06f;
	 dedo2 = glm::clamp(dedo2, -90.0f, 0.0f); // Restricci�n
 } 



