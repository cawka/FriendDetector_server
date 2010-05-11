
bin_PROGRAMS=server

server_SOURCES=Recognizer.cpp Recognizer.h \
			   RecognizerI.cpp RecognizerI.h \
			   iFaceIdentifier.h \
			   EigenFace.h EigenFace.cpp \
			   main.cpp


server_LDFLAGS=$(LDFLAGS) \
			   $(ICE_LIB) $(ICE_EXTRA) -lIce -lIceUtil \
			   $(OPENCV_LIB) -lcxcore -lcv -lcvaux -lhighgui \
			   -llog4cxx \
			   -lboost_program_options \
			   -lsqlite3 -lsqlitewrapped
	
server_CPPFLAGS=$(ICE_INCLUDE) $(OPENCV_INCLUDE) -I. 
#$(CPPFLAGS)
	
