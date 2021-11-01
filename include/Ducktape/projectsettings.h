#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

namespace ProjectSettings 
{
	std::string windowTitle = "Ducktape Project";
	Color sceneBackgroundColor = Color(0, 0, 0, 255);
	Vector2 globalGravity = Vector2(0.0f, 1.0f);

	void Initialize(std::string _projectFilePath)
	{
		std::ifstream projectFileInput("../examples/flappybird.json");

		int hasContent = false;
		char c;
		c = projectFileInput.get();
		while (projectFileInput)
		{
			hasContent = true;
		    c = projectFileInput.get();
		}

		if(!hasContent)
		{
			Debug::LogFatalError("The Ducktape project file could not be found/was empty at \"" + _projectFilePath + "\".");
		}
	
		std::ifstream projectFileInputTwo("../examples/flappybird.json");

		json projectFile;
		projectFileInputTwo >> projectFile;

		windowTitle = projectFile["application"]["windowTitle"];
		sceneBackgroundColor.red = projectFile["scene"]["sceneBackgroundColor"]["red"];
		sceneBackgroundColor.blue = projectFile["scene"]["sceneBackgroundColor"]["blue"];
		sceneBackgroundColor.green = projectFile["scene"]["sceneBackgroundColor"]["green"];
		globalGravity.x = projectFile["physics"]["globalGravity"]["x"];
		globalGravity.y = projectFile["physics"]["globalGravity"]["y"];
	}
}

#endif