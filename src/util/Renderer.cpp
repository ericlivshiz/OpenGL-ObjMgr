#include "Renderer.h"

Renderer::Renderer(Window& window)
	:
	window{ window }
{
	frame_state = 0;
}

void Renderer::PreRender()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(ObjMgr& objmgr)
{
	if (SHOULD_LOAD_SQUARE)
		RenderSquare(objmgr);

	if (SHOULD_LOAD_CUBE)
		RenderCube(objmgr);
}

void Renderer::PostRender()
{
	glfwSwapBuffers(window.Get_Window());
	glfwPollEvents();
}

void Renderer::ToggleWireframe()
{
	// if wireframes off on call, turn on. vice versa.

	if (!frame_state)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (frame_state)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::RenderSquare(ObjMgr& objmgr)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objmgr.square.texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, objmgr.square.texture2);

	objmgr.square.squareShader.use();

	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)window.Get_AspectRatio(), 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(objmgr.square.squareShader.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(objmgr.square.squareShader.ID, "view");
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	objmgr.square.squareShader.setMat4("projection", projection);

	// render container
	glBindVertexArray(objmgr.square.VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderCube(ObjMgr& objmgr)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objmgr.cube.texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, objmgr.cube.texture2);

	// activate shader
	objmgr.cube.cubeShader.use();

	// create transformations
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)window.Get_AspectRatio(), 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(objmgr.cube.cubeShader.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(objmgr.cube.cubeShader.ID, "view");
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	objmgr.cube.cubeShader.setMat4("projection", projection);

	// render box
	glBindVertexArray(objmgr.cube.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
