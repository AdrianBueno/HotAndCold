# TileMap System Documentation

## Objetivo del sistema
El sistema `TileMap` está diseñado para gestionar de manera eficiente y escalable mapas 2D basados en tiles en un juego con vista top-down.  
El diseño sigue el **patrón Flyweight**, permitiendo gestionar mapas grandes con **múltiples capas lógicas** y **scroll en ambas direcciones**, optimizando el uso de memoria.

---

## Arquitectura actual de `TileMap`

### Capas soportadas (`LayerType`)
El mapa está compuesto por una estructura multicapa gestionada mediante un **enum interno `LayerType`**, que define las capas disponibles y su orden de renderización.

```cpp
enum LayerType {
    LAYER_GROUND = 0,     // Suelo base
    LAYER_COLLISION,      // Elementos sólidos (muros, rocas)
    LAYER_DECORATION,     // Decoración visual no sólida
    LAYER_OVERLAY,        // Efectos especiales (nubes, clima)
    LAYER_SYSTEM,         // Datos ocultos (triggers, zonas)
    LAYER_COUNT           // Contador automático de capas (siempre al final)
};



Patrón Flyweight:
Todos los Tile son instancias compartidas (Tile*), almacenadas en capas como punteros.
Las celdas no contienen estado dinámico propio (como vida, daño), solo referencia al tipo de tile.
Si se requiere estado dinámico por celda, este debe almacenarse en una estructura aparte (CellData) gestionada por el sistema de entidades o el mapa avanzado.

Seguridad y legibilidad:
Se utiliza enum LayerType en vez de números mágicos, evitando errores y mejorando la claridad del código.

Eficiencia en memoria y procesamiento:
Solo se renderiza el área visible dentro de un viewport/cámara.
Cada capa se gestiona de manera independiente, permitiendo renderizar, actualizar o modificar solo las capas necesarias.