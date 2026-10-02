# Tarea Semana 9 – Manipulación de archivos CSV en C++

**Universidad Mariano Gálvez · Facultad de Ingeniería en Sistemas · Curso: Algoritmos**
**Estudiante:** Esteban Mauro Antonio Godoy Barrios · **Carné:** 1690 26 15201 **Sección:** B

## Descripción del problema

Una tienda guarda su catálogo en `datos/productos.csv`. El programa lee los
registros, detecta los que tienen datos inválidos sin detenerse, calcula el valor
total del inventario (solo con registros válidos), permite buscar un producto por
código y genera el reporte `reportes/resumen.txt`. El CSV se abre únicamente en
modo lectura (`ifstream`), por lo que nunca se modifica.

## Estructura del proyecto

```
semana9/
├── main.cpp
├── main.txt            (copia de main.cpp en .txt para Canvas)
├── ANALISIS.md         (entradas/proceso/salidas, pseudocódigo, pruebas)
├── README.md
├── datos/productos.csv
├── reportes/resumen.txt   (generado por el programa)
└── evidencias/            (capturas)
```

## Estructura del CSV

Primera línea de encabezado y luego un producto por línea, con 4 campos
separados por coma:

| Campo | Tipo | Ejemplo |
| --- | --- | --- |
| codigo | texto | P001 |
| nombre | texto | Teclado USB |
| precio | decimal (punto) | 125.50 |
| existencia | entero | 8 |

Las tres últimas filas del archivo incluido tienen errores intencionales
(código vacío, precio `abc`, existencia `-2`).

## Compilación y ejecución

Ejecutar siempre **desde la carpeta `semana9/`**
```bash
g++ main.cpp -o main             
```

El programa pide un código (ejemplo: `P003`), lee el CSV, muestra los
resultados en pantalla y genera `reportes/resumen.txt`.

Para probar una ruta incorrecta (caso 5), renombre temporalmente
`datos/productos.csv` y ejecute el programa; luego devuélvale su nombre.

## Decisiones de validación

- Cada fila se separa con `stringstream` y `getline(..., ',')` en cuatro campos:
  código, nombre, precio y existencia.
- La primera línea (encabezado) se omite comparando el código con `"codigo"`.
- **Código** y **nombre**: no pueden estar vacíos.
- **Precio**: se convierte con `stod` y debe ser mayor que 0.
- **Existencia**: se convierte con `stoi` y debe ser mayor o igual que 0.
- Si `stod` o `stoi` fallan (por ejemplo, precio `abc`), `try/catch` atrapa la
  excepción, la fila se cuenta como inválida y el programa continúa.
- Los registros inválidos no se suman al conteo de válidos ni al valor total.
- La búsqueda compara el código exactamente como se escribe (distingue
  mayúsculas de minúsculas). Si el código existe pero su fila es inválida, el
  programa lo indica.
- Limitaciones: no se soportan comas dentro de un campo, solo se leen los
  primeros 4 campos de cada fila, y `stod`/`stoi` aceptan valores como `12abc`
  o `3.5` (toman la parte numérica inicial).
- Si el CSV no se puede abrir, el programa muestra el error y termina con
  código 1. Si no existe la carpeta `reportes/`, muestra error al crear el reporte.

## Uso de IA


Consulté a una herramienta de IA (Claude) para generar una primera versión de
`main.cpp`, este README y el documento de análisis. Revisé el código línea por
línea, lo compilé y lo ejecuté con los casos de prueba. Las partes que modifiqué
o comprobé por mi cuenta fueron: 