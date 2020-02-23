#include "PCH.h"
#include "GL_Shader.h"

namespace YAGE
{
	Shader::Shader()
	{
		m_glType = GL_TYPE_SHADER;

		create();
	}

	Shader::~Shader()
	{
		glDeleteProgram(muiGLID);
		LOG(LOG_DEBUG) << "Deleted shader program " << muiGLID;
	}

	void Shader::load(const std::string& _file)
	{
		if (m_linked)
		{
			LOG(LOG_ERROR) << "Unable to load to Shader " << muiGLID << ", already linked";
			return;
		}

		std::string file = IOUtilities::loadText(_file);
		if (file == "NULL")
		{
			LOG(LOG_ERROR) << "Unable to load glsl shader, file not loaded correctly";
			return;
		}

		std::vector<std::string> fileLines = IOUtilities::split(file, '\n');

		std::string currentShaderText;
		ShaderSourceType currentShaderType = SHADER_SOURCE_UNKNOWN;
		int lineNumber = 0;
		for (const std::string &line : fileLines)
		{
			// if the line is the start of a vertex shader
			if (line == "[[VERTEX]]")
			{
				// if there is already a shader being written, attach it to the program
				if (currentShaderText.size() != 0)
				{
					attach(currentShaderText, currentShaderType);
				}

				// clear the shader text and set the new shader type
				currentShaderText.clear();
				currentShaderType = SHADER_SOURCE_VERTEX;
			}
			// if the line is the start of a fragment shader
			else if (line == "[[FRAGMENT]]")
			{
				// if there is already a shader being written, attach it to the program
				if (currentShaderText.size() != 0)
				{
					attach(currentShaderText, currentShaderType);
				}

				// clear the shader text and set the new shader type
				currentShaderText.clear();
				currentShaderType = SHADER_SOURCE_FRAGMENT;
			}
			// if the line is to be added to the shader
			else
			{
				currentShaderText.append(line + '\n');
			}


			++lineNumber;
			// if at the end of the file
			if (lineNumber == fileLines.size())
			{
				if (currentShaderType == SHADER_SOURCE_UNKNOWN)
				{
					LOG(LOG_WARNING) << "Unable to load shader source from file: no shaders found";
				}
				else
				{
					attach(currentShaderText, currentShaderType);
				}
			}
		}
	}

	void Shader::attach(const std::string& _source, const ShaderSourceType &_type)
	{
		unsigned int shaderID = glCreateShader(_type);

		const char* rawText = _source.c_str();
		glShaderSource(shaderID, 1, &rawText, NULL);
		glCompileShader(shaderID);

		// check the shader is valid and store the result
		int success;
		char infoLog[512];

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		// if the length is greater than 0, something went wrong :(
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			LOG(LOG_ERROR) << "ERROR: Shader Compile failed: " << infoLog << std::endl;

			glDeleteShader(shaderID);
			return;
		}
		
		// attach the shader to the program
		glAttachShader(muiGLID, shaderID);

		LOG(LOG_DEBUG) << "Shader " << shaderID << " with type " << _type << " successfully attached to program " << muiGLID;

		// push back the shaderID so we can remove it later once we've linked the shader program together
		m_attached.push_back(std::pair<unsigned int, ShaderSourceType>(shaderID, _type));
	}

	bool Shader::complete()
	{
		// link the program
		glLinkProgram(muiGLID);

		// check the shader is valid and store the result
		int  success;
		char infoLog[512];
		glGetProgramiv(muiGLID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(muiGLID, 512, NULL, infoLog);
			LOG(LOG_ERROR) << "Program link failed: " << infoLog;
			return false;
		}

		m_linked = true;
		LOG(LOG_DEBUG) << "Shader Program " << muiGLID << " successfully linked";

		if (getUniformBlockIndex("uCameraData") != -1)
		{
			LOG(LOG_DEBUG) << "Found uCameraData uniform block, starting link";
			// link the BasicShader Uniform block "u_camera_data" to the binding point
			linkUniformBlock("uCameraData", SHADER_BINDPOINT_CAMERA_VP);
		}
		else
		{
			LOG(LOG_DEBUG) << "Unable to find u_camera_data uniform block, assuming not needed";
		}

		// remove the linked shaders
		for (const auto &pair : m_attached)
		{
			glDeleteShader(pair.first);
			LOG(LOG_DEBUG) << "Removed source shader " << pair.first;
		}
		return true;
	}

	int Shader::getUniformLocation(const std::string &_uniform)
	{
		// if the uniform is in the cache, just return that
		if (m_uniformLocationCache.find(_uniform) != m_uniformLocationCache.end())
			return m_uniformLocationCache[_uniform];

		// else, lets go looking for it
		int location = glGetUniformLocation(muiGLID, _uniform.c_str());
		if (location == -1)
		{
			LOG(LOG_WARNING) << "Attribute name " << _uniform << " does not exist!";
			return -1;
		}

		// update the cache
		m_uniformLocationCache[_uniform] = location;
		LOG(LOG_DEBUG) << "Found shader uniform " << _uniform << " at location " << location << ", adding to cache";

		return location;
	}

	void Shader::create()
	{
		muiGLID = glCreateProgram();
		LOG(LOG_DEBUG) << "Created shader program " << muiGLID;
	}

	GLuint Shader::getUniformBlockIndex(const std::string& _name)
	{
		bind();
		GLuint blockIndex = glGetUniformBlockIndex(muiGLID, _name.c_str());
		if (blockIndex == -1)
		{
			LOG(LOG_WARNING) << "Uniform block " << _name << " does not exist (" << blockIndex << ")";
		}
		return blockIndex;
	}

	void Shader::linkUniformBlock(const std::string& _blockIndex, GLuint _bindingPoint)
	{
		bind();
		glUniformBlockBinding(muiGLID, getUniformBlockIndex(_blockIndex), _bindingPoint);
		LOG(LOG_DEBUG) << "Linked shader " << muiGLID << " uniform block " << _blockIndex << " to binding point " << _bindingPoint;
	}
}