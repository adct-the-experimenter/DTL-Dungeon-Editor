#include "DungeonXMLHandler.h"
#include <iostream>

DungeonXMLHandler::DungeonXMLHandler()
{

	m_dungeonPtr = nullptr;

	DungeonXMLHandler::pushElement(DungeonXMLHandler::NO_ELEMENT);
}

DungeonXMLHandler::~DungeonXMLHandler()
{
    m_dungeonPtr = nullptr;
}

void DungeonXMLHandler::SetPointerToDungeon(Dungeon* thisDungeon){m_dungeonPtr = thisDungeon;}

void DungeonXMLHandler::pushElement(DungeonXMLHandler::Element element){ currentElement = element;}

void DungeonXMLHandler::popCurrentElement(){ /*elementStack.pop();*/ currentElement = DungeonXMLHandler::NO_ELEMENT; }

DungeonXMLHandler::Element DungeonXMLHandler::getCurrentElement(){return /*elementStack.top();*/ currentElement;}

/* *** Instrument *** */

void DungeonXMLHandler::runPartNameStartElementEvent(char *localname_char)
{
    //if element is part-name
    if( strcmp(localname_char,"part-name") == 0){DungeonXMLHandler::pushElement(DungeonXMLHandler::PART_NAME);}
}

void DungeonXMLHandler::runPartNameCharEvent(char* char_local)
{
//	if(strcmp(char_local,"Piano") == 0){ DungeonXMLHandler::setNoteInstrument(Note::PIANO);}
//	else if(strcmp(char_local,"Electric Guitar") == 0){ DungeonXMLHandler::setNoteInstrument(Note::ELECTRIC_GUITAR);}

}

void DungeonXMLHandler::runPartNameEndElementEvent(char *localname_char)
{
    //if element is part name
    if( strcmp(localname_char,"part-name") == 0
        && DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::PART_NAME)
    {
        DungeonXMLHandler::popCurrentElement();
    }
}

/* *** Note Element processes *** */

void DungeonXMLHandler::setNoteState( DungeonXMLHandler::NoteState state){ noteState = state;}
DungeonXMLHandler::NoteState DungeonXMLHandler::getNoteState(){ return noteState;}

void DungeonXMLHandler::runNoteStartElementEvent(char* localname_char,const Attributes& attributes)
{
	//if element is note
	if( strcmp(localname_char,"note") == 0)
	{ 
		// *** NOTE *** skip extra note element by only acting on 
		//every other note element. Done with condition that noteElementCounter is odd number. *** NOTE ***

					//std::cout << "Found element note!" << "Note " << DungeonXMLHandler::getNoteElementCounter() << std::endl;

		//currentNote->setInstrument(DungeonXMLHandler::getNoteInstrument());
		//if no attributes
		if(attributes.getLength() == 0)
		{
			//std::cout << "No attributes. \n";
			//if note type is not defined yet and noteElementCounter is odd

			DungeonXMLHandler::setNoteState(DungeonXMLHandler::REST_STATE);
			//currentNote->setNoteType(Note::REST);
		}
		else
		{
			//std::cout << "Attributes! Quantity:" << attributes.getLength() << std::endl;
			//if note type is not defined and noteElementCounter is odd				

			DungeonXMLHandler::setNoteState(DungeonXMLHandler::NOTE_STATE);
			//currentNote->setNoteType(Note::NOTE);
		}
	}
	
}

void DungeonXMLHandler::runNoteEndElementEvent(char* localname_char)
{
	//if element is note
	if( strcmp(localname_char,"note") == 0)
	{
		/*
		//assign measure number to Note object
		currentNote->setMeasureNumber(DungeonXMLHandler::getMeasureNumberCount());

		if(currentNote->getTimeSignature() == Note::NO_TIME_SIGN)
		{
			currentNote->setBeat(DungeonXMLHandler::getBeat());
			currentNote->setBeatType(DungeonXMLHandler::getBeatType());
			currentNote->setTimeSignatureFromBeatPrivate();
		}

		//DungeonXMLHandler::checkFinalNote();
		*/
		DungeonXMLHandler::setNoteState(DungeonXMLHandler::NO_STATE);
	}
}

