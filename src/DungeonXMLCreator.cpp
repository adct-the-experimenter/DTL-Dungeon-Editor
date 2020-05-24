#include "DungeonXMLCreator.h"


#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>



XERCES_CPP_NAMESPACE_USE

DungeonXMLCreator::DungeonXMLCreator()
{
	m_dungeonPtr = nullptr;
	
}

DungeonXMLCreator::~DungeonXMLCreator()
{
	
}

void DungeonXMLCreator::SetPointerToDungeon(Dungeon* thisDungeon){m_dungeonPtr = thisDungeon;}

void DungeonXMLCreator::CreateXMLFile()
{
	DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));

	if (impl == NULL)
	{
		return;
	}
	
	DOMDocument* doc = impl->createDocument(
				   0,                    // root element namespace URI.
				   XMLString::transcode("Door To Life XML"),         // root element name
				   0);                   // document type object (DTD).

	DOMElement* rootElem = doc->getDocumentElement();

	DOMElement* prodElem = doc->createElement(XMLString::transcode("Tile"));
	rootElem->appendChild(prodElem);

	DOMText* prodDataVal = doc->createTextNode(XMLString::transcode("Empty"));
	prodElem->appendChild(prodDataVal);


	doc->release();
	
}
