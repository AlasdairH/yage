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
		glDeleteProgram(m_glID);
		LOG(LOG_DEBUG) << "Deleted shader program " << m_glID;
	}

	void Shader::load(const std::string& _file)
	{
		if (m_linked)
		{
			LOG(LOG_ERROR) << "Unable to load to Shader " << m_glID << ", already linked";
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
			if (line == "[[VERTEX]]")
			{
				// if there is already a shader being written, attach it to the program
				if (currentShaderText.size() != 0)
				{
					attach(currentShaderText, currentShaderType);
				}

				currentShaderText.clear();
				currentShaderType = SHADER_SOURCE_VERTEX;
			}
			else if (line == "[[FRAGMENT]]")
			{
				// if there is already a shader being written, attach it to the program
				if (currentShaderText.size() != 0)
				{
					attach(currentShaderText, currentShaderType);
				}

				currentShaderText.clear();
				currentShaderType = SHADER_SOURCE_FRAGMENT;
			}
			else
			{
				currentShaderText.append(line + '\n');
			}


			++lineNumber;
			// if at the end of the file
			if (lineNumber == fileLines.size())
			{
				attach(currentShaderText, currentShaderType);
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
		glAttachShader(m_glID, shaderID);

		LOG(LOG_DEBUG) << "Shader " << shaderID << " with type " << _type << " successfully attached to program " << m_glID;

		// push back the shaderID so we can remove it later once we've linked the shader program together
		m_attached.push_back(std::pair<unsigned int, ShaderSourceType>(shaderID, _type));
	}

	bool Shader::complete()
	{
		// link the program
		glLinkProgram(m_glID);

		// check the shader is valid and store the result
		int  success;
		char infoLog[512];
		glGetProgramiv(m_glID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_glID, 512, NULL, infoLog);
			LOG(LOG_ERROR) << "Program link failed: " << infoLog;
			return false;
		}

		m_linked = true;
		LOG(LOG_DEBUG) << "Shader Program " << m_glID << " successfully linked";

		// remove the linked shaders
		for (const auto &pair : m_attached)
		{
			glDeleteShader(pair.first);
		}
		return true;
	}

	void Shader::create()
	{
		m_glID = glCreateProgram();
		LOG(LOG_DEBUG) << "Created shader program " << m_glID;
	}
}