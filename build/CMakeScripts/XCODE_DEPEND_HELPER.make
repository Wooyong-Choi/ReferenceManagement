# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Test.Debug:
/Users/sung9/Documents/강의/test/test/build/Debug/Test:
	/bin/rm -f /Users/sung9/Documents/강의/test/test/build/Debug/Test


PostBuild.Test.Release:
/Users/sung9/Documents/강의/test/test/build/Release/Test:
	/bin/rm -f /Users/sung9/Documents/강의/test/test/build/Release/Test


PostBuild.Test.MinSizeRel:
/Users/sung9/Documents/강의/test/test/build/MinSizeRel/Test:
	/bin/rm -f /Users/sung9/Documents/강의/test/test/build/MinSizeRel/Test


PostBuild.Test.RelWithDebInfo:
/Users/sung9/Documents/강의/test/test/build/RelWithDebInfo/Test:
	/bin/rm -f /Users/sung9/Documents/강의/test/test/build/RelWithDebInfo/Test




# For each target create a dummy ruleso the target does not have to exist
