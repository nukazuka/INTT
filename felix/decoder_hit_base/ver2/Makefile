PACKAGE = InttHitBaseDecoder

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --glibs)

CXXFLAGS = -I.  $(ROOTFLAGS) -I$(ONLINE_MAIN)/include -I$(OFFLINE_MAIN)/include
RCFLAGS = -I.  -I$(ONLINE_MAIN)/include -I$(OFFLINE_MAIN)/include

LDFLAGS = -Wl,--no-as-needed  $(ROOTLIBS) -fPIC -L$(ONLINE_MAIN)/lib -L$(OFFLINE_MAIN)/lib -lEvent -lNoRootEvent -lmessage 

HDRFILES = InttEvent.h ConvertInttData.h InttDecode.h
LINKFILE = LinkDef.h

ADDITIONAL_SOURCES = InttEvent.cc ConvertInttData.cc InttDecode.cc
ADDITIONAL_LIBS = 

SO = lib$(PACKAGE).so

#$(SO) : $(PACKAGE).cc $(PACKAGE)_dict.C $(ADDITIONAL_SOURCES) $(LINKFILE)
#	$(CXX) $(CXXFLAGS) -o $@ -shared  $<  $(ADDITIONAL_SOURCES) $(PACKAGE)_dict.C $(LDFLAGS)  $(ADDITIONAL_LIBS)

$(SO) : InttEvent_dict.C $(ADDITIONAL_SOURCES) $(LINKFILE)
	$(CXX) $(CXXFLAGS) -o $@ -shared  $<  $(ADDITIONAL_SOURCES) $(LDFLAGS) $(ADDITIONAL_LIBS)

InttEvent_dict.C : $(HDRFILES) $(LINKFILE)
	rootcling -f $@  -c $(RCFLAGS) $^

##rootcint -f $@  -c $(RCFLAGS) $^

.PHONY: clean

clean: 
	rm -f $(SO) $(PACKAGE)_dict.C $(PACKAGE)_dict.h $(PACKAGE)_dict_rdict.pcm