void DungeonXMLHandler::runBackUpStartElementEvent(char* localname_char)
{
	//if element is backup
	if( strcmp(localname_char,"backup") == 0){ DungeonXMLHandler::setNoteState(DungeonXMLHandler::BACKUP_STATE);}
}

void DungeonXMLHandler::runBackUpEndElementEvent(char* localname_char)
{
	//if element is backup
	if( strcmp(localname_char,"backup") == 0){ DungeonXMLHandler::setNoteState(DungeonXMLHandler::NO_STATE);}
}

/* *************** Time Signature ********************** */


//Beats and Beat type element processes

void DungeonXMLHandler::runBeatsStartElementEvent(char* localname_char)
{
	//if element is beats
        if( strcmp(localname_char,"beats") == 0){ DungeonXMLHandler::pushElement(DungeonXMLHandler::BEATS);}
}

void DungeonXMLHandler::runBeatsEndElementEvent(char* localname_char)
{
	if( strcmp(localname_char,"beats") == 0
			&& DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::BEATS)
	{
		//currentNote->setBeat(DungeonXMLHandler::getBeat());
		DungeonXMLHandler::popCurrentElement();
	}
}

void DungeonXMLHandler::setBeat(int thisBeat){ beat = thisBeat;}

int DungeonXMLHandler::getBeat(){return beat;}

void DungeonXMLHandler::runBeatTypeStartElementEvent(char* localname_char)
{
	//if element is beat type
        if( strcmp(localname_char,"beat-type") == 0)
        { DungeonXMLHandler::pushElement(DungeonXMLHandler::BEAT_TYPE);}
}

void DungeonXMLHandler::runBeatTypeEndElementEvent(char* localname_char)
{
	//if element is beat type
	if( strcmp(localname_char,"beat-type") == 0
			&& DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::BEAT_TYPE)
	{
		//currentNote->setBeatType( DungeonXMLHandler::getBeatType() );
		//currentNote->setTimeSignatureFromBeatPrivate();
		DungeonXMLHandler::popCurrentElement();
	}
}

void DungeonXMLHandler::setBeatType(int thisBeatType){ beatType = thisBeatType; }

int DungeonXMLHandler::getBeatType(){return beatType;}

/* *************** Measure Number ****************** */

void DungeonXMLHandler::incrementMeasureNumberCounter() { measureNumberCounter += 1;}

void DungeonXMLHandler::setMeasureNumberCount(int number){ measureNumberCounter = number;}
int DungeonXMLHandler::getMeasureNumberCount(){return measureNumberCounter;}

void DungeonXMLHandler::resetMeasureNumberCounter(){ measureNumberCounter = 0;}

void DungeonXMLHandler::runMeasureStartElementEvent(char* localname_char)
{
	if( strcmp(localname_char,"measure") == 0)
        {
                DungeonXMLHandler::incrementMeasureNumberCounter();
                DungeonXMLHandler::pushElement(DungeonXMLHandler::MEASURE);
	}
}

void DungeonXMLHandler::runMeasureEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"measure") == 0
                && DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::MEASURE)
        {
            DungeonXMLHandler::popCurrentElement();
        }
}



/*  ******************* Duration ******************** */

void DungeonXMLHandler::runDurationStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"duration") == 0)
        {
            //if(currentNote->getNoteType() == Note::REST
            //        || currentNote->getNoteType() == Note::NOTE)
            //{
                DungeonXMLHandler::pushElement(DungeonXMLHandler::DURATION);
            //}
        }
}

void DungeonXMLHandler::runDurationEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"duration") == 0
                && DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::DURATION )
        {
            //assign duration to current note
//            currentNote->setNoteDuration(DungeonXMLHandler::getDuration());
            DungeonXMLHandler::popCurrentElement();
        }
}

