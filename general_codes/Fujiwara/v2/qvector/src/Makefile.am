AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = \
    libinttqvector.la

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -isystem`root-config --incdir`

#ROOTDICTS = \
  InttEvent_Dict.cc \
  InttOfflineEvent_Dict.cc \
  InttOfflineCluster_Dict.cc

#pcmdir = $(libdir)

#nobase_dist_pcm_DATA = \
  InttEvent_Dict_rdict.pcm \
  InttOfflineEvent_Dict_rdict.pcm \
  InttOfflineCluster_Dict_rdict.pcm

pkginclude_HEADERS = \
  InttQvector.h

libinttqvector_la_SOURCES = \
  InttQvector.cc

libinttqvector_la_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -lcalo_io \
  -lfun4all \
  -lg4detectors_io \
  -lphg4hit \
  -lg4dst \
  -lg4eval 


################################################
# linking tests

BUILT_SOURCES = testexternals.cc

noinst_PROGRAMS = \
  testexternals

testexternals_SOURCES = testexternals.cc
testexternals_LDADD = libinttqvector.la

testexternals.cc:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

#%_Dict.cc: %.h %LinkDef.h
#	rootcling -f $@ -c $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

#just to get the dependency
#%_Dict_rdict.pcm: %_Dict.cc ;


clean-local:
	rm -f *Dict* $(BUILT_SOURCES) *.pcm
