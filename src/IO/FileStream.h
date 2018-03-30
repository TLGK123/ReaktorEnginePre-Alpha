#pragma once

//= INCLUDES =====
#include <vector>
#include <fstream>
//================

namespace TmingEngine
{
	class GameObject;
	struct VertexPosTexTBN
	{

	};
	namespace Math
	{
		class Vector2;
		class Vector3;
		class Vector4;
		class Quaternion;
	}

	enum FileStreamMode
	{
		FileStreamMode_Read,
		FileStreamMode_Write
	};

	class FileStream
	{
	public:
		FileStream(const std::string& path, FileStreamMode mode);
		~FileStream();

		bool IsOpen() { return m_isOpen; }

		//= WRITING ==================================================
		template <class T, class = typename std::enable_if<
			std::is_same<T, int>::value || 
			std::is_same<T, unsigned int>::value ||
			std::is_same<T, unsigned long>::value ||
			std::is_same<T, unsigned char>::value ||
			std::is_same<T, std::byte>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, bool>::value ||
			std::is_same<T, double>::value 
		>::type>
		void Write(T value)
		{
			out.write(reinterpret_cast<char*>(&value), sizeof(value));
		}

		void Write(const std::string& value);
		void Write(const Math::Vector2& value);
		void Write(const Math::Vector3& value);
		void Write(const Math::Vector4& value);
		void Write(const Math::Quaternion& value);
		void Write(const std::vector<std::string>& value);
		void Write(const std::vector<VertexPosTexTBN>& value);
		void Write(const std::vector<unsigned int>& value);
		void Write(const std::vector<unsigned char>& value);
		void Write(const std::vector<std::byte>& value);
		//===========================================================
		
		//= READING ================================================
		template <class T, class = typename std::enable_if<
			std::is_same<T, int>::value ||
			std::is_same<T, unsigned int>::value ||
			std::is_same<T, unsigned long>::value ||
			std::is_same<T, unsigned char>::value ||
			std::is_same<T, std::byte>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, bool>::value ||
			std::is_same<T, double>::value
		>::type>
			void Read(T* value)
		{
			in.read(reinterpret_cast<char*>(value), sizeof(T));
		}

		void Read(std::string* value);	
		void Read(Math::Vector2* value);
		void Read(Math::Vector3* value);
		void Read(Math::Vector4* value);
		void Read(Math::Quaternion* value);
		void Read(std::vector<std::string>* vec);
		void Read(std::vector<VertexPosTexTBN>* vec);
		void Read(std::vector<unsigned int>* vec);
		void Read(std::vector<unsigned char>* vec);
		void Read(std::vector<std::byte>* vec);

		// Helps when reading enums
		int ReadInt()
		{
			int value = 0;
			Read(&value);
			return value;
		}

		unsigned int ReadUInt()
		{
			unsigned int value = 0;
			Read(&value);
			return value;
		}
		//==========================================================

	private:
		std::ofstream out;
		std::ifstream in;
		FileStreamMode m_mode;
		bool m_isOpen;
	};
}
