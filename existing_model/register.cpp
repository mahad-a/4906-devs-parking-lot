/*******************************************************************
*
*  Auto Generated File
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  This registration file is used to describe the atomic models that can be used to compose coupled models.
*
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico
#include "ggad.h"       // DEVS-Graphs interpreter
#include "AccessControlType.h"        // class AccessControlType
#include "Sensor1Type.h"	// class Sensor1Type
#include "ScreenType.h"	// class ScreenType

void MainSimulator::registerNewAtomics()
{
	// Register Built-in models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Ggad>() , "Ggad" ) ; // DEVS-GRAPHS interpreter

	// Register custom models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AccessControlType>(), "AccessControlType" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Sensor1Type>() , "Sensor1Type" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<ScreenType>() , "ScreenType" ) ;
}
