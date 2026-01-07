import os
import subprocess
import sys
import platform

# ==============================
# CONFIG GÉNÉRALE
# ==============================

COMPILER = "clang++"   # ou "g++"

STD = "-std=c++17"
WARNINGS = ["-Wall", "-Wextra"]

LIBS = ["-lSDL3", "-lSDL3_image"]

EXCLUDE_DIRS = {
    ".git", "build", "bin", "_pycache_"
}

BUILD_DIR = "build"

SYSTEM = platform.system()
EXE = "main.exe" if SYSTEM == "Windows" else "main"
OUTPUT = os.path.join(BUILD_DIR, EXE)

# ==============================
# MODE DE BUILD
# ==============================

mode = "release"
if len(sys.argv) > 1:
    mode = sys.argv[1]

if mode == "debug":
    FLAGS = ["-g", "-O0"]
elif mode == "release":
    FLAGS = ["-O2"]
elif mode == "clean":
    print("🧹 Nettoyage du build...")
    if os.path.exists(BUILD_DIR):
        for f in os.listdir(BUILD_DIR):
            os.remove(os.path.join(BUILD_DIR, f))
    print("✅ Build nettoyé")
    sys.exit(0)
else:
    print("❌ Mode inconnu : debug | release | clean")
    sys.exit(1)

# ==============================
# RECHERCHE AUTOMATIQUE
# ==============================

cpp_files = []
include_dirs = set()

for root, dirs, files in os.walk("."):
    dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]

    include_dirs.add(root)

    for file in files:
        if file.endswith(".cpp"):
            cpp_files.append(os.path.join(root, file))

if not cpp_files:
    print("❌ Aucun fichier .cpp trouvé")
    sys.exit(1)

# ==============================
# CONSTRUCTION COMMANDE
# ==============================

cmd = []
cmd.append(COMPILER)
cmd.append(STD)
cmd.extend(WARNINGS)
cmd.extend(FLAGS)
cmd.extend(cpp_files)

for inc in sorted(include_dirs):
    cmd.append(f"-I{inc}")

cmd.append("-o")
cmd.append(OUTPUT)
cmd.extend(LIBS)

# ==============================
# BUILD
# ==============================

os.makedirs(BUILD_DIR, exist_ok=True)

print("\n=== COMMANDE DE COMPILATION ===\n")
print(" ".join(cmd))
print("\n==============================\n")

print("🚀 Compilation en cours...\n")
result = subprocess.run(cmd)

if result.returncode != 0:
    print("\n❌ ERREUR DE COMPILATION")
    sys.exit(1)

print("\n✅ COMPILATION RÉUSSIE")

# ==============================
# LANCEMENT
# ==============================

print("\n▶ Lancement du programme...\n")
subprocess.run([OUTPUT])