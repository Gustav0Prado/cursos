JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

# This uses the line continuation character (\) for readability
# You can list these all on a single line, separated by a space instead.
# If your version of make can't handle the leading tabs on each
# line, just remove them (these are also just added for readability).
CLASSES = \
        Disciplina.java \
        ListaDisc2011.java \
        ListaDisc2019.java \
        ListaDisc.java \
        Main.java 

all: classes
	jar cfe T1.jar Main ./*.class

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class ./T1.jar