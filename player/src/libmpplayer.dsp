# Microsoft Developer Studio Project File - Name="libmpplayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libmpplayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libmpplayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libmpplayer.mak" CFG="libmpplayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libmpplayer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libmpplayer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "libmpplayer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
RSC=rc.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/video/mpeg4 ./codec ./codec/mpeg4 ../lib ../lib/audio ../lib/SDL/include ../../common/mp4 ../../include" /I "." /I "../../common/video/mpeg4" /I "./codec" /I "./codec/mpeg4" /I "../lib" /I "../lib/audio" /I "../lib/SDL/include" /I "../../common/mp4" /I "../../include" /I "../lib/video/divx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_REENTRANT" /D "NOCONTROLS" /D _WIN32_WINNT=0x0400 /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libmpplayer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
RSC=rc.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "." /I "../../common/video/mpeg4" /I "./codec" /I "./codec/mpeg4" /I "../lib" /I "../lib/audio" /I "../lib/SDL/include" /I "../../common/mp4" /I "../../include" /I "../lib/video/divx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_REENTRANT" /D "NOCONTROLS" /D _WIN32_WINNT=0x0400 /D "_AFXDLL" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libmpplayer - Win32 Release"
# Name "libmpplayer - Win32 Debug"
# Begin Group "source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\audio.cpp
# End Source File
# Begin Source File

SOURCE=.\ip_port.cpp
# End Source File
# Begin Source File

SOURCE=.\media_utils.cpp
# End Source File
# Begin Source File

SOURCE=.\msg_queue.cpp
# End Source File
# Begin Source File

SOURCE=.\our_bytestream_file.cpp
# End Source File
# Begin Source File

SOURCE=.\our_bytestream_mem.cpp
# End Source File
# Begin Source File

SOURCE=.\player_media.cpp
# End Source File
# Begin Source File

SOURCE=.\player_media_decode.cpp
# End Source File
# Begin Source File

SOURCE=.\player_mem_bytestream.cpp
# End Source File
# Begin Source File

SOURCE=.\player_rtp_bytestream.cpp
# End Source File
# Begin Source File

SOURCE=.\player_sdp.c
# End Source File
# Begin Source File

SOURCE=.\player_session.cpp
# End Source File
# Begin Source File

SOURCE=.\player_util.c
# End Source File
# Begin Source File

SOURCE=.\qtime_bytestream.cpp
# End Source File
# Begin Source File

SOURCE=.\qtime_file.cpp
# End Source File
# Begin Source File

SOURCE=.\sync.cpp
# End Source File
# Begin Source File

SOURCE=.\video.cpp
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\audio.h
# End Source File
# Begin Source File

SOURCE=.\codec\codec.h
# End Source File
# Begin Source File

SOURCE=.\ip_port.h
# End Source File
# Begin Source File

SOURCE=.\media_utils.h
# End Source File
# Begin Source File

SOURCE=.\msg_queue.h
# End Source File
# Begin Source File

SOURCE=.\our_bytestream.h
# End Source File
# Begin Source File

SOURCE=.\our_bytestream_file.h
# End Source File
# Begin Source File

SOURCE=.\our_bytestream_mem.h
# End Source File
# Begin Source File

SOURCE=.\player_media.h
# End Source File
# Begin Source File

SOURCE=.\player_mem_bytestream.h
# End Source File
# Begin Source File

SOURCE=.\player_rtp_bytestream.h
# End Source File
# Begin Source File

SOURCE=.\player_sdp.h
# End Source File
# Begin Source File

SOURCE=.\player_session.h
# End Source File
# Begin Source File

SOURCE=.\player_util.h
# End Source File
# Begin Source File

SOURCE=.\qtime_bytestream.h
# End Source File
# Begin Source File

SOURCE=.\qtime_file.h
# End Source File
# Begin Source File

SOURCE=.\video.h
# End Source File
# End Group
# Begin Group "codec/aa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\codec\aa\aa.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\aa\aa.h
# End Source File
# Begin Source File

SOURCE=.\codec\aa\aa_file.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\aa\aa_file.h
# End Source File
# End Group
# Begin Group "codec/divx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\codec\divx\divx.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\divx\divx.h
# End Source File
# Begin Source File

SOURCE=.\codec\divx\divx_file.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\divx\divx_file.h
# End Source File
# End Group
# Begin Group "codec/mpeg4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\codec\mpeg4\mpeg4.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\mpeg4\mpeg4.h
# End Source File
# Begin Source File

SOURCE=.\codec\mpeg4\mpeg4_file.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\mpeg4\mpeg4_file.h
# End Source File
# End Group
# Begin Group "codec/wav"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\codec\wav\ourwav.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\wav\ourwav.h
# End Source File
# Begin Source File

SOURCE=.\codec\wav\wav_file.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\wav\wav_file.h
# End Source File
# End Group
# Begin Group "codec/mp3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\codec\mp3\mp3.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\mp3\mp3.h
# End Source File
# Begin Source File

SOURCE=.\codec\mp3\mp3_file.cpp
# End Source File
# Begin Source File

SOURCE=.\codec\mp3\mp3_file.h
# End Source File
# End Group
# End Target
# End Project