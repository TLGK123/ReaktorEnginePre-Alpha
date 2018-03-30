#pragma once

//= INCLUDES ====
#include <memory>
#include <vector>
#include <string>
//===============

//= FORWARD DECLARATIONS =
namespace pugi
{
	class xml_document;
	class xml_node;
	class xml_attribute;
}
//========================

namespace TmingEngine
{
	//========================

	class XmlDocument
	{
	public:
		XmlDocument();
		~XmlDocument();

		//= NODES =============================================================================
		void AddNode(const std::string& nodeName);
		bool AddChildNode(const std::string& parentNodeName, const std::string& childNodeName);
		//=====================================================================================

		//= ADD ATTRIBUTE =========================================================================================
		bool AddAttribute(const std::string& nodeName, const char* attributeName, const char* value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, const std::string& value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, bool value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, int value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, unsigned int value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, float value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, double value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, Vector2& value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, Vector3& value);
		bool AddAttribute(const std::string& nodeName, const std::string& attributeName, Vector4& value);
		//=========================================================================================================

		//= GET ATTRIBUTE =============================================================================
		bool GetAttribute(const std::string& nodeName, const char* attributeName, std::string& value);
		bool GetAttribute(const std::string& nodeName, const char* attributeName, int& value);
		bool GetAttribute(const std::string& nodeName, const char* attributeName, unsigned int& value);
		bool GetAttribute(const std::string& nodeName, const char* attributeName, bool& value);
		bool GetAttribute(const std::string& nodeName, const char* attributeName, float& value);
		bool GetAttribute(const std::string& nodeName, const char* attributeName, double& value);

		std::string GetAttributeAsStr(const std::string& nodeName, const char* attributeName);
		int GetAttributeAsInt(const std::string& nodeName, const char* attributeName);
		unsigned int GetAttributeAsUnsignedInt(const std::string& nodeName, const char* attributeName);
		Vector2 GetAttributeAsVector2(const std::string& nodeName, const char* attributeName);
		Vector3 GetAttributeAsVector3(const std::string& nodeName, const char* attributeName);
		Vector4 GetAttributeAsVector4(const std::string& nodeName, const char* attributeName);
		//=============================================================================================

		//= IO ================================
		bool Load(const std::string& filePath);
		bool Save(const std::string& filePath);
		//=====================================

	private:
		// Returns an attribute as xml_attribute for further handling
		pugi::xml_attribute GetAttribute(const std::string& nodeName, const char* attributeName);

		// Returns a node by name
		std::shared_ptr<pugi::xml_node> GetNodeByName(const std::string& name);

		// Returns all the nodes in the current document
		void GetAllNodes();

		// Returns all the descendant nodes of a node
		void GetNodes(pugi::xml_node node);

		std::unique_ptr<pugi::xml_document> m_document;
		std::vector<std::shared_ptr<pugi::xml_node>> m_nodes;
	};
}
