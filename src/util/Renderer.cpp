#include "Renderer.h"

Renderer::Renderer(Window& window, ControlsMgr& ctrlmgr)
	:
	window{ window },
	ctrlmgr{ctrlmgr}
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

	if (SHOULD_LOAD_SPHERE)
		RenderSphere(objmgr);

	if (SHOULD_LOAD_DEMO_CUBES)
		RenderDemoCubes(objmgr);

	if (SHOULD_LOAD_DEMO_SPHERES)
		RenderDemoSpheres(objmgr);
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
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		frame_state = true;
	}

	else if (frame_state)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		frame_state = false;
	}
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

	unsigned int modelLoc, viewLoc;

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)window.Get_AspectRatio(), 0.1f, 100.0f);

	// retrieve the matrix uniform locations
	modelLoc = glGetUniformLocation(objmgr.square.squareShader.ID, "model");
	viewLoc = glGetUniformLocation(objmgr.square.squareShader.ID, "view");

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

	unsigned int modelLoc, viewLoc;

	// retrieve the matrix uniform locations
	modelLoc = glGetUniformLocation(objmgr.cube.cubeShader.ID, "model");
	viewLoc = glGetUniformLocation(objmgr.cube.cubeShader.ID, "view");
	
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);


	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	objmgr.cube.cubeShader.setMat4("projection", projection);
	

	// render box
	glBindVertexArray(objmgr.cube.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Renderer::RenderSphere(ObjMgr& objmgr)
{
	glBindVertexArray(objmgr.sphere.sphereVAO);
	glDrawElements(GL_TRIANGLE_STRIP, objmgr.sphere.indexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderDemoCubes(ObjMgr& objmgr)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objmgr.cube.texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, objmgr.cube.texture2);

	objmgr.cube.camShader.use();

	glm::mat4 projection = glm::perspective(glm::radians(ctrlmgr.camera.Zoom), (float)window.Get_AspectRatio(), 0.1f, 100.f);
	objmgr.cube.camShader.setMat4("projection", projection);

	glm::mat4 view = ctrlmgr.camera.GetViewMatrix();
	objmgr.cube.camShader.setMat4("view", view);

	glBindVertexArray(objmgr.cube.VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::translate(model, objmgr.cube.cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		objmgr.cube.camShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Renderer::RenderDemoSpheres(ObjMgr& objmgr)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objmgr.sphere.texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, objmgr.sphere.texture2);

	objmgr.sphere.SphereDemoShader.use();

	glm::mat4 projection = glm::perspective(glm::radians(ctrlmgr.camera.Zoom), (float)window.Get_AspectRatio(), 0.1f, 100.f);
	objmgr.sphere.SphereDemoShader.setMat4("projection", projection);

	glm::mat4 view = ctrlmgr.camera.GetViewMatrix();
	objmgr.sphere.SphereDemoShader.setMat4("view", view);

	glBindVertexArray(objmgr.sphere.sphereVAO);
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, objmgr.sphere.positions[0]);
	float angle = 20.0;
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	objmgr.sphere.SphereDemoShader.setMat4("model", model);

	glDrawElements(GL_TRIANGLE_STRIP, objmgr.sphere.indexCount, GL_UNSIGNED_INT, 0);

	/// FINISH!

}
