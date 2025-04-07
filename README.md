# Raylib PS1 Game Engine

Uma mini engine modular em C usando [Raylib](https://www.raylib.com/) para criar jogos no estilo **PlayStation 1**, com foco em:

- Simplicidade e performance (estilo C puro)
- Estilo visual retrô (low poly, low res)
- Arquitetura baseada em componentes (ECS simplificado)
- Modularidade por sistemas: movimento, colisão, renderização, triggers, etc.

---

## 🕹️ Como rodar

### Requisitos

- [MSYS2 + MinGW 64-bit](https://www.msys2.org/)
- Raylib instalado via pacman:
  ```bash
  pacman -S mingw-w64-x86_64-raylib
  ```
- CMake 3.10+
- Compilador C (MinGW ou MSVC)

---

### Build no Windows (PowerShell)

```powershell
./build.ps1
```

---

### Build manual (CMake)

```bash
cmake -B build
cmake --build build
```

---

## 📁 Estrutura do Projeto

```
.
├── include/
│   ├── core/         # Entity, EntityManager
│   ├── components/   # Transform, Collider, Renderable
│   ├── systems/      # MovementSystem, RenderSystem, etc.
│   ├── triggers/     # Eventos de jogo (ex: pegar chave)
│   └── game.hpp      # Inicialização e update do jogo
├── src/              # Implementações (.c/.cpp)
├── build.ps1         # Script de build para Windows
├── CMakeLists.txt
└── README.md
```

---

## 🎮 Controles

- `WASD`: mover o jogador
- `E`: interagir com objetos (triggers)

---

## 🧱 Componentes & Sistemas

| Componente | Descrição                      |
| ---------- | ------------------------------ |
| Transform  | Posição, velocidade, movimento |
| Collider   | Tamanho, colisão e triggers    |
| Renderable | Visualização via DrawCube      |

| Sistema         | Função                          |
| --------------- | ------------------------------- |
| MovementSystem  | Leitura de input e movimentação |
| CollisionSystem | Colisões AABB entre entidades   |
| RenderSystem    | Desenha as entidades            |
| TriggerSystem   | Interações baseadas em colisões |
| UIMessageSystem | Mensagens de texto temporárias  |

---

## 🚀 Feito com

- ❤️ [C](<https://en.wikipedia.org/wiki/C_(programming_language)>)
- 🎮 [Raylib](https://www.raylib.com/)
- 🛠️ [CMake](https://cmake.org/)
- 🐧 (opcional) MSYS2 + MinGW

---

## 📌 Observações

- A engine ainda está em desenvolvimento.
- O nome final será escolhido depois :)
- Totalmente open-source para estudos, modificações e nostalgia.

---

## 📸 Preview (em breve)

_(Adicione aqui um gif ou screenshot do gameplay)_

---

## 📜 Licença

Este projeto é distribuído sob a licença MIT.
