#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Variables globales
std::string linea, codigo, nombre, precioTexto, existenciaTexto;
const char* rutaCsv = "./data/productos.csv";
const char* rutaReporte = "./reports/resumen.txt";
int registrosValidos = 0;
int registrosInvalidos = 0;
double valorTotal = 0;
std::string resultadoBusqueda = "El codigo no existe en el archivo.";

// Lee el CSV, valida cada fila, cuenta, suma el valor y busca el codigo
bool LeerData(std::string buscar){
    std::ifstream leerData(rutaCsv);

    // Revisar que el archivo se abrio bien
    if(!leerData.is_open()){
        std::cout << "Ha ocurrido un error al abrir el archivo: " << rutaCsv << std::endl;
        return false;
    }

    while(getline(leerData, linea)){
        // Separar los 4 campos por coma
        std::stringstream ss(linea);
        getline(ss, codigo, ',');
        getline(ss, nombre, ',');
        getline(ss, precioTexto, ',');
        getline(ss, existenciaTexto, ',');

        // Omitir el encabezado
        if(codigo != "codigo"){
            try{

                double precio = std::stod(precioTexto);
                int existencia = std::stoi(existenciaTexto);

                if(codigo != "" && nombre != "" && precio > 0 && existencia >= 0){
                    registrosValidos++;
                    valorTotal = valorTotal + (precio * existencia);

                    // Si es el codigo que busca el usuario, guardar los datos
                    if(codigo == buscar){
                        std::stringstream r;
                        r << std::fixed;
                        r.precision(2);
                        r << "Encontrado: " << codigo << " | " << nombre << " | Q" << precio << " | " << existencia;
                        resultadoBusqueda = r.str();
                    }
                }
                else{
                    registrosInvalidos++;
                    std::cout << "Registro invalido: " << linea << std::endl;
                    if(codigo == buscar){
                        resultadoBusqueda = "El codigo existe pero su registro es invalido.";
                    }
                }
            }
            catch(const std::exception& e){
                registrosInvalidos++;
                std::cout << "Registro invalido: " << linea << std::endl;
                if(codigo == buscar){
                    resultadoBusqueda = "El codigo existe pero su registro es invalido.";
                }
            }
        }
    }

    leerData.close();
    return true;
}

// Escribe el resumen en reportes/resumen.txt
void GenerarReporte(std::string buscar){
    std::ofstream reporte(rutaReporte);

    if(!reporte.is_open()){
        std::cout << "Ha ocurrido un error al crear el reporte: " << rutaReporte << std::endl;
        return;
    }

    reporte << std::fixed;
    reporte.precision(2);
    reporte << "RESUMEN DE INVENTARIO" << std::endl;
    reporte << "Total de registros validos: " << registrosValidos << std::endl;
    reporte << "Total de registros invalidos: " << registrosInvalidos << std::endl;
    reporte << "Valor total del inventario: Q" << valorTotal << std::endl;
    reporte << "Busqueda (" << buscar << "): " << resultadoBusqueda << std::endl;

    reporte.close();
    std::cout << "Reporte generado en " << rutaReporte << std::endl;
}

int main(){
    std::string buscar;
    std::cout << "Ingrese el codigo a buscar: ";
    getline(std::cin, buscar);

    if(!LeerData(buscar)){
        return 1;
    }

    if(buscar == ""){
        resultadoBusqueda = "No se ingreso ningun codigo.";
    }

    std::cout << std::fixed;
    std::cout.precision(2);
    std::cout << std::endl;
    std::cout << "Registros validos: " << registrosValidos << std::endl;
    std::cout << "Registros invalidos: " << registrosInvalidos << std::endl;
    std::cout << "Valor total del inventario: Q" << valorTotal << std::endl;
    std::cout << resultadoBusqueda << std::endl;
    std::cout << std::endl;

    GenerarReporte(buscar);

    return 0;
}