void DungeonXMLHandler::setDuration(int thisDuration){ duration = thisDuration;}

int DungeonXMLHandler::getDuration(){return duration;}




/*  ************************* Pitch ************************ */

void DungeonXMLHandler::runStepStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"step") == 0)
        {DungeonXMLHandler::pushElement(DungeonXMLHandler::STEP);}
}

void DungeonXMLHandler::runStepEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"step") == 0
                && DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::STEP)
        {
//            currentNote->setPitchStep(DungeonXMLHandler::getStep());
            DungeonXMLHandler::popCurrentElement();
        }
}

void DungeonXMLHandler::setStep(char thisStep){step = thisStep;}
char DungeonXMLHandler::getStep(){return step;}

void DungeonXMLHandler::runOctaveStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"octave") == 0){DungeonXMLHandler::pushElement(DungeonXMLHandler::OCTAVE);}
}

void DungeonXMLHandler::runOctaveEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"octave") == 0
                && DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::OCTAVE)
        {
//            currentNote->setPitchOctave(DungeonXMLHandler::getOctave());
            //setup pitch from octave step members assigned
//            currentNote->setPitchFromOctaveStep();
            DungeonXMLHandler::popCurrentElement();
        }
}

void DungeonXMLHandler::setOctave(int thisOctave){ octave = thisOctave;}
int DungeonXMLHandler::getOctave(){return octave;}

/* ********* Staff ************ */

void DungeonXMLHandler::runStaffStartElementEvent(char* localname_char)
{
	if( strcmp(localname_char,"staff") == 0)
        {
//               if(!currentNote->getMultipleStaffBool()){currentNote->setMultipleStaffBool(true);}
               DungeonXMLHandler::pushElement(DungeonXMLHandler::STAFF);
        }
}

void DungeonXMLHandler::runStaffEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"staff") == 0
                && DungeonXMLHandler::getCurrentElement() == DungeonXMLHandler::STAFF)
        {
            //assign staff to note
            //currentNote->setStaffFromInt(DungeonXMLHandler::getNoteStaff());
            DungeonXMLHandler::popCurrentElement();
        }
}

void DungeonXMLHandler::setNoteStaff(int thisStaff){ noteStaff = thisStaff;}
int DungeonXMLHandler::getNoteStaff(){return noteStaff;}


/* ********* Chord ********** */

void DungeonXMLHandler::runChordStartElementEvent(char* localname_char)
{
	//if( strcmp(localname_char, "chord") == 0 ){currentNote->setChordStatus(true);}
}



void DungeonXMLHandler::startElementRoutine(char* localname_char, const Attributes& attributes)
{
	//function to run if part name element found
	DungeonXMLHandler::runPartNameStartElementEvent(localname_char);

	//function to run if measure number element found
	DungeonXMLHandler::runMeasureStartElementEvent(localname_char);
		
        //functions to run if beats and beat-type element found
	DungeonXMLHandler::runBeatsStartElementEvent(localname_char);
	DungeonXMLHandler::runBeatTypeStartElementEvent(localname_char);

	//function to run if note element found
	DungeonXMLHandler::runNoteStartElementEvent(localname_char,attributes);

	//function to run if backup element found
	DungeonXMLHandler::runBackUpStartElementEvent(localname_char);

	//function to run if chord element found
	DungeonXMLHandler::runChordStartElementEvent(localname_char);

	//function to run if step element found
	DungeonXMLHandler::runStepStartElementEvent(localname_char);

	//function to run if octave element found
	DungeonXMLHandler::runOctaveStartElementEvent(localname_char);

	//function to run if duration element found
	DungeonXMLHandler::runDurationStartElementEvent(localname_char);

	//function to run if staff element found
	DungeonXMLHandler::runStaffStartElementEvent(localname_char);
}

