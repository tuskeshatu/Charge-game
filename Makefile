# TARGET: Target executable name
TARGET = charge.exe

# CXX: The C++ compiler you want to use
CXX = g++
# CXXFLAGS: Compiler flags
CXXFLAGS = -g -Wall -Wpedantic
# For optimalization comment it out
#CXXFLAGS += -O3
# For memtrace (not working)
#CXXFLAGS += -DMEMTRACE
# LDFLAGS: Linker flags
LDFLAGS = -LC:\path\to\libsfml-files.a  -lsfml-graphics -lsfml-window -lsfml-system
#INCFLAGS: Include flags
INCFLAGS = -I$(INCDIR)

# SRCDIR: Source directory with the .cpp files
SRCDIR   = src
# OBJDIR: For .o and .d files
OBJDIR   = obj
# BINDIR: Directory for the executable binary
BINDIR   = bin
# INCDIR: For .h header files
INCDIR   = include
# UMLDIR: For .puml and .png UML files
UMLDIR	 = uml

# Get every .cpp file in SRCDIR
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Get the header files for uml commands
HEADERS = $(filter-out $(INCDIR)/memtrace.h $(INCDIR)/gtest_lite.h, $(wildcard $(INCDIR)/*.h))
# Create header flags for hpp2plantuml
HEADER_FLAGS = $(patsubst $(INCDIR)/%.h,-i $(INCDIR)/%.h,$(HEADERS))

# For object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
# Dependency files
DEPS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)

# The target is dependent on all object files
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

# Every object is dependent on the cpp file with the same name
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCFLAGS) -MMD $< 

# Get every dependency rule
include $(DEPS)

$(DEPS): ;

# Rule to make puml diagram
.PHONY: uml
uml:
	@if not exist $(UMLDIR) mkdir $(UMLDIR)
	cd $(UMLDIR)
	hpp2plantuml $(HEADER_FLAGS) -o $(UMLDIR)/ChargeUML.puml
	java -jar C:/path/to/plantuml.jar -tpng -darkmode $(UMLDIR)/ChargeUML.puml

# ONLY WORKS ON WINDOWS!!!
# Clean rule
.PHONY: clean
clean:
	del obj\*.* bin\*.exe /Q