#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

struct ResultadoOtimizacao {
    int armazensNecessarios;
    int caminhoesNecessarios;
};

ResultadoOtimizacao calcularRecursos(std::vector<double>& volumes, double capacidadeArmazem, double capacidadeCaminhao) {
    std::sort(volumes.rbegin(), volumes.rend());

    std::vector<double> espacoDisponivelArmazens;
    
    if (capacidadeArmazem > 0) {
        for (double volumeContainer : volumes) {
            bool alocado = false;
        
            for (size_t i = 0; i < espacoDisponivelArmazens.size(); ++i) {
                if (volumeContainer <= espacoDisponivelArmazens[i]) {
                    espacoDisponivelArmazens[i] -= volumeContainer;
                    alocado = true;
                    break;
                }
            }

        
            if (!alocado) {
                espacoDisponivelArmazens.push_back(capacidadeArmazem - volumeContainer);
            }
        }
    }


    double volumeTotal = std::accumulate(volumes.begin(), volumes.end(), 0.0);
    
    int caminhoesNecessarios = 0;
    if (capacidadeCaminhao > 0) {
        caminhoesNecessarios = static_cast<int>(std::ceil(volumeTotal / capacidadeCaminhao));
    }
    
    ResultadoOtimizacao resultado;
    resultado.armazensNecessarios = espacoDisponivelArmazens.size();
    resultado.caminhoesNecessarios = caminhoesNecessarios;

    return resultado;
}

int main() {
    std::vector<double> volumesDosContainers = {10, 8, 8, 5, 5, 5, 4, 4, 2, 2};
    double capacidadeArmazemX = 20.0;
    double capacidadeCaminhaoY = 35.0;

    ResultadoOtimizacao resultado = calcularRecursos(volumesDosContainers, capacidadeArmazemX, capacidadeCaminhaoY);

    std::cout << "--- Otimização de Logística ---" << std::endl;
    std::cout << "Número mínimo de armazéns necessários: " << resultado.armazensNecessarios << std::endl;
    std::cout << "Número mínimo de caminhões necessários: " << resultado.caminhoesNecessarios << std::endl;

    return 0;
}
