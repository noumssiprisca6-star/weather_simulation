# ce script sert à :
# trouver automatiquement tous les fichiers.cpp
# les compiler avec clang++ ou g++
# gerer plusieurs modes (debug , release , clean )
#lancer le programme compile 


# LES MODULES 
# os permet de parcourir les dossiers , creer des repertoires 
# subprocess execute des commandes systeme(clang++ , g++)
# sys lit les arguments ( debug , release , clean)
# platform  detecte le systeme (windows /linus)


import os
import subprocess
import sys
import platform


# CONFIGuration  GÉNÉRALE
# -wall  -wextra affiche beaucoup d'avertissement utiles
#-std=c++17 est un standard C++17 c'est une bonne pratique 
#les dossiers ignores pendant la recherche des fichiers .cpp sont des Exclude  
#c'est important pour eviter les erreurs et compiler inutilement



COMPILER = "clang++"   # ou "g++"

STD = "-std=c++17"
WARNINGS = ["-Wall", "-Wextra"]

LIBS = ["-lSDL3", "-lSDL3_image"]

EXCLUDE_DIRS = {
    ".git", "build", "bin", "_pycache_"
}
 
 # le doosier ou sera placer l'executable final

BUILD_DIR = "build"

SYSTEM = platform.system()
EXE = "main.exe" if SYSTEM == "Windows" else "main"
OUTPUT = os.path.join(BUILD_DIR, EXE)
# detection automatique du systeme  window (main.exe)
# linux/ Mac ( main)


# MODE DE BUILD


mode = "release"
# par defaut release 
if len(sys.argv) > 1:
    mode = sys.argv[1]
 


if mode == "debug":
    #-g mode de debogage  
    # -00 aucune optimisation 
    FLAGS = ["-g", "-O0"]
elif mode == "release":
    # mode release 
    FLAGS = ["-O2"]
    # flags permets l'optimisation du code 
    # programme plus rapide 

    # MODE CLEAN

elif mode == "clean":
#suprime tous les fichiers dans build 
#puis quitte le script
    print("🧹 Nettoyage du build...")
    if os.path.exists(BUILD_DIR):
        for f in os.listdir(BUILD_DIR):
            os.remove(os.path.join(BUILD_DIR, f))
    print("✅ Build nettoyé")
    sys.exit(0)
else:
    print("❌ Mode inconnu : debug | release | clean")
    sys.exit(1)


# RECHERCHE AUTOMATIQUE DES FICHIERS . CPP


cpp_files = []
include_dirs = set()
# cpp files liste de tous les fichiers .cpp
#include dossiers a ajouter avec -I
for root, dirs, files in os.walk("."): # parcours tout le projet 
    dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]  # ignore les dossiers inutiles (build, git )

    include_dirs.add(root)
# chaque dossiers devient un -| pour les .h 
    for file in files:
        if file.endswith(".cpp"):
            cpp_files.append(os.path.join(root, file))

if not cpp_files:
    print("❌ Aucun fichier .cpp trouvé")
    sys.exit(1)
 # securite si aucun fichier .cpp ne fut trouve  on arrete tous 

# CONSTRUCTION  DE LA COMMANDE DE COMPILATION

cmd = [] # liste qui contiendra la commande finale 
cmd.append(COMPILER)
cmd.append(STD)
cmd.extend(WARNINGS)
cmd.extend(FLAGS)
cmd.extend(cpp_files)

for inc in sorted(include_dirs):
    cmd.append(f"-I{inc}") # ajoute automatiquement tous les dossiers d'include 
# definit le fichier de sortie 
# les bibliotheques SDL
cmd.append("-o")
cmd.append(OUTPUT)
cmd.extend(LIBS)

# COMPILATION


os.makedirs(BUILD_DIR, exist_ok=True)
# on cree un  fichier build s'il n'existe pas 
print("\n=== COMMANDE DE COMPILATION ===\n") # ajoute la commande exacte  utile pour le debogage 
print(" ".join(cmd))
print("\n==============================\n")

print("🚀 Compilation en cours...\n")
result = subprocess.run(cmd) # execute la compilation 

if result.returncode != 0:
    print("\n❌ ERREUR DE COMPILATION") # arret immediat si erreur 
    sys.exit(1)

print("\n✅ COMPILATION RÉUSSIE") # lancement si tout va bien 


# LANCEMENT DU PROGRAMME

#lance automatiquement ton programme compile 
print("\n▶ Lancement du programme...\n")
subprocess.run([OUTPUT])

#c'est un mini CMake fait maison en python 