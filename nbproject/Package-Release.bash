#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=GNU-Linux
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build
CND_DLIB_EXT=so
NBTMPDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
<<<<<<< HEAD
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bezierr
OUTPUT_BASENAME=bezierr
PACKAGE_TOP_DIR=bezierr/
=======
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wwnf
OUTPUT_BASENAME=wwnf
PACKAGE_TOP_DIR=wwnf/
>>>>>>> eb2f958d50a72c57f68e71ec1fe5e69ae78d0e7c

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${NBTMPDIR}
mkdir -p ${NBTMPDIR}

# Copy files and create directories and links
cd "${TOP}"
<<<<<<< HEAD
makeDirectory "${NBTMPDIR}/bezierr/bin"
=======
makeDirectory "${NBTMPDIR}/wwnf/bin"
>>>>>>> eb2f958d50a72c57f68e71ec1fe5e69ae78d0e7c
copyFileToTmpDir "${OUTPUT_PATH}" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755


# Generate tar file
cd "${TOP}"
<<<<<<< HEAD
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/bezierr.tar
cd ${NBTMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/bezierr.tar *
=======
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/wwnf.tar
cd ${NBTMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/wwnf.tar *
>>>>>>> eb2f958d50a72c57f68e71ec1fe5e69ae78d0e7c
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${NBTMPDIR}
