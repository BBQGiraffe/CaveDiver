import glob
import os
headers = glob.glob("*.h")
sources = glob.glob("*.c")
buildScript = "gcc -Wall -g -Wno-missing-braces"

for h in headers:
    buildScript = buildScript + " " + h + " "
for c in sources:
    buildScript = buildScript + " " + c + " "

buildScript = buildScript + " -o game -lSDL2 -lSDL2_ttf -ffast-math -O2 -lm"

os.system(buildScript)