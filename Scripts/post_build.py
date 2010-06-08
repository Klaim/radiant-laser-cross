
# WIP
import sys
import shutil
import os
import os.path

BUILDS_ROOT_DIRECTORY = "../Build" # root of the directory where all the builds are

os.chdir( os.path.dirname( sys.argv[0] ) )

# get the provided Build mode - HAVE TO BE THE FIRST PARAMETER

if len(sys.argv) != 2 or len(sys.argv[1]) == 0 :
	raise "!- Invalid command line parameter : You HAVE TO provide a Build configuration name!"
	
CONFIG_MODE = sys.argv[1]
CONFIG_MODE= CONFIG_MODE.strip()

print( "Build Mode : \"" +CONFIG_MODE+"\"" )


BUILD_DIR = BUILDS_ROOT_DIRECTORY + CONFIG_MODE;
RESOURCE_FOLDER = "../Resources/"

shutil.copytree( src=RESOURCE_FOLDER, dst=BUILD_DIR, ignore=".svn" )

