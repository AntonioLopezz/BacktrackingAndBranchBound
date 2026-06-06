# ==========================================
# COMPILADOR Y BANDERAS (FLAGS)
# ==========================================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# ==========================================
# REGLA POR DEFECTO
# ==========================================
all: tests_unitarios_BT tiempos_BT tests_unitarios_AR tiempos_AR

# ==========================================
# BACKTRACKING
# ==========================================

# 1. Tests Unitarios BT
tests_unitarios_BT: test_unitarios_BT.cpp E_BT.cpp E_BT.h
	$(CXX) $(CXXFLAGS) test_unitarios_BT.cpp E_BT.cpp -o tests_unitarios_BT.exe

# 2. Medición de Tiempos BT
tiempos_BT: tiempos_BT.cpp E_BT.cpp E_BT.h
	$(CXX) $(CXXFLAGS) tiempos_BT.cpp E_BT.cpp -o tiempos_BT.exe

# ==========================================
# ALGORITMO VORAZ (AR)
# ==========================================

# 4. Tests Unitarios AR
tests_unitarios_AR: test_unitarios_AR.cpp E_AR.cpp E_AR.h
	$(CXX) $(CXXFLAGS) test_unitarios_AR.cpp E_AR.cpp -o tests_unitarios_AR.exe

# 5. Medición de Tiempos AR
tiempos_AR: tiempos_AR.cpp E_AR.cpp E_AR.h
	$(CXX) $(CXXFLAGS) tiempos_AR.cpp E_AR.cpp -o tiempos_AR.exe

# ==========================================
# LIMPIEZA
# ==========================================
clean:
	rm -f *.o *.exe