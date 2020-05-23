#ifndef SAX2HANDLERMUSICXML_H
#define SAX2HANDLERMUSICXML_H

#include <xercesc/sax2/ContentHandler.hpp> //header file for default handler which implements content & error handler
#include <xercesc/sax2/Attributes.hpp> //attributes defintion
#include <xercesc/sax/SAXParseException.hpp>

#include <vector> //header for vector container class
#include <sstream> //header for string stream processing
#include <string>

#include "Dungeon.h"

//file to read from xml

using namespace xercesc;

class DungeonXMLHandler : public ContentHandler 
{
public:


	//constructor
	DungeonXMLHandler();

	//destructor
	~DungeonXMLHandler();

	//function to pass vector of notes to DungeonXMLHandler object
	void SetPointerToDungeon(Dungeon* thisDungeon);

//functions derived from ContentHandler
	
	//what to do at start of each element
	virtual void startElement(
		const   XMLCh* const    uri,
		const   XMLCh* const    localname,
		const   XMLCh* const    qname,
		const   Attributes&     attrs
	);
	
	//what to do at an error
	virtual void fatalError(const SAXParseException&);

	virtual void characters
	(
		const   XMLCh* const    chars
		, const XMLSize_t       length
	);

	virtual void endDocument ();

	virtual void endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	);

	virtual void ignorableWhitespace
	(
		const   XMLCh* const    chars
		, const XMLSize_t       length
	);

	virtual void processingInstruction
	(
		const   XMLCh* const    target
		, const XMLCh* const    data
	);

	virtual void setDocumentLocator(const Locator* const locator);

	virtual void startDocument();

	virtual void startPrefixMapping
	(
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	);

	virtual void endPrefixMapping
	(
		const	XMLCh* const	prefix
	);

	virtual void skippedEntity
	(
		const	XMLCh* const	name
	);

private:

	//function to run start element processes
	void startElementRoutine(char* localname_char, const Attributes& attributes);
	//function to run characters processes
	void charactersRoutine(char* chars_local);
	//function to run end element processes
	void endElementRoutine(char* localname_char);

/*
	********************************************************
	********************** Note ****************************
	********************************************************
*/
	//pointer to vector of notes
	Dungeon* m_dungeonPtr;

/*
	*********************************************************
	**************** Music XML Elements *********************
	*********************************************************
*/

	void runPartNameStartElementEvent(char* localname_char);
	void runPartNameCharEvent(char* char_local);
	void runPartNameEndElementEvent(char* localname_char);

	// *** Note Type: Note or Rest ***
	//Note element processes

	int noteElementCounter;
	
	//different enum cases for state of note
	enum NoteState{ NO_STATE = 0, NOTE_STATE, REST_STATE, BACKUP_STATE };
	
	DungeonXMLHandler::NoteState noteState;
	void setNoteState( DungeonXMLHandler::NoteState state);
	DungeonXMLHandler::NoteState getNoteState();

	//enum cases for elements found
	enum Element {NO_ELEMENT = 0,
				  PART_NAME,
				  NOTE,REST,BACKUP,CHORD,
				  MEASURE,
				  BEATS,BEAT_TYPE,
				  STEP,OCTAVE,
				  DURATION,
				  STAFF};

	DungeonXMLHandler::Element currentElement;


	void pushElement(DungeonXMLHandler::Element element);
	void popCurrentElement();
	DungeonXMLHandler::Element getCurrentElement();



	//function to run if note element found in start element
	void runNoteStartElementEvent(char* localname_char,const Attributes& attributes);
	void runNoteEndElementEvent(char* localname_char);

	//back up element is important because it allows us to 
	// distinguish from real note and copy note
	void runBackUpStartElementEvent(char* localname_char);
	void runBackUpEndElementEvent(char* localname_char);
	
	// *** Time Signature *** 


	//Beats and beat type element processes
	
	//function to run if beats element found
	void runBeatsStartElementEvent(char* localname_char);
	void runBeatsEndElementEvent(char* localname_char);
	
	int beat;
	void setBeat(int thisBeat);
	int getBeat();

	//function to run if beat-type element found
	void runBeatTypeStartElementEvent(char* localname_char);
	void runBeatTypeEndElementEvent(char* localname_char);

	int beatType;
	void setBeatType(int thisBeatType);
	int getBeatType();

	// *** Measure Number ***
	int measureNumberCounter;
	void incrementMeasureNumberCounter();
	void setMeasureNumberCount(int number);
	int getMeasureNumberCount();
	void resetMeasureNumberCounter();

	void runMeasureStartElementEvent(char* localname_char);
	void runMeasureEndElementEvent(char* localname_char);

	// *** Duration ***

	int duration;
	void setDuration(int thisDuration);
	int getDuration();

	void runDurationStartElementEvent(char* localname_char);
	void runDurationEndElementEvent(char* localname_char);

	// *** Pitch ***

	char step;
	void setStep(char thisStep);
	char getStep();


	void runStepStartElementEvent(char* localname_char);
	void runStepEndElementEvent(char* localname_char);

	int octave;
	void setOctave(int thisOctave);
	int getOctave();

	void runOctaveStartElementEvent(char* localname_char);
	void runOctaveEndElementEvent(char* localname_char);
	

	/* ********** Staff *********** */

	int noteStaff;
	void setNoteStaff(int thisStaff);
	int getNoteStaff();

	void runStaffStartElementEvent(char* localname_char);
	void runStaffEndElementEvent(char* localname_char);

	/* ********** Chord ************ */

	void runChordStartElementEvent(char* localname_char);



};

#endif
