#!/bin/bash
# Couleurs pour faire joli
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color
echo "�  Compilation en cours..."
clang++ src/main.cpp -o build/mon_app -lSDL3 -std=c++17
if [ $? -eq 0 ]; then
echo -e "${GREEN}✅  Compilation réussie ! ${NC}"
 echo "Lance avec : ./build/mon_app"
else
 echo -e "${RED}❌  Erreur de compilation${NC}"
 exit 1
fi