void DungeonXMLHandler::charactersRoutine(char* chars_local)
{
        
	switch(DungeonXMLHandler::getCurrentElement())
	{
		case DungeonXMLHandler::PART_NAME:
		{
			DungeonXMLHandler::runPartNameCharEvent(chars_local);
		}

		case DungeonXMLHandler::BEATS :
		{
			DungeonXMLHandler::setBeat( atoi(chars_local) );
			break;
		}
		case DungeonXMLHandler::BEAT_TYPE :
		{
			DungeonXMLHandler::setBeatType( atoi(chars_local) );
			break;
		}
		case DungeonXMLHandler::DURATION :
		{
			DungeonXMLHandler::setDuration( atoi(chars_local) );
			break;
		}
		case DungeonXMLHandler::STEP :
		{
			DungeonXMLHandler::setStep(*chars_local);
			break;
		}
		case DungeonXMLHandler::OCTAVE :
		{

			DungeonXMLHandler::setOctave( atoi(chars_local) );
			break;
		}
		case DungeonXMLHandler::STAFF :
		{
			DungeonXMLHandler::setNoteStaff(atoi(chars_local));
			break;
		}
	}
}

void DungeonXMLHandler::endElementRoutine(char* localname_char)
{
	//function to run if part name element found
	DungeonXMLHandler::runPartNameEndElementEvent(localname_char);

	//function to run if measure element found
	DungeonXMLHandler::runMeasureEndElementEvent(localname_char);

	//function to run if note element found
	DungeonXMLHandler::runNoteEndElementEvent(localname_char);

	//function to run if backup element found
	DungeonXMLHandler::runBackUpEndElementEvent(localname_char);

	//functions to run if beats and beat-type element found 
	DungeonXMLHandler::runBeatsEndElementEvent(localname_char);
	DungeonXMLHandler::runBeatTypeEndElementEvent(localname_char);
	
	//function to run if step element found
	DungeonXMLHandler::runStepEndElementEvent(localname_char);

	//function to run if octave element found
	DungeonXMLHandler::runOctaveEndElementEvent(localname_char);

	//function to run if duration element found
	DungeonXMLHandler::runDurationEndElementEvent(localname_char);

	//function to run if staff element found
	DungeonXMLHandler::runStaffEndElementEvent(localname_char);
}

//SAX2 Content Handler functions

void DungeonXMLHandler::startElement(const   XMLCh* const    uri,
                            const   XMLCh* const    localname,
                            const   XMLCh* const    qname,
                            const   Attributes&     attrs)
{
	//save localname to local char var.
    char* message_localname = XMLString::transcode(localname);
	
	//run start element processes
	DungeonXMLHandler::startElementRoutine(message_localname,attrs);

	//release local char variable for localname 		
    XMLString::release(&message_localname);
}


void DungeonXMLHandler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << std::endl;
}

void DungeonXMLHandler::characters
(
        const   XMLCh* const    chars
        , const XMLSize_t       length
) 
{
    //save chars to local char var.
    char* message_chars = XMLString::transcode(chars);
	
    DungeonXMLHandler::charactersRoutine(message_chars);

    //release local char var containing chars
    XMLString::release(&message_chars);
}

void DungeonXMLHandler::endDocument () {}

void DungeonXMLHandler::endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	) 
{
	//save localname to local char var.
	char* message_localname = XMLString::transcode(localname);

	DungeonXMLHandler::endElementRoutine(message_localname);

        XMLString::release(&message_localname);
}

void DungeonXMLHandler::ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const XMLSize_t       length
    ) {}

void DungeonXMLHandler::processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    ) {}

void DungeonXMLHandler::setDocumentLocator(const Locator* const locator) {}

void DungeonXMLHandler::startDocument() {}

	
void DungeonXMLHandler::startPrefixMapping
	(
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	){}

void DungeonXMLHandler::endPrefixMapping
	(
		const	XMLCh* const	prefix
	){}

void DungeonXMLHandler::skippedEntity
(
	const	XMLCh* const	name
){}

