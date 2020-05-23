#include "DungeonXMLCreator.h"


#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>



XERCES_CPP_NAMESPACE_USE

DungeonXMLCreator::DungeonXMLCreator()
{
	
}

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

	DOMElement* prodElem = doc->createElement(XMLString::transcode("product"));
	rootElem->appendChild(prodElem);

	DOMText* prodDataVal = doc->createTextNode(XMLString::transcode("Xerces-C"));
	prodElem->appendChild(prodDataVal);

	DOMElement* catElem = doc->createElement(XMLString::transcode("category"));
	rootElem->appendChild(catElem);

	catElem->setAttribute(XMLString::transcode("idea"), XMLString::transcode("great") );

	DOMText* catDataVal = doc->createTextNode(XMLString::transcode("XML Parsing Tools") );
	catElem->appendChild(catDataVal);

	DOMElement* devByElem = doc->createElement(XMLString::transcode("developedBy") );
	rootElem->appendChild(devByElem);

	DOMText* devByDataVal = doc->createTextNode(XMLString::transcode("Apache Software Foundation"));
	devByElem->appendChild(devByDataVal);

	doc->release();
	
}
