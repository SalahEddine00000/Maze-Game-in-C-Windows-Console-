# 🌀 Maze Game in C (Windows Console)

This project is a simple **maze exploration game** written in C.  
It generates random mazes using the **Aldous-Broder algorithm**, and the player can move around with **keyboard controls**.  
The maze is rendered in the Windows console, and the program tracks **FPS, delta time, and player levels**.

---

## 🎮 Features

- Procedural maze generation (Aldous-Broder algorithm).
- Player movement with **WASD** keys or **Arrow keys**.
- Random **collectibles** (`*`) that increase the player's level.
- Console **color changes** each time a level is completed.
- Delta time & FPS counter for smoother performance tracking.
- Exit game with **Q**.

---

## 🕹️ Controls

| Key       | Action     |
| --------- | ---------- |
| **W / ↑** | Move Up    |
| **S / ↓** | Move Down  |
| **A / ←** | Move Left  |
| **D / →** | Move Right |
| **Q**     | Quit Game  |

---

## 📦 Requirements

- **Windows OS** (uses `<windows.h>` and `conio.h`).
- **GCC (MinGW)** or MSVC compiler.

---

## ⚙️ How to Compile & Run

### Using MinGW (GCC for Windows):

```bash
gcc main.c -o maze.exe
maze.exe
```

### Using MSVC (Visual Studio Developer Command Prompt):

```bash
cl main.c
main.exe
```

---

## 📸 Example Gameplay

```
LV : 1
#########################################
#O     #     #     #     #     #     #  #
# ### ##### ### ### ### ### ### ##### ##
#   #     #     #     #     #     #    #
### ### ### ### ### ### ### ### ##### ##
#   #     #     #     #     #     #    #
#########################################

Delta Time: 0.016 s
FPS: 60.0
```

---

## 📚 Project Structure

- **`init_Maze()`** – Initializes maze with walls.
- **`aldous_broder()`** – Generates maze randomly.
- **`print_Maze()`** – Renders maze in console.
- **`read_dir()`** – Handles player input (WASD + arrows).
- **`move_player()`** – Updates player position & levels.
- **`load_level()`** – Loads a new level when completed.
- **`main()`** – Game loop (handles delta time, FPS, rendering).

---

## 🚀 Future Improvements

- Add enemies or moving traps.
- Implement save/load system.
- Add different maze generation algorithms (DFS, Prim’s, Kruskal’s).
- Cross-platform support (Linux/macOS).

---

## 👨‍💻 Author

Made with salah eddine in C for fun & practice.  
Feel free to fork and improve it!
