#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/GraphicalInterface.o \
	${OBJECTDIR}/GroupObject.o \
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/SingleObject.o \
	${OBJECTDIR}/Zone.o \
	${OBJECTDIR}/editor.o \
	${OBJECTDIR}/event.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../../../../irrlicht-1.8.1/lib/Win32-gcc/libIrrlicht.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editeur-3d.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editeur-3d.exe: ../../../../../irrlicht-1.8.1/lib/Win32-gcc/libIrrlicht.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editeur-3d.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editeur-3d ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/GraphicalInterface.o: GraphicalInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GraphicalInterface.o GraphicalInterface.cpp

${OBJECTDIR}/GroupObject.o: GroupObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GroupObject.o GroupObject.cpp

${OBJECTDIR}/Object.o: Object.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object.o Object.cpp

${OBJECTDIR}/SingleObject.o: SingleObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SingleObject.o SingleObject.cpp

${OBJECTDIR}/Zone.o: Zone.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Zone.o Zone.cpp

${OBJECTDIR}/editor.o: editor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/editor.o editor.cpp

${OBJECTDIR}/event.o: event.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/event.o event.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../MinGW/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editeur-3d.